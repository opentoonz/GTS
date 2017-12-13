#ifndef opengl_vertex_buffer_object_h
#define opengl_vertex_buffer_object_h

#include <FL/gl.h>	/* GLfloat GLubyte GLuint GLenum */

namespace opengl {
class vertex_buffer_object {
public:
	vertex_buffer_object();
	~vertex_buffer_object();

	/* vboメモリで浮動小数の型 vbo_type_と合わせること*/
	//using vbo_float = GLdouble;
	using vbo_float = GLfloat;

	/* 処理開始と終了、あるいは pixel_size数の変更のときは
	一旦close()してから再度open_or_reopen()する
	ret.empty()=OK , !ret.empty()=Error */
	std::string open_or_reopen( unsigned pixel_size );
	void close(void);

	/* 始めの値のセット、あるいは 数が同じで値のみ変更 */
	vbo_float* start_vertex( void );
	/* 注:start_vertex()からend_vertex()までvertex bufferがbind状態 */
	void end_vertex( void );

	GLubyte* start_color( void );
	/* 注:start_color()からend_color()までcolor bufferがbind状態 */
	void end_color( void );

	/* 描画実行 */
	void draw(void);

	/* hsv --> xyz変換 */
	void hsv_to_xyz(
		const double h , const double s , const double v
		,double& x , double& y , double& z
	);
	void hsv_to_xyzarray(
		const double h , const double s , const double v
		,vertex_buffer_object::vbo_float* xyz
	);

	void set_hsv_view_start_sw(bool sw) { this->hsv_view_start_sw_=sw; }
	bool get_hsv_view_start_sw(void) const { return this->hsv_view_start_sw_;}

	/* for debug */
	void pr_vbo_info(void);
private:
	GLuint id_vbo_[2];
	GLuint pixel_size_;
	GLenum vbo_type_;// use glVertexPointer(,vbo_type,,)
	bool hsv_view_start_sw_;

	void clear_id_vbo_(void);
}; // class vertex_buffer_object
} // namespace opengl

#endif /* !opengl_vertex_buffer_object_h */
