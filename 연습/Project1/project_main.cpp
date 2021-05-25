// INTERACTIVE DRAWING

#include "cg.h"
#include "draw.h"
#include <cmath>
#include<iostream>

using namespace std;

#define _WINDOW_WIDTH  1024
#define _WINDOW_HEIGHT 1024

struct polytype {
	vector3D a, b ; // 시작 위치, 끝 위치 
	vector3D sp, cp; // 마우스 드래그 시 시작, 드래그 중 위치 
	int pmode;// 1: line, 2: triangle, 3:circle, 4:rectangle -> 도형을 더 추가할 수도 있다 
	vector3D color;
	bool on = false; // 클릭후, 드래그 했으면, true(도형그려짐) // 아니면 false( 안그려짐 )
};
polytype polygon[100];

int clickedFigIdx = -1 ;
int index = 0; // 몇번째 polygon 을 그리고 있는가 

enum class displayModes {SIMPLE_DRAWING = 1, TWO_D, THREE_D};
displayModes displayMode = displayModes::SIMPLE_DRAWING;
enum class colorModes {RED = 1, YELLOW, BLUE, GREEN, CYAN, MATAGATA};
colorModes colorMode = colorModes::RED;
enum class figureModes { LINE = 1, RENTANGLE,TRIANGLE, ELLIPSE, SPHERE, BIG_ARROW, THREE_WAY_LINE };
figureModes figureMode = figureModes::LINE;
enum class drawModes { DRAW_OBJECT = 1, EDIT_OBJECT, RESIZE_OBJECT };
drawModes drawMode = drawModes::DRAW_OBJECT; // 0 : 그리기, 1 : 편집 
enum class resizeDirs {LEFT_TOP = 1,LEFT_BOTTOM,RIGHT_TOP,RIGHT_BOTTOM};
resizeDirs resizeDir = resizeDirs::LEFT_TOP;
vector3D color = vector3D(0.9, 0.9, 0.8);

struct campos {
	// cam : 어디서 보느냐
// ex) 0.5, -0.5 ,1 : 밑에서 위를 보기 
// ex) 0.0, -0.0 ,5 : 맨 위에서 아래를 내려다 보기
	GLfloat camx = 0.0, camy = -0.0, camz = 1;
	// center : 어디를 보느냐 
	GLfloat cam2x = 0, cam2y = 0, cam2z = 0;// 원점 바라봄
	// cam_up : 어디가 위쪽이냐
	GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;
};
campos cam_pos;

void reshape(int width, int height);
void mykey(unsigned char key, int x, int y);
bool checkRange(float x, float y, float poly_a_x, float poly_a_y, float poly_b_x, float poly_b_y);
bool checkFigure(float x, float y);
void mymouse(int button, int state, int x, int y);
void mymousemotion(int x, int y);
void checkResizeDir(float mouse_x, float mouse_y, vector3D fig_a, vector3D fig_b);
void selectMenu(int value);
void selectSubMenu(int value);
void selectDrawMenu(int value);
void selectFigMenu(int value);
void display();
void drawSimpleDrawing(vector3D a, vector3D b, vector3D color);

