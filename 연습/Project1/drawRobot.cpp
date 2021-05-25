#include "cg.h"
#include "drawRobot.h"
#include "vec.h"

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
	glColor3f(1, 1, 1);

	// matrix �׸��� x,y,z �� �ʱ�ȭ 
	// glMatrixMode(GL_MODELVIEW); 
	// glLoadIdentity();

	// x�� ����  -> y,z�� rotate �� ���� ����
	drawXAxis();
	// y��
	glRotatef(90, 0, 0, 1); // x���� y������ �������, z�� ���� ������ �Ѵ� 
	drawXAxis();
	glRotatef(-90, 0, 0, 1); // �����·� �ǵ�����(�� ������ ������, ���� ��ȯ�� �ǹ����� ) 
	// z �� 
	glRotatef(-90, 0, 1, 0);
	drawXAxis();
	glRotatef(90, 0, 1, 0);

	glEnd();
}


void drawCube()
{
	glScalef(2, 1, 1); // x������ 2�� �ø���
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

void drawUpperRightArm(GLfloat z_angle , GLfloat y_angle)
{
	// �̵� �κ� 
	// 1) ����, ȸ������ �׳� ���� �簢�� ������ ���� ���� �� 
	// cube ��ġ�� x������ 2, wirecube�� 0.25�� 
	//-->> 2 * 0.25 = 0.5
	// glTranslatef(0.5,0.4,0); 

	// 2) ȸ���� ��Ű���� �Ҷ�
	glTranslatef(0.25, 0.2, 0); // �̵� 
	glRotatef(y_angle, 0, 1, 0); // y�� ���� ȸ�� 
	glRotatef(z_angle, 0, 0, 1); // z�� ���� ȸ�� 
	glTranslatef(0.25, 0.0, 0); // �̵�
	drawCuboid(0.5, 0.2, 0.2);
}

void drawUpperLeftArm(GLfloat z_angle, GLfloat y_angle)
{
	glTranslatef(-0.25, 0.2, 0); // �̵� 
	glRotatef(y_angle, 0, 1, 0); // y�� ���� ȸ�� 
	glRotatef(z_angle, 0, 0, 1); // z�� ���� ȸ�� 
	glTranslatef(-0.25, 0.0, 0); // �̵�
	drawCuboid(0.5, 0.2, 0.2);
}

// ȸ���� ���� ���� 
void drawLowerRightArm(GLfloat angle)
{
	// drawAxis();
	glTranslatef(0.25, 0.0, 0); // �̵� 
	glRotatef(angle, 0, 1, 0); // y�� ���� ȸ�� 
	glTranslatef(0.25, 0.0, 0); // �̵�
	// drawAxis();
	drawCuboid(0.5, 0.2, 0.2);
}
void drawLowerLeftArm(GLfloat angle)
{
	// drawAxis();
	glTranslatef(-0.25, 0.0, 0); // �̵� 
	glRotatef(angle, 0, 1, 0); // y�� ���� ȸ�� 
	glTranslatef(-0.25, 0.0, 0); // �̵�
	// drawAxis();
	drawCuboid(0.5, 0.2, 0.2);
}
void drawRightHand()
{
	// drawAxis();
	// ��.�� �׸���
	glTranslatef(0.35, 0, 0);
	glutWireSphere(0.1, 15, 15);
	// drawAxis();
}
void drawLeftHand()
{
	// drawAxis();
	// ��.�� �׸���
	glTranslatef(-0.35, 0, 0);
	glutWireSphere(0.1, 15, 15);
	// drawAxis();
}

void drawUpperRightLeg(GLfloat angle)
{
	// 2) ȸ���� ��Ű���� �Ҷ�
	glTranslatef(0.15, -1.1, 0); // �̵� 
	glRotatef(angle, 0, 0, 1); // z�� ���� ȸ�� 
	glTranslatef(0.25, 0.0, 0); // �̵�
	drawCuboid(0.7, 0.2, 0.2);
}

void drawUpperLeftLeg(GLfloat angle)
{
	glTranslatef(-0.15, -1.1, 0); // �̵� 
	glRotatef(angle, 0, 0, 1); // z�� ���� ȸ�� 
	glTranslatef(0.25, 0.0, 0); // �̵�
	drawCuboid(0.7, 0.2, 0.2);
}

// ȸ���� ���� ���� 
void drawLowerRightLeg(GLfloat angle)
{
	// drawAxis();
	//glTranslatef(0, 0.25, 0); // �̵� 
	//glRotatef(angle, 0, 0, 1); // z�� ���� ȸ�� 
	glTranslatef(-0.7, 0.0, 0); // �̵�
	// drawAxis();
	drawCuboid(0.7, 0.2, 0.2);
}
void drawLowerLeftLeg(GLfloat angle)
{
	// drawAxis();
	//glTranslatef(0, 0.25, 0); // �̵� 
	//glRotatef(angle, 0, 0, 1); // z�� ���� ȸ�� 
	glTranslatef(-0.7, 0.0, 0); // �̵�
	// drawAxis();
	drawCuboid(0.7, 0.2, 0.2);
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

void drawHead()
{
	glPushMatrix();
		glTranslatef(0.0, 0.55, 0);
		glutWireSphere(0.07, 15, 15);
		glTranslatef(0.0, 0.2, 0);
		glutWireCube(0.3);
	glPopMatrix();
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