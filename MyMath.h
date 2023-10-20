#pragma once
#include "Vector2.h"
#include <cmath>
#define M_PI 3.14f

// Vector2 内積
float DotProduct(Vector2 a, Vector2 b);
// Vector2ノルム(大きさ)
float VectorMagnitude(Vector2 v);
// ふたつのベクトルのなす角
float CalculateAngle(Vector2 a, Vector2 b);

float ToRadian(int degree);
int ToDegree(float radian);
Vector2 Normalize(Vector2 const& obj);

Vector2 Add(Vector2 v1, Vector2 v2);
Vector2 Sub(Vector2 v1, Vector2 v2);
Vector2 Mul(Vector2 v1, Vector2 v2);