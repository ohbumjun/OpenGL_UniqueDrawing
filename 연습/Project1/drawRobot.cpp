#include "cg.h"
#include "drawRobot.h"
#include "vec.h"

void drawXAxis()
{
	glBegin(GL_LINES);
	// x축 방향 
	glVertex3f(0, 0, 0);
	glVertex3f(0.2, 0, 0);
	glVertex3f(0.2, 0, 0);
	glVertex3f(0.18, 0.03, 0);
	glVertex3f(0.2, 0, 0);
	glVertex3f(0.18, -0.03, 0);
	glEnd();
}

// 축 그리기
void drawAxis()
{
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);

	// matrix 그리기 x,y,z 축 초기화 
	// glMatrixMode(GL_MODELVIEW); 
	// glLoadIdentity();

	// x축 방향  -> y,z는 rotate 를 통해 구현
	drawXAxis();
	// y축
	glRotatef(90, 0, 0, 1); // x축을 y축으로 만드려면, z축 기준 돌려야 한다 
	drawXAxis();
	glRotatef(-90, 0, 0, 1); // 원상태로 되돌리기(이 과정이 없으면, 복합 변환이 되버린다 ) 
	// z 축 
	glRotatef(-90, 0, 1, 0);
	drawXAxis();
	glRotatef(90, 0, 1, 0);

	glEnd();
}


void drawCube()
{
	glScalef(2, 1, 1); // x축으로 2배 늘리기
	glRotatef(30, 0, 0, 1);  // 회전하고
	glTranslatef(0.3, 0, 0); // 이동시키고

	// 하지만,우리가 적용한 것 반대로 적용되기 때문에
	// 1.이동 + 2. 해당 위치에서 회전 + 3. size 늘리기
	glutWireCube(0.2);
}

void drawCuboid(GLfloat sx, GLfloat sy, GLfloat sz)
{
	// 몸 파트 부분에 해당하는, 직육면체 그리기 
	glPushMatrix();
	glScalef(sx, sy, sz);
	glutWireCube(1);
	glPopMatrix();
}

void drawUpperRightArm(GLfloat z_angle , GLfloat y_angle)
{
	// 이동 부분 
	// 1) 만일, 회전없이 그냥 몸통 사각형 오른쪽 위에 붙일 때 
	// cube 위치가 x축으로 2, wirecube는 0.25배 
	//-->> 2 * 0.25 = 0.5
	// glTranslatef(0.5,0.4,0); 

	// 2) 회전을 시키고자 할때
	glTranslatef(0.25, 0.2, 0); // 이동 
	glRotatef(y_angle, 0, 1, 0); // y축 기준 회전 
	glRotatef(z_angle, 0, 0, 1); // z축 기준 회전 
	glTranslatef(0.25, 0.0, 0); // 이동
	drawCuboid(0.5, 0.2, 0.2);
}

void drawUpperLeftArm(GLfloat z_angle, GLfloat y_angle)
{
	glTranslatef(-0.25, 0.2, 0); // 이동 
	glRotatef(y_angle, 0, 1, 0); // y축 기준 회전 
	glRotatef(z_angle, 0, 0, 1); // z축 기준 회전 
	glTranslatef(-0.25, 0.0, 0); // 이동
	drawCuboid(0.5, 0.2, 0.2);
}

// 회전할 각도 지정 
void drawLowerRightArm(GLfloat angle)
{
	// drawAxis();
	glTranslatef(0.25, 0.0, 0); // 이동 
	glRotatef(angle, 0, 1, 0); // y축 기준 회전 
	glTranslatef(0.25, 0.0, 0); // 이동
	// drawAxis();
	drawCuboid(0.5, 0.2, 0.2);
}
void drawLowerLeftArm(GLfloat angle)
{
	// drawAxis();
	glTranslatef(-0.25, 0.0, 0); // 이동 
	glRotatef(angle, 0, 1, 0); // y축 기준 회전 
	glTranslatef(-0.25, 0.0, 0); // 이동
	// drawAxis();
	drawCuboid(0.5, 0.2, 0.2);
}
void drawRightHand()
{
	// drawAxis();
	// 구.를 그리기
	glTranslatef(0.35, 0, 0);
	glutWireSphere(0.1, 15, 15);
	// drawAxis();
}
void drawLeftHand()
{
	// drawAxis();
	// 구.를 그리기
	glTranslatef(-0.35, 0, 0);
	glutWireSphere(0.1, 15, 15);
	// drawAxis();
}

void drawUpperRightLeg(GLfloat angle)
{
	// 2) 회전을 시키고자 할때
	glTranslatef(0.15, -1.1, 0); // 이동 
	glRotatef(angle, 0, 0, 1); // z축 기준 회전 
	glTranslatef(0.25, 0.0, 0); // 이동
	drawCuboid(0.7, 0.2, 0.2);
}

void drawUpperLeftLeg(GLfloat angle)
{
	glTranslatef(-0.15, -1.1, 0); // 이동 
	glRotatef(angle, 0, 0, 1); // z축 기준 회전 
	glTranslatef(0.25, 0.0, 0); // 이동
	drawCuboid(0.7, 0.2, 0.2);
}

// 회전할 각도 지정 
void drawLowerRightLeg(GLfloat angle)
{
	// drawAxis();
	//glTranslatef(0, 0.25, 0); // 이동 
	//glRotatef(angle, 0, 0, 1); // z축 기준 회전 
	glTranslatef(-0.7, 0.0, 0); // 이동
	// drawAxis();
	drawCuboid(0.7, 0.2, 0.2);
}
void drawLowerLeftLeg(GLfloat angle)
{
	// drawAxis();
	//glTranslatef(0, 0.25, 0); // 이동 
	//glRotatef(angle, 0, 0, 1); // z축 기준 회전 
	glTranslatef(-0.7, 0.0, 0); // 이동
	// drawAxis();
	drawCuboid(0.7, 0.2, 0.2);
}

// pipeline
// body 그리고 -> 좌표축 x,y,z 기준 이동시키면서 upperArm 그리고 
// --> axis 그리고 ( glMatrixMode를 통한 초기화 생략 ) -->  변경된 x,y,z 기준으로 하여 LowerArm 그리고 

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