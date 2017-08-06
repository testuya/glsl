#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glut.h>
#include "glsl.h"

Glsl::Glsl(){
	GLenum glewStatus = glewInit();
	if (glewStatus != GLEW_OK)
	{
		std::cout << "Error: " << glewGetErrorString(glewStatus) << std::endl;
		std::exit(1);
	}

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] = {
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


	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
	
	std::vector<int> root_tip_index;
	root_tip_index.push_back(0);
	for (int i = 1; i < 13; i++){
		if (index[i] == 0){
			root_tip_index.push_back(i);
		}
	}
	for (int i = 0; i < root_tip_index.size(); i = i + 2){
		//std::cout << "line  : " << root_tip_index[i] << " : " << root_tip_index[i  + 1] + 1  << std::endl;
		glDrawArrays(GL_LINE_STRIP, root_tip_index[i], root_tip_index[i + 1] + 1  - root_tip_index[i]);
	}


	glDisableVertexAttribArray(0);

}

Glsl::~Glsl(){

}