// �� ��ȯ �ǽ� 
#include "cg.h"
#include "math.h"
#include <stdio.h>

/*

#define _WINDOW_HEIGHT 700
#define _WINDOW_WIDTH  700

void drawRect(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat r, GLfloat g, GLfloat b);
void drawBlackWhiteRect(GLint nx, GLint nz, GLfloat sx, GLfloat sy, GLfloat sz, GLfloat w, int bBlack);

// cam : ��� ������
// ex) 0.5, -0.5 ,1 : �ؿ��� ���� ���� 
GLfloat camx  = 0,	camy = 5,		camz = -5;
// center : ��� ������ ( z������ �� �ָ�  �ٶ󺸱� )
GLfloat cam2x = 0,		cam2y = 0,		cam2z = 10;// ���� �ٶ�
// cam_up : ��� �����̳�
GLfloat cam_upx = 0,	cam_upy = 1,	cam_upz = 0;

int w = 1024;
int h = 1024;

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		camx, camy, camz,
		cam2x, cam2y, cam2z,
		cam_upx, cam_upy, cam_upz
	); // ���� ����

	// glutWireTeapot(0.3);
	// drawRect(0, 0, 0, -.3, 1, 1, 1);
	
	// ���̿�����̽� ȿ�� ( ���⼭ �� �԰� �ִ� ) 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// polygon smooth ȿ��
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);


	// hint
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			int bBlack = (i + j) % 2;
			// ���� �߽��� 0,0 �� �ƴ϶�
			// �ٸ� ��ġ�� �������ֱ� 
			drawBlackWhiteRect(i, j, -10, 0, 0, 0.2, bBlack);

		}
	}
	glDisable(GL_BLEND);
	
	
	glFlush();
}

// ���簢�� �׸��� 
void drawRect(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat r, GLfloat g, GLfloat b)
{
	glColor3f(r,g,b);
	glBegin(GL_POLYGON);
	glVertex3f(x,y,z);
	glVertex3f(x+width, y, z);
	glVertex3f(x+width,y,z+width);
	glVertex3f(x,y,z+width);

	glEnd();
}

void drawBlackWhiteRect(GLint nx, GLint nz, GLfloat sx, GLfloat sy, GLfloat sz, GLfloat w, int bBlack) {
	// sx,sy,sz : ������ 
	// y�� ���� 
	GLfloat x,y,z;
	// bBlack : ������� ���������� 
	x = sx + nx * w;
	y = sy;
	z = sz + nz * w;
	if (bBlack == 1)
		drawRect(x, y, z, w, 0, 0, 0);
	else
		drawRect(x, y, z, w, 1, 1, 1);
}


void MyReshape(int width, int height)
{
	GLfloat left = 0, bottom = 0;
	glViewport(left, bottom, width - left, height - bottom);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat ratio = (float)width / height;
	gluPerspective(60, ratio, 0.1, 1000);
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	// GLUT_DEPTH : ���� ���۸� ����ϰڴ� 
	glutInitDisplayMode(GLUT_RGB);

	// glutwindowsize�� �� �տ� ���´��� create window !
	glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("title");

	// glClearColor(-.5, 0.5, 0.5, 0.0); // ���ȭ�� 

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);

	// ���ܸ� � �� �� �ִ��� Ȯ���ϱ� 
	int num;
	glGetIntegerv(GL_MAX_CLIP_PLANES, &num);
	printf("num of clip planes : %d", num);

	glutMainLoop();
	return 0;
}

*/