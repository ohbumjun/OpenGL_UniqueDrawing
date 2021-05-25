// INTERACTIVE DRAWING

#include "cg.h"
#include "draw.h"
#include <cmath>
#include<iostream>

using namespace std;

#define _WINDOW_WIDTH  1024
#define _WINDOW_HEIGHT 1024

struct polytype {
	vector3D a, b ; // ���� ��ġ, �� ��ġ 
	vector3D sp, cp; // ���콺 �巡�� �� ����, �巡�� �� ��ġ 
	int pmode;// 1: line, 2: triangle, 3:circle, 4:rectangle -> ������ �� �߰��� ���� �ִ� 
	vector3D color;
	bool on = false; // Ŭ����, �巡�� ������, true(�����׷���) // �ƴϸ� false( �ȱ׷��� )
};
polytype polygon[100];

int clickedFigIdx = -1 ;
int index = 0; // ���° polygon �� �׸��� �ִ°� 

enum class displayModes {SIMPLE_DRAWING = 1, TWO_D, THREE_D};
displayModes displayMode = displayModes::SIMPLE_DRAWING;
enum class colorModes {RED = 1, YELLOW, BLUE, GREEN, CYAN, MATAGATA};
colorModes colorMode = colorModes::RED;
enum class figureModes { LINE = 1, RENTANGLE,TRIANGLE, ELLIPSE, SPHERE, BIG_ARROW, THREE_WAY_LINE };
figureModes figureMode = figureModes::LINE;
enum class drawModes { DRAW_OBJECT = 1, EDIT_OBJECT, RESIZE_OBJECT };
drawModes drawMode = drawModes::DRAW_OBJECT; // 0 : �׸���, 1 : ���� 
enum class resizeDirs {LEFT_TOP = 1,LEFT_BOTTOM,RIGHT_TOP,RIGHT_BOTTOM};
resizeDirs resizeDir = resizeDirs::LEFT_TOP;
vector3D color = vector3D(0.9, 0.9, 0.8);

struct campos {
	// cam : ��� ������
// ex) 0.5, -0.5 ,1 : �ؿ��� ���� ���� 
// ex) 0.0, -0.0 ,5 : �� ������ �Ʒ��� ������ ����
	GLfloat camx = 0.0, camy = -0.0, camz = 1;
	// center : ��� ������ 
	GLfloat cam2x = 0, cam2y = 0, cam2z = 0;// ���� �ٶ�
	// cam_up : ��� �����̳�
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
		glutSetMenu(drawMenuId);// ���� �޴� ���� 
		glutAttachMenu(GLUT_RIGHT_BUTTON);// menu �� ���콺 ��ư�� ���
		// 3D Model�� Ŭ����, �Ʒ��� 3�� subMenu�� ������ ���̴� 
		glutAddMenuEntry("Draw Mode", 1); // �޴��� ���� �־��ֱ�
		glutAddMenuEntry("Edit Mode", 2);
		glutAddMenuEntry("Resize Mode", 3);

	int figureMenuId = glutCreateMenu(selectFigMenu);
		glutSetMenu(figureMenuId);// ���� �޴� ���� 
		glutAttachMenu(GLUT_RIGHT_BUTTON);// menu �� ���콺 ��ư�� ���
		// 3D Model�� Ŭ����, �Ʒ��� 3�� subMenu�� ������ ���̴� 
		glutAddMenuEntry("Line", static_cast<int>(figureModes::LINE)); // �޴��� ���� �־��ֱ�
		glutAddMenuEntry("Rectangle", static_cast<int>(figureModes::RENTANGLE));
		glutAddMenuEntry("Triangle", static_cast<int>(figureModes::TRIANGLE));
		glutAddMenuEntry("Ellipse", static_cast<int>(figureModes::ELLIPSE));
		glutAddMenuEntry("Sphere", static_cast<int>(figureModes::SPHERE));
		glutAddMenuEntry("Big Arrow", static_cast<int>(figureModes::BIG_ARROW));
		glutAddMenuEntry("3 Way Lines", static_cast<int>(figureModes::THREE_WAY_LINE));