bool checkFigure(float x, float y)
{
	bool isFigClicked = false;
	for (int i = index; i >= 0; i--) {
		if (checkRange(x,y, polygon[i].a.x, polygon[i].a.y, polygon[i].b.x, polygon[i].b.y))
		{
			clickedFigIdx = i;
			isFigClicked = true;
			break;
		}
	}
	cout << "clickedFigIdx : " << clickedFigIdx << endl;
	return isFigClicked;
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
	glutCreateWindow("simple");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mymouse);
	glutMotionFunc(mymousemotion);
	glutKeyboardFunc(mykey);

	int drawMenuId = glutCreateMenu(selectDrawMenu);
		glutSetMenu(drawMenuId);// 현재 메뉴 지정 
		glutAttachMenu(GLUT_RIGHT_BUTTON);// menu 를 마우스 버튼에 등록
		// 3D Model을 클릭시, 아래의 3개 subMenu가 나오는 것이다 
		glutAddMenuEntry("Draw Mode", 1); // 메뉴에 내용 넣어주기
		glutAddMenuEntry("Edit Mode", 2);
		glutAddMenuEntry("Resize Mode", 3);

	int figureMenuId = glutCreateMenu(selectFigMenu);
		glutSetMenu(figureMenuId);// 현재 메뉴 지정 
		glutAttachMenu(GLUT_RIGHT_BUTTON);// menu 를 마우스 버튼에 등록
		// 3D Model을 클릭시, 아래의 3개 subMenu가 나오는 것이다 
		glutAddMenuEntry("Line", static_cast<int>(figureModes::LINE)); // 메뉴에 내용 넣어주기
		glutAddMenuEntry("Rectangle", static_cast<int>(figureModes::RENTANGLE));
		glutAddMenuEntry("Triangle", static_cast<int>(figureModes::TRIANGLE));
		glutAddMenuEntry("Ellipse", static_cast<int>(figureModes::ELLIPSE));
		glutAddMenuEntry("Sphere", static_cast<int>(figureModes::SPHERE));
		glutAddMenuEntry("Big Arrow", static_cast<int>(figureModes::BIG_ARROW));
		glutAddMenuEntry("3 Way Lines", static_cast<int>(figureModes::THREE_WAY_LINE));

	int simpleDrawMenuId = glutCreateMenu(selectSubMenu);
		glutSetMenu(simpleDrawMenuId);// 현재 메뉴 지정 
		glutAttachMenu(GLUT_RIGHT_BUTTON);// menu 를 마우스 버튼에 등록
		glutAddSubMenu("Draw Mode", drawMenuId); // 메뉴에 내용 넣어주기
		glutAddSubMenu("Figure", figureMenuId);

	int subMenuId = glutCreateMenu(selectSubMenu);
		glutSetMenu(subMenuId);// 현재 메뉴 지정 
		glutAttachMenu(GLUT_RIGHT_BUTTON);// menu 를 마우스 버튼에 등록
		glutAddSubMenu("Simple Drawing", simpleDrawMenuId); // 메뉴에 내용 넣어주기
		glutAddMenuEntry("2D", 2);
		glutAddMenuEntry("3D", 3);

	int mainMenuId = glutCreateMenu(selectMenu);
		glutSetMenu(mainMenuId);// 현재 메뉴 지정 
		glutAttachMenu(GLUT_RIGHT_BUTTON);// menu 를 마우스 버튼에 등록
		glutAddSubMenu("What do you want", subMenuId); // 메뉴에 내용 넣어주기
		glutAddMenuEntry("Exit", 2);

	glutMainLoop();
}

void drawClock()
{
	glPushMatrix();
		glScalef(2, 4, 0);
		glutWireCube(0.25);
	glPopMatrix();
}

void drawSimpleDrawing(vector3D a, vector3D b, vector3D color)
{
	for (int i = 0; i <= index; i++) {
		// .on == false : 아직 드래그가 안끝난 것 ( 아직 안그려진 것 )
		if (polygon[i].on == true) {
			a = polygon[i].a;
			b = polygon[i].b;
			color = polygon[i].color;
			figureMode = static_cast<figureModes>(polygon[i].pmode);
			glColor3f(color.x, color.y, color.z);
			if (figureMode == figureModes::LINE)
				line(a, b);
			else if (figureMode == figureModes::RENTANGLE) {  //rectangle
				rect(a, b);
			}
			else if (figureMode == figureModes::TRIANGLE) {
				//triangle
				vector3D lDown, mTop, rDown;
				// x : 가로위치, y : 세로 위치 
				lDown = vector3D(a.x, b.y, 0);
				mTop = vector3D(a.x + (b.x - a.x) / 2, a.y, 0);
				rDown = b;
				triangle(mTop, lDown, rDown);
			}
			else if (figureMode == figureModes::ELLIPSE) {
				//ellipse
				float width = (b.x - a.x) / 2;
				float height = (a.y - b.y) / 2;
				vector3D center = vector3D(a.x + width / 2, b.y + height, 0);
				ellipse(center, width, height);
			}
			else if (figureMode == figureModes::SPHERE) {
				float radius = (b.x - a.x) / 2;
				vector3D center = vector3D(a.x + radius / 2, b.y + radius, 0);
				circle(center, radius);
			}
			else if (figureMode == figureModes::BIG_ARROW) {
				vector3D recLTop, recRDown;
				recLTop = vector3D(a.x, a.y - (a.y - b.y) * 0.3, 0);
				recRDown = vector3D(a.x + (b.x - a.x) * 0.6, b.y + (a.y - b.y) * 0.3, 0);
				rect(recLTop, recRDown);
				vector3D lTop, rMid, lDown;
				lTop = vector3D(a.x + (b.x - a.x) * 0.6, a.y, 0);
				rMid = vector3D(b.x, b.y + (a.y - b.y) * 0.5, 0);
				lDown = vector3D(a.x + (b.x - a.x) * 0.6, b.y, 0);
				triangle(lTop, rMid, lDown);
			}
			else if (figureMode == figureModes::THREE_WAY_LINE) {
				vector3D fstP = a;
				vector3D secP = vector3D(a.x, b.y + (a.y - b.y) / 2, 0);
				vector3D trdP = vector3D(b.x, b.y + (a.y - b.y) / 2, 0);
				vector3D fthP = b;
				threeline(fstP, secP, trdP, fthP);
			}
		}
	}
}

