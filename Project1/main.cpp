/*
#include "cg.h"
#include "draw.h"
#include "vec.h"

int w = 512;
int h = 512;
vector2D points[100];
int count;
int animOn = 1;
float colorRGB[3] = { 1.0,1.0,1.0 }; // r,g,b

#define _WINDOW_HEIGHT 600
#define _WINDOW_WIDTH  600


void idle();
void display();
void moveAnim(int);
void stopAnim(int);
void reshape(int rw, int rh);
void changeColor(float r, float g, float b);
void key(unsigned char key, int x, int y);

void idle()
{
	if (animOn == 1)
	{
		for (int i = 0; i < count; i++)
			points[i].x += 0.0001;
	}

	glutPostRedisplay();
}
void moveAnim(int value)
{

	for (int i = 0; i < count; i++)
	{
		points[i].x += (animOn == 1 ? 0.001 : 0.0);
	}
	glutPostRedisplay();
	glutTimerFunc(1000.0 / 60.0, moveAnim, 0);

}
void stopAnim(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000.0 / 60.0, stopAnim, 0);
}
void display()
{
	// ���� ���� �����ֱ� 
	glClear(GL_COLOR_BUFFER_BIT);
	// ������� ����� ���� ���� only
	glClearColor(0.8, 0.8, 0.8, 1.0);
	// ���� ���� ���� setting
	glColor3f(colorRGB[0], colorRGB[1], colorRGB[2]);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < count; i++)
	{
		glVertex3f(points[i].x, points[i].y, 0.0);
	}
	glEnd();
	glutSwapBuffers();
}

// openGL window â ������ ����, display ��絵 �ٲ��ش� 
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	GLfloat f_w = (GLfloat)width / (GLfloat)_WINDOW_WIDTH;
	GLfloat f_h = (GLfloat)height / (GLfloat)_WINDOW_HEIGHT;
	// glOrtho�� �׸��� ���� �ʿ��� 2�� line
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// ��𼭺���, ������ ��� �� ���ΰ� : -2  ~ 2
	glOrtho(-1.0 * f_w, 1.0 * f_w, -1.0 * f_h, 1.0 * f_h, -2, 2);

}


void changeColor(float r, float g, float b)
{
	colorRGB[0] = r;
	colorRGB[1] = g;
	colorRGB[2] = b;
	glutPostRedisplay();
}
void key(unsigned char key, int x, int y)
{
	if (key == 'Q' | key == 'q')
		exit(0);
	if (key == 'R' | key == 'r')
		changeColor(255.0, 0.0, 0.0);
	if (key == 'G' | key == 'g')
		changeColor(0.0, 128.0, 0.0);
	if (key == 'B' | key == 'b')
		changeColor(0.0, 0.0, 255.0);
	if (key == 'C' | key == 'c')
		changeColor(253.0, 253.0, 0.0);
	if (key == 'P' | key == 'p')
		changeColor(128.0, 0.0, 128.0);
	if (key == 'Y' | key == 'y')
		changeColor(255.0, 255.0, 0.0);
}

void mouse(GLint button, GLint state, GLint x, GLint y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // ���� ���콺 Ŭ���ϸ� close 
		exit(0);
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		points[count].x = (float)x / (float)w * 2.0 - 1.0;
		points[count].y = -(float)y / (float)h * 2.0 + 1.0;
		count++;
	}
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		std::cout << "mouse inclick" << std::endl;
		if (animOn == 1) { // ���� �������̸� ���߱� 
			animOn *= -1;
		}
		else { // ������ ���¶�� 
			animOn *= -1;
		}
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	// glutInitDisplayMode(GLUT_RGBA); // single buffer 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // idle func�� �̿��� ���, double buffer�� ����ؾ� �Ѵ� 
	glutInitWindowSize(w, h);
	glutCreateWindow("Simple Interactive application");

	count = 0;

	// glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);

	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	glutTimerFunc(1000, moveAnim, 0);

	glutMainLoop();

	return 0;
}


*/