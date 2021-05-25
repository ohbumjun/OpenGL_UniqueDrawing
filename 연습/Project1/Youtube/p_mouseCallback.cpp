/*

#include "cg.h"

#define _WINDOW_HEIGHT 300
#define _WINDOW_WIDTH 100

GLfloat r = 1.0, g = 1.0, b = 1.0 ;
GLint cur_x = -1, cur_y = -1;
int mode_visual = 1;
int mode = 0;

void reshape(int width, int height)
{
	glViewport(0,0,width,height);
	GLfloat f_w = (GLfloat)width / (GLfloat)_WINDOW_WIDTH;
	GLfloat f_h = (GLfloat)height / (GLfloat)_WINDOW_HEIGHT;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0 * f_w, 1.0 * f_w, -1.0 * f_h, 1.0 * f_h, -1, 1);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	if (mode_visual == 1)
	{
		if (mode == 0)
			// glutWireSphere : ���� �׸��� �Լ�
			// radius : ���� ������ �����ϱ�
			// slices : ���� �߽��� ����, ���η� ����ȭ�� ���� �� ���� ( �漱 )
			// stacks : ���� �߽ɿ� �����ϰ� , ���η� ����ȭ�� ���� �� ����( ���� ) 
			glutWireSphere(1.0, 15, 15);
		else if (mode == 1)
			glutWireTeapot(0.7);
	}
	else {
		// �׿ܿ��� �ȱ׷��ش� 
	}
	
	// mode�� 2��� �ƹ��͵� �ȱ׸��� ������, �ڵ������� �������� ȿ�� 
	glFlush();
}

void mouseBtn(int btn,int states, int x, int y)
{
	// ���콺 ���� �� ���� �ٲٱ� 
	// ���� ���콺 ��ư, ���콺���� �� ����
	if (btn == GLUT_LEFT_BUTTON && states == GLUT_UP)
	{
		mode = (mode + 1) % 2;
		// ���� �ٽ� �׸���
		glutPostRedisplay();
	}
}

void mouseDrag(int x, int y)
{
	// ���ذ���� : mouseDrag �϶�, mouseFunc �� ���� ����, ��, callback �Լ��� 2���� ���� ����
	// �̸� ������ �� �ִ� ����� ������ ? 
	std::cout << "mouseDrag x,y" << x << y << std::endl;
	std::cout << "mouseDrag cur_x, cur_y" << cur_x << cur_y << std::endl;

	// ���콺 �����ӿ� ���� ���� ��ȭ
	// x,y : ���� �ֱ��� x,y ��ǥ
	GLint dx, dy; // ��ȭ ����

	if (cur_x >= 0 || cur_y >= 0)
	{
		// �巡�� ���� ���� 
		dx = abs(x - cur_x);
		dy = abs(y - cur_y);
		GLint sum = dx + dy;
		if (sum > 5) {
			g = (g - 0.1 < 0 ? 0 : g - 0.1);
			b = (b - 0.1 < 0 ? 0 : b - 0.1);
			r = (r - 0.1 < 0 ? 0 : r - 0.1);
			glColor3f(r, g, b);
			glutMouseFunc(NULL);
			glutPostRedisplay();
		}
	}
	cur_x = x;
	cur_y = y;
}

void winEntry(int state)
{
	// window â ������ ������ �ȴٸ� 
	if (state == GLUT_LEFT)
	{
		// std::cout << "winEntry : left" << state << std::endl;
		mode_visual = 0;
	}
	else
	{
		mode_visual = 1;
	}
		
	glutPostRedisplay();

	std::cout << "winEntry : state" << state << std::endl;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutCreateWindow("title");
	glutInitWindowSize(_WINDOW_WIDTH,_WINDOW_HEIGHT);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseBtn);
	glutMotionFunc(mouseDrag);
	glutEntryFunc(winEntry);

	glutMainLoop();
	return 0;
}

*/