void display()
{
	vector3D a, b;
	vector3D color = vector3D(0.9, 0.0, 0.9);

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// 1_ animation에 따른 카메라 각도 변환을 구현하기 위해서는
	// gluLookAt을 display 함수에 넣어주어야 한다 
	// 2) glMatrixMode(GL_MODELVIEW); 안에다가 넣어주어야 한다
	// 밖에 넣어주면, glLoadIdentity 에 의해, 좌표값 관련 세팅이 초기화되기 때문
	// 앞 3 : 어디에서
	// 중간 3 : 어디로 볼 것인가
	// 뒤 3 : 어디가 위쪽인가 ( 0,1,0 : y축이 위쪽이다 ) 
	gluLookAt(
		cam_pos.camx, cam_pos.camy, cam_pos.camz,
		cam_pos.cam2x, cam_pos.cam2y, cam_pos.cam2z,
		cam_pos.cam_upx, cam_pos.cam_upy, cam_pos.cam_upz
	); // 보는 방향

	// Blend 효과 넣어주기
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 중앙을 나타내기 위해 점 하나 가운데에 그리기
	glPointSize(5);
	glBegin(GL_POINTS);
		glVertex3f(0, 0, 0);
	glEnd();

	if (displayMode == displayModes::SIMPLE_DRAWING)
		drawSimpleDrawing(a,b,color);
	if (displayMode == displayModes::TWO_D)
		drawClock();

	
	glutSwapBuffers();
}


void reshape(int width, int height)
{
	GLfloat left = 0, bottom = 0;
	// 오른쪽 상단에 위치하여 뷰포트 변환하기 
	glViewport(0, 0, width , height );
	GLfloat f_w = (GLfloat)width / (GLfloat)_WINDOW_WIDTH;
	GLfloat f_h = (GLfloat)height / (GLfloat)_WINDOW_HEIGHT;

	// glOrtho를 그리기 위해 필요한 2개 line
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 어디서부터, 어디까지 어떻게 볼 것인가 : -2  ~ 2
	// glOrtho(-2, 2, -2, 2, -2, 2);
	// glOrtho(-1 * f_w, 1 * f_w, -1 * f_h, 1 * f_h, -2, 2);
	GLfloat ratio = (float)(width - left) / (height - bottom);

	// ratio : X 방향의 뷰 필드를 결정 하는 가로 세로 비율입니다. 가로 세로 비율은 x (너비)와 y (높이)의 비율
	gluPerspective(60, ratio, 0.1, 10);

	// 가까이는 0.1 만큼 까지만
	// 멀리는 10까지만 보겠다 
	// gluPerspective(40, ratio, 0.1, 10);
}


