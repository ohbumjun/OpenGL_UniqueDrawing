#include "cg.h"
#include "draw.h"
#include "drawRobot.h"
#include <random>

#define _WINDOW_WIDTH 500
#define _WINDOW_HEIGHT 500

GLfloat camx = -15, camy = 0, camz = -0;
GLfloat cam2x = 0, cam2y = 0, cam2z = 0;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

struct cloud {
	int cloudNum = 20 ;
	int* clouds[20];
	float rotate = 0.01;
};
cloud cloudObj;

// RobotNums
const int robotNums = 3;
int* robotCoords[robotNums];
Robot robot[robotNums];

using namespace std;

int* makeRandomCoord(float minXZ, float maxXZ, float minY, float maxY) {
	int* arr = new int[3];
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<int> xz(minXZ, maxXZ);
	uniform_int_distribution<int> y(minY, maxY);
	// x,y,z
	arr[0] = xz(eng);
	arr[1] = y(eng);
	arr[2] = xz(eng);
	return arr;
}

void drawWall(GLfloat z) {
	GLfloat x = -5, y =-5, w = 10;

	// reshape window â ���� �ص� ���� �����ϰ� ���ִ� �ڵ�
	glDisable(GL_COLOR_MATERIAL);

	GLfloat matrial_0_ambient[] = { 0.0,1.0,0.0,1.0 };
	GLfloat matrial_0_diffuse[] = { 0.1,0.3,0.4,1.0 };
	// ���� �ſ�ݻ�� �����ϰ� setting ���ش� 
	GLfloat matrial_0_specular[] = { 1.0,1.0,1.0,1.0 };
	// �ݻ籤�� ���� ��¦�Ÿ��� ���� 
	GLfloat matrial_0_shiness[] = { 2.0 }; // 0 ~ 128
	// �߱�ü ���� : ��, ��ü ��ü���� ���� ���Բ�
	// GLfloat matrial_0_emission[] = { 0.0, 0.0, 0.5, 1.0 };

	// ����
	glMaterialfv(GL_FRONT, GL_AMBIENT, matrial_0_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matrial_0_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matrial_0_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matrial_0_shiness);
	// glMaterialfv(GL_FRONT, GL_EMISSION, matrial_0_emission);

	glNormal3f(0, 0, -1);
	glBegin(GL_POLYGON);
		glVertex3f(x, y, z);
		glVertex3f(x, y + w, z);
		glVertex3f(x + w, y + w, z);
		glVertex3f(x + w, y, z);
	glEnd();

	GLfloat matrial_1_ambient[] = { 0.0,0.0,1.0,1.0 };
	GLfloat matrial_1_diffuse[] = { 0.0,1.0,0.0,1.0 };
	// ���� �ſ�ݻ�� �����ϰ� setting ���ش� 
	GLfloat matrial_1_specular[] = { 1.0,1.0,1.0,1.0 };
	// �ݻ籤�� ���� ��¦�Ÿ��� ���� 
	GLfloat matrial_1_shiness[] = { 10.0 }; // 0 ~ 128
	// �߱�ü ���� : ��, ��ü ��ü���� ���� ���Բ�
	// ������, �ٸ� ��ü�� ���� ���������� �ʴ´� 
	GLfloat matrial_1_emission[] = { 0.0, 0.0, 0.5, 1.0 };

	// ����
	glMaterialfv(GL_FRONT, GL_AMBIENT, matrial_1_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matrial_1_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matrial_1_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matrial_1_shiness);
	rect(vector3D(x, y, z-0.001),vector3D(x+w,y+w*0.2,z-0.001));
	ellipse(vector3D(x + w * 0.5, y + w * 0.2, z - 0.001), w * 0.5, 1.2);
}

