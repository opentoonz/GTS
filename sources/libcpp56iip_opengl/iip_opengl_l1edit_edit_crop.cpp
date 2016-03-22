#include <math.h>
#include "pri.h"
#include "iip_opengl_l1edit.h"

void iip_opengl_l1edit::_edit_crop_start( void )
{
	this->_l_crop_xp_backup_for_cancel = this->_l_crop_xp;
	this->_l_crop_yp_backup_for_cancel = this->_l_crop_yp;
	this->_l_crop_width_backup_for_cancel = this->_l_crop_width;
	this->_l_crop_height_backup_for_cancel = this->_l_crop_height;
}
void iip_opengl_l1edit::_edit_crop_end( void )
{
	if (ON == this->get_i_pv_sw()) {
		pri_funct_msg_vr( "old xp %ld yp %ld w %ld h %ld",
		this->_l_crop_xp_backup_for_cancel,
		this->_l_crop_yp_backup_for_cancel,
		this->_l_crop_width_backup_for_cancel,
		this->_l_crop_height_backup_for_cancel );

		pri_funct_msg_vr( "new xp %ld yp %ld w %ld h %ld",
		this->_l_crop_xp,
		this->_l_crop_yp,
		this->_l_crop_width,
		this->_l_crop_height );
	}
}
void iip_opengl_l1edit::edit_crop_cancel( void )
{
	this->_l_crop_xp = this->_l_crop_xp_backup_for_cancel;
	this->_l_crop_yp = this->_l_crop_yp_backup_for_cancel;
	this->_l_crop_width = this->_l_crop_width_backup_for_cancel;
	this->_l_crop_height = this->_l_crop_height_backup_for_cancel;
	this->_e_select_part = E_SELECT_IMAGE;
}

void iip_opengl_l1edit::_edit_crop_moving(long l_move_x, long l_move_y)
{
	int	i_xp_moved_sw,
		i_yp_moved_sw;

	if (OFF == this->_i_crop_disp_sw) {
		return;
	}

	/* 上下方向反転 */
	l_move_y = - l_move_y;
	if (0.0 != this->_d_zoom) {
		l_move_x = (long)(l_move_x / this->_d_zoom);
		l_move_y = (long)(l_move_y / this->_d_zoom);
	}

	i_xp_moved_sw = OFF;
	i_yp_moved_sw = OFF;

	/* 切抜きを部分的移動し、移動情報を得る */
	this->_edit_crop_move_part(
		l_move_x, l_move_y, &i_xp_moved_sw, &i_yp_moved_sw);

	/* 画像外へ出さない & 1pixel以下に小さくしない */
	this->_edit_crop_limit( i_xp_moved_sw, i_yp_moved_sw );

	/* aspect ratioを固定した場合、小さくなる方向で固定2013-11-28 */
	this->edit_crop_fix_aspect_ratio_( i_xp_moved_sw, i_yp_moved_sw );
}

void iip_opengl_l1edit::set_crop_area(long l_xpos, long l_ypos, long l_xsize, long l_ysize )
{
	int	i_xp_moved_sw,
		i_yp_moved_sw;

	/******if (OFF == this->_i_crop_disp_sw) {
		return;
	}******/

	i_xp_moved_sw = OFF;
	i_yp_moved_sw = OFF;

	if (this->_l_crop_xp != l_xpos) { i_xp_moved_sw = ON; }
	if (this->_l_crop_yp != l_ypos) { i_yp_moved_sw = ON; }
	this->_l_crop_xp = l_xpos;
	this->_l_crop_yp = l_ypos;
	this->_l_crop_width = l_xsize;
	this->_l_crop_height = l_ysize;

	/* 画像外へ出さない & 1pixel以下に小さくしない */
	this->_edit_crop_limit( i_xp_moved_sw, i_yp_moved_sw );
}

void iip_opengl_l1edit::_edit_crop_move_part(long l_move_x, long l_move_y, int *ip_xp_moved_sw, int *ip_yp_moved_sw)
{
	switch (this->_e_select_part) {
	case E_SELECT_LEFTBOTTOM:
		this->_l_crop_xp =
			this->_l_crop_xp_backup_for_cancel + l_move_x;
		*ip_xp_moved_sw = ON;
		this->_l_crop_yp =
			this->_l_crop_yp_backup_for_cancel + l_move_y;
		*ip_yp_moved_sw = ON;
		this->_l_crop_width =
			this->_l_crop_width_backup_for_cancel -l_move_x;
		this->_l_crop_height =
			this->_l_crop_height_backup_for_cancel-l_move_y;
		break;
	case E_SELECT_LEFT:
		this->_l_crop_xp =
			this->_l_crop_xp_backup_for_cancel + l_move_x;
		*ip_xp_moved_sw = ON;
		this->_l_crop_width =
			this->_l_crop_width_backup_for_cancel -l_move_x;
		break;
	case E_SELECT_LEFTTOP:
		this->_l_crop_xp =
			this->_l_crop_xp_backup_for_cancel + l_move_x;
		*ip_xp_moved_sw = ON;
		this->_l_crop_width =
			this->_l_crop_width_backup_for_cancel -l_move_x;
		this->_l_crop_height =
			this->_l_crop_height_backup_for_cancel+l_move_y;
		break;
	case E_SELECT_TOP:
		this->_l_crop_height =
			this->_l_crop_height_backup_for_cancel+l_move_y;
		break;
	case E_SELECT_RIGHTTOP:
		this->_l_crop_width =
			this->_l_crop_width_backup_for_cancel +l_move_x;
		this->_l_crop_height =
			this->_l_crop_height_backup_for_cancel+l_move_y;
		break;
	case E_SELECT_RIGHT:
		this->_l_crop_width =
			this->_l_crop_width_backup_for_cancel +l_move_x;
		break;
	case E_SELECT_RIGHTBOTTOM:
		this->_l_crop_width =
			this->_l_crop_width_backup_for_cancel +l_move_x;
		this->_l_crop_yp =
			this->_l_crop_yp_backup_for_cancel + l_move_y;
		*ip_yp_moved_sw = ON;
		this->_l_crop_height =
			this->_l_crop_height_backup_for_cancel-l_move_y;
		break;
	case E_SELECT_BOTTOM:
		this->_l_crop_yp =
			this->_l_crop_yp_backup_for_cancel + l_move_y;
		*ip_yp_moved_sw = ON;
		this->_l_crop_height =
			this->_l_crop_height_backup_for_cancel-l_move_y;
		break;
	case E_SELECT_CENTER:
		this->_l_crop_xp =
			this->_l_crop_xp_backup_for_cancel + l_move_x;
		*ip_xp_moved_sw = ON;
		this->_l_crop_yp =
			this->_l_crop_yp_backup_for_cancel + l_move_y;
		*ip_yp_moved_sw = ON;
		break;
	default:
		break;
	}
}

