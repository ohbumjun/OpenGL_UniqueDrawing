// 3d ������ü �׸���
// 8�� ����
// 6�� �� 

/*
#include "cg.h"

#define _WINDOW_HEIGHT 1200
#define _WINDOW_WIDTH  1200

int list_id;
int w = 1024;
int h = 1024;

GLfloat myCube[8][3];
GLfloat defaultCube[8][3] = {
	// �Ѹ��� �ʺ� 1 �� �Ǿ��ִ� 
{-0.5,-0.5,0.5},
{-0.5,0.5,0.5},
{0.5,0.5,0.5},
{0.5,-0.5,0.5},
{-0.5,-0.5,-0.5},
{-0.5,0.5,-0.5},
{0.5,0.5,-0.5},
{0.5,-0.5,-0.5}
};
GLfloat MyColors[8][3] = { {0.2,0.2,0.2},{1.0,0.0,0.0},{1.0,1.0,0.0},{0.0,1.0,0.0},
	{0.0,0.0,1.0},{1.0,0.0,1.0},{1.0,1.0,1.0},{0.0,1.0,0.0} };

void drawCube(GLfloat size, GLint x, GLint y, GLint z)
{
	// ũ������ : size ��ŭ �Ѻ��� ���̸� �����Ѵ� : defaultCube ���� size�� �����ָ� �ȴ�. ���� myCube �Ѻ��� ���̰� 1 �̱� ������
	// �̵� : x�����δ� x, y�����δ� y, z�����δ� z��ŭ �̵��Ѵ� : + �� ���ָ� �ȴ�
	for (int i = 0; i < 8; i++) {
		myCube[i][0] = size * defaultCube[i][0] + x;
		myCube[i][1] = size * defaultCube[i][1] + y;
		myCube[i][2] = size * defaultCube[i][2] + z;
	}

	int idx[6][4] = { 
		{0,3,2,1},
		{2,3,7,6},
		{7,4,5,6},
		{1,2,6,5},
		{0,3,7,4},
		{0,4,5,1} 
	};
	// ������ü�� �׸��� ���ؼ���, 6���� ���� �׷����Ѵ�
	// ��, 4�� ������ 6�� ���� �Ѵٴ� ���̴�
	for (int i = 0; i < 6; i++) {
		int idx0 = idx[i][0];
		int idx1 = idx[i][1];
		int idx2 = idx[i][2];
		int idx3 = idx[i][3];

		glBegin(GL_POLYGON);
			glColor3fv(MyColors[idx0]); glVertex3fv(myCube[idx0]);
			glColor3fv(MyColors[idx1]); glVertex3fv(myCube[idx1]);
			glColor3fv(MyColors[idx2]); glVertex3fv(myCube[idx2]);
			glColor3fv(MyColors[idx3]); glVertex3fv(myCube[idx3]);
		glEnd();
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT); // clear
	
	drawCube(0.1, 0, 0, 0);

	glFlush();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	GLfloat f_w = (GLfloat)width / (GLfloat)_WINDOW_WIDTH;
	GLfloat f_h = (GLfloat)height / (GLfloat)_WINDOW_HEIGHT;
	// glOrtho�� �׸��� ���� �ʿ��� 2�� line
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// ��𼭺���, ������ ��� �� ���ΰ�
	glOrtho(-1.0 * f_w, 1.0 * f_w, -1.0 * f_h, 1.0 * f_h, -2, 2);
	// �� 3 : ��𿡼�
	// �߰� 3 : ���� �� ���ΰ�
	// �� 3 : ��� �����ΰ�
	gluLookAt(0.5, 0.5, -1, 0, 0, 0, 0, 1, 0); // ���� ����
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);

	// glutwindowsize�� �� �տ� ���´��� create window !
	glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("title");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// createList();

	glutMainLoop();
	return 0;
}

*/