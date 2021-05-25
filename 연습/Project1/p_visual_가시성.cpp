// �� ��ȯ �ǽ� 
#include "cg.h"
#include "math.h"
#include <stdio.h>

/*


#define _WINDOW_HEIGHT 700
#define _WINDOW_WIDTH  700

int angle_upper = 0;
int angle_low = 0;

int dir_upper = 1;
int dir_low = 4;


// cam : ��� ������
// ex) 0.5, -0.5 ,1 : �ؿ��� ���� ���� 
GLfloat camx = 0.5, camy = 1, camz = 2;
// center : ��� ������ 
GLfloat cam2x = 0, cam2y = 0, cam2z = 0;// ���� �ٶ�
// cam_up : ��� �����̳�
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

int list_id;
int w = 1024;
int h = 1024;

// �� �־��ֱ� 
void InitLight()
{
	GLfloat mat_diffuse[]  = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = {50.0};
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8,0.8,1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_position[] = { -3, 2, 3, 0.0 };

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void InitVisibility()
{
	glEnable(GL_CULL_FACE); // ���ܸ� ���� ���� 
	glDisable(GL_CULL_FACE); // ���ܸ� ���� ��ȿȭ
	
	// glPolygonMode(GL_FRONT, GL_FILL); // �ո� ä���
	// glPolygonMode(GL_BACK, GL_LINE);  // �޸��� ���� ���̰� �ϱ� 

	glPolygonMode(GL_FRONT, GL_LINE); // �ո� ä���
	// ��� �Ʒ����� cullface back�� ���شٸ� ���⼭ ���� ���ڵ带 ���� �ʿ�� ���� 
	glPolygonMode(GL_BACK, GL_LINE);  

	glFrontFace(GL_CW);     // clockwise�� front face 
	// glCullFace(GL_BACK);	// �ĸ� ���� ���� ���� 
	// glCullFace(GL_FRONT);    // ���� ���� 
	glEnable(GL_DEPTH_TEST);

	// ���ܸ� �߰�
	glEnable(GL_CLIP_PLANE0); // 0�� ���ܸ� ����ϰڴ�


}

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		camx, camy, camz,
		cam2x, cam2y, cam2z,
		cam_upx, cam_upy, cam_upz
	); // ���� ����

	// gluLookAt 
	// ī�޶� ������ ������ ���Ŀ� ���ܸ��� �����ϴ� �ڵ带 �־��
	// ���� ��ü �߽����� �߷��� ȿ���� ���´� 
	// GLdouble eq[4] = { 0,1,0,0 }; // y �� 0�� ��� ���ʸ� �츮�ڴ� 
	GLdouble eq[4] = { 0,0,1,0 }; // z�� 0 --> ���η� �߸�  
	glClipPlane(GL_CLIP_PLANE0, eq);

	glutSolidTeapot(0.3);
	glutSwapBuffers();
}

void MyReshape(int width, int height)
{
	// glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	GLfloat left = 0, bottom = 0;
	// ������ ��ܿ� ��ġ�Ͽ� ����Ʈ ��ȯ�ϱ� 
	glViewport(left, bottom, width - left, height - bottom);
	// gluPerspective�� �ϱ� ��, mode�� GL_PROJECTION���� �ٲ���ִ� ����
	// Ȯ���� �� �ִ� 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// ��𼭺���, ������ ��� �� ���ΰ� : -2  ~ 2


	GLfloat ratio = (float)(width - left) / (height - bottom);
	// �����̴� 0.1 ��ŭ ������
	// �ָ��� 10������ ���ڴ� 
	gluPerspective(40, ratio, 0.1, 10);

	// < ũ�� ���̰�, �۰� ���̰� ���� >
	// 1) robot, camera ��ġ 
	// ���� robot body�� ����
	// ī�޶�� camz , ��, z ������ 1��ŭ�� ������
	// ����� ������ ���� �����̴� 
	// 2) ���� ���� : 60 �� 
	// ������ �۾��� ����, ���� ������ ����
	// ��, ����� ũ�� ���δ� 
	// ��, �ʹ� �а� ����, �ְ��� ����� ������ �������� 
}

void MyTimer(int value)
{

	// ī�޶� ȸ�� animation 
	// ���� y���� ��������
	// y��ǥ�� �״�� �ְ� 
	// y �� ���� ���ư��鼭 ���� 
	GLfloat theta = 0.01;
	GLfloat tmp_x = camx; // ������ �ִ� x ��ǥ �״�� 
	camx = camx * cos(theta) + camz * sin(theta);
	camz = -tmp_x * sin(theta) + camz * cos(theta);

	// ���� : ī�޶� ��ȯ �ִϸ��̼��� 
	// ���� timer func �ֵ� �ȴ� 
	glutTimerFunc(1000 / 60, MyTimer, 1);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	// GLUT_DEPTH : ���� ���۸� ����ϰڴ� 
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// glutwindowsize�� �� �տ� ���´��� create window !
	glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("title");

	glClearColor(-.5, 0.5, 0.5, 0.0); // ���ȭ�� 

	// ���� ȿ�� 
	InitLight();
	InitVisibility();

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutTimerFunc(1000/60, MyTimer, 1);

	// ���ܸ� � �� �� �ִ��� Ȯ���ϱ� 
	int num;
	glGetIntegerv(GL_MAX_CLIP_PLANES,&num);
	printf("num of clip planes : %d", num);

	glutMainLoop();
	return 0;
}



*/