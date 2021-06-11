
/*
#include "cg.h"

#define _WINDOW_HEIGHT 300
#define _WINDOW_WIDTH 100

GLfloat r = 1.0, g = 1.0, b = 1.0 ;
GLint cur_x = -1, cur_y = -1;
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
	
	if (mode == 0) {}
	else if (mode == 1)
		glutWireSphere(1.0, 15, 15);
	else if (mode == 2)
		glutWireTorus(0.2,0.5,15,15);
	else if (mode == 3)
		glutWireTeapot(0.7);

	glFlush();
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

void selectMenu(int value) {
	// Exit �̸� ����������
	if (value == 2)
		exit(0);
}
void selectSubMenu(int value) {
	// ������ �������� mode ���� 
	mode = value;
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutCreateWindow("title");
	glutInitWindowSize(_WINDOW_WIDTH,_WINDOW_HEIGHT);
	glutDisplayFunc(display);
	glutMotionFunc(mouseDrag);
	glutReshapeFunc(reshape);

	int subMenuId = glutCreateMenu(selectSubMenu);
		glutSetMenu(subMenuId);// ���� �޴� ���� 
		glutAttachMenu(GLUT_RIGHT_BUTTON);// menu �� ���콺 ��ư�� ���
		// 3D Model�� Ŭ����, �Ʒ��� 3�� subMenu�� ������ ���̴� 
		glutAddMenuEntry("Sphere", 1); // �޴��� ���� �־��ֱ�
		glutAddMenuEntry("Torus", 2);
		glutAddMenuEntry("Teaport", 3);

	int mainMenuId = glutCreateMenu(selectMenu);
		glutSetMenu(mainMenuId);// ���� �޴� ���� 
		glutAttachMenu(GLUT_RIGHT_BUTTON);// menu �� ���콺 ��ư�� ���
		glutAddSubMenu("3D Model", subMenuId); // �޴��� ���� �־��ֱ�
		glutAddMenuEntry("Exit",2); 

	

	glutMainLoop();
	return 0;
}


*/