void mykey(unsigned char key, int x, int y)
{
	// 앞으로 칠할 색상 선택하기 
	// red, yellow, blue, green, cyan, magenta
	switch (key)
	{
	case '1' :
		cout << "press 1" << endl;
		if (drawMode == drawModes::DRAW_OBJECT) figureMode = figureModes::LINE;
		break;
	case '2' :
		if (drawMode == drawModes::DRAW_OBJECT) figureMode = figureModes::RENTANGLE;
		break;
	case '3':
		if (drawMode == drawModes::DRAW_OBJECT) figureMode = figureModes::TRIANGLE;
		break;
	case '4':
		if (drawMode == drawModes::DRAW_OBJECT) figureMode = figureModes::ELLIPSE;
		break;
	case '5':
		if (drawMode == drawModes::DRAW_OBJECT) figureMode = figureModes::SPHERE;
		break;
	case '6':
		if (drawMode == drawModes::DRAW_OBJECT) figureMode = figureModes::BIG_ARROW;
		break;
	case '7':
		if (drawMode == drawModes::DRAW_OBJECT) figureMode = figureModes::THREE_WAY_LINE;
		break;
	case 'r':
		if (drawMode == drawModes::DRAW_OBJECT) color = vector3D(1.0, 0.0, 0.0);
		else if (drawMode == drawModes::EDIT_OBJECT && clickedFigIdx != -1)
		{
			polygon[clickedFigIdx].color = vector3D(1.0, 0.0, 0.0);
			glutPostRedisplay();
		}
		break;
	case 'y':
		if (drawMode == drawModes::DRAW_OBJECT) color = vector3D(1.0, 1.0, 0.0);
		else if (drawMode == drawModes::EDIT_OBJECT && clickedFigIdx != -1)
		{
			polygon[clickedFigIdx].color = vector3D(1.0, 1.0, 0.0);
			glutPostRedisplay();
		}
		break;
	case 'b':
		if (drawMode == drawModes::DRAW_OBJECT) color = vector3D(0.0, 0.0, 1.0);
		else if (drawMode == drawModes::EDIT_OBJECT && clickedFigIdx != -1)
		{
			polygon[clickedFigIdx].color = vector3D(0.0, 0.0, 1.0);
			glutPostRedisplay();
		}
		break;
	case 'g':
		if (drawMode == drawModes::DRAW_OBJECT) color = vector3D(0.0, 1.0, 0.0);
		else if (drawMode == drawModes::EDIT_OBJECT && clickedFigIdx != -1)
		{
			polygon[clickedFigIdx].color = vector3D(0.0, 1.0, 0.0);
			glutPostRedisplay();
		}
		break;
	case 'c':
		if (drawMode == drawModes::DRAW_OBJECT) color = vector3D(0.0, 1.0, 1.0);
		else if (drawMode == drawModes::EDIT_OBJECT && clickedFigIdx != -1)
		{
			polygon[clickedFigIdx].color = vector3D(0.0, 1.0, 1.0);
			glutPostRedisplay();
		}
		break;
	case 'm':
		if (drawMode == drawModes::DRAW_OBJECT) color = vector3D(1.0, 0.0, 1.0);
		else if (drawMode == drawModes::EDIT_OBJECT && clickedFigIdx != -1)
		{
			polygon[clickedFigIdx].color = vector3D(1.0, 0.0, 1.0);
			glutPostRedisplay();
		}
		break;
	case 'd': 
		// draw mode에 있고 + 선택한 도형이 존재한다면, 오른쪽으로 이동 
		if (drawMode == drawModes::EDIT_OBJECT && clickedFigIdx != -1) {
			cout << "right move" << endl;
			polygon[clickedFigIdx].a.x += 0.005;
			polygon[clickedFigIdx].b.x += 0.005;
			glutPostRedisplay();
		}
		// 그외 : drawMode로 바꾸기 
		else
		{
			cout << "mode changed to draw mode" << endl;
			drawMode = drawModes::DRAW_OBJECT; 
		}
		break;
	case 'e': 
		drawMode = drawModes::EDIT_OBJECT; 
		cout << "mode changed to edit mode" << endl;
		break;
	case 's': 
		// draw mode에 있고 + 선택한 도형이 존재한다면, 아래로 이동 
		if (drawMode == drawModes::EDIT_OBJECT && clickedFigIdx != -1) {
			cout << "down move" << endl;
			polygon[clickedFigIdx].a.y -= 0.005;
			polygon[clickedFigIdx].b.y -= 0.005;
			glutPostRedisplay();
		}
		// 그외 : drawMode로 바꾸기 
		else
		{
			cout << "mode changed to resize mode" << endl;
			drawMode = drawModes::RESIZE_OBJECT; 
		}
		break;
	case 'w':
		// draw mode에 있고 + 선택한 도형이 존재한다면, 위로 이동 
		if (drawMode == drawModes::EDIT_OBJECT && clickedFigIdx != -1) {
			cout << "up move" << endl;
			polygon[clickedFigIdx].a.y += 0.005;
			polygon[clickedFigIdx].b.y += 0.005;
			glutPostRedisplay();
		}
		break;
	case 'a':
		// draw mode에 있고 + 선택한 도형이 존재한다면, 왼쪽로 이동 
		if (drawMode == drawModes::EDIT_OBJECT && clickedFigIdx != -1) {
			cout << "left move" << endl;
			polygon[clickedFigIdx].a.x -= 0.005;
			polygon[clickedFigIdx].b.x -= 0.005;
			glutPostRedisplay();
		}
		break;
	case 46:
		std::cout << "delete btn clicked" << std::endl;
		if (drawMode == drawModes::EDIT_OBJECT && clickedFigIdx != -1) {
			// 해당 idx 부터 시작하여, array idx + 1을 앞으로 끌어당긴다
			for (int i = clickedFigIdx; i <= index; i++) {
				// .on == false : 아직 드래그가 안끝난 것 ( 아직 안그려진 것 )
				polygon[i] = polygon[i + 1];
			}
			// 그리고 index를 1 감소시켜준다 
			index -= 1;
			// 다시 clickedFigIdx를 -1로 세팅 
			clickedFigIdx = -1;
			// 화면 다시 그리기
			glutPostRedisplay();
		}
		break;
	case 'o':
		cout << "zoom out" << endl;
		cam_pos.camz += 0.01;
		glutPostRedisplay();
		break;
	case 'i':
		cout << "zoom in" << endl;
		cam_pos.camz -= 0.01;
		glutPostRedisplay();
		break;
	default :
		break;

	}
}

