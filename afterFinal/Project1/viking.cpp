/*

#include "cg.h"
#include "draw.h"

int w = 1000;
int h = 1000;
float t  = 0.0;
float tI = 0.01;

using namespace std;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(0.6, 0.6, 0.6, 1.0);
	// center
	glColor3f(1.0, 1.0, 1.0);
	circle(vector3D(0, 0, 0), 0.1);
	glPushMatrix();
		line(vector3D(0.5, -0.5, 0), vector3D(-0.5, -0.5, 0));
		line(vector3D(0.0, 0.0, 0), vector3D(-0.5, -0.5, 0));
		line(vector3D(0.0, 0.0, 0), vector3D(0.5, -0.5, 0));
	glPopMatrix();

	

	// boat center
	glPushMatrix(); // 여기서 push,pop을 안하면, 아래의 transformation이 위에 sun에도 모두 적용되어 버린다
	glRotatef(3.0 * t, 0.0, 0.0, 1.0); // 실제 z축 중심 회전시키기
	line(vector3D(0,0,0), vector3D(0,-0.4,0));
	glTranslatef(0.0, -0.4, 0.0);  //instancing --> 우선 태양으로부터 떨어지게 세팅해놓는다
	glColor3f(0.0, 0.0, 1.0);
	ellipse(vector3D(0,0,0),0.1,0.05);

	// boat right
	glPushMatrix();
		glRotatef(-15, 0.0, 0.0, 1.0); // instancing  : 방향선정
		glTranslatef(-0.2, 0.0, 0.0);   // instancing  : 위치선정
		ellipse(vector3D(0, 0, 0), 0.1, 0.05);
		glPushMatrix();
			glRotatef(-15, 0.0, 0.0, 1.0); // instancing  : 방향선정
			glTranslatef(-0.2, 0.0, 0.0);   // instancing  : 위치선정
			ellipse(vector3D(0, 0, 0), 0.1, 0.05);
		glPopMatrix();
	glPopMatrix();

	// boat left
	glPushMatrix();
		glRotatef(15, 0.0, 0.0, 1.0); // instancing  : 방향선정
		glTranslatef(0.2, 0.0, 0.0);   // instancing  : 위치선정
		ellipse(vector3D(0, 0, 0), 0.1, 0.05);
		glPushMatrix();
			glRotatef(15, 0.0, 0.0, 1.0); // instancing  : 방향선정
			glTranslatef(0.2, 0.0, 0.0);   // instancing  : 위치선정
			ellipse(vector3D(0, 0, 0), 0.1, 0.05);
		glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

void idle()
{
	t += tI;
	if (t <= -20|| t >= 20) tI *= -1;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(w, h);
	glutCreateWindow("transformations");

	glMatrixMode(GL_MODELVIEW);

	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glutMainLoop();
}

*/