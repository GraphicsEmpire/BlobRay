//============================================================================
// Name        : OclImplicitRaytracer.cpp
// Author      : Pourya Shirazian
// Version     :
// Copyright   : CopyRight 2012
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "PS_Graphics/PS_GLSurface.h"
#include "PS_Base/PS_Logger.h"

using namespace std;

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define FOVY 45.0
#define ZNEAR 0.01
#define ZFAR 100.0

GLSurface* g_lpSurface = NULL;

//Global Funcs
void SpecialKey(int key, int x, int y);
void NormalKey(unsigned char key, int x, int y);

///////////////////////////////////////////
void Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(g_lpSurface)
		g_lpSurface->drawAsQuad();
	/*
	glColor3f(0, 1, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0.5, 1, 0);
	glEnd();
	*/

	glutSwapBuffers();
}

void Resize(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(FOVY, (double)w/(double)h, ZNEAR, ZFAR);
	glOrtho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void SpecialKey(int key, int x, int y) {
	switch(key) {
	case(GLUT_KEY_F11): {
		glutLeaveMainLoop();
		break;
	}

	}
}

void NormalKey(unsigned char key, int x, int y) {

	switch(key) {
	case('c'): {
		glutLeaveMainLoop();
		break;
	}
	}
}

void Close() {

}

void Init() {
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);



	g_lpSurface = new GLSurface(WINDOW_WIDTH, WINDOW_HEIGHT);
	g_lpSurface->attach();
	g_lpSurface->testDrawTriangle();
	g_lpSurface->detach();
	g_lpSurface->saveAsPNG("test1.png");

	//g_lpSurface->detach();
}

int main(int argc, char* argv[]) {

	//Initialize app
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("BlobTree Implicit Raytracer");
	glutDisplayFunc(Draw);
	glutReshapeFunc(Resize);
//	glutMouseFunc(MousePress);
//	glutPassiveMotionFunc(MousePassiveMove);
//	glutMotionFunc(MouseMove);
//	glutMouseWheelFunc(MouseWheel);

	glutKeyboardFunc(NormalKey);
	glutSpecialFunc(SpecialKey);
	glutCloseFunc(Close);
	//glutTimerFunc(g_appSettings.timerInterval, TimeStep, 0);


	TheEventLogger::Instance().setWriteFlags(PS_LOG_WRITE_EVENTTYPE | PS_LOG_WRITE_SOURCE | PS_LOG_WRITE_TO_SCREEN);
	LogInfo("Initialize GLEW and Raytracer");

	//Initialize GLEW
	GLenum err = glewInit();
	if (err != GLEW_OK)	{
		//Problem: glewInit failed, something is seriously wrong.
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(1);
	}

	Init();


	glutMainLoop();

	return 0;
}
