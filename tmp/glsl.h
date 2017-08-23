#include <iostream>
#include <vector>

class Glsl{
private:
	void init();

	//shader読み込み
	void read_shader(char *name, std::string &out);
	void shader_porocess();

	//バッファ
	void create_vertex_buff(float *position, unsigned int &buff, int num);
	void create_index_buff(unsigned int *index, unsigned int &buff, int num);
	void create_uniform_buff(unsigned int *data, unsigned int &buff, int num);
	void create_strage_buff(unsigned int *strage, unsigned int &buff, int num);

public:
	Glsl();
	~Glsl();
	unsigned int vertexbuffer, indexbuffer, stragebuffer,uniformbuffer;
	int vertex_num, index_num;

	//前処理
	void preprocess(float *position, int position_num, unsigned int *root_tip_index);
	void preprocess(float *position, int position_num, unsigned int *index, int index_num);
	void preprocess(float *position, int position_num);

	void modify_vertex_buff(float *position, unsigned int &buff, int num);
	void modify_index_buff(unsigned int *index, unsigned int &buff, int num);


	//描画
	void draw_line(float *position);
	void draw_mesh(float *position, int position_num, unsigned int *index, int index_num);
	void LINES(float *position, unsigned int *root_tip_index);
};