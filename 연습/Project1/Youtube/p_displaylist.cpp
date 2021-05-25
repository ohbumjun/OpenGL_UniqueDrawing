// 디스플레이 리스트
// display function 에서
// 계산을 줄이기 위한 setting 
// Display 콜백함수에서, Object 의 색상 점등을 계산하면
// display 시 load가 커진다
// Object 수가 많아지고, 복잡해질 수록, 속도도 저하된다
// Object를 미리 만들어서, list에 넣어두고, 콜백함수에서는 이를 재사용한다 ( cache의 개념 ) 

/*
< 코드 >
int list_id; // 전역 변수 생성
void createList() { // 함수이름은 바뀌어도 된다 
	list_id = glGenLists(1); // list 1개 생성 
	glNewList(list_id, GL_COMPILE) { // 리스트의 시작, 컴파일만 수행용
		glBegin(GL_POLYGON);
		//  그릴 내용 넣기
		glEnd();
		glEndList(); // 리스트 종료
	}
}
createList(); // Object 리스트 생성
glCallList(list_id); // Object List에 있는 내용 그리기, display 콜백 함수 등에서 호출 
*/

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

void drawCube(GLfloat size, GLfloat x, GLfloat y, GLfloat z)
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
	gluLookAt(0.5, 0.5, 1, 0, 0, 0, 0, 1, 0); // 보는 방향
}

void createList() {
	list_id = glGenLists(1);
	// 실행은 안하고, 미리 세팅만 시켜두기
	glNewList(list_id, GL_COMPILE);
		drawCube(0.4, 0, 0, 0);
		drawCube(0.2, 0.1, 0, 0);
		drawCube(0.1, 0, 0.1, 0);
		drawCube(0.1, 0, 0, 0.1);
		drawCube(0.1, 0.1, 0.1, 0.1);
	glEndList();
}


void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT); // clear
	// list 를 그려라 !
	glCallList(list_id);
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);

	glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("title");

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(reshape);

	createList();
	

	glutMainLoop();
	return 0;
}

*/