void iip_opengl_l1edit::_edit_crop_limit(int i_xp_moved_sw, int i_yp_moved_sw)
{
	if (this->_e_select_part == E_SELECT_CENTER) {
		/* scan画像よりcropの方が大きいならcropサイズを切り詰める */
		if (this->get_l_width() < this->_l_crop_width) {
			this->_l_crop_width = this->get_l_width();
		}
		if (this->get_l_height() < this->_l_crop_height) {
			this->_l_crop_height = this->get_l_height();
		}
		/* 右、上、にはみ出そうとしたら、接する位置で止める */
		if (this->get_l_width() <
		(this->_l_crop_xp + this->_l_crop_width) ) {
			this->_l_crop_xp = this->get_l_width() -
					this->_l_crop_width;
		}
		if (this->get_l_height() <
		(this->_l_crop_yp + this->_l_crop_height) ) {
			this->_l_crop_yp = this->get_l_height() -
					this->_l_crop_height;
		}
		/* 左、下、にはみ出そうとしたら、接する位置で止める */
		if (this->_l_crop_xp < 0L) { this->_l_crop_xp = 0L; }
		if (this->_l_crop_yp < 0L) { this->_l_crop_yp = 0L; }
		return;
	}
	/*
	 * 画像外へ出さない
	 */

	/* 右上のはみ出しをカット */
	if (this->get_l_width() <
	(this->_l_crop_xp + this->_l_crop_width) ) {
		this->_l_crop_width =	this->get_l_width() -
					this->_l_crop_xp;
	}
	if (this->get_l_height() <
	(this->_l_crop_yp + this->_l_crop_height) ) {
		this->_l_crop_height = this->get_l_height() -
					this->_l_crop_yp;
	}

	/* 左下のはみ出しをカット */
	if (this->_l_crop_xp < 0L) {
		this->_l_crop_width += this->_l_crop_xp;
		this->_l_crop_xp = 0L;
	}
	if (this->_l_crop_yp < 0L) {
		this->_l_crop_height += this->_l_crop_yp;
		this->_l_crop_yp = 0L;
	}

	/*
	 * 1pixel以下に小さくしない
	 */
	if (this->_l_crop_width < 1L) {
		if (ON == i_xp_moved_sw) {
			this->_l_crop_xp += this->_l_crop_width - 1L;
		}
		this->_l_crop_width = 1L;
	}
	if (this->_l_crop_height < 1L) {
		if (ON == i_yp_moved_sw) {
			this->_l_crop_yp += this->_l_crop_height - 1L;
		}
		this->_l_crop_height = 1L;
	}
}
void iip_opengl_l1edit::edit_crop_fix_aspect_ratio_(
	int i_xp_moved_sw, int i_yp_moved_sw
) {
	/* 画面比が指定されていないときはなにもしない */
	if (	this->crop_aspect_ratio_w == 0.0 ||
		this->crop_aspect_ratio_h == 0.0) { return; }

/*
	以下不完全であり作りかけ --> 将来設計からやり直す
	this->crop_aspect_ratio_w or hをゼロとして使わない
*/
	if ((this->crop_aspect_ratio_w / this->crop_aspect_ratio_h) <
	(this->_l_crop_width / this->_l_crop_height)) {
		const long ww = this->_l_crop_width;
		/* 指定の画面比より幅が広いとき */
		this->_l_crop_width = static_cast<long>(
				this->_l_crop_height *
				this->crop_aspect_ratio_w /
				this->crop_aspect_ratio_h);
		if (ON == i_xp_moved_sw) {
			this->_l_crop_xp += ww - this->_l_crop_width;
		}
	} else {
		const long hh = this->_l_crop_height;
		/* 指定の画面比より高さが高いとき */
		this->_l_crop_height = static_cast<long>(
				this->_l_crop_width *
				this->crop_aspect_ratio_h /
				this->crop_aspect_ratio_w);
		if (ON == i_yp_moved_sw) {
			this->_l_crop_yp += hh - this->_l_crop_height;
		}
	}
}
