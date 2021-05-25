#include "cg.h"
#include "draw.h"
void mydisplay() // -1 부터 +1 까지의 범위이다 
{
	/*
	-- 점진적인 원 drawing
		float x, y; x = 0.0; y = 0.0;
		glBegin(GL_POINTS);
		glPointSize(10);
		glColor3f(1.0, 0.0, 1.0);
		for (float r = 0.0, g = 0.0; r <= 1.0; r += 0.00001, g += 0.001) {
			// 원을 그려가는데, 반지름이 조금씩 증가하는 형태이다
			x = r * cos(g);
			y = r * sin(g);
			glVertex2f(x, y);
		}
		glEnd();
	*/

	/*
	-- sin 함수 그리기

	float x, y; x = 0.0; y = 0.0;
	glBegin(GL_POINTS);
	glPointSize(10);

	for (float x = -1.0; x <= 1.0; x += 0.001) {
		// 원을 그려가는데, 반지름이 조금씩 증가하는 형태이다
		// M_PI * x 라고 해주는 이유는 ? 이렇게 되면 -파이 ~ 파이. 범위 까지의 그림을 그리게 된다
		// sin(2 * M_PI * x) : -360 ~ 360 까지 나오게 된다
		// 0.5 * sin(2 * M_PI * x) 을 해주게 되면, 위아래로 조금은 수축된 형태의 그래프를 얻는다
		glColor3f(1.0, 0.0, 1.0);
		y = 0.5 * sin(2 * M_PI * x);
		glVertex2f(x, y);
		glColor3f(1.0, 1.0, 0.0);
		y = 0.5 * cos(2 * M_PI * x);
		glVertex2f(x, y);
	}
	glEnd();
	*/

	/* -- y = x ^ 2
		float x, y; x = -1.0; y = 1.0; // 초기 시작점
		glLineWidth(4.0);
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_LINES);
		for (float t = -1.0; t <= 1.0; t += 0.05) {
			// 여기와 아래, 2개의 vertext를 세팅해주는 이유는
			// 여기 점과, 다음 점 사이의 선을 그려야 하기 때문이다
			glVertex2f(x, y);
			x = t;
			y = t * t;
			glVertex2f(x, y);
		}
		glEnd();
	*/

	// 먼저 기본이 되는 사각형 2개를 그린다 
	/* -- 원 3개 그리기 
		glColor3f(1.0, 1.0, 1.0);
		rect(vector2D(-1.0, 1.0), vector2D(1.0, -1.0));
		// 검정 사각형 외곽선 그리기
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(5.0);
		glColor3f(0.0, 0.0, 0.0);
		rect(vector2D(-1.0, 1.0), vector2D(1.0, -1.0));

		// 1) 큰 원 그리기
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(1.0, 1.0, 0.0);
		circle(vector2D(0.0, -0.2), 0.6);
		// 가운데 큰 원 외곽선 그리기
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(3.0);
		glColor3f(1.0, 1.0, 0.0);
		circle(vector2D(0.0, -0.2), 0.6);

		// 2) 중간 원 그리기
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(1.0, 0.7, 0.0);
		circle(vector2D(0.0, -0.4), 0.4);
		// 가운데 큰 원 외곽선 그리기
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(3.0);
		glColor3f(1.0, 0.7, 0.0);
		circle(vector2D(0.0, -0.4), 0.4);

		// 3) 제일 작은 원 그리기
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(1.0, 0.0, 0.0);
		circle(vector2D(0.0, -0.6), 0.2);
		// 가운데 큰 원 외곽선 그리기
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(3.0);
		glColor3f(1.0, 0.0, 0.0);
		circle(vector2D(0.0, -0.6), 0.2);
	*/
		

	/* -- red transparency
		// opengl default 세팅은, rgba 에서 a를 안쓰는 것
		// 맨 마지막 alpha 값을 사용하기 위해서 이를 허용해주어야 하는 것이다
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// 먼저 기본이 되는 사각형 2개를 그린다
		glColor3f(0, 0, 0);
		rect(vector2D(0.0, 1.0), vector2D(1.0, -1.0));
		glColor3f(0, 0, 1.0);
		rect(vector2D(-1.0, 1.0), vector2D(0.0, -1.0));

		glColor4f(1.0, 0, 0.0, 1.0); // rgba --> a까지 추가해서, 투명도를 조절
		rect(vector2D(-1.0, 1.0), vector2D(1.0, 0.6));
		glColor4f(1.0, 0, 0.0, 0.8);
		rect(vector2D(-1.0, 0.5), vector2D(1.0, 0.1));
		glColor4f(1.0, 0, 0.0, 0.5);
		rect(vector2D(-1.0, 0.0), vector2D(1.0, -0.4));
		glColor4f(1.0, 0, 0.0, 0.2);
		rect(vector2D(-1.0, -0.5), vector2D(1.0, -0.9));
	*/

	/* -- circular face
		glColor3f(0.7, 0.7, 0.7);
		rect(vector2D(-1.0, 1.0), vector2D(1.0, -1.0));

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 흰색 사각형 그리기
		glColor3f(1.0, 1.0, 1.0);
		rect(vector2D(-0.1, 0.1), vector2D(0.1, -0.6));

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 검정 사각형 외곽선 그리기
		glLineWidth(3.0);
		glColor3f(0.0, 0.0, 0.0);
		rect(vector2D(-0.1, 0.1), vector2D(0.1, -0.6));

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 가운데 큰 원 그리기
		glColor3f(1.0, 1.0, 1.0);
		circle(vector2D(0.0, 0.4), 0.35);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 가운데 큰 원 외곽선 그리기
		glLineWidth(3.0);
		glColor3f(0.0, 0.0, 0.0);
		circle(vector2D(0.0, 0.4), 0.35);

		ellipse(vector2D(-0.2, 0.4), 0.1, 0.2); // 원 안의 타원형 그리기
		ellipse(vector2D(0.2, 0.4), 0.1, 0.2);

		line(vector2D(-0.1, -0.6), vector2D(-0.2, -0.7));
		line(vector2D(0.1, -0.6), vector2D(0.2, -0.7));
	*/


	/* --
		glColor3f(0.4, 0.4, 0.4); // 0.8로 갈수록 더 밝아지는 형태를 띤다고 할 수 있다
		rect(vector2D(-1.0, 1.0), vector2D(1.0, -1.0));

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_LINE : polygon을 그릴 때, 외곽선만 그려라
		glColor3f(1.0, 1.0, 1.0);
		rect(vector2D(-0.7, 0.7), vector2D(0.2, -0.2));

		glColor3f(0.0, 0.0, 0.0);
		glLineWidth(5.0); // line의 두께
		line(vector2D(-1.0, 1.0), vector2D(1.0, -1.0));
	*/

	glutSwapBuffers();
	/* -- 기본 도형들 그리기
		glColor3f(1.0, 0.0, 0.0);
		line(vector2D(0.2, -0.5), vector2D(0.2, 0.5));

		glColor3f(1.0, 1.0, 0.0);
		rect(vector2D(-0.5, 0.4), vector2D(0.4, -0.3));

		glColor3f(1.0, 0.0, 1.0);
		circle(vector2D(0.0, 0.0), 0.2);
	*/

	/*  -- 서로 다른 사각형 그리기
		glColor3f(1.0, 0.0, 0.0);
		rect(-0.5, -0.7, 0.5, 0.7);
		glColor3f(0.0, 1.0, 0.0);
		rect(-0.3, -0.7, 0.3, 0.5);
		glColor3f(0.0, 0.0, 1.0);
		rect(-0.2, -0.7, 0.2, 0.3);
	*/
}

/*
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutCreateWindow("simple");
	glutDisplayFunc(mydisplay);

	glutMainLoop();
}
*/

