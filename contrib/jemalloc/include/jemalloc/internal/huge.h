/******************************************************************************/
#ifdef JEMALLOC_H_TYPES

#endif /* JEMALLOC_H_TYPES */
/******************************************************************************/
#ifdef JEMALLOC_H_STRUCTS

#endif /* JEMALLOC_H_STRUCTS */
/******************************************************************************/
#ifdef JEMALLOC_H_EXTERNS

/* Huge allocation statistics. */
extern uint64_t		huge_nmalloc;
extern uint64_t		huge_ndalloc;
extern size_t		huge_allocated;

/* Protects chunk-related data structures. */
extern malloc_mutex_t	huge_mtx;

NO_SB_CC void	*huge_malloc(size_t size, bool zero);
NO_SB_CC void	*huge_palloc(size_t size, size_t alignment, bool zero);
NO_SB_CC void	*huge_ralloc_no_move(void *ptr, size_t oldsize, size_t size,
    size_t extra);
NO_SB_CC void	*huge_ralloc(void *ptr, size_t oldsize, size_t size, size_t extra,
    size_t alignment, bool zero, bool try_tcache_dalloc);
NO_SB_CC void	huge_dalloc(void *ptr, bool unmap);
NO_SB_CC size_t	huge_salloc(const void *ptr);
NO_SB_CC prof_ctx_t	*huge_prof_ctx_get(const void *ptr);
NO_SB_CC void	huge_prof_ctx_set(const void *ptr, prof_ctx_t *ctx);
NO_SB_CC bool	huge_boot(void);
NO_SB_CC void	huge_prefork(void);
NO_SB_CC void	huge_postfork_parent(void);
NO_SB_CC void	huge_postfork_child(void);

#endif /* JEMALLOC_H_EXTERNS */
/******************************************************************************/
#ifdef JEMALLOC_H_INLINES

#endif /* JEMALLOC_H_INLINES */
/******************************************************************************/
