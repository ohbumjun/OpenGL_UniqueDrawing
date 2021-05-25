
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
	// 1st arg : 1000 --> 1초후 실행 
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

// w,h는 각각 너비와 높이
// api 덕분에 자동으로 인자로 들어오게 된다( openGl이 알아서 바꿔줌 )
void reshape(int w, int h)
{
	// viewport ( display 되는 구간, 화면에 보여지는 구간 )
	// 1st,2nd : x,y 좌표 --> 기준이 되는 좌표 : ( 맨 왼쪽 아래가 기준이되므로, 0.0 )
	glViewport(0,0,w,h);
	// projection (projection matrix )로 바꿀 것이다
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // resets current matrix
	
	// 2차원 좌표계 형태를 사용할 것이며 
	// 양쪽 4개의 점들은 -10 ~ 10 사이의 범위를 지니게 할 것이다 
	gluOrtho2D(-10,10,-10,10);

	// 다시 model_view matrix로
	// default는 modelview 이다. projection을 change할 때에만, 위의 gl_projection을 사용하고, 다시 되돌리자 
	glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
	// 아래의 코드를 통해 display function을 다시 실행
	glutPostRedisplay();

	// 1000/60 : 60 frame per sec 대로 timer 호출 --> smooth한 animation을 구현하기 위한 과정 
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