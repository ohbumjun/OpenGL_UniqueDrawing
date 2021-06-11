#include "cg.h"
#include "draw.h"
#include <random>

#define _WINDOW_WIDTH 500
#define _WINDOW_HEIGHT 500

GLfloat camx = -4, camy = 10, camz = -15;
GLfloat cam2x = 0, cam2y = 0, cam2z = 0;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

using namespace std;

//참고 : 빛을 설정해줄 때는 1) 빛 2) 물체의 색상
// 2개를 세팅해야 하는데, 1) 빛의 색상. 이 우선순위를 가진다는 점이 중요하다 
// 예를 들어, 들어오는 빛이 RGB에서 B만 있다고 해보자. 파란색만 있는 것이다
// 그리고 물체의 색상은 완전히 빨간색이라고 해보자
// 그렇다고 하더라도, 색상은 빨간색을 반사시킬 수 없다. 왜냐하면 애초부터 빛에 빨간색이 없으므로 

// diffuse 값을 기준으로 분류해보자
// 1. light_diffuse가 0,0,1
// material_ambient가 0.3, 0.3, 0.3 이라고 해보자
// 그러면, 실제 물체 색상의 r,g,는 전혀 영향받지 않게 되고, 물체의 rg 색상이 그대로 표현된다 

int* makeRandomCoord() {
	int* arr = new int[3];
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<int> xz(-4.5, 4.5);
	uniform_int_distribution<int> y(2, 5);
		
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
	// 하지만, 다른 물체로 빛이 빛춰지지는 않는다 
	// GLfloat matrial_0_emission[] = { 0.0, 0.0, 0.5, 1.0 };

	// 적용
	glMaterialfv(GL_FRONT, GL_AMBIENT, matrial_0_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matrial_0_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matrial_0_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matrial_0_shiness);
	// glMaterialfv(GL_FRONT, GL_EMISSION, matrial_0_emission);

	// 법선벡터를 -z축,우리쪽 방향 세팅
	// 그래야만, 벽,바닥끼리 구분이 된다
	// 법선벡터는 어디가 앞면이고, 어디가 뒷면인지를 알려주는 정보에 해당하기 때문이다 
	// 그리고 각각에 대한 shading도 들어가게 된다 
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

void drawBall(float sx, float sy, float sz) {
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
		for (float f = 0.0; f < 2 * M_PI; f += M_PI / 12.0) // 36.0 으로 나눈다는 것은 10씩 증가시킨다 
		{
			glPushMatrix();
			// 원을 나타내는 수식 : x^2  + y^2 = r^2
			// parametric 형식 : X = r * cos (f) -> f: 각도 ( 0 ~ 360 )
			// parametric 형식 : Y = r * sin (f) -> f: 각도 
			x = sx + 0.6 * cos(f);
			z = sz + 0.6 * sin(f);
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

	drawFloor(-5.0);
	drawWall(5.0);

	// float sx, float sz, float sy
	int* p;
	for (int i = 0; i < 20; i++) {
		p = makeRandomCoord();
		drawBall(p[0], p[1], p[2]);
	}

	glFlush();
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

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}


