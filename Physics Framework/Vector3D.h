#pragma once

#include <DirectXMath.h>

class Vector3D
{
public:
	float x, y, z;

	Vector3D(float inputx, float inputy, float inputz);
	Vector3D();

	~Vector3D();

	//Methods
	float Dot(const Vector3D& inputVector);
	Vector3D Cross(const Vector3D& inputVector);
	double CalcMagnitude();
	void Normalize();
	Vector3D NormalizeWithOutput();

	//Overloaded operators
	Vector3D operator+(const Vector3D& inputVector);
	Vector3D operator-(const Vector3D& inputVector);
	Vector3D operator*(const Vector3D& inputVector);
	Vector3D operator*(const float t);
	Vector3D operator/(const float t);
};

