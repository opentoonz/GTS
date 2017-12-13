#include <iostream>	/* std::cout */
#include <sstream>	/* std::ostringstream */
#include <cmath>	/* sin(-) cos(-) */

#define GLEW_STATIC	/* use glew32s.lib */
#include <GL/glew.h>	/* gl.hより前に必要 */

#include "calc_rad_deg.h"
#include "calc_trace_by_hsv.h"
#include "opengl_vertex_buffer_object.h"

/*---------- opengl::vertex_buffer_object関数 ----------*/

namespace opengl {
void vertex_buffer_object::clear_id_vbo_(void)
{
	for (int ii=0;ii<sizeof(this->id_vbo_) / sizeof(GLuint) ;++ii) {
		this->id_vbo_[0] = 0;
	}
}

vertex_buffer_object::vertex_buffer_object()
	:pixel_size_(0)
	/* vboメモリで浮動小数の型 vbo_floatと合わせること*/
	//,vbo_type_(GL_DOUBLE)
	,vbo_type_(GL_FLOAT)
	,hsv_view_start_sw_(false)
{
	this->clear_id_vbo_();
}
vertex_buffer_object::~vertex_buffer_object()
{
	this->close();
}
std::string vertex_buffer_object::open_or_reopen( unsigned pixel_size )
{
	/* 以前のvboバッファが残っていれば閉じる */
	this->close();

	/* vboバッファのIDを得る。座標と色の二つ */
	glGenBuffers( sizeof(this->id_vbo_)/sizeof(GLuint),this->id_vbo_ );

	/* 頂点用VBOを確保 */
	glBindBuffer( GL_ARRAY_BUFFER ,this->id_vbo_[0] );
	glBufferData( GL_ARRAY_BUFFER
	 ,pixel_size * sizeof(vbo_float) * 3 ,nullptr ,GL_DYNAMIC_DRAW );

	/* 頂点用VBO確保の確認 */
	{
	GLint chk_sz=0;
	glGetBufferParameteriv( GL_ARRAY_BUFFER ,GL_BUFFER_SIZE ,&chk_sz );
	if ( pixel_size * sizeof(vbo_float) * 3 != chk_sz ) {
		if (0 < chk_sz) {
			glDeleteBuffers( 1 , &this->id_vbo_[0] );
		}

		/* bindを指定なしにする */
		glBindBuffer( GL_ARRAY_BUFFER ,0 );

		this->clear_id_vbo_();

		std::ostringstream ost;
		ost	<< "Error:Can not get vbo for vertex:"
			<< "pixel_size("
			<<  pixel_size
			<< ")*sizeof(vbo_float)("
			<<    sizeof(vbo_float)
			<< ")*3!=chk_sz("
			<<       chk_sz
			<< ")"
			;
		return ost.str();
	}
	}

	/* 色用VBOを確保 */
	glBindBuffer( GL_ARRAY_BUFFER ,this->id_vbo_[1] );
	glBufferData( GL_ARRAY_BUFFER
	 ,pixel_size * sizeof(GLubyte) * 3 ,nullptr ,GL_DYNAMIC_DRAW );

	/* 色用VBO確保の確認 */
	{
	GLint chk_sz=0;
	glGetBufferParameteriv( GL_ARRAY_BUFFER ,GL_BUFFER_SIZE ,&chk_sz );
	if ( pixel_size * sizeof(GLubyte) * 3 != chk_sz ) {
		if (0 < chk_sz) {
			glDeleteBuffers(
				sizeof(this->id_vbo_) / sizeof(GLuint)
				, this->id_vbo_ );
		}
		else {
			/* すでに確保したVBOを削除 */
			glDeleteBuffers( 1 , &this->id_vbo_[0] );
		}

		/* bindを指定なしにする */
		glBindBuffer( GL_ARRAY_BUFFER ,0 );

		this->clear_id_vbo_();

		std::ostringstream ost;
		ost	<< "Error:Can not get vbo for color:"
			<< "pixel_size("
			<<  pixel_size
			<< ")*sizeof(GLubyte)("
			<<    sizeof(GLubyte)
			<< ")*3!=chk_sz("
			<<       chk_sz
			<< ")"
			;
		return ost.str();
	}
	}

	this->pixel_size_ = pixel_size;

	/* bindを指定なしにする */
	glBindBuffer( GL_ARRAY_BUFFER ,0 );

	return std::string();
}
void vertex_buffer_object::close(void)
{
	/* VBO用ID破棄 */
	if (this->id_vbo_[0] != 0) {
		glDeleteBuffers(
			sizeof(this->id_vbo_) / sizeof(GLuint)
			, this->id_vbo_ );
		this->clear_id_vbo_();
	}
}

vertex_buffer_object::vbo_float* vertex_buffer_object::start_vertex( void )
{
	if (this->id_vbo_[0] == 0) {
		return nullptr;
	}
	/* 頂点用VBO */
	glBindBuffer( GL_ARRAY_BUFFER ,this->id_vbo_[0] );
	return static_cast<vbo_float *>(glMapBuffer(
				GL_ARRAY_BUFFER , GL_READ_WRITE ));
}
void vertex_buffer_object::end_vertex( void )
{
	if (this->id_vbo_[0] == 0) {
		return;
	}
	glUnmapBuffer( GL_ARRAY_BUFFER );
}
GLubyte* vertex_buffer_object::start_color( void )
{
	if (this->id_vbo_[1] == 0) {
		return nullptr;
	}
	/* 色用VBO */
	glBindBuffer( GL_ARRAY_BUFFER ,this->id_vbo_[1] );
	return static_cast<GLubyte *>(glMapBuffer(
				GL_ARRAY_BUFFER , GL_READ_WRITE ));
	/* ここからend_color()までcolorbufferがbind状態 */
}
void vertex_buffer_object::end_color( void )
{
	if (this->id_vbo_[1] == 0) {
		return;
	}
	glUnmapBuffer( GL_ARRAY_BUFFER );
}

void vertex_buffer_object::draw(void)
{
	if (this->id_vbo_[0] == 0) {
		return;
	}
	/* 頂点の格納場所を伝える */
	glBindBuffer( GL_ARRAY_BUFFER ,this->id_vbo_[0] );
	glVertexPointer( 3 ,this->vbo_type_ ,0 ,0 );

	/* 色の格納場所を伝える */
	glBindBuffer( GL_ARRAY_BUFFER ,this->id_vbo_[1] );
	glColorPointer( 3 ,GL_UNSIGNED_BYTE ,0 ,0 );

	/* 描画を有効化 */
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );

