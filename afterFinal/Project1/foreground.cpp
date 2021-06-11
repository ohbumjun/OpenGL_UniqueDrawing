
#include "cg.h"
#include "draw.h"
#include "vec.h"

int w = 800;
int h = 800;
float backColor = 0;;

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
	cout << "backColor :" << backColor << endl;
	
	glPushMatrix(); 
		glRotatef(3.0 + backColor, 0.0, 0.0, 1.0);
		line(vector3D(0, 0, 0), vector3D(-0.75, 0.5, 0));
		glTranslatef(-0.75, 0.5, 0.0);
		glRotatef(3.0 + backColor, 0.0, 0.0, 1.0);
		glColor4f(0.5, 0.0, 0.0, 1);
		circle(vector3D(-0.0, 0.0, 0), 0.1);
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
	glColor4f(0.6,1.0,1.0, 0.0);
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
	backColor += 0.0001;
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