void checkResizeDir(float mouse_x, float mouse_y, vector3D fig_a, vector3D fig_b)
{
	float fig_width  = fig_b.x - fig_a.x;
	float fig_height = fig_a.y - fig_b.y;
	// 왼쪽 상단 
	if (abs(fig_a.x-mouse_x) < 0.1 * fig_width && abs(fig_a.y - mouse_y) < 0.* fig_height)
	{
		resizeDir = resizeDirs::LEFT_TOP;
	}
	// 왼쪽 하당
	if (abs(fig_a.x - mouse_x) < 0.1 * fig_width && abs(fig_b.y - mouse_y) < 0.1 * fig_height)
	{
		resizeDir = resizeDirs::LEFT_BOTTOM;
	}
	// 오른쪽 상단
	if (abs(fig_b.x - mouse_x) < 0.1 * fig_width && abs(fig_a.y - mouse_y) < 0.1 * fig_height)
	{
		resizeDir = resizeDirs::RIGHT_TOP;
	}
	// 오른쪽 하단 
	if (abs(fig_b.x - mouse_x) < 0.1 * fig_width && abs(fig_b.y - mouse_y) < 0.1 * fig_height)
	{
		resizeDir = resizeDirs::RIGHT_BOTTOM;
	}
}

bool checkRange(float x, float y, float poly_a_x, float poly_a_y, float poly_b_x, float poly_b_y)
{
	// 왼쪽 상단으로 드래그
	if (poly_b_x <= poly_a_x && poly_b_y > poly_a_y)
	{
		if ((x < poly_a_x && x >= poly_b_x) && (poly_a_y < y && y <= poly_b_y))
		{
			return true;
		}
		else {
			return false;
		}
	}
	// 왼쪽 하단으로 드래그
	if (poly_b_x <= poly_a_x && poly_b_y <= poly_a_y)
	{
		if ((x < poly_a_x && x >= poly_b_x) && (poly_a_y >= y && y >= poly_b_y))
		{
			return true;
		}
		else {
			return false;
		}
	}
	// 오른쪽 상단으로 드래그
	if (poly_b_x > poly_a_x && poly_b_y > poly_a_y)
	{
		if ((x < poly_b_x && x >= poly_a_x) && (poly_b_y >= y && y >= poly_a_y))
		{
			return true;
		}
		else {
			return false;
		}
	}
	// 오른쪽 하단으로 드래그 
	if (poly_b_x > poly_a_x && poly_b_y <= poly_a_y)
	{
		if ((x < poly_b_x && x >= poly_a_x) && (poly_a_y > y && y >= poly_b_y))
		{
			return true;
		}
		else {
			return false;
		}
	}
}

