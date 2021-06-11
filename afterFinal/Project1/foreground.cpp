
#include "cg.h"
#include "draw.h"
#include "vec.h"

int w = 800;
int h = 800;

struct sunInfo {
	float sunRotate = -10.0;
	float sunRotateDg = 0.05;
	float sunDayStDeg = 0.0;
	float sunDayEdDeg = -110.0;
	float sunMidSdDeg = -237.0;
	float sunMidEdDeg = -365.0;
	float sunDayDegDiff = sunDayStDeg - sunDayEdDeg;
	float sunMidDegDiff = sunDayEdDeg - sunMidSdDeg;
	float sunMorDiff = sunMidSdDeg - sunMidEdDeg;
};
sunInfo sun;

struct backRGB {
	float R = 0.6;
	float G = 1.0;
	float B = 1.0;
	float dayStR = 0.6, dayStG = 1.0, dayStB = 1.0;
	float dayEdR = 1.0, dayEdG = 0.8, dayEdB = 0.0;
	float midR = 0.1, midG = 0.1, midB = 0.1;
	};
backRGB backgrdRGB;
struct leaf {
	float width  = 0.03;
	float height = 0.01;
	float translate = width * 1.2;
};
leaf leafObj;
using namespace std;

void drawHouse();
void drawPerson();
void drawSun();
void drawTrees();
void drawLeaf(float tx);
void drawBackground();

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
	// 특정 각도에서만 그린다
	if (sun.sunRotate <= sun.sunDayStDeg && sun.sunRotate >= sun.sunDayEdDeg) {
		glPushMatrix();
		glRotatef(sun.sunRotate, 0.0, 0.0, 1.0);
		glTranslatef(-0.65, 0.5, 0.0);
		glColor3f(1.0, 0.5, 0.0);
		circle(vector3D(-0.0, 0.0, 0), 0.1);
		for (float f = 0.0; f < 2 * M_PI; f += M_PI / 6) // 6.0 으로 나눈다는 것은 60씩 증가시킨다 --> 12개 그려진다 
		{
			glPushMatrix(); // --> 위에서 세팅된 x,y,z 에 기초하여 transformation이 이루어질 것이다
			glRotatef(5 * sun.sunRotate, 0.0, 0.0, 1.0);
			pmx = cx + (radius / 4) * cos(f);
			pmy = cx + (radius / 4) * sin(f);
			glTranslatef(pmx, pmy, 0.0);// instancing
			glColor3f(1.0, 1.0, 0.0);
			rect(vector3D(-0.01, 0.02, 0), vector3D(0.01, -0.02, 0));
			glPopMatrix();
		}
		glPopMatrix();
	}
	
}

void drawTrees() {
	float tx = 0;
	for (int i = 0; i < 2; i++) {
		glPushMatrix();
		glColor4f(0.6, 0.4, 0.3, 1);
		rect(vector3D(-0.6 + tx, -0.1, 0), vector3D(-0.7 + tx, -0.7, 0));
		glColor4f(0.0, 0.6, 0.0, 1);
		circle(vector3D(-0.65 + tx, 0.05, 0), 0.2);
		// 잎사귀
		drawLeaf(-0.65 + tx);
		glPopMatrix();
		
		tx += 0.6;
	}
}

void drawLeaf(float tx) {
	// boat center
	glPushMatrix(); // 여기서 push,pop을 안하면, 아래의 transformation이 위에 sun에도 모두 적용되어 버린다
		// glRotatef(3.0 * t, 0.0, 0.0, 1.0); // 실제 z축 중심 회전시키기
		glRotatef(3.0, 0.0, 0.0, 1.0); // 실제 z축 중심 회전시키기
		glTranslatef(tx, -leafObj.translate, 0.0);  //instancing --> 우선 태양으로부터 떨어지게 세팅해놓는다
		glColor3f(0.0, 1.0, 0.0);
		ellipse(vector3D(0, 0, 0), leafObj.width, leafObj.height);
		// boat right
		glPushMatrix();
			glRotatef(-15, 0.0, 0.0, 1.0); // instancing  : 방향선정
			glTranslatef(-leafObj.translate, 0.0, 0.0);   // instancing  : 위치선정
			ellipse(vector3D(0.0, 0, 0), leafObj.width, leafObj.height);
		glPopMatrix();

		// boat left
		glPushMatrix();
			glRotatef(15, 0.0, 0.0, 1.0); // instancing  : 방향선정
			glTranslatef(leafObj.translate, 0.0, 0.0);   // instancing  : 위치선정
			ellipse(vector3D(0.0, 0, 0), leafObj.width, leafObj.height);
		glPopMatrix();
	glPopMatrix();
}

