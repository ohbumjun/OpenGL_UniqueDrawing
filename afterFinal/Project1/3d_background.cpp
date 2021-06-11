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

	// reshape window 창 등을 해도 색상 유지하게 해주는 코드
	glDisable(GL_COLOR_MATERIAL);

	GLfloat matrial_0_ambient[] = { 0.0,1.0,0.0,1.0 };
	GLfloat matrial_0_diffuse[] = { 0.1,0.3,0.4,1.0 };
	// 빛의 거울반사와 동일하게 setting 해준다 
	GLfloat matrial_0_specular[] = { 1.0,1.0,1.0,1.0 };
	// 반사광에 대해 반짝거리는 정도 
	GLfloat matrial_0_shiness[] = { 2.0 }; // 0 ~ 128
	// 발광체 설정 : 즉, 물체 자체에서 빛이 나게끔
	// GLfloat matrial_0_emission[] = { 0.0, 0.0, 0.5, 1.0 };

	// 적용
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
	// 빛의 거울반사와 동일하게 setting 해준다 
	GLfloat matrial_1_specular[] = { 1.0,1.0,1.0,1.0 };
	// 반사광에 대해 반짝거리는 정도 
	GLfloat matrial_1_shiness[] = { 10.0 }; // 0 ~ 128
	// 발광체 설정 : 즉, 물체 자체에서 빛이 나게끔
	// 하지만, 다른 물체로 빛이 빛춰지지는 않는다 
	GLfloat matrial_1_emission[] = { 0.0, 0.0, 0.5, 1.0 };

	// 적용
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
			// 머리
			drawHead();
			// 몸통
			drawBody();
			// 왼쪽 팔
			glPushMatrix();
				drawUpperLeftArm(robot[i].leftarm_z_angle_upper[robotAngIdx], robot[i].leftarm_y_angle_upper);
				drawLowerLeftArm(robot[i].leftarm_angle_low[robotAngIdx]);
				drawLeftHand();
			glPopMatrix();
			// 오른쪽 팔
			glPushMatrix();
				drawUpperRightArm(robot[i].rightarm_z_angle_upper[robotAngIdx], robot[i].rightarm_y_angle_upper);
				drawLowerRightArm(robot[i].rightarm_angle_low[robotAngIdx]);
				drawRightHand();
			glPopMatrix();
			// 왼쪽 다리
			glPushMatrix();
				drawUpperLeftLeg(robot[i].leftleg_z_angle_upper, robot[i].leftleg_x_angle_upper);
				drawLowerLeftLeg(robot[i].leftleg_angle_low);
				// drawRightHand();
			glPopMatrix();
			// 오른쪽 다리
			glPushMatrix();
				drawUpperRightLeg(robot[i].rightleg_z_angle_upper, robot[i].rightleg_x_angle_upper);
				drawLowerRightLeg(robot[i].rightleg_angle_low);
				// drawRightHand();
			glPopMatrix();
		glPopMatrix();
	}
}

