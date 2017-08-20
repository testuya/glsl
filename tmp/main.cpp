#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glut.h>
#include "glsl.h"

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("OpenGL");
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0);

	//ÉfÅ[É^
	Glsl glsl;
	float g_vertex_buffer_data[] = {
		//1
		0.0f, -1.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f

	};

	unsigned int edge[] = { 0, 1 ,3, 0, 2, 3};

	//BufferÇ…ä÷Ç∑ÇÈèàóù
	glsl.vertex_num = sizeof(g_vertex_buffer_data) / sizeof(g_vertex_buffer_data[0]);
	glsl.index_num = sizeof(edge) / sizeof(edge[0]);
	glsl.create_vertex_buff(g_vertex_buffer_data, glsl.vertexbuffer, glsl.vertex_num);
	glsl.create_index_buff(edge, glsl.indexbuffer, glsl.index_num);

	//ï`âÊ
	glLineWidth(10.0);
	glsl.draw_line(g_vertex_buffer_data, glsl.vertex_num, edge, glsl.index_num);
	//glsl.draw_mesh(g_vertex_buffer_data, glsl.vertex_num, edge, glsl.index_num);

	
	glutSwapBuffers();
	glutMainLoop();
	return 0;
}