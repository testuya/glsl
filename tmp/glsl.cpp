#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glut.h>
#include "glsl.h"


Glsl::Glsl(){
	init();
}

Glsl::~Glsl(){
	//解放
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &indexbuffer);
}

void Glsl::init(){
	GLenum glewStatus = glewInit();
	if (glewStatus != GLEW_OK)
	{
		std::cout << "Error: " << glewGetErrorString(glewStatus) << std::endl;
		std::exit(1);
	}

	shader_porocess();
}

void Glsl::read_shader(char *name, std::string &out){
	std::ifstream inputFile1(name);
	std::istreambuf_iterator<char> vdataBegin(inputFile1);
	std::istreambuf_iterator<char> vdataEnd;
	std::string filedata(vdataBegin, vdataEnd);
	out = filedata;
}

void Glsl::preprocess(float *position, int position_num, unsigned int *root_tip_index){
	//indexの生成
	std::vector<unsigned int> index;
	for (int i = 0; i < position_num / 3; i++){
		index.push_back(i);
	}

	//Bufferに関する処理
	this->vertex_num = position_num;
	this->index_num = index.size();
	this->create_vertex_buff(position, this->vertexbuffer, this->vertex_num);
	this->create_index_buff(index.data(), this->indexbuffer, this->index_num);
	//this->create_strage_buff(root_tip_index, this->stragebuffer, index_num);
	this->create_uniform_buff(root_tip_index, this->stragebuffer, index_num);
}

void Glsl::preprocess(float *position, int position_num, unsigned int *index, int index_num){
	//Bufferに関する処理
	this->vertex_num = position_num;
	this->index_num = index_num;
	this->create_vertex_buff(position, this->vertexbuffer, position_num);
	this->create_index_buff(index, this->indexbuffer, index_num);
}

void Glsl::preprocess(float *position, int position_num){
	//indexの生成
	std::vector<unsigned int> index;
	for (int i = 0; i < position_num / 3; i++){
		index.push_back(i);
	}

	//Bufferに関する処理
	this->vertex_num = position_num;
	this->index_num = index.size();
	this->create_vertex_buff(position, this->vertexbuffer, this->vertex_num);
	this->create_index_buff(index.data(), this->indexbuffer, this->index_num);
}


void Glsl::shader_porocess(){
	//バーテックスシェーダのコンパイル
	GLuint vShaderId = glCreateShader(GL_VERTEX_SHADER);
	std::string vertexShader;
	read_shader("Shader.vert", vertexShader);
	const char* vs = vertexShader.c_str();
	glShaderSource(vShaderId, 1, &vs, NULL);
	glCompileShader(vShaderId);

	//フラグメントシェーダのコンパイル
	GLuint fShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmentShader;
	read_shader("Shader.frag", fragmentShader);
	const char* fs = fragmentShader.c_str();
	glShaderSource(fShaderId, 1, &fs, NULL);
	glCompileShader(fShaderId);

	//ジオメトリシェーダのコンパイル
	GLuint gShaderId = glCreateShader(GL_GEOMETRY_SHADER);
	std::string geometryShader;
	read_shader("Shader.gs", geometryShader);
	const char* gs = geometryShader.c_str();
	glShaderSource(gShaderId, 1, &gs, NULL);
	glCompileShader(gShaderId);

	//プログラムオブジェクトの作成
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vShaderId);
	glAttachShader(programId, fShaderId);
	glAttachShader(programId, gShaderId);

	// リンク
	GLint linked;
	glLinkProgram(programId);
	glGetProgramiv(programId, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE)
	{
		std::cerr << "Link Err.\n";
	}
	glUseProgram(programId);
}

void Glsl::create_vertex_buff(float *position, unsigned int &buff, int num){
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, num * sizeof(GLfloat), position, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	buff = vertexbuffer;
}

void Glsl::modify_vertex_buff(float *position, unsigned int &buff, int num){
	glBindBuffer(GL_ARRAY_BUFFER, buff);
	float *ptr = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	for (int i = 0; i < num; i++){
		ptr[i] = position[i];
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Glsl::create_index_buff(unsigned int *index, unsigned int &buff, int num){
	GLuint indexbuffer;
	glGenBuffers(1, &indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num * sizeof(GLuint), index, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	buff = indexbuffer;
}

void Glsl::modify_index_buff(unsigned int *index, unsigned int &buff, int num){
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buff);
	unsigned int *ptr = (unsigned int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
	for (int i = 0; i < num; i++){
		ptr[i] = index[i];
	}
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Glsl::create_strage_buff(unsigned int *strage, unsigned int &buff, int num){
	GLuint stragebuffer;
	glGenBuffers(1, &stragebuffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, stragebuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, num * sizeof(GLuint), strage, GL_DYNAMIC_COPY);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	buff = stragebuffer;
}

void Glsl::create_uniform_buff(unsigned int *data, unsigned int &buff, int num){
	GLuint uniformbuffer;
	glGenBuffers(1, &uniformbuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, uniformbuffer);
	glBufferData(GL_UNIFORM_BUFFER, num * sizeof(GLuint), data, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	buff = uniformbuffer;
}

void Glsl::draw_mesh(float *position, int position_num, unsigned int *index, int index_num){
	//描画
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawElements(GL_TRIANGLES, position_num, GL_UNSIGNED_INT, NULL);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Glsl::draw_line(float *position){
	modify_vertex_buff(position, this->vertexbuffer, this->vertex_num);

	//描画
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexbuffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->stragebuffer);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, this->uniformbuffer);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, 0); 
	//glDrawElements(GL_LINES, this->vertex_num, GL_UNSIGNED_INT, NULL);
	glDrawElements(GL_LINE_STRIP, this->vertex_num, GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);	
}

void Glsl::LINES(float *position, unsigned int *root_tip_index){
	this->draw_line(position);
}
