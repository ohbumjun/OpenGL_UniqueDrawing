#pragma once
#include "vec.h"

void rect(vector3D a, vector3D b); // a 왼쪽 위, b 오른쪽 아래 
void circle(vector3D center, float radius); // center : 중심점, radius : 반지름
void ellipse(vector3D center, float width, float height);
void triangle(vector3D a , vector3D b, vector3D c); // a,b,c 꼭짓점 
void line(vector3D a, vector3D b); // a-b 까지 line
void threeline(vector3D a, vector3D b, vector3D c, vector3D d);// 3개 line