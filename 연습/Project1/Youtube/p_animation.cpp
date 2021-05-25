// 애니메이션 기본원리 ?
// 여러장의 프레임을 빠른 속도로 전환

/*

#include "cg.h"

#define _WINDOW_HEIGHT 300
#define _WINDOW_WIDTH 300

GLfloat Delta = 0.0;
int w = 1024;
int h = 1024;

void MyTimer(int value)
{
	Delta = Delta + 0.001;
	glutPostRedisplay(); // 화면 새로 그리기 
	glutTimerFunc(1000/60,MyTimer,value);
}

void reshape(int width, int height)
{
	glViewport(0,0,width,height);
	GLfloat f_w = (GLfloat)width / (GLfloat)_WINDOW_WIDTH;
	GLfloat f_h = (GLfloat)height / (GLfloat)_WINDOW_HEIGHT;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0 * f_w, 1.0 * f_w, -1.0 * f_h, 1.0 * f_h, -1, 1);
}

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glColor3f(0.0,0.5,0.8);

	glVertex3f(-1.0 + Delta, -0.5,0.0);
	glVertex3f(0.0 + Delta, -0.5, 0.0);
	glVertex3f(0.0 + Delta, 0.5, 0.0);
	glVertex3f(-1.0 + Delta, 0.5, 0.0);

	glEnd();
	glutSwapBuffers();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	
	glutInitWindowSize(_WINDOW_WIDTH,_WINDOW_HEIGHT);
	glutInitWindowPosition(0,0);
	glutCreateWindow("title");

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	glutDisplayFunc(MyDisplay);
	glutTimerFunc(40,MyTimer,1);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}


*/
