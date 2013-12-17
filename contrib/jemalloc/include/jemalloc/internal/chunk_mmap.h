/******************************************************************************/
#ifdef JEMALLOC_H_TYPES

#endif /* JEMALLOC_H_TYPES */
/******************************************************************************/
#ifdef JEMALLOC_H_STRUCTS

#endif /* JEMALLOC_H_STRUCTS */
/******************************************************************************/
#ifdef JEMALLOC_H_EXTERNS

NO_SB_CC bool	pages_purge(void *addr, size_t length);

NO_SB_CC void	*chunk_alloc_mmap(size_t size, size_t alignment, bool *zero);
NO_SB_CC bool	chunk_dealloc_mmap(void *chunk, size_t size);

#endif /* JEMALLOC_H_EXTERNS */
/******************************************************************************/
#ifdef JEMALLOC_H_INLINES

#endif /* JEMALLOC_H_INLINES */
/******************************************************************************/
