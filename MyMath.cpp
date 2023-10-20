#include "MyMath.h"

float DotProduct(Vector2 a, Vector2 b) { 
	return a.x * b.x + a.y * b.y; 
}

float VectorMagnitude(Vector2 v) { 
	return std::sqrtf(v.x * v.x + v.y * v.y);
}

float CalculateAngle(Vector2 a, Vector2 b) {
	float dot = DotProduct(a, b);
	float magnitudeA = VectorMagnitude(a);
	float magnitudeB = VectorMagnitude(b);
	return std::acosf(dot / (magnitudeA * magnitudeB));
}

float ToRadian(int degree) { return degree * M_PI / 180.0f; }

int ToDegree(float radian) { return (int)(radian * 180.0f / M_PI); }

Vector2 Normalize(Vector2 const& obj) {
	float length = 0;
	Vector2 newObj = {};

	length = VectorMagnitude(obj);

	newObj.x = obj.x;
	newObj.y = obj.y;

	if (length != 0.0f) {
		newObj.x = obj.x / length;
		newObj.y = obj.y / length;
	}
	return newObj;
}

Vector2 Add(Vector2 v1, Vector2 v2) {
	Vector2 result = {v1.x + v2.x, v1.y + v2.y};
	return result;
}

Vector2 Sub(Vector2 v1, Vector2 v2) {
	Vector2 result = {v1.x - v2.x, v1.y - v2.y};
	return result;
}

Vector2 Mul(Vector2 v1, Vector2 v2) {
	Vector2 result = {v1.x * v2.x, v1.y * v2.y};
	return result;
}
