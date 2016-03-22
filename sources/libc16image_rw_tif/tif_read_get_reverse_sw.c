#include "ptbl_returncode.h"

#include "tif.h"

int tif_read_get_reverse_sw( TIF_IMAGE_RW *tp_read )
{
	/* 上下の判別、Xウインドウ用のオーダーのときは
	   上下反転して読み込む */
	/* BOT... is order */
	/* TOP... is reverse */
	switch ( (int)tp_read->ui16_orientation ) {
	case ORIENTATION_BOTLEFT:  /* 縦ゼロ位置が下、横ゼロ位置が左 */
	case ORIENTATION_BOTRIGHT: /* 縦ゼロ位置が下、横ゼロ位置が右 */
	case ORIENTATION_LEFTBOT:  /* 縦ゼロ位置が左、横ゼロ位置が下 */
	case ORIENTATION_RIGHTBOT: /* 縦ゼロ位置が右、横ゼロ位置が下 */
		return OFF;
		break;

	/* TOPLEFTが画像データとして標準的? */
	case ORIENTATION_TOPLEFT:  /* 縦ゼロ位置が上、横ゼロ位置が左 */

	case ORIENTATION_TOPRIGHT: /* 縦ゼロ位置が上、横ゼロ位置が右 */
	case ORIENTATION_LEFTTOP:  /* 縦ゼロ位置が左、横ゼロ位置が上 */

	/* scannerから取り込んだ直のデータ? */
	case ORIENTATION_RIGHTTOP: /* 縦ゼロ位置が右、横ゼロ位置が上 */

	/* photoshopで作成したTIFFデータはゼロになっている */
	default: break;
	}
	return ON;
}
