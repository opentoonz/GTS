#ifndef __ptbl_returncode_h__
#define __ptbl_returncode_h__

/* 関数の戻り値 */
#ifndef	OK
#define	OK	(0)
#endif
#ifndef	NG
#define	NG	(-1)
#endif
#ifndef	CANCEL	/* スキャン中のキャンセルの感知のため作成 2017-02-06 */
#define	CANCEL	(2)
#endif

#ifndef	OFF
#define	OFF	(0)
#endif
#ifndef	ON
#define	ON	(1)
#endif

#endif /* !__ptbl_returncode_h__ */
