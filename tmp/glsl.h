class Glsl{
private:
	void init();

	//shader読み込み
	void read_shader(char *name, std::string &out);
	void shader_porocess();

public:
	Glsl();
	~Glsl();
	unsigned int vertexbuffer, indexbuffer;
	int vertex_num, index_num;
	
	//バッファ
	void create_vertex_buff(float *position,unsigned int &buff, int num);
	void modify_vertex_buff(float *position, unsigned int &buff, int num);
	void create_index_buff(unsigned int *index, unsigned int &buff, int num);
	void modify_index_buff(unsigned int *index, unsigned int &buff, int num);


	//描画
	void draw_line(float *position, int position_num, unsigned int *index, int index_num);
	void draw_mesh(float *position, int position_num, unsigned int *index, int index_num);
};