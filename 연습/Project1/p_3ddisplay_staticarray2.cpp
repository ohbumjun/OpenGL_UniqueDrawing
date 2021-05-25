// 3d 정육면체 그리기
// 8개 정점
// 6개 면 

/*
#include "cg.h"

#define _WINDOW_HEIGHT 1200
#define _WINDOW_WIDTH  1200

int list_id;
int w = 1024;
int h = 1024;

GLfloat myCube[8][3];
GLfloat defaultCube[8][3] = {
	// 한면의 너비가 1 로 되어있다 
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
	// 크기조정 : size 만큼 한변의 길이를 조정한다 : defaultCube 값에 size를 곱해주면 된다. 현재 myCube 한변의 길이가 1 이기 때문에
	// 이동 : x축으로는 x, y축으로는 y, z축으로는 z만큼 이동한다 : + 를 해주면 된다
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
	// 정육면체를 그리기 위해서는, 6개의 면을 그려야한다
	// 즉, 4개 정점을 6번 찍어야 한다는 것이다
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
	// glOrtho를 그리기 위해 필요한 2개 line
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// 어디서부터, 어디까지 어떻게 볼 것인가
	glOrtho(-1.0 * f_w, 1.0 * f_w, -1.0 * f_h, 1.0 * f_h, -2, 2);
	// 앞 3 : 어디에서
	// 중간 3 : 어디로 볼 것인가
	// 뒤 3 : 어디가 위쪽인가
	gluLookAt(0.5, 0.5, -1, 0, 0, 0, 0, 1, 0); // 보는 방향
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);

	// glutwindowsize가 맨 앞에 나온다음 create window !
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