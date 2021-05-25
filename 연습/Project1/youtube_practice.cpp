
/*

#include "cg.h"

void display();
void reshape(int,int);
void timer(int);

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.1);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(200,100);
	glutInitWindowSize(500,500);

	glutCreateWindow("Window 1");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	// 1st arg : 1000 --> 1���� ���� 
	// 2nd : function
	// 3rd : param passed into function
	glutTimerFunc(1000, timer, 0); 
	init();
	glutMainLoop();
}

float x_position = -10.0;
int state = 1;

void display()
{
	// clear frame buffer( clear the screen )
	glClear(GL_COLOR_BUFFER_BIT);
	// reset all the transforation of current method
	glLoadIdentity();

	// draw 
	glBegin(GL_POLYGON);

	glVertex2f(x_position, 1.0);
	glVertex2f(x_position,-1.0);
	glVertex2f(x_position + 2.0, -1.0);
	glVertex2f(x_position + 2.0,  1.0);

	glEnd();

	glutSwapBuffers();
}

// w,h�� ���� �ʺ�� ����
// api ���п� �ڵ����� ���ڷ� ������ �ȴ�( openGl�� �˾Ƽ� �ٲ��� )
void reshape(int w, int h)
{
	// viewport ( display �Ǵ� ����, ȭ�鿡 �������� ���� )
	// 1st,2nd : x,y ��ǥ --> ������ �Ǵ� ��ǥ : ( �� ���� �Ʒ��� �����̵ǹǷ�, 0.0 )
	glViewport(0,0,w,h);
	// projection (projection matrix )�� �ٲ� ���̴�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // resets current matrix
	
	// 2���� ��ǥ�� ���¸� ����� ���̸� 
	// ���� 4���� ������ -10 ~ 10 ������ ������ ���ϰ� �� ���̴� 
	gluOrtho2D(-10,10,-10,10);

	// �ٽ� model_view matrix��
	// default�� modelview �̴�. projection�� change�� ������, ���� gl_projection�� ����ϰ�, �ٽ� �ǵ����� 
	glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
	// �Ʒ��� �ڵ带 ���� display function�� �ٽ� ����
	glutPostRedisplay();

	// 1000/60 : 60 frame per sec ��� timer ȣ�� --> smooth�� animation�� �����ϱ� ���� ���� 
	glutTimerFunc(1000/60,timer,0);

	// x pos update
	switch (state)
	{
	case 1 :
		if (x_position < 8)
			x_position += 0.15;
		else
			state = -1;
		break;
	case -1 :
		if (x_position > -10)
			x_position -= 0.15;
		else 
			state = 1;
	}
	
}

*/