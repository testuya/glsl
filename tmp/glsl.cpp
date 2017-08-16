#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glut.h>
#include "glsl.h"

Glsl::Glsl(){
	init();

	GLuint vertexarrayID;
	
	GLuint array[2];
	static GLfloat g_vertex_buffer_data[] = {
		//1
		-0.5f, 0.5f, 0.0f,
		-0.5f, 0.4f, 0.0f,
		-0.5f, 0.3f, 0.0f,
		-0.5f, 0.2f, 0.0f,
		-0.5f, 0.1f, 0.0f,
		-0.5f, 0.0f, 0.0f,
		//2
		0.5f, 0.8f, 0.0f,
		0.5f, 0.4f, 0.0f,
		0.5f, 0.3f, 0.0f,
		0.5f, 0.2f, 0.0f,
		0.5f, 0.1f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.4f, -0.5f, 0.0f
	};

	int index[13] = {
		0,1,1,1,1,0,
		0,1,1,1,1,1,0
	};

	//Buffer‚ÉŠÖ‚·‚éˆ—
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	buffer_process(vertexbuffer, *g_vertex_buffer_data, 39, 0);
	
	//”¯‚Ì’Tõ
	std::vector<int> root_tip_index;
	root_tip_index.push_back(0);
	for (int i = 1; i < 13; i++){
		if (index[i] == 0){
			root_tip_index.push_back(i);
		}
	}

	//•`‰æ‚ÉŠÖ‚·‚éˆ—
	for (int i = 0; i < root_tip_index.size(); i = i + 2){
		draw_line_strip(10, root_tip_index[i], root_tip_index[i + 1] + 1 - root_tip_index[i]);
	}



}

Glsl::~Glsl(){

}

void Glsl::init(){
	GLenum glewStatus = glewInit();
	if (glewStatus != GLEW_OK)
	{
		std::cout << "Error: " << glewGetErrorString(glewStatus) << std::endl;
		std::exit(1);
	}
}

void Glsl::buffer_process(GLuint &buff , GLfloat &data ,int size,int index){
	glEnableVertexAttribArray(index);
	glBindBuffer(GL_ARRAY_BUFFER, buff);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), &data, GL_DYNAMIC_DRAW);
}

void Glsl::draw_line_strip(int width, int begin_index, int num){
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glLineWidth(width);
	glDrawArrays(GL_LINE_STRIP, begin_index, num);	
}

void Glsl::draw_mesh(){

}