void drawRobot(float sx,float sy,float sz) {
	int robotAngIdx = 0;
	for (int i = 0; i < robotNums; i++) {
		glPushMatrix();
			glTranslatef(sx,sy,sz);
			// �Ӹ�
			drawHead();
			// ����
			drawBody();
			// ���� ��
			glPushMatrix();
				drawUpperLeftArm(robot[i].leftarm_z_angle_upper[robotAngIdx], robot[i].leftarm_y_angle_upper);
				drawLowerLeftArm(robot[i].leftarm_angle_low[robotAngIdx]);
				drawLeftHand();
			glPopMatrix();
			// ������ ��
			glPushMatrix();
				drawUpperRightArm(robot[i].rightarm_z_angle_upper[robotAngIdx], robot[i].rightarm_y_angle_upper);
				drawLowerRightArm(robot[i].rightarm_angle_low[robotAngIdx]);
				drawRightHand();
			glPopMatrix();
			// ���� �ٸ�
			glPushMatrix();
				drawUpperLeftLeg(robot[i].leftleg_z_angle_upper, robot[i].leftleg_x_angle_upper);
				drawLowerLeftLeg(robot[i].leftleg_angle_low);
				// drawRightHand();
			glPopMatrix();
			// ������ �ٸ�
			glPushMatrix();
				drawUpperRightLeg(robot[i].rightleg_z_angle_upper, robot[i].rightleg_x_angle_upper);
				drawLowerRightLeg(robot[i].rightleg_angle_low);
				// drawRightHand();
			glPopMatrix();
		glPopMatrix();
	}
}

void drawFloor(GLfloat y) {
	// �ٴ� �׸���
	// x,z -2.5���� �ʺ� 5�� �簢���� �׸��ڴ� 
	GLfloat x = -5, z = -5, w = 10;

	glDisable(GL_COLOR_MATERIAL);

	GLfloat matrial_0_ambient[] = { 0.0,0.0,1.0,1.0 };
	GLfloat matrial_0_diffuse[] = { 0.0,1.0,0.0,1.0 };
	// ���� �ſ�ݻ�� �����ϰ� setting ���ش� 
	GLfloat matrial_0_specular[] = { 1.0,1.0,1.0,1.0 };
	// �ݻ籤�� ���� ��¦�Ÿ��� ���� 
	GLfloat matrial_0_shiness[] = { 10.0 }; // 0 ~ 128
	// �߱�ü ���� : ��, ��ü ��ü���� ���� ���Բ�
	// ������, �ٸ� ��ü�� ���� ���������� �ʴ´� 
	GLfloat matrial_0_emission[] = { 0.0, 0.0, 0.5, 1.0 };

	// ����
	glMaterialfv(GL_FRONT, GL_AMBIENT, matrial_0_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matrial_0_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matrial_0_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matrial_0_shiness);
	// glMaterialfv(GL_FRONT, GL_EMISSION, matrial_0_emission);
	
	// 2. ���ʳ��� ������ �������ֱ�(�� ���,���� ���� ������ ���ϰ� ����)
	// �׷��� �Ǹ�, openGL�� �ش� ����� �����ϴٰ� �ν��Ѵ� 
	// 3. ���ʳ��� ������ �����صα� 
	// �ش� ����� �����ϴٰ� �ν��ϰ� �ȴ� 
	// glNormal3f(0,1,0); // y��, ���� ���� 
	glBegin(GL_POLYGON);
	glNormal3f(-1, 1, 0);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z + w);
	glNormal3f(1, 1, 0);
	glVertex3f(x + w, y, z + w);
	glVertex3f(x + w, y, z);
	glEnd();
}

