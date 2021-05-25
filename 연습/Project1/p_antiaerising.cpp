// 모델 변환 실습 
/*
#include "cg.h"
#include "math.h"
#include <stdio.h>

#define _WINDOW_HEIGHT 700
#define _WINDOW_WIDTH  700

int angle_upper = 0;
int angle_low = 0;

int dir_upper = 1;
int dir_low = 4;


// cam : 어디서 보느냐
// ex) 0.5, -0.5 ,1 : 밑에서 위를 보기 
GLfloat camx = 0.5, camy = 1, camz = 2;
// center : 어디를 보느냐 
GLfloat cam2x = 0, cam2y = 0, cam2z = 0;// 원점 바라봄
// cam_up : 어디가 위쪽이냐
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

int list_id;
int w = 1024;
int h = 1024;

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT );
	
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	// Blend 효과 넣어주기
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glPointSize(10);
	// 점 : blend 없으면 사각형 그려짐
	// blend를 통해 원을 그리기 
	glBegin(GL_POINTS);
		glVertex3f(0,0,0);
	glEnd();

	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	// 위에서 glEnable(GL_LINE_SMOOTH)
	// 과정을 거치지 않으면, 즉, 안티에어리싱 과정이 없으면 
	// 옆으로 꺾여서 가는 선들은 지그재그임을 확인할수 있다
	glVertex3f(0, 0, 0);
	glVertex3f(2, 2, 0);
	glEnd();

	glFlush();
}

void MyReshape(int width, int height)
{
	// glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	GLfloat left = 0, bottom = 0;
	glViewport(left, bottom, width - left, height - bottom);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(-2,2,-2,2,-2,2);

}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	// GLUT_DEPTH : 깊이 버퍼를 사용하겠다 
	glutInitDisplayMode(GLUT_RGB);

	// glutwindowsize가 맨 앞에 나온다음 create window !
	glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("title");

	glClearColor(-.5, 0.5, 0.5, 0.0); // 배경화면 

	// 빛을 효과 
	

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);

	// 절단면 몇개 쓸 수 있는지 확인하기 
	int num;
	glGetIntegerv(GL_MAX_CLIP_PLANES, &num);
	printf("num of clip planes : %d", num);

	glutMainLoop();
	return 0;
}

*/