	int simpleDrawMenuId = glutCreateMenu(selectSubMenu);
		glutSetMenu(simpleDrawMenuId);// ���� �޴� ���� 
		glutAttachMenu(GLUT_RIGHT_BUTTON);// menu �� ���콺 ��ư�� ���
		glutAddSubMenu("Draw Mode", drawMenuId); // �޴��� ���� �־��ֱ�
		glutAddSubMenu("Figure", figureMenuId);

	int subMenuId = glutCreateMenu(selectSubMenu);
		glutSetMenu(subMenuId);// ���� �޴� ���� 
		glutAttachMenu(GLUT_RIGHT_BUTTON);// menu �� ���콺 ��ư�� ���
		glutAddSubMenu("Simple Drawing", simpleDrawMenuId); // �޴��� ���� �־��ֱ�
		glutAddMenuEntry("2D", 2);
		glutAddMenuEntry("3D", 3);

	int mainMenuId = glutCreateMenu(selectMenu);
		glutSetMenu(mainMenuId);// ���� �޴� ���� 
		glutAttachMenu(GLUT_RIGHT_BUTTON);// menu �� ���콺 ��ư�� ���
		glutAddSubMenu("What do you want", subMenuId); // �޴��� ���� �־��ֱ�
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
		// .on == false : ���� �巡�װ� �ȳ��� �� ( ���� �ȱ׷��� �� )
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
				// x : ������ġ, y : ���� ��ġ 
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

	// 1_ animation�� ���� ī�޶� ���� ��ȯ�� �����ϱ� ���ؼ���
	// gluLookAt�� display �Լ��� �־��־�� �Ѵ� 
	// 2) glMatrixMode(GL_MODELVIEW); �ȿ��ٰ� �־��־�� �Ѵ�
	// �ۿ� �־��ָ�, glLoadIdentity �� ����, ��ǥ�� ���� ������ �ʱ�ȭ�Ǳ� ����
	// �� 3 : ��𿡼�
	// �߰� 3 : ���� �� ���ΰ�
	// �� 3 : ��� �����ΰ� ( 0,1,0 : y���� �����̴� ) 
	gluLookAt(
		cam_pos.camx, cam_pos.camy, cam_pos.camz,
		cam_pos.cam2x, cam_pos.cam2y, cam_pos.cam2z,
		cam_pos.cam_upx, cam_pos.cam_upy, cam_pos.cam_upz
	); // ���� ����

	// Blend ȿ�� �־��ֱ�
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// �߾��� ��Ÿ���� ���� �� �ϳ� ����� �׸���
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
	// ������ ��ܿ� ��ġ�Ͽ� ����Ʈ ��ȯ�ϱ� 
	glViewport(0, 0, width , height );
	GLfloat f_w = (GLfloat)width / (GLfloat)_WINDOW_WIDTH;
	GLfloat f_h = (GLfloat)height / (GLfloat)_WINDOW_HEIGHT;

	// glOrtho�� �׸��� ���� �ʿ��� 2�� line
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// ��𼭺���, ������ ��� �� ���ΰ� : -2  ~ 2
	// glOrtho(-2, 2, -2, 2, -2, 2);
	// glOrtho(-1 * f_w, 1 * f_w, -1 * f_h, 1 * f_h, -2, 2);
	GLfloat ratio = (float)(width - left) / (height - bottom);

	// ratio : X ������ �� �ʵ带 ���� �ϴ� ���� ���� �����Դϴ�. ���� ���� ������ x (�ʺ�)�� y (����)�� ����
	gluPerspective(60, ratio, 0.1, 10);

	// �����̴� 0.1 ��ŭ ������
	// �ָ��� 10������ ���ڴ� 
	// gluPerspective(40, ratio, 0.1, 10);
}


