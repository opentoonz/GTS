#ifndef __ptbl_math_h__
#define __ptbl_math_h__

/* WindowsではM_PIが見つからない */
#if defined _WIN32
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
#endif

#endif /* !__ptbl_math_h__ */
