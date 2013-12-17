/******************************************************************************/
#ifdef JEMALLOC_H_TYPES

typedef enum {
	dss_prec_disabled  = 0,
	dss_prec_primary   = 1,
	dss_prec_secondary = 2,

	dss_prec_limit     = 3
} dss_prec_t ;
#define	DSS_PREC_DEFAULT	dss_prec_secondary
#define	DSS_DEFAULT		"secondary"

#endif /* JEMALLOC_H_TYPES */
/******************************************************************************/
#ifdef JEMALLOC_H_STRUCTS

extern const char *dss_prec_names[];

#endif /* JEMALLOC_H_STRUCTS */
/******************************************************************************/
#ifdef JEMALLOC_H_EXTERNS

NO_SB_CC dss_prec_t	chunk_dss_prec_get(void);
NO_SB_CC bool	chunk_dss_prec_set(dss_prec_t dss_prec);
NO_SB_CC void	*chunk_alloc_dss(size_t size, size_t alignment, bool *zero);
NO_SB_CC bool	chunk_in_dss(void *chunk);
NO_SB_CC bool	chunk_dss_boot(void);
NO_SB_CC void	chunk_dss_prefork(void);
NO_SB_CC void	chunk_dss_postfork_parent(void);
NO_SB_CC void	chunk_dss_postfork_child(void);

#endif /* JEMALLOC_H_EXTERNS */
/******************************************************************************/
#ifdef JEMALLOC_H_INLINES

#endif /* JEMALLOC_H_INLINES */
/******************************************************************************/