// 마우스 이벤트 -------------------------------------------------------------
void mymouse(int button, int state, int x, int y)
{
	float px, py;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		px = (float)x / (float)_WINDOW_WIDTH * 2.0 - 1.0;
		py = -(float)y / (float)_WINDOW_HEIGHT * 2.0 + 1.0;
		// 수정 모드
		std::cout << "checkFigure(px, py)" << checkFigure(px, py) << std::endl;
		if (polygon[index].on == true) index++;
		// 그리기 모드
		if (drawMode == drawModes::DRAW_OBJECT)
		{
			polygon[index].a = vector3D(px, py,0);
			// 키보드 입력으로, color, mode를 받기는 하지만
			// 키보드 입력을 아무것도 안했을 때 !!! default setting을 해주는 ㅓㄱㅅ이다
			polygon[index].color = color;
			polygon[index].pmode = static_cast<int>(figureMode);
		}
		else if (drawMode == drawModes::EDIT_OBJECT && clickedFigIdx != -1)
		{
			// 이동 모드 변환
			// drawMode == MOVE_OBJECT;
			// 현재좌표값으로 세팅
			polygon[clickedFigIdx].sp.x = px, polygon[clickedFigIdx].sp.y = py;
		}
		else if (drawMode == drawModes::RESIZE_OBJECT)
		{
			polygon[clickedFigIdx].sp.x = px, polygon[clickedFigIdx].sp.y = py;
		}
	}
}

