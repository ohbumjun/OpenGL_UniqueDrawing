
#include "cg.h"
#include "draw.h"
#include "vec.h"

int w = 800;
int h = 800;
float sunRotate = -10.0;
float sunRotateDg = 0.005;
struct backRGB {
	float R = 0.6;
	float G = 1.0;
	float B = 1.0;
	};
backRGB backgrdRGB;
using namespace std;

void drawHouse()
{

	glColor4f(0.8, 0.8, 0.8,1);
	triangle(vector3D(0.55,-0.2,0), vector3D(0.3, -0.35,0), vector3D(0.80, -0.35,0));
	glColor4f(0.5, 0.5, 0.8, 1);
	rect(vector3D(0.4, -0.35,0), vector3D(0.7, -0.7,0));
	glColor4f(0.7, 0.7, 0.7, 1);
	rect(vector3D(0.5, -0.5,0), vector3D(0.6, -0.7,0));
}

void drawPerson() {
	
}

void drawSun() {
	float cx = 0.0, cy = 0.0, radius = 0.6;
	float px = 0.0, pmx = 0.0;
	float py = 0.0, pmy = 0.0;

	glPushMatrix(); 
		glRotatef(sunRotate , 0.0, 0.0, 1.0);
		glTranslatef(-0.75, 0.5, 0.0);
		glColor3f(1.0, 0.5, 0.0);
		circle(vector3D(-0.0, 0.0, 0), 0.1);
		for (float f = 0.0; f < 2 * M_PI; f += M_PI / 6) // 6.0 으로 나눈다는 것은 60씩 증가시킨다 --> 12개 그려진다 
		{
			glPushMatrix(); // --> 위에서 세팅된 x,y,z 에 기초하여 transformation이 이루어질 것이다
				glRotatef(5*sunRotate, 0.0, 0.0, 1.0);
				pmx = cx + (radius / 4) * cos(f);
				pmy = cx + (radius / 4) * sin(f);
				glTranslatef(pmx, pmy, 0.0);// instancing
				glColor3f(1.0, 1.0, 0.0);
				rect(vector3D(-0.01, 0.02, 0), vector3D(0.01, -0.02, 0));
			glPopMatrix();
		}
	glPopMatrix();
}

void drawTrees() {
	float tx = 0;
	for (int i = 0; i < 2; i++) {
		glColor4f(0.6, 0.4, 0.3, 1);
		rect(vector3D(-0.6 + tx, -0.1, 0), vector3D(-0.7 + tx, -0.7, 0));
		glColor4f(0.0, 0.6, 0.0, 1);
		circle(vector3D(-0.65 + tx, 0.05, 0), 0.2);
		tx += 0.6;
	}
}

void drawBackground() {
	// Background
	glColor4f(backgrdRGB.R, backgrdRGB.G, backgrdRGB.B, 0.0); // -- 하늘색
	// glColor4f(1.0, 0.8, 0.0, 0.0); -- 주황색 
	rect(vector3D(0.9, -0.9, 0), vector3D(-0.9, 0.9, 0));
	// Ground
	glColor4f(0.4, 0.2, 0.1, 0.0);
	rect(vector3D(0.9, -0.7, 0), vector3D(-0.9, -0.9, 0));
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.6, 0.6, 0.6, 1.0);
	// 배경 
	drawBackground();
	// 집 
	drawHouse();
	// 나무 
	drawTrees();
	// 태양
	drawSun();
	glutSwapBuffers();
}

void idle()
{
	
	if (sunRotate > -100) {
		sunRotate -= sunRotateDg;
		backgrdRGB.R += (1.0 - 0.6) / (90 * (1.0 / sunRotateDg));
		backgrdRGB.G -= (1.0 - 0.8) / (90 * (1.0 / sunRotateDg));
		backgrdRGB.B -= (1) / (90 * (1.0 / sunRotateDg));
	}
	else {
		sunRotate -= 0.00;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(w, h);
	glutCreateWindow("transformations");

	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glutMainLoop();
}

