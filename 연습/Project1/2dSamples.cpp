#include "cg.h"
#include "draw.h"
void mydisplay() // -1 ���� +1 ������ �����̴� 
{
	/*
	-- �������� �� drawing
		float x, y; x = 0.0; y = 0.0;
		glBegin(GL_POINTS);
		glPointSize(10);
		glColor3f(1.0, 0.0, 1.0);
		for (float r = 0.0, g = 0.0; r <= 1.0; r += 0.00001, g += 0.001) {
			// ���� �׷����µ�, �������� ���ݾ� �����ϴ� �����̴�
			x = r * cos(g);
			y = r * sin(g);
			glVertex2f(x, y);
		}
		glEnd();
	*/

	/*
	-- sin �Լ� �׸���

	float x, y; x = 0.0; y = 0.0;
	glBegin(GL_POINTS);
	glPointSize(10);

	for (float x = -1.0; x <= 1.0; x += 0.001) {
		// ���� �׷����µ�, �������� ���ݾ� �����ϴ� �����̴�
		// M_PI * x ��� ���ִ� ������ ? �̷��� �Ǹ� -���� ~ ����. ���� ������ �׸��� �׸��� �ȴ�
		// sin(2 * M_PI * x) : -360 ~ 360 ���� ������ �ȴ�
		// 0.5 * sin(2 * M_PI * x) �� ���ְ� �Ǹ�, ���Ʒ��� ������ ����� ������ �׷����� ��´�
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
		float x, y; x = -1.0; y = 1.0; // �ʱ� ������
		glLineWidth(4.0);
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_LINES);
		for (float t = -1.0; t <= 1.0; t += 0.05) {
			// ����� �Ʒ�, 2���� vertext�� �������ִ� ������
			// ���� ����, ���� �� ������ ���� �׷��� �ϱ� �����̴�
			glVertex2f(x, y);
			x = t;
			y = t * t;
			glVertex2f(x, y);
		}
		glEnd();
	*/

	// ���� �⺻�� �Ǵ� �簢�� 2���� �׸��� 
	/* -- �� 3�� �׸��� 
		glColor3f(1.0, 1.0, 1.0);
		rect(vector2D(-1.0, 1.0), vector2D(1.0, -1.0));
		// ���� �簢�� �ܰ��� �׸���
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(5.0);
		glColor3f(0.0, 0.0, 0.0);
		rect(vector2D(-1.0, 1.0), vector2D(1.0, -1.0));

		// 1) ū �� �׸���
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(1.0, 1.0, 0.0);
		circle(vector2D(0.0, -0.2), 0.6);
		// ��� ū �� �ܰ��� �׸���
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(3.0);
		glColor3f(1.0, 1.0, 0.0);
		circle(vector2D(0.0, -0.2), 0.6);

		// 2) �߰� �� �׸���
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(1.0, 0.7, 0.0);
		circle(vector2D(0.0, -0.4), 0.4);
		// ��� ū �� �ܰ��� �׸���
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(3.0);
		glColor3f(1.0, 0.7, 0.0);
		circle(vector2D(0.0, -0.4), 0.4);

		// 3) ���� ���� �� �׸���
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(1.0, 0.0, 0.0);
		circle(vector2D(0.0, -0.6), 0.2);
		// ��� ū �� �ܰ��� �׸���
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(3.0);
		glColor3f(1.0, 0.0, 0.0);
		circle(vector2D(0.0, -0.6), 0.2);
	*/
		

	/* -- red transparency
		// opengl default ������, rgba ���� a�� �Ⱦ��� ��
		// �� ������ alpha ���� ����ϱ� ���ؼ� �̸� ������־�� �ϴ� ���̴�
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// ���� �⺻�� �Ǵ� �簢�� 2���� �׸���
		glColor3f(0, 0, 0);
		rect(vector2D(0.0, 1.0), vector2D(1.0, -1.0));
		glColor3f(0, 0, 1.0);
		rect(vector2D(-1.0, 1.0), vector2D(0.0, -1.0));

		glColor4f(1.0, 0, 0.0, 1.0); // rgba --> a���� �߰��ؼ�, ������ ����
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

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // ��� �簢�� �׸���
		glColor3f(1.0, 1.0, 1.0);
		rect(vector2D(-0.1, 0.1), vector2D(0.1, -0.6));

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // ���� �簢�� �ܰ��� �׸���
		glLineWidth(3.0);
		glColor3f(0.0, 0.0, 0.0);
		rect(vector2D(-0.1, 0.1), vector2D(0.1, -0.6));

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // ��� ū �� �׸���
		glColor3f(1.0, 1.0, 1.0);
		circle(vector2D(0.0, 0.4), 0.35);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // ��� ū �� �ܰ��� �׸���
		glLineWidth(3.0);
		glColor3f(0.0, 0.0, 0.0);
		circle(vector2D(0.0, 0.4), 0.35);

		ellipse(vector2D(-0.2, 0.4), 0.1, 0.2); // �� ���� Ÿ���� �׸���
		ellipse(vector2D(0.2, 0.4), 0.1, 0.2);

		line(vector2D(-0.1, -0.6), vector2D(-0.2, -0.7));
		line(vector2D(0.1, -0.6), vector2D(0.2, -0.7));
	*/


	/* --
		glColor3f(0.4, 0.4, 0.4); // 0.8�� ������ �� ������� ���¸� ��ٰ� �� �� �ִ�
		rect(vector2D(-1.0, 1.0), vector2D(1.0, -1.0));

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_LINE : polygon�� �׸� ��, �ܰ����� �׷���
		glColor3f(1.0, 1.0, 1.0);
		rect(vector2D(-0.7, 0.7), vector2D(0.2, -0.2));

		glColor3f(0.0, 0.0, 0.0);
		glLineWidth(5.0); // line�� �β�
		line(vector2D(-1.0, 1.0), vector2D(1.0, -1.0));
	*/

	glutSwapBuffers();
	/* -- �⺻ ������ �׸���
		glColor3f(1.0, 0.0, 0.0);
		line(vector2D(0.2, -0.5), vector2D(0.2, 0.5));

		glColor3f(1.0, 1.0, 0.0);
		rect(vector2D(-0.5, 0.4), vector2D(0.4, -0.3));

		glColor3f(1.0, 0.0, 1.0);
		circle(vector2D(0.0, 0.0), 0.2);
	*/

	/*  -- ���� �ٸ� �簢�� �׸���
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

