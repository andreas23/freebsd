/******************************************************************************/
#ifdef JEMALLOC_H_TYPES

#endif /* JEMALLOC_H_TYPES */
/******************************************************************************/
#ifdef JEMALLOC_H_STRUCTS

#endif /* JEMALLOC_H_STRUCTS */
/******************************************************************************/
#ifdef JEMALLOC_H_EXTERNS

NO_SB_CC void	*base_alloc(size_t size);
NO_SB_CC void	*base_calloc(size_t number, size_t size);
NO_SB_CC extent_node_t *base_node_alloc(void);
NO_SB_CC void	base_node_dealloc(extent_node_t *node);
NO_SB_CC bool	base_boot(void);
NO_SB_CC void	base_prefork(void);
NO_SB_CC void	base_postfork_parent(void);
NO_SB_CC void	base_postfork_child(void);

#endif /* JEMALLOC_H_EXTERNS */
/******************************************************************************/
#ifdef JEMALLOC_H_INLINES

#endif /* JEMALLOC_H_INLINES */
/******************************************************************************/
