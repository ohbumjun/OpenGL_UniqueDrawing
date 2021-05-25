// 모델 변환 실습 
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


// cam : 어디서 보느냐
// ex) 0.5, -0.5 ,1 : 밑에서 위를 보기 
GLfloat camx = 0.5, camy = 1, camz = 2;
// center : 어디를 보느냐 
GLfloat cam2x = 0, cam2y = 0, cam2z = 0;// 원점 바라봄
// cam_up : 어디가 위쪽이냐
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

int list_id;
int w = 1024;
int h = 1024;

// 빛 넣어주기 
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
	glEnable(GL_CULL_FACE); // 절단면 제거 세팅 
	glDisable(GL_CULL_FACE); // 절단면 제거 무효화
	
	// glPolygonMode(GL_FRONT, GL_FILL); // 앞면 채우기
	// glPolygonMode(GL_BACK, GL_LINE);  // 뒷면은 선만 보이게 하기 

	glPolygonMode(GL_FRONT, GL_LINE); // 앞면 채우기
	// 사실 아래에서 cullface back을 해준다면 여기서 굳이 이코드를 넣을 필요는 없다 
	glPolygonMode(GL_BACK, GL_LINE);  

	glFrontFace(GL_CW);     // clockwise가 front face 
	// glCullFace(GL_BACK);	// 후면 제거 실제 적용 
	// glCullFace(GL_FRONT);    // 전면 제거 
	glEnable(GL_DEPTH_TEST);

	// 절단면 추가
	glEnable(GL_CLIP_PLANE0); // 0번 절단면 사용하겠다


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
	); // 보는 방향

	// gluLookAt 
	// 카메라 방향이 정해진 이후에 절단면을 제거하는 코드를 넣어야
	// 실제 물체 중심으로 잘려진 효과가 나온다 
	// GLdouble eq[4] = { 0,1,0,0 }; // y 가 0인 평면 위쪽만 살리겠다 
	GLdouble eq[4] = { 0,0,1,0 }; // z가 0 --> 세로로 잘림  
	glClipPlane(GL_CLIP_PLANE0, eq);

	glutSolidTeapot(0.3);
	glutSwapBuffers();
}

void MyReshape(int width, int height)
{
	// glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	GLfloat left = 0, bottom = 0;
	// 오른쪽 상단에 위치하여 뷰포트 변환하기 
	glViewport(left, bottom, width - left, height - bottom);
	// gluPerspective를 하기 전, mode가 GL_PROJECTION으로 바뀌어있는 것을
	// 확인할 수 있다 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// 어디서부터, 어디까지 어떻게 볼 것인가 : -2  ~ 2


	GLfloat ratio = (float)(width - left) / (height - bottom);
	// 가까이는 0.1 만큼 까지만
	// 멀리는 10까지만 보겠다 
	gluPerspective(40, ratio, 0.1, 10);

	// < 크게 보이고, 작게 보이고 차이 >
	// 1) robot, camera 위치 
	// 지금 robot body는 원점
	// 카메라는 camz , 즉, z 축으로 1만큼만 떨어짐
	// 상당히 가까이 놓인 상태이다 
	// 2) 보는 각도 : 60 도 
	// 각도가 작아질 수록, 작은 범위를 본다
	// 즉, 대상은 크게 보인다 
	// 단, 너무 넓게 보면, 왜곡이 생기기 때문에 주의하자 
}

void MyTimer(int value)
{

	// 카메라 회전 animation 
	// 세로 y축을 기준으로
	// y좌표는 그대로 있고 
	// y 축 기준 돌아가면서 돌기 
	GLfloat theta = 0.01;
	GLfloat tmp_x = camx; // 기존에 있던 x 좌표 그대로 
	camx = camx * cos(theta) + camz * sin(theta);
	camz = -tmp_x * sin(theta) + camz * cos(theta);

	// 참고 : 카메라 변환 애니메이션은 
	// 별도 timer func 둬도 된다 
	glutTimerFunc(1000 / 60, MyTimer, 1);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	// GLUT_DEPTH : 깊이 버퍼를 사용하겠다 
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// glutwindowsize가 맨 앞에 나온다음 create window !
	glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("title");

	glClearColor(-.5, 0.5, 0.5, 0.0); // 배경화면 

	// 빛을 효과 
	InitLight();
	InitVisibility();

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutTimerFunc(1000/60, MyTimer, 1);

	// 절단면 몇개 쓸 수 있는지 확인하기 
	int num;
	glGetIntegerv(GL_MAX_CLIP_PLANES,&num);
	printf("num of clip planes : %d", num);

	glutMainLoop();
	return 0;
}



*/