void drawBackground() {
	// Background
	glColor4f(backgrdRGB.R, backgrdRGB.G, backgrdRGB.B, 0.0); // -- 하늘색 ~~ glColor4f(1.0, 0.8, 0.0, 0.0); -- 주황색 
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
	// 낮 시간 동안의 변화 
	cout << "Sun Degree :" << sun.sunRotate << endl;
	cout << "backgrdRGB.R :" << backgrdRGB.R << endl;
	cout << "backgrdRGB.G :" << backgrdRGB.G << endl;
	cout << "backgrdRGB.B :" << backgrdRGB.B << endl;

	// float sunRotate = -10.0;
	// float sunRotateDg = 0.05;
	// float sunDayStDeg = 0.0;
	// float sunDayEdDeg = -110.0;
	// float sunMidSdDeg = -237.0;
	// float sunMidEdDeg = -365.0;
	// float sunDayDegDiff = sunDayStDeg - sunDayEdDeg;
	// float sunMidDegDiff = sunDayEdDeg - sunMidSdDeg;
	// float sunMorDiff = sunMidSdDeg - sunMidEdDeg;

	sun.sunRotate -= sun.sunRotateDg;
	if (sun.sunRotate <= sun.sunMidEdDeg) sun.sunRotate = sun.sunDayStDeg;
	if (sun.sunRotate <= sun.sunDayStDeg && sun.sunRotate >= sun.sunDayEdDeg) {
		backgrdRGB.R += (backgrdRGB.dayEdR - backgrdRGB.dayStR) / (sun.sunDayDegDiff * (1.0 / sun.sunRotateDg));
		backgrdRGB.G -= (backgrdRGB.dayStG - backgrdRGB.dayEdG) / (sun.sunDayDegDiff * (1.0 / sun.sunRotateDg));
		backgrdRGB.B -= (backgrdRGB.dayStB - backgrdRGB.dayEdB) / (sun.sunDayDegDiff * (1.0 / sun.sunRotateDg));
	}
	// 밤 ~ 새벽
	else if(sun.sunRotate < sun.sunDayEdDeg && sun.sunRotate >= sun.sunMidSdDeg) {
		backgrdRGB.R -= (backgrdRGB.dayEdR - backgrdRGB.midR) / (sun.sunMidDegDiff * (1.0 / sun.sunRotateDg));
		backgrdRGB.G -= (backgrdRGB.dayEdG - backgrdRGB.midG) / (sun.sunMidDegDiff * (1.0 / sun.sunRotateDg));
		backgrdRGB.B += (backgrdRGB.midB - backgrdRGB.dayEdB) / (90 * (1.0 / sun.sunRotateDg));
	}
	// 새벽 ~ 아침 
	else if(sun.sunRotate < sun.sunMidSdDeg && sun.sunRotate >= sun.sunMidEdDeg) {
		backgrdRGB.R += (backgrdRGB.dayStR - backgrdRGB.midR) / (sun.sunMorDiff * (1.0 / sun.sunRotateDg));
		backgrdRGB.G += (backgrdRGB.dayStG - backgrdRGB.midG) / (sun.sunMorDiff * (1.0 / sun.sunRotateDg));
		backgrdRGB.B += (backgrdRGB.dayStB - backgrdRGB.midB) / (90 * (1.0 / sun.sunRotateDg));
	}
	// float dayStR = 0.6, dayStG = 1.0, dayStB = 1.0;
	// float dayEdR = 1.0, dayEdG = 0.8, dayEdB = 0.0;
	// float midR = 0.1, midG = 0.1, midB = 0.1;

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