	/* 描画 */
	glDrawArrays( GL_POINTS ,0 ,this->pixel_size_ );

	/* 描画を無効化 */
	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );

	/* bind指定なしにする。エラー除け??? */
	glBindBuffer( GL_ARRAY_BUFFER ,0 );
}

void vertex_buffer_object::pr_vbo_info(void)
{
	std::cout << "vertex buffer="
		<< this->pixel_size_ * sizeof(vbo_float) * 3 << "bytes\n";
	std::cout << " color buffer="
		<< this->pixel_size_ * sizeof(GLubyte)   * 3 << "bytes\n";
	std::cout << "        total="
		<< this->pixel_size_ * sizeof(vbo_float) * 3
		 + this->pixel_size_ * sizeof(GLubyte)   * 3 << "bytes\n";
}

void vertex_buffer_object::hsv_to_xyz(
	const double h , const double s , const double v
	,double& x , double& y , double& z
)
{
	/* hsv --> x,y,z */
	x = cos( calc::rad_from_deg(h) ) * s * v;
	y = sin( calc::rad_from_deg(h) ) * s * v;
	z = 1. - v;
}

void vertex_buffer_object::hsv_to_xyzarray(
	const double h , const double s , const double v
	, vertex_buffer_object::vbo_float* xyz
)
{
	/* hsv --> xyzarray */
	xyz[0] = static_cast<vertex_buffer_object::vbo_float>(
		cos( calc::rad_from_deg(h) ) * s * v
	);
	xyz[1] = static_cast<vertex_buffer_object::vbo_float>(
		sin( calc::rad_from_deg(h) ) * s * v
	);
	xyz[2] = static_cast<vertex_buffer_object::vbo_float>(
		1. - v
	);
}
} // namespace opengl
