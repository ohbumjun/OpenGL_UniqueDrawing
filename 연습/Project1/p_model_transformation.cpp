// 모델 변환 실습 
#include "cg.h"
#include "math.h"

/*
#define _WINDOW_HEIGHT 600
#define _WINDOW_WIDTH  600



int angle_upper=0;
int angle_low=0;

int dir_upper = 1;
int dir_low = 4;

// cam : 어디서 보느냐
// ex) 0.5, -0.5 ,1 : 밑에서 위를 보기 
GLfloat camx = 0.5, camy = -0.5, camz = 1;
// center : 어디를 보느냐 
GLfloat cam2x = 0, cam2y = 0, cam2z = 0;// 원점 바라봄
// cam_up : 어디가 위쪽이냐
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

int list_id;
int w = 1024;
int h = 1024;

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
	glColor3f(1,1,1);

	// matrix 그리기 x,y,z 축 초기화 
	// glMatrixMode(GL_MODELVIEW); 
	// glLoadIdentity();

	// x축 방향  -> y,z는 rotate 를 통해 구현
	drawXAxis();
	// y축
	glRotatef(90,0,0,1); // x축을 y축으로 만드려면, z축 기준 돌려야 한다 
	drawXAxis();
	glRotatef(-90, 0, 0, 1); // 원상태로 되돌리기(이 과정이 없으면, 복합 변환이 되버린다 ) 
	// z 축 
	glRotatef(-90, 0, 1, 0); 
	drawXAxis();
	glRotatef(90, 0, 1, 0);

	//돌리고, 원상태로 해주는
	//코드의 세트가 사실, 편하지는 않기 때문에
	//drawXAxis();
	//glPushMatrix();
	//	glRotatef(90,0,0,1);  
	//	drawXAxis();
	//glPopMatrix();
	//glPushMatrix();
	//	glRotatef(-90, 0, 1, 0);
	//	drawXAxis();
	//glPopMatrix();

	//와 같이 
	//Matrix  push 하여 저장했다가,pop 시켜주는 방식의
	//코드를 작성하기도 한다 

	glEnd();
}

void drawCube()
{
	glScalef(2,1,1); // x축으로 2배 늘리기
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

void drawUpperArm(GLfloat angle)
{
	// 이동 부분 
	// 1) 만일, 회전없이 그냥 몸통 사각형 오른쪽 위에 붙일 때 
	// cube 위치가 x축으로 2, wirecube는 0.25배 
	//-->> 2 * 0.25 = 0.5
	// glTranslatef(0.5,0.4,0); 

	// 2) 회전을 시키고자 할때
	glTranslatef(0.25, 0.2, 0); // 이동 
	glRotatef(angle, 0, 0, 1); // z축 기준 회전 
	glTranslatef(0.25, 0.0, 0); // 이동

	drawCuboid(0.5,0.2,0.2);
}

// 회전할 각도 지정 
void drawLowerArm(GLfloat angle)
{
	// drawAxis();
	glTranslatef(0.25, 0.0, 0); // 이동 
	glRotatef(angle, 0, 0, 1); // z축 기준 회전 
	glTranslatef(0.25, 0.0, 0); // 이동
	// drawAxis();
	drawCuboid(0.5, 0.2, 0.2);
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

void drawHand()
{
	// drawAxis();
	// 구.를 그리기
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

	// 1_ animation에 따른 카메라 각도 변환을 구현하기 위해서는
	// gluLookAt을 display 함수에 넣어주어야 한다 
	// 2) glMatrixMode(GL_MODELVIEW); 안에다가 넣어주어야 한다
	// 밖에 넣어주면, glLoadIdentity 에 의해, 좌표값 관련 세팅이 초기화되기 때문
	// 앞 3 : 어디에서
	// 중간 3 : 어디로 볼 것인가
	// 뒤 3 : 어디가 위쪽인가 ( 0,1,0 : y축이 위쪽이다 ) 
	gluLookAt(
		camx, camy, camz,
		cam2x, cam2y, cam2z,
		cam_upx, cam_upy, cam_upz
	); // 보는 방향

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
	// glOrtho를 그리기 위해 필요한 2개 line
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// 어디서부터, 어디까지 어떻게 볼 것인가 : -2  ~ 2
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

	// 카메라 회전 animation 
	// 세로 y축을 기준으로
	// y좌표는 그대로 있고 
	// y 축 기준 돌아가면서 돌기 
	GLfloat theta = 0.01;
	camx = camx * cos(theta) + camz * sin(theta) ;
	camz = -camx * sin(theta) + camz * cos(theta) ;

	// 참고 : 카메라 변환 애니메이션은 
	// 별도 timer func 둬도 된다 
	glutTimerFunc(1000/60, MyTimer, 1);
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);

	// glutwindowsize가 맨 앞에 나온다음 create window !
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