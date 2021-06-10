#pragma once
#include "vec.h"

void rect(vector3D a, vector3D b); // a ���� ��, b ������ �Ʒ� 
void circle(vector3D center, float radius); // center : �߽���, radius : ������
void ellipse(vector3D center, float width, float height);
void triangle(vector3D a , vector3D b, vector3D c); // a,b,c ������ 
void line(vector3D a, vector3D b); // a-b ���� line
void threeline(vector3D a, vector3D b, vector3D c, vector3D d);// 3�� line