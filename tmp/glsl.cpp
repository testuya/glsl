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

	//プログラムオブジェクトの作成
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vShaderId);
	glAttachShader(programId, fShaderId);

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

void Glsl::draw_mesh(float *position, int position_num, unsigned int *index, int index_num){
	//描画
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawElements(GL_TRIANGLES, position_num, GL_UNSIGNED_INT, NULL);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Glsl::draw_line(float *position, int position_num, unsigned int *index, int index_num){
	//描画
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawElements(GL_LINES, position_num, GL_UNSIGNED_INT, NULL);
	glDisableClientState(GL_VERTEX_ARRAY);	
}

