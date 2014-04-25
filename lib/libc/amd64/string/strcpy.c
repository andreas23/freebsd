/*
 * Copyright 2011 George V. Neville-Neil. All rights reserved.
 *
 * The compilation of software known as FreeBSD is distributed under the
 * following terms:
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <softbound.h>

NO_SB_CC char *__stpcpy(char * __restrict, const char * __restrict);

NO_SB_CC char *
__softbound_strcpy(char * __restrict to, const char * __restrict from)
{
	__stpcpy(to, from);
	return(to);
}

NO_SB_IB char *
strcpy(char * __restrict to, const char * __restrict from)
{
  void*  to_base = __softboundcets_load_base_shadow_stack(1);
  void*  to_bound = __softboundcets_load_bound_shadow_stack(1);
  size_t to_key = __softboundcets_load_key_shadow_stack(1);
  void*  to_lock = __softboundcets_load_lock_shadow_stack(1);

  void*  from_base = __softboundcets_load_base_shadow_stack(2);
  void*  from_bound = __softboundcets_load_bound_shadow_stack(2);
  size_t from_key = __softboundcets_load_key_shadow_stack(2);
  void*  from_lock = __softboundcets_load_lock_shadow_stack(2);

  __softboundcets_spatial_load_dereference_check(from_base, from_bound, (void*)from, sizeof(*from));
  __softboundcets_temporal_load_dereference_check(from_lock, from_key, from_base, from_bound);
  
  size_t size = __softbound_strlen(from) + 1; // trailing zero is the + 1

  __softboundcets_spatial_load_dereference_check(from_base, from_bound, (void*)(from + size), sizeof(*from));

  __softboundcets_spatial_store_dereference_check(to_base, to_bound, (void*)to, size);
  __softboundcets_temporal_store_dereference_check(to_lock, to_key, to_base, to_bound);

  __stpcpy(to, from);
  __softboundcets_propagate_metadata_shadow_stack_from(1, 0);
  return(to);
}
