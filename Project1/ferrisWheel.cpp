/*
#include "cg.h"
#include "draw.h"

int w = 1000;
int h = 1000;
float t = 0.0;

using namespace std;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(0.6, 0.6, 0.6, 1.0);

	// sun
	glColor3f(1.0, 1.0, 0.0);
	circle(vector3D(0, 0, 0), 0.1);
	glPushMatrix();
	line(vector3D(0.8, -0.8, 0), vector3D(-0.8, -0.8, 0));
	line(vector3D(0.0, 0.0, 0), vector3D(-0.8, -0.8, 0));
	line(vector3D(0.0, 0.0, 0), vector3D(0.8, -0.8, 0));
	glPopMatrix();

	//earth
	float cx = 0.0, cy = 0.0, radius = 0.6;
	float px = 0.0, pmx = 0.0;
	float py = 0.0, pmy = 0.0;
	for (float f = 0.0; f < 2 * M_PI; f += M_PI / 6.0) // 6.0 으로 나눈다는 것은 60씩 증가시킨다 --> 12개 그려진다 
	{
		// 원을 나타내는 수식 : x^2  + y^2 = r^2
		// parametric 형식 : X = r * cos (f) -> f: 각도 ( 0 ~ 360 )
		// parametric 형식 : Y = r * sin (f) -> f: 각도 
		px = cx + radius * cos(f);
		py = cx + radius * sin(f);
		// RT 와 TR 의 차이 명심할 것
		glPushMatrix(); // 여기서 push,pop을 안하면, 아래의 transformation이 위에 sun에도 모두 적용되어 버린다
		glRotatef(3.0 * t, 0.0, 0.0, 1.0); // 실제 z축 중심 회전시키기
		line(vector3D(cx, cy, 0), vector3D(px, py, 0));
		glTranslatef(px, py, 0.0);  //instancing --> 우선 태양으로부터 떨어지게 세팅해놓는다
		glColor3f(0.0, 0.0, 1.0);
		circle(vector3D(0, 0, 0), 0.05);

		//moon
		for (float f = 0.0; f < 2 * M_PI; f += M_PI / 45) // 6.0 으로 나눈다는 것은 60씩 증가시킨다 --> 12개 그려진다 
		{
			glPushMatrix(); // --> 위에서 세팅된 x,y,z 에 기초하여 transformation이 이루어질 것이다
			glColor3f(1.0, 0.0, 1.0);
			glRotatef(5 * t, 0.0, 0.0, 1.0);
			pmx = cx + (radius / 4) * cos(f);
			pmy = cx + (radius / 4) * sin(f);
			line(vector3D(cx, cy, 0), vector3D(pmx, pmy, 0));
			glTranslatef(pmx, pmy, 0.0);// instancing
			rect(vector3D(-0.01, 0.02, 0), vector3D(0.01, -0.02, 0));
			glPopMatrix();

		}
		glPopMatrix();
	}

	glutSwapBuffers();
}

void idle()
{
	t += 0.01;
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

