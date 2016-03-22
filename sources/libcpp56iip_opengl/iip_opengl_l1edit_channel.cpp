// #include <GL/glut.h>
#include "pri.h"
#include "iip_opengl_l1edit.h"

void iip_opengl_l1edit::_pri_ch_info( void )
{
	pri_funct_msg_v( " this->_i_disp_ch  %4d ", this->_i_disp_ch );
	switch (this->_i_disp_ch) {
	case CH_RGB: pri_funct_msg_vr("CH_RGB"); break;
	case CH_RED: pri_funct_msg_vr("CH_RED"); break;
	case CH_GRE: pri_funct_msg_vr("CH_GRE"); break;
	case CH_BLU: pri_funct_msg_vr("CH_BLU"); break;
	case CH_ALP: pri_funct_msg_vr("CH_ALP"); break;
	default: pri_funct_msg_vr("CH_???"); break;
	}

	pri_funct_msg_v( " this->_gle_type   %4d ", this->_gle_type );
	switch (this->_gle_type) {
	case GL_UNSIGNED_BYTE:
		pri_funct_msg_vr("GL_UNSIGNED_BYTE"); break;
	case GL_UNSIGNED_SHORT:
		pri_funct_msg_vr("GL_UNSIGNED_SHORT"); break;
	case GL_BITMAP:
		pri_funct_msg_vr("GL_BITMAP"); break;
	default: pri_funct_msg_vr("GL_???"); break;
	}

	pri_funct_msg_v( " this->_gle_format %4d ",this->_gle_format );
	switch (this->_gle_format) {
	case GL_RGB:       pri_funct_msg_vr("GL_RGB"); break;
	case GL_RGBA:      pri_funct_msg_vr("GL_RGBA"); break;
	case GL_RED:       pri_funct_msg_vr("GL_RED"); break;
	case GL_GREEN:     pri_funct_msg_vr("GL_GREEN"); break;
	case GL_BLUE:      pri_funct_msg_vr("GL_BLUE"); break;
	case GL_LUMINANCE: pri_funct_msg_vr("GL_LUMINANCE"); break;
	case GL_COLOR_INDEX: pri_funct_msg_vr("GL_COLOR_INDEX"); break;
	default: pri_funct_msg_vr("GL_???"); break;
	}
}

/* OpenGL表示用のチャンネル数設定 */
void iip_opengl_l1edit::init_channel( void )
{
	if (ON == this->get_i_mv_sw()) {
		pri_funct_msg_vr("iip_opengl_l1edit::init_channel()");
	}
		this->_i_disp_ch = CH_RGB; /* Grayscale,BWも含む */

	/* BW以外 */
	if (1L == this->cl_ch_info.get_l_bytes()) {
		this->_gle_type = GL_UNSIGNED_BYTE;
	} else if (2L == this->cl_ch_info.get_l_bytes()) {
		this->_gle_type = GL_UNSIGNED_SHORT;
	}

	if (1L == this->get_l_channels()) {
	 if (1L == this->cl_ch_info.get_l_bits()) {
		this->_gle_type = GL_BITMAP;
		this->_gle_format = GL_COLOR_INDEX;
	 } else {
		this->_gle_format = GL_LUMINANCE;
	 }
	} else {
		this->_gle_format = GL_RGB;
	}

	if (ON == this->get_i_pv_sw()) {
		this->_pri_ch_info();
	}
}

/* 表示するデータとOpenGLフォーマットの設定 */
void iip_opengl_l1edit::set_channel( int i_data_ch, int i_view_ch )
{
	switch (this->get_l_channels()) {
	case 4L:
		switch (i_data_ch) {
		case CH_RGB: this->_i_disp_ch = CH_RGB; break;
		case CH_RED: this->_i_disp_ch = CH_RED; break;
		case CH_GRE: this->_i_disp_ch = CH_GRE; break;
		case CH_BLU: this->_i_disp_ch = CH_BLU; break;
		case CH_ALP: this->_i_disp_ch = CH_ALP; break;
		}
		switch (i_view_ch) {
		case CH_RGB: this->_gle_format = GL_RGBA;  break;
		case CH_RED: this->_gle_format = GL_RED;   break;
		case CH_GRE: this->_gle_format = GL_GREEN; break;
		case CH_BLU: this->_gle_format = GL_BLUE;  break;
		case CH_ALP: this->_gle_format = GL_LUMINANCE; break;
		}
		break;
	case 3L:
		switch (i_data_ch) {
		case CH_RGB: this->_i_disp_ch = CH_RGB; break;
		case CH_RED: this->_i_disp_ch = CH_RED; break;
		case CH_GRE: this->_i_disp_ch = CH_GRE; break;
		case CH_BLU: this->_i_disp_ch = CH_BLU; break;
		case CH_ALP: break;
		}
		switch (i_view_ch) {
		case CH_RGB: this->_gle_format = GL_RGB;   break;
		case CH_RED: this->_gle_format = GL_RED;   break;
		case CH_GRE: this->_gle_format = GL_GREEN; break;
		case CH_BLU: this->_gle_format = GL_BLUE;  break;
		case CH_ALP:
			if (CH_ALP != i_data_ch) {
				this->_gle_format = GL_LUMINANCE;
			}
			break;
		}
		break;
	default:
		/* 変化しない */
		break;
	}
}
