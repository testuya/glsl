class Glsl{
public:
	Glsl();
	~Glsl();
	void init();
	void buffer_process(GLuint &buff, GLfloat &data ,int size ,int index);
	void draw_line_strip(int width, int begin_index, int num);
	void draw_mesh();
};