void mykey(unsigned char key, int x, int y)
{
	// ������ ĥ�� ���� �����ϱ� 
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
		// draw mode�� �ְ� + ������ ������ �����Ѵٸ�, ���������� �̵� 
		if (drawMode == drawModes::EDIT_OBJECT && clickedFigIdx != -1) {
			cout << "right move" << endl;
			polygon[clickedFigIdx].a.x += 0.005;
			polygon[clickedFigIdx].b.x += 0.005;
			glutPostRedisplay();
		}
		// �׿� : drawMode�� �ٲٱ� 
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
		// draw mode�� �ְ� + ������ ������ �����Ѵٸ�, �Ʒ��� �̵� 
		if (drawMode == drawModes::EDIT_OBJECT && clickedFigIdx != -1) {
			cout << "down move" << endl;
			polygon[clickedFigIdx].a.y -= 0.005;
			polygon[clickedFigIdx].b.y -= 0.005;
			glutPostRedisplay();
		}
		// �׿� : drawMode�� �ٲٱ� 
		else
		{
			cout << "mode changed to resize mode" << endl;
			drawMode = drawModes::RESIZE_OBJECT; 
		}
		break;
	case 'w':
		// draw mode�� �ְ� + ������ ������ �����Ѵٸ�, ���� �̵� 
		if (drawMode == drawModes::EDIT_OBJECT && clickedFigIdx != -1) {
			cout << "up move" << endl;
			polygon[clickedFigIdx].a.y += 0.005;
			polygon[clickedFigIdx].b.y += 0.005;
			glutPostRedisplay();
		}
		break;
	case 'a':
		// draw mode�� �ְ� + ������ ������ �����Ѵٸ�, ���ʷ� �̵� 
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
			// �ش� idx ���� �����Ͽ�, array idx + 1�� ������ �������
			for (int i = clickedFigIdx; i <= index; i++) {
				// .on == false : ���� �巡�װ� �ȳ��� �� ( ���� �ȱ׷��� �� )
				polygon[i] = polygon[i + 1];
			}
			// �׸��� index�� 1 ���ҽ����ش� 
			index -= 1;
			// �ٽ� clickedFigIdx�� -1�� ���� 
			clickedFigIdx = -1;
			// ȭ�� �ٽ� �׸���
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
	// ���� ��� 
	if (abs(fig_a.x-mouse_x) < 0.1 * fig_width && abs(fig_a.y - mouse_y) < 0.* fig_height)
	{
		resizeDir = resizeDirs::LEFT_TOP;
	}
	// ���� �ϴ�
	if (abs(fig_a.x - mouse_x) < 0.1 * fig_width && abs(fig_b.y - mouse_y) < 0.1 * fig_height)
	{
		resizeDir = resizeDirs::LEFT_BOTTOM;
	}
	// ������ ���
	if (abs(fig_b.x - mouse_x) < 0.1 * fig_width && abs(fig_a.y - mouse_y) < 0.1 * fig_height)
	{
		resizeDir = resizeDirs::RIGHT_TOP;
	}
	// ������ �ϴ� 
	if (abs(fig_b.x - mouse_x) < 0.1 * fig_width && abs(fig_b.y - mouse_y) < 0.1 * fig_height)
	{
		resizeDir = resizeDirs::RIGHT_BOTTOM;
	}
}