void mymousemotion(int x, int y)
{
	float px, py;
	px = (float)x / (float)_WINDOW_WIDTH * 2.0 - 1.0;
	py = -(float)y / (float)_WINDOW_HEIGHT * 2.0 + 1.0;
	if (drawMode == drawModes::DRAW_OBJECT)
	{
		polygon[index].b = vector3D(px, py,0); // b 에다가 넣고
		polygon[index].on = true; // 드래그 및 움직임이 있었으므로 true로 세팅
		glutPostRedisplay();
	}
	// 해당 도형 이동 및 사이즈 조정
	else if (drawMode == drawModes::EDIT_OBJECT && clickedFigIdx != -1)
	{
		cout << "abs(polygon[clickedFigIdx].a.x - polygon[clickedFigIdx].sp.x ) : " << abs(polygon[clickedFigIdx].a.x - polygon[clickedFigIdx].sp.x) << endl;
		cout << "abs(polygon[clickedFigIdx].a.y - polygon[clickedFigIdx].sp.y ) : " << abs(polygon[clickedFigIdx].a.y - polygon[clickedFigIdx].sp.y) << endl;

		polygon[clickedFigIdx].a = vector3D(polygon[clickedFigIdx].a.x + (px - polygon[clickedFigIdx].sp.x),
			polygon[clickedFigIdx].a.y + (py - polygon[clickedFigIdx].sp.y),
			0); // a 에다가 넣고
		polygon[clickedFigIdx].b = vector3D(polygon[clickedFigIdx].b.x + (px - polygon[clickedFigIdx].sp.x),
			polygon[clickedFigIdx].b.y + (py - polygon[clickedFigIdx].sp.y),
			0); // b 에다가 넣고
		
		polygon[clickedFigIdx].sp.x = px, polygon[clickedFigIdx].sp.y = py; // start position update
		polygon[clickedFigIdx].on = true; // 드래그 및 움직임이 있었으므로 true로 세팅
		glutPostRedisplay();
	}
	else if (drawMode == drawModes::RESIZE_OBJECT)
	{
		cout << "resize" << endl;
		// 어떤 방향으로 resize 할지를 정한다 
		checkResizeDir(px, py, polygon[clickedFigIdx].a, polygon[clickedFigIdx].b);
		if (resizeDir == resizeDirs::LEFT_TOP)
		{
			cout << "left_top" << endl;
			polygon[clickedFigIdx].a = vector3D(polygon[clickedFigIdx].a.x + (px - polygon[clickedFigIdx].sp.x),
				polygon[clickedFigIdx].a.y + (py - polygon[clickedFigIdx].sp.y)); // a 에다가 넣고
		}
		if (resizeDir == resizeDirs::LEFT_BOTTOM)
		{
			cout << "left_bottom" << endl;
			polygon[clickedFigIdx].a.x = polygon[clickedFigIdx].a.x + (px - polygon[clickedFigIdx].sp.x);
			polygon[clickedFigIdx].b.y = polygon[clickedFigIdx].b.y + (py - polygon[clickedFigIdx].sp.y);
		}
		if (resizeDir == resizeDirs::RIGHT_TOP)
		{
			cout << "right_top" << endl;
			polygon[clickedFigIdx].b.x = polygon[clickedFigIdx].b.x + (px - polygon[clickedFigIdx].sp.x);
			polygon[clickedFigIdx].a.y = polygon[clickedFigIdx].a.y + (py - polygon[clickedFigIdx].sp.y);
		}
		if (resizeDir == resizeDirs::RIGHT_BOTTOM)
		{
			cout << "right_bottom" << endl;
			polygon[clickedFigIdx].b.x = polygon[clickedFigIdx].b.x + (px - polygon[clickedFigIdx].sp.x);
			polygon[clickedFigIdx].b.y = polygon[clickedFigIdx].b.y + (py - polygon[clickedFigIdx].sp.y);
		}
		// start position update
		polygon[clickedFigIdx].sp.x = px, polygon[clickedFigIdx].sp.y = py;
		polygon[clickedFigIdx].on = true; // 드래그 및 움직임이 있었으므로 true로 세팅
		glutPostRedisplay();
	}
}

// menu callback
void selectMenu(int value) {
	// Exit 이면 빠져나가기
	if (value == 2)
		exit(0);
}
void selectSubMenu(int value) {
	// 선택한 도형으로 mode 지정
	// 2d
	if (value == 2)
	{
		displayMode = displayModes::TWO_D;
		glutPostRedisplay();
	}
	// 3d
	else if (value == 3)
	{
		displayMode = displayModes::THREE_D;
		glutPostRedisplay();
	}
	else {
		displayMode = displayModes::SIMPLE_DRAWING;
	}
}
void selectDrawMenu(int value) {
	//enum drawModes { DRAW_OBJECT = 1, EDIT_OBJECT, RESIZE_OBJECT };
	if (displayMode != displayModes::SIMPLE_DRAWING)
	{
		displayMode = displayModes::SIMPLE_DRAWING;
		glutPostRedisplay();
	}

	if (value == 1)
		drawMode = drawModes::DRAW_OBJECT;
	else if (value == 2)
		drawMode = drawModes::EDIT_OBJECT;
	else if (value == 3)
		drawMode = drawModes::RESIZE_OBJECT;
}
void selectFigMenu(int value) {
	// 도형 모양 선택하기 
	if (displayMode != displayModes::SIMPLE_DRAWING)
	{
		displayMode = displayModes::SIMPLE_DRAWING;
		glutPostRedisplay();
	}
	
	if (value == 1) // line
		figureMode = figureModes::LINE;
	else if (value == 2) // 사각형 
		figureMode = figureModes::RENTANGLE;
	else if (value == 3) // triangle 
		figureMode = figureModes::TRIANGLE;
	else if (value == 4) // 타원
		figureMode = figureModes::ELLIPSE;
	else if (value == 5) // 원 그리기 
		figureMode = figureModes::SPHERE;
	else if (value == 6) // 거대 화살표 그리기 
		figureMode = figureModes::BIG_ARROW;
	else if (value == 7) // 세방향 직선 조합 그리기 
		figureMode = figureModes::THREE_WAY_LINE;
	
}