void drawFloor(GLfloat y) {
	// 바닥 그리기
	// x,z -2.5에서 너비가 5인 사각형을 그리겠다 
	GLfloat x = -5, z = -5, w = 10;

	glDisable(GL_COLOR_MATERIAL);

	GLfloat matrial_0_ambient[] = { 0.0,0.0,1.0,1.0 };
	GLfloat matrial_0_diffuse[] = { 0.0,1.0,0.0,1.0 };
	// 빛의 거울반사와 동일하게 setting 해준다 
	GLfloat matrial_0_specular[] = { 1.0,1.0,1.0,1.0 };
	// 반사광에 대해 반짝거리는 정도 
	GLfloat matrial_0_shiness[] = { 10.0 }; // 0 ~ 128
	// 발광체 설정 : 즉, 물체 자체에서 빛이 나게끔
	// 하지만, 다른 물체로 빛이 빛춰지지는 않는다 
	GLfloat matrial_0_emission[] = { 0.0, 0.0, 0.5, 1.0 };

	// 적용
	glMaterialfv(GL_FRONT, GL_AMBIENT, matrial_0_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matrial_0_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matrial_0_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matrial_0_shiness);
	// glMaterialfv(GL_FRONT, GL_EMISSION, matrial_0_emission);
	
	// 2. 양쪽끝을 밖으로 지정해주기(한 평면,양쪽 끝이 밖으로 향하게 세팅)
	// 그렇게 되면, openGL은 해당 평면이 볼록하다고 인식한다 
	// 3. 양쪽끝을 안으로 지정해두기 
	// 해당 평면이 오목하다고 인식하게 된다 
	// glNormal3f(0,1,0); // y축, 위쪽 방향 
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
	// 공 그리기 ---
	glDisable(GL_COLOR_MATERIAL);
	// 물체의 색상
	GLfloat matrial_0_ambient[] = { 0.3,0.0,0.0,1.0 };
	GLfloat matrial_0_diffuse[] = { 0.6,1.0,1.0,1.0 };
	// 빛의 거울반사와 동일하게 setting 해준다 
	GLfloat matrial_0_specular[] = { 1.0,1.0,1.0,1.0 };
	// 반사광에 대해 반짝거리는 정도 
	GLfloat matrial_0_shiness[] = { 10.0 }; // 0 ~ 128
	// 발광체 설정 : 즉, 물체 자체에서 빛이 나게끔
	// 하지만, 다른 물체로 빛이 빛춰지지는 않는다 
	GLfloat matrial_0_emission[] = { 0.0, 0.0, 0.5, 1.0 };

	// 적용
	glMaterialfv(GL_FRONT, GL_AMBIENT, matrial_0_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matrial_0_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matrial_0_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matrial_0_shiness);
	// glMaterialfv(GL_FRONT, GL_EMISSION, matrial_0_emission);

	float x, z;
	// glRotatef(cloudObj.rotate, 0, 1, 0);
	for (float f = 0.0; f < 2 * M_PI; f += M_PI / 12.0) // 36.0 으로 나눈다는 것은 10씩 증가시킨다 
	{
		glPushMatrix();
		// 원을 나타내는 수식 : x^2  + y^2 = r^2
		// parametric 형식 : X = r * cos (f) -> f: 각도 ( 0 ~ 360 )
		// parametric 형식 : Y = r * sin (f) -> f: 각도 
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
	// 구름 회전 
	cloudObj.rotate += 0.01;

	// 로봇 움직임
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
		// 다리 
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

	// shade 해주는 다양한 방법이 있었다
	// 1.플랫 2.구로 3.폼 4.미세면
	// GL_SMOOTH는 플랫에 해당한다 
	glShadeModel(GL_SMOOTH); // smooth model을 사용하겠다
	glEnable(GL_DEPTH_TEST);
	int bNonDirectionalLight = 1;

	// 전역 주변광 넣기(주변에서 반사되는 빛 setting)
	// 이것만 세팅하면, 가운데 공이 안보인다
	// 왜냐하면, shading이 제대로 나타날 수 없기 때문이다
	// shading이란, 특정 방향으로 빛이 들어와서
	// 해당 빛의 양만큼 물체에 음영이 지는 것이다 
	// 그런데, 음영이 질만한 조명이 없는 것이다 
	GLfloat light_global_ambient[] = { 0.1, 0.1, 0.1, 1.0 };

	// 전등의 위치라고 생각하면 편하다 
	// 4번째 인자 --> 1이면, directional light가 아니고
	// 흩어지면서 빛이 날아오는 개념 
	// 4번째 인자 --> 0이면, directional light가 맞다
	// 평행으로 빛이 날아오는 개념 
	GLfloat light_0_pos[] = { 5.0,5.0,0.0,bNonDirectionalLight };

	// 반사광 (들어오면 퍼져버리는 것 )
	// 확산 반사 -> 입체감 부여 가능 
	GLfloat light_0_diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
	// 거울 반사 ( 들어온 각도대로 반사되는 것 )
	GLfloat light_0_specular[] = { 1.0, 1.0 , 1.0, 1.0 };

	// GL_LIGHT0 (위치성 광원 : 특정 위치에 존재함 ) : light 1개를 쓰겠다 !
	// 무조건 빛 한개는 쓸 수 있다. 쓸수 있는 빛의 개수는 gpu 에 의존 
	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_global_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_0_pos);

	// 보기에 조금 더 부드럽게 해주는 코드
	// 왜 > 시점 위치가 물체에 매우 가까운 것으로 간주되어
	// 물체면을 구성하는 모든 삼각형마다 별도의 시점벡터가 계산된다 
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	// drawFloor 에서 glNormal 이라는 코드를 통해
	// 법선벡터를 양끝에서 밖 혹은 안으로 지정했다
	// 그런데 normal vector의 크기는 1이 되어야 한다
	// 이를 위해 자동으로 계산해주는 코드가 아래
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

	// 반드시 createWindow 한 다음에 초기화해줘야 한다 
	init_light();

	// clouds , robots 위치 설정
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


