// �� ��ȯ �ǽ� 
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


// cam : ��� ������
// ex) 0.5, -0.5 ,1 : �ؿ��� ���� ���� 
GLfloat camx = 0.5, camy = 1, camz = 2;
// center : ��� ������ 
GLfloat cam2x = 0, cam2y = 0, cam2z = 0;// ���� �ٶ�
// cam_up : ��� �����̳�
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

int list_id;
int w = 1024;
int h = 1024;

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT );
	
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	// Blend ȿ�� �־��ֱ�
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glPointSize(10);
	// �� : blend ������ �簢�� �׷���
	// blend�� ���� ���� �׸��� 
	glBegin(GL_POINTS);
		glVertex3f(0,0,0);
	glEnd();

	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	// ������ glEnable(GL_LINE_SMOOTH)
	// ������ ��ġ�� ������, ��, ��Ƽ����� ������ ������ 
	// ������ ������ ���� ������ ����������� Ȯ���Ҽ� �ִ�
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
	// GLUT_DEPTH : ���� ���۸� ����ϰڴ� 
	glutInitDisplayMode(GLUT_RGB);

	// glutwindowsize�� �� �տ� ���´��� create window !
	glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("title");

	glClearColor(-.5, 0.5, 0.5, 0.0); // ���ȭ�� 

	// ���� ȿ�� 
	

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);

	// ���ܸ� � �� �� �ִ��� Ȯ���ϱ� 
	int num;
	glGetIntegerv(GL_MAX_CLIP_PLANES, &num);
	printf("num of clip planes : %d", num);

	glutMainLoop();
	return 0;
}

*/