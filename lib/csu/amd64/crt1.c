/* LINTLIBRARY */
/*-
 * Copyright 1996-1998 John D. Polstra.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#ifndef lint
#ifndef __GNUC__
#error "GCC is needed to compile this file"
#endif
#endif /* lint */

#include <stdlib.h>
#include <softbound.h>

#include "libc_private.h"
#include "crtbrand.c"
#include "ignore_init.c"

typedef void (*fptr)(void);

#ifdef GCRT
extern void _mcleanup(void);
extern void monstartup(void *, void *);
extern int eprol;
extern int etext;
#endif

void _start(char **, void (*)(void));

/* The entry function. */
NO_SB_CC void
_start(char **ap, void (*cleanup)(void))
{
	int argc;
	char **argv;
	char **env;

	argc = *(long *)(void *)ap;
	argv = ap + 1;
	env = ap + 2 + argc;
	handle_argv(argc, argv, env);

  char** new_argv = argv;
  int i;
  char* temp_ptr;
  int return_value;
  size_t argv_key;
  void* argv_loc;

  int* temp = __malloc(1);
  __softboundcets_allocation_secondary_trie_allocate_range(0, (size_t)temp);
  __softboundcets_stack_memory_allocation(&argv_loc, &argv_key);

  for(i = 0; i < argc; i++) {
    __softboundcets_metadata_store(&new_argv[i],
                                   new_argv[i],
                                   new_argv[i] + strlen(new_argv[i]) + 1,
                                   argv_key, argv_loc);
  }

  /* Santosh: Real Nasty hack because C programmers assume argv[argc]
   * to be NULL. Also this NUll is a pointer, doing + 1 will make the
   * size_of_type to fail
   */
  temp_ptr = ((char*) &new_argv[argc]) + 8;

  /* &new_argv[0], temp_ptr, argv_key, argv_loc * the metadata */

  __softboundcets_allocate_shadow_stack_space(2);

  __softboundcets_store_base_shadow_stack(&new_argv[0], 1);
  __softboundcets_store_bound_shadow_stack(temp_ptr, 1);
  __softboundcets_store_key_shadow_stack(argv_key, 1);
  __softboundcets_store_lock_shadow_stack(argv_loc, 1);


	if (&_DYNAMIC != NULL)
		atexit(cleanup);
	else
		_init_tls();

#ifdef GCRT
	atexit(_mcleanup);
	monstartup(&eprol, &etext);
__asm__("eprol:");
#endif

	handle_static_init(argc, argv, env);

        return_value = main(argc, new_argv, env);
  __softboundcets_deallocate_shadow_stack_space();

  __softboundcets_stack_memory_deallocation(argv_key);

  exit(return_value);
}
