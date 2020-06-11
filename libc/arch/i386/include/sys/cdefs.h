#ifndef __SYS_CDEFS_H__
#define __SYS_CDEFS_H__

# if (defined __cplusplus						\
      || (defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L))
#  define __inline	inline
# else
#  define __inline		/* No inline functions.  */
# endif

#ifdef	__cplusplus
# define __BEGIN_DECLS	extern "C" {
# define __END_DECLS	}
#else
# define __BEGIN_DECLS
# define __END_DECLS
#endif

#endif /* __SYS_CDEFS_H__ */