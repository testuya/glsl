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

	Glsl glsl;
	
	glutSwapBuffers();
	glutMainLoop();
	return 0;
}