void drawClouds(float sx, float sy, float sz) {
	// �� �׸��� ---
	glDisable(GL_COLOR_MATERIAL);
	// ��ü�� ����
	GLfloat matrial_0_ambient[] = { 0.3,0.0,0.0,1.0 };
	GLfloat matrial_0_diffuse[] = { 0.6,1.0,1.0,1.0 };
	// ���� �ſ�ݻ�� �����ϰ� setting ���ش� 
	GLfloat matrial_0_specular[] = { 1.0,1.0,1.0,1.0 };
	// �ݻ籤�� ���� ��¦�Ÿ��� ���� 
	GLfloat matrial_0_shiness[] = { 10.0 }; // 0 ~ 128
	// �߱�ü ���� : ��, ��ü ��ü���� ���� ���Բ�
	// ������, �ٸ� ��ü�� ���� ���������� �ʴ´� 
	GLfloat matrial_0_emission[] = { 0.0, 0.0, 0.5, 1.0 };

	// ����
	glMaterialfv(GL_FRONT, GL_AMBIENT, matrial_0_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matrial_0_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matrial_0_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matrial_0_shiness);
	// glMaterialfv(GL_FRONT, GL_EMISSION, matrial_0_emission);

	float x, z;
	// glRotatef(cloudObj.rotate, 0, 1, 0);
	for (float f = 0.0; f < 2 * M_PI; f += M_PI / 12.0) // 36.0 ���� �����ٴ� ���� 10�� ������Ų�� 
	{
		glPushMatrix();
		// ���� ��Ÿ���� ���� : x^2  + y^2 = r^2
		// parametric ���� : X = r * cos (f) -> f: ���� ( 0 ~ 360 )
		// parametric ���� : Y = r * sin (f) -> f: ���� 
		x = sx + 0.6 * cos(f);
		z = sz + 0.6 * sin(f);
		glRotatef(cloudObj.rotate * sy * 5, 0, 1, 0);
		glTranslatef(x, sy, z);
		glutSolidSphere(0.3, 20, 20);
		glPopMatrix();
	}
	
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camx, camy, camz, cam2x, cam2y, cam2z, cam_upx, cam_upy, cam_upz);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	// Floor
	drawFloor(-5.0);
	// Wall
	drawWall(5.0);
	// Cloud
	// float sx, float sz, float sy
	for (int i = 0; i < cloudObj.cloudNum; i++) {
		drawClouds(cloudObj.clouds[i][0], cloudObj.clouds[i][1], cloudObj.clouds[i][2]);
	}
	// Robot
	for (int i = 0; i < robotNums; i++) {
		glPushMatrix();
		glRotatef(-cloudObj.rotate * robotCoords[i][0] * 5, 0, 1, 0);
		drawRobot(robotCoords[i][0], robotCoords[i][1], robotCoords[i][2]);
		glPopMatrix();
	}

	glFlush();
}

void idle()
{
	// ���� ȸ�� 
	cloudObj.rotate += 0.01;

	// �κ� ������
	for (int i = 0; i < robotNums; i++) {
		int arm_limit = 45;
		robot[i].rightarm_y_angle_upper += robot[i].dir_arm_right_upper;
		// angle_low += dir_low;
		if (robot[i].rightarm_y_angle_upper >= arm_limit)
			robot[i].dir_arm_right_upper = -1;
		else if (robot[i].rightarm_y_angle_upper < -arm_limit)
			robot[i].dir_arm_right_upper = 1;

		robot[i].leftarm_y_angle_upper += robot[i].dir_arm_left_upper;
		// angle_low += dir_low;
		if (robot[i].leftarm_y_angle_upper >= arm_limit)
			robot[i].dir_arm_left_upper = -1;
		else if (robot[i].leftarm_y_angle_upper < -arm_limit)
			robot[i].dir_arm_left_upper = 1;
		// �ٸ� 
		int leg_limit = 45;
		robot[i].rightleg_x_angle_upper += robot[i].dir_leg_right_upper;
		// angle_low += dir_low;
		if (robot[i].rightleg_x_angle_upper >= arm_limit)
			robot[i].dir_leg_right_upper = -1;
		else if (robot[i].rightleg_x_angle_upper < -arm_limit)
			robot[i].dir_leg_right_upper = 1;

		robot[i].leftleg_x_angle_upper += robot[i].dir_leg_left_upper;
		// angle_low += dir_low;
		if (robot[i].leftleg_x_angle_upper >= arm_limit)
			robot[i].dir_leg_left_upper = -1;
		else if (robot[i].leftleg_x_angle_upper < -arm_limit)
			robot[i].dir_leg_left_upper = 1;
	}
	
	glutPostRedisplay();
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat ratio = (float)width / height;
	gluPerspective(40, ratio, 0.1, 1000);
}

