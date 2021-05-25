// �� ��ȯ �ǽ� 
#include "cg.h"
#include "math.h"

/*
#define _WINDOW_HEIGHT 600
#define _WINDOW_WIDTH  600



int angle_upper=0;
int angle_low=0;

int dir_upper = 1;
int dir_low = 4;

// cam : ��� ������
// ex) 0.5, -0.5 ,1 : �ؿ��� ���� ���� 
GLfloat camx = 0.5, camy = -0.5, camz = 1;
// center : ��� ������ 
GLfloat cam2x = 0, cam2y = 0, cam2z = 0;// ���� �ٶ�
// cam_up : ��� �����̳�
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

int list_id;
int w = 1024;
int h = 1024;

void drawXAxis()
{
	glBegin(GL_LINES);
		// x�� ���� 
		glVertex3f(0, 0, 0);
		glVertex3f(0.2, 0, 0);
		glVertex3f(0.2, 0, 0);
		glVertex3f(0.18, 0.03, 0);
		glVertex3f(0.2, 0, 0);
		glVertex3f(0.18, -0.03, 0);
	glEnd();
}

// �� �׸���
void drawAxis()
{
	glBegin(GL_LINES);
	glColor3f(1,1,1);

	// matrix �׸��� x,y,z �� �ʱ�ȭ 
	// glMatrixMode(GL_MODELVIEW); 
	// glLoadIdentity();

	// x�� ����  -> y,z�� rotate �� ���� ����
	drawXAxis();
	// y��
	glRotatef(90,0,0,1); // x���� y������ �������, z�� ���� ������ �Ѵ� 
	drawXAxis();
	glRotatef(-90, 0, 0, 1); // �����·� �ǵ�����(�� ������ ������, ���� ��ȯ�� �ǹ����� ) 
	// z �� 
	glRotatef(-90, 0, 1, 0); 
	drawXAxis();
	glRotatef(90, 0, 1, 0);

	//������, �����·� ���ִ�
	//�ڵ��� ��Ʈ�� ���, �������� �ʱ� ������
	//drawXAxis();
	//glPushMatrix();
	//	glRotatef(90,0,0,1);  
	//	drawXAxis();
	//glPopMatrix();
	//glPushMatrix();
	//	glRotatef(-90, 0, 1, 0);
	//	drawXAxis();
	//glPopMatrix();

	//�� ���� 
	//Matrix  push �Ͽ� �����ߴٰ�,pop �����ִ� �����
	//�ڵ带 �ۼ��ϱ⵵ �Ѵ� 

	glEnd();
}

void drawCube()
{
	glScalef(2,1,1); // x������ 2�� �ø���
	glRotatef(30, 0, 0, 1);  // ȸ���ϰ�
	glTranslatef(0.3, 0, 0); // �̵���Ű��

	// ������,�츮�� ������ �� �ݴ�� ����Ǳ� ������
	// 1.�̵� + 2. �ش� ��ġ���� ȸ�� + 3. size �ø���
	glutWireCube(0.2);
}

void drawCuboid(GLfloat sx, GLfloat sy, GLfloat sz)
{
	// �� ��Ʈ �κп� �ش��ϴ�, ������ü �׸��� 
	glPushMatrix();
		glScalef(sx, sy, sz);
		glutWireCube(1);
	glPopMatrix();
}

void drawUpperArm(GLfloat angle)
{
	// �̵� �κ� 
	// 1) ����, ȸ������ �׳� ���� �簢�� ������ ���� ���� �� 
	// cube ��ġ�� x������ 2, wirecube�� 0.25�� 
	//-->> 2 * 0.25 = 0.5
	// glTranslatef(0.5,0.4,0); 

	// 2) ȸ���� ��Ű���� �Ҷ�
	glTranslatef(0.25, 0.2, 0); // �̵� 
	glRotatef(angle, 0, 0, 1); // z�� ���� ȸ�� 
	glTranslatef(0.25, 0.0, 0); // �̵�

	drawCuboid(0.5,0.2,0.2);
}

// ȸ���� ���� ���� 
void drawLowerArm(GLfloat angle)
{
	// drawAxis();
	glTranslatef(0.25, 0.0, 0); // �̵� 
	glRotatef(angle, 0, 0, 1); // z�� ���� ȸ�� 
	glTranslatef(0.25, 0.0, 0); // �̵�
	// drawAxis();
	drawCuboid(0.5, 0.2, 0.2);
}

// pipeline
// body �׸��� -> ��ǥ�� x,y,z ���� �̵���Ű�鼭 upperArm �׸��� 
// --> axis �׸��� ( glMatrixMode�� ���� �ʱ�ȭ ���� ) -->  ����� x,y,z �������� �Ͽ� LowerArm �׸��� 

void drawBody()
{
	glPushMatrix();
		glScalef(2, 4, 1);
		glutWireCube(0.25);
	glPopMatrix();
}

void drawHand()
{
	// drawAxis();
	// ��.�� �׸���
	glTranslatef(0.35, 0, 0);
	glutWireSphere(0.1,15,15);
	drawAxis();
}

void drawFinger()
{
	glTranslatef(0.15, 0, 0);
	drawCuboid(0.1, 0.02, 0.02);
}
void drawFinger2()
{
	glRotatef(30, 0, 0, 1);
	glTranslatef(0.15, 0, 0);
	drawCuboid(0.1, 0.02, 0.02);
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT); // clear

	// drawAxis();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// 1_ animation�� ���� ī�޶� ���� ��ȯ�� �����ϱ� ���ؼ���
	// gluLookAt�� display �Լ��� �־��־�� �Ѵ� 
	// 2) glMatrixMode(GL_MODELVIEW); �ȿ��ٰ� �־��־�� �Ѵ�
	// �ۿ� �־��ָ�, glLoadIdentity �� ����, ��ǥ�� ���� ������ �ʱ�ȭ�Ǳ� ����
	// �� 3 : ��𿡼�
	// �߰� 3 : ���� �� ���ΰ�
	// �� 3 : ��� �����ΰ� ( 0,1,0 : y���� �����̴� ) 
	gluLookAt(
		camx, camy, camz,
		cam2x, cam2y, cam2z,
		cam_upx, cam_upy, cam_upz
	); // ���� ����

	drawBody();
	
	drawUpperArm(angle_upper);
	drawLowerArm(angle_low);
	drawHand();
	glPushMatrix();
		drawFinger();
	glPopMatrix();
	glPushMatrix();
		drawFinger2();
	glPopMatrix();
	
	// glFlush();
	glutSwapBuffers();
}

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

void MyTimer(int value )
{
	angle_upper += dir_upper;
	angle_low += dir_low;
	if (angle_upper >= 90)
		dir_upper = -1;
	else if (angle_upper < -30)
		dir_upper = 1;

	if (angle_low >= 120)
		dir_low = -4;
	else if (angle_low < 0)
		dir_low = 4;

	// ī�޶� ȸ�� animation 
	// ���� y���� ��������
	// y��ǥ�� �״�� �ְ� 
	// y �� ���� ���ư��鼭 ���� 
	GLfloat theta = 0.01;
	camx = camx * cos(theta) + camz * sin(theta) ;
	camz = -camx * sin(theta) + camz * cos(theta) ;

	// ���� : ī�޶� ��ȯ �ִϸ��̼��� 
	// ���� timer func �ֵ� �ȴ� 
	glutTimerFunc(1000/60, MyTimer, 1);
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);

	// glutwindowsize�� �� �տ� ���´��� create window !
	glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("title");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutTimerFunc(20,MyTimer,1);

	// createList();

	glutMainLoop();
	return 0;
}

*/