#ifndef __ptbl_vsnprintf_h__
#define __ptbl_vsnprintf_h__

/* Windowsでもvsnprintf()として使うためのdefine */
/* Windowsではvsnprintf()の頭にアンダーバーが付く!!! */
#if defined _WIN32
# define vsnprintf(buf,len,fmt,ap) _vsnprintf(buf,len,fmt,ap)
#endif

#endif /* !__ptbl_vsnprintf_h__ */
