/*
  Example: Using the mouse position, draw a triangle if three vertices are clicked

#include "cg.h"
#include "draw.h"

int w = 512;
int h = 512;

vector2D points[100];
int count = 0;
vector3D col = vector3D(0.6, 0.6, 0.6);
bool on = true;

void mouse(GLint button, GLint state, GLint x, GLint y)
{
	if ((button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) || (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN))
	{
		points[count].x = (float)x / (float)w * 2.0 - 1.0;
		points[count].y = -(float)y / (float)h * 2.0 + 1.0;
		count++;
	}
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(col.x, col.y, col.z);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < count; i++)
		glVertex3f(points[i].x, points[i].y, 0.0);
	glEnd();

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'r') col = vector3D(1.0, 0.0, 0.0);
	else if (key == 'g') col = vector3D(0.0, 1.0, 0.0);
	else if (key == 'b') col = vector3D(0.0, 0.0, 1.0);
	else if (key == 'c') col = vector3D(0.0, 0.7, 0.7);
	else if (key == 'p') col = vector3D(0.7, 0.0, .7);
	else if (key == 'y') col = vector3D(0.7, 0.7, 0.0);
	else if (key == 'n') {
		if (on == true) on = false;
		else on = true;
	}
}

void idle()
{
	if (on)
		for (int i = 0; i < count; i++)
			points[i].x += 0.00001;

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(w, h);
	glutCreateWindow("simple");

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

	glutMainLoop();
}

*/