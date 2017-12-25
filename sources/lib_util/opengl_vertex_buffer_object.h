#ifndef opengl_vertex_buffer_object_h
#define opengl_vertex_buffer_object_h

#include <FL/gl.h>	/* GLfloat GLubyte GLuint GLenum */
//#include <GL/gl.h>	/* GLfloat GLubyte GLuint GLenum */

namespace opengl {

class vertex_buffer_object {
public:
	vertex_buffer_object();
	~vertex_buffer_object();

	/* vboメモリで浮動小数の型 vbo_type_と合わせること*/
	//using vbo_float = GLdouble;
	using vbo_float = GLfloat;

	/* vboで使うpixel書式 */
	struct vertex { vbo_float x,y,z; };
	struct color { GLubyte r,g,b; };
	struct vertex_color { vertex xyz; color rgb; };

	/* 処理開始と終了、あるいは pixel_size数の変更のときは
	一旦close()してから再度open_or_reopen()する
	ret.empty()=OK , !ret.empty()=Error */
	std::string open_or_reopen( unsigned pixel_size );
	void close(void);

	/* 始めの値のセット、あるいは 数が同じで値のみ変更 */
	vertex_color* start_vertex_color( void );
	/* 注:start_vertex_color()からend_vertex_color()まで
	vertex_color bufferがbind状態 */
	void end_vertex_color( void );

	/* 描画実行 */
	void draw(void);

	void set_hsv_view_start_sw(bool sw) { this->hsv_view_start_sw_=sw; }
	bool get_hsv_view_start_sw(void) const { return this->hsv_view_start_sw_;}
	int get_pixel_size(void) const { return this->pixel_size_; }

	/* for debug */
	void pr_vbo_info(void);
private:
	GLuint id_vbo_;
	GLuint pixel_size_;
	GLenum vbo_type_;// use glVertexPointer(,vbo_type,,)
	bool hsv_view_start_sw_;

}; // class vertex_buffer_object

} // namespace opengl

#endif /* !opengl_vertex_buffer_object_h */