bool checkRange(float x, float y, float poly_a_x, float poly_a_y, float poly_b_x, float poly_b_y)
{
	// ���� ������� �巡��
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
	// ���� �ϴ����� �巡��
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
	// ������ ������� �巡��
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
	// ������ �ϴ����� �巡�� 
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

// ���콺 �̺�Ʈ -------------------------------------------------------------
void mymouse(int button, int state, int x, int y)
{
	float px, py;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		px = (float)x / (float)_WINDOW_WIDTH * 2.0 - 1.0;
		py = -(float)y / (float)_WINDOW_HEIGHT * 2.0 + 1.0;
		// ���� ���
		std::cout << "checkFigure(px, py)" << checkFigure(px, py) << std::endl;
		if (polygon[index].on == true) index++;
		// �׸��� ���
		if (drawMode == drawModes::DRAW_OBJECT)
		{
			polygon[index].a = vector3D(px, py,0);
			// Ű���� �Է�����, color, mode�� �ޱ�� ������
			// Ű���� �Է��� �ƹ��͵� ������ �� !!! default setting�� ���ִ� �ä����̴�
			polygon[index].color = color;
			polygon[index].pmode = static_cast<int>(figureMode);
		}
		else if (drawMode == drawModes::EDIT_OBJECT && clickedFigIdx != -1)
		{
			// �̵� ��� ��ȯ
			// drawMode == MOVE_OBJECT;
			// ������ǥ������ ����
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
		polygon[index].b = vector3D(px, py,0); // b ���ٰ� �ְ�
		polygon[index].on = true; // �巡�� �� �������� �־����Ƿ� true�� ����
		glutPostRedisplay();
	}
	// �ش� ���� �̵� �� ������ ����
	else if (drawMode == drawModes::EDIT_OBJECT && clickedFigIdx != -1)
	{
		cout << "abs(polygon[clickedFigIdx].a.x - polygon[clickedFigIdx].sp.x ) : " << abs(polygon[clickedFigIdx].a.x - polygon[clickedFigIdx].sp.x) << endl;
		cout << "abs(polygon[clickedFigIdx].a.y - polygon[clickedFigIdx].sp.y ) : " << abs(polygon[clickedFigIdx].a.y - polygon[clickedFigIdx].sp.y) << endl;

		polygon[clickedFigIdx].a = vector3D(polygon[clickedFigIdx].a.x + (px - polygon[clickedFigIdx].sp.x),
			polygon[clickedFigIdx].a.y + (py - polygon[clickedFigIdx].sp.y),
			0); // a ���ٰ� �ְ�
		polygon[clickedFigIdx].b = vector3D(polygon[clickedFigIdx].b.x + (px - polygon[clickedFigIdx].sp.x),
			polygon[clickedFigIdx].b.y + (py - polygon[clickedFigIdx].sp.y),
			0); // b ���ٰ� �ְ�
		
		polygon[clickedFigIdx].sp.x = px, polygon[clickedFigIdx].sp.y = py; // start position update
		polygon[clickedFigIdx].on = true; // �巡�� �� �������� �־����Ƿ� true�� ����
		glutPostRedisplay();
	}
	else if (drawMode == drawModes::RESIZE_OBJECT)
	{
		cout << "resize" << endl;
		// � �������� resize ������ ���Ѵ� 
		checkResizeDir(px, py, polygon[clickedFigIdx].a, polygon[clickedFigIdx].b);
		if (resizeDir == resizeDirs::LEFT_TOP)
		{
			cout << "left_top" << endl;
			polygon[clickedFigIdx].a = vector3D(polygon[clickedFigIdx].a.x + (px - polygon[clickedFigIdx].sp.x),
				polygon[clickedFigIdx].a.y + (py - polygon[clickedFigIdx].sp.y)); // a ���ٰ� �ְ�
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
		polygon[clickedFigIdx].on = true; // �巡�� �� �������� �־����Ƿ� true�� ����
		glutPostRedisplay();
	}
}

// menu callback
void selectMenu(int value) {
	// Exit �̸� ����������
	if (value == 2)
		exit(0);
}
void selectSubMenu(int value) {
	// ������ �������� mode ����
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
	// ���� ��� �����ϱ� 
	if (displayMode != displayModes::SIMPLE_DRAWING)
	{
		displayMode = displayModes::SIMPLE_DRAWING;
		glutPostRedisplay();
	}
	
	if (value == 1) // line
		figureMode = figureModes::LINE;
	else if (value == 2) // �簢�� 
		figureMode = figureModes::RENTANGLE;
	else if (value == 3) // triangle 
		figureMode = figureModes::TRIANGLE;
	else if (value == 4) // Ÿ��
		figureMode = figureModes::ELLIPSE;
	else if (value == 5) // �� �׸��� 
		figureMode = figureModes::SPHERE;
	else if (value == 6) // �Ŵ� ȭ��ǥ �׸��� 
		figureMode = figureModes::BIG_ARROW;
	else if (value == 7) // ������ ���� ���� �׸��� 
		figureMode = figureModes::THREE_WAY_LINE;
	
}
