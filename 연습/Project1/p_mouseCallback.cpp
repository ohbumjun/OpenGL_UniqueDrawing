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
			// glutWireSphere : 원을 그리는 함수
			// radius : 구의 반지름 설정하기
			// slices : 구의 중심을 따라, 세로로 세분화할 면의 수 지정 ( 경선 )
			// stacks : 구의 중심에 평행하게 , 가로로 세분화할 면의 수 지정( 위선 ) 
			glutWireSphere(1.0, 15, 15);
		else if (mode == 1)
			glutWireTeapot(0.7);
	}
	else {
		// 그외에는 안그려준다 
	}
	
	// mode가 2라면 아무것도 안그리기 때문에, 자동적으로 지워지는 효과 
	glFlush();
}

void mouseBtn(int btn,int states, int x, int y)
{
	// 마우스 누를 때 도형 바꾸기 
	// 왼쪽 마우스 버튼, 마우스에서 손 땔때
	if (btn == GLUT_LEFT_BUTTON && states == GLUT_UP)
	{
		mode = (mode + 1) % 2;
		// 새로 다시 그리기
		glutPostRedisplay();
	}
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

void winEntry(int state)
{
	// window 창 밖으로 나가게 된다면 
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