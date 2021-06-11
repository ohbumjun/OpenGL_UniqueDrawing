
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
	// 미해결과제 : mouseDrag 일때, mouseFunc 도 같이 실행, 즉, callback 함수가 2개가 동시 실행
	// 이를 방지할 수 있는 방법이 없을까 ?
	std::cout << "mouseDrag x,y" << x << y << std::endl;
	std::cout << "mouseDrag cur_x, cur_y" << cur_x << cur_y << std::endl;

	// 마우스 움직임에 따라 색상 변화
	// x,y : 가장 최근의 x,y 좌표
	GLint dx, dy; // 변화 정도

	if (cur_x >= 0 || cur_y >= 0)
	{
		// 드래그 량의 차이
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
	// Exit 이면 빠져나가기
	if (value == 2)
		exit(0);
}
void selectSubMenu(int value) {
	// 선택한 도형으로 mode 지정 
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
		glutSetMenu(subMenuId);// 현재 메뉴 지정 
		glutAttachMenu(GLUT_RIGHT_BUTTON);// menu 를 마우스 버튼에 등록
		// 3D Model을 클릭시, 아래의 3개 subMenu가 나오는 것이다 
		glutAddMenuEntry("Sphere", 1); // 메뉴에 내용 넣어주기
		glutAddMenuEntry("Torus", 2);
		glutAddMenuEntry("Teaport", 3);

	int mainMenuId = glutCreateMenu(selectMenu);
		glutSetMenu(mainMenuId);// 현재 메뉴 지정 
		glutAttachMenu(GLUT_RIGHT_BUTTON);// menu 를 마우스 버튼에 등록
		glutAddSubMenu("3D Model", subMenuId); // 메뉴에 내용 넣어주기
		glutAddMenuEntry("Exit",2); 

	

	glutMainLoop();
	return 0;
}


*/