void init_light() {
	glEnable(GL_LIGHTING);

	// shade ���ִ� �پ��� ����� �־���
	// 1.�÷� 2.���� 3.�� 4.�̼���
	// GL_SMOOTH�� �÷��� �ش��Ѵ� 
	glShadeModel(GL_SMOOTH); // smooth model�� ����ϰڴ�
	glEnable(GL_DEPTH_TEST);
	int bNonDirectionalLight = 1;

	// ���� �ֺ��� �ֱ�(�ֺ����� �ݻ�Ǵ� �� setting)
	// �̰͸� �����ϸ�, ��� ���� �Ⱥ��δ�
	// �ֳ��ϸ�, shading�� ����� ��Ÿ�� �� ���� �����̴�
	// shading�̶�, Ư�� �������� ���� ���ͼ�
	// �ش� ���� �縸ŭ ��ü�� ������ ���� ���̴� 
	// �׷���, ������ ������ ������ ���� ���̴� 
	GLfloat light_global_ambient[] = { 0.1, 0.1, 0.1, 1.0 };

	// ������ ��ġ��� �����ϸ� ���ϴ� 
	// 4��° ���� --> 1�̸�, directional light�� �ƴϰ�
	// ������鼭 ���� ���ƿ��� ���� 
	// 4��° ���� --> 0�̸�, directional light�� �´�
	// �������� ���� ���ƿ��� ���� 
	GLfloat light_0_pos[] = { 5.0,5.0,0.0,bNonDirectionalLight };

	// �ݻ籤 (������ ���������� �� )
	// Ȯ�� �ݻ� -> ��ü�� �ο� ���� 
	GLfloat light_0_diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
	// �ſ� �ݻ� ( ���� ������� �ݻ�Ǵ� �� )
	GLfloat light_0_specular[] = { 1.0, 1.0 , 1.0, 1.0 };

	// GL_LIGHT0 (��ġ�� ���� : Ư�� ��ġ�� ������ ) : light 1���� ���ڴ� !
	// ������ �� �Ѱ��� �� �� �ִ�. ���� �ִ� ���� ������ gpu �� ���� 
	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_global_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_0_pos);

	// ���⿡ ���� �� �ε巴�� ���ִ� �ڵ�
	// �� > ���� ��ġ�� ��ü�� �ſ� ����� ������ ���ֵǾ�
	// ��ü���� �����ϴ� ��� �ﰢ������ ������ �������Ͱ� ���ȴ� 
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	// drawFloor ���� glNormal �̶�� �ڵ带 ����
	// �������͸� �糡���� �� Ȥ�� ������ �����ߴ�
	// �׷��� normal vector�� ũ��� 1�� �Ǿ�� �Ѵ�
	// �̸� ���� �ڵ����� ������ִ� �ڵ尡 �Ʒ�
	glEnable(GL_NORMALIZE);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowPosition(300, 200);
	glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glutCreateWindow("Window 1");

	// �ݵ�� createWindow �� ������ �ʱ�ȭ����� �Ѵ� 
	init_light();

	// clouds , robots ��ġ ����
	for (int i = 0; i < cloudObj.cloudNum; i++) {
		cloudObj.clouds[i] = makeRandomCoord(-3.5,3.5,3,5);
	}
	for (int i = 0; i < robotNums; i++) {
		robotCoords[i] = makeRandomCoord(-3.5, 3.5, -3, -3.1);
	}
	
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}


