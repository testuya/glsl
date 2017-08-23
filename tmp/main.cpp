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

	//データ
	Glsl glsl;

	float g_vertex_buffer_data[] = {
		//1
		0.5f, 0.9f, 0.0f,
		0.4f, 0.6f, 0.0f,
		0.5f, 0.2f, 0.0f,
		0.4f, -0.2f, 0.0f,
		0.5f, -0.6f, 0.0f,
		0.4f, -0.9f, 0.0f
	};

	unsigned int root_tip_index[] = { 0, 1,	1, 1, 1, 0};

	//前処理
	//glsl.preprocess(g_vertex_buffer_data, sizeof(g_vertex_buffer_data) / sizeof(g_vertex_buffer_data[0]));
	glsl.preprocess(g_vertex_buffer_data, sizeof(g_vertex_buffer_data) / sizeof(g_vertex_buffer_data[0]),root_tip_index);

	//描画
	glLineWidth(10.0);
	//glsl.draw_line();
	//glsl.draw_mesh(g_vertex_buffer_data, glsl.vertex_num, edge, glsl.index_num);
	
	g_vertex_buffer_data[0] += 1.0;
	glsl.draw_line(g_vertex_buffer_data);

	glutSwapBuffers();
	glutMainLoop();
	return 0;
}