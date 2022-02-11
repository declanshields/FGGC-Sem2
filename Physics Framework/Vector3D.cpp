#include "Vector3D.h"

Vector3D::Vector3D()
{
	
}

Vector3D::Vector3D(float inputx, float inputy, float inputz)
{
	x = inputx;
	y = inputy;
	z = inputz;
}

Vector3D::~Vector3D()
{
	
}

//Methods and calculations implemented
float Vector3D::Dot(const Vector3D &inputVector)
{
	return ((inputVector.x * x) + (inputVector.y * y) + (inputVector.z * z));
}

Vector3D Vector3D::Cross(const Vector3D& inputVector)
{
	Vector3D product;

	product.x = ((y * inputVector.z) - (z * inputVector.y));
	product.y = ((x * inputVector.z) - (z * inputVector.x));
	product.z = ((x * inputVector.y) + (y * inputVector.x));

	return product;
}

double Vector3D::CalcMagnitude()
{
	return sqrt((x * x) + (y * y) + (z * z));
}

void Vector3D::Normalize()
{
	double length = CalcMagnitude();

	x = x / length;
	y = y / length;
	z = z / length;
}

//Overloaded operators

Vector3D Vector3D::operator+(const Vector3D& inputVector)
{
	Vector3D product;

	product.x = x + inputVector.x;
	product.y = y + inputVector.y;
	product.z = z + inputVector.z;

	return product;
}

Vector3D Vector3D::operator-(const Vector3D& inputVector)
{
	Vector3D product;

	product.x = x - inputVector.x;
	product.y = y - inputVector.y;
	product.z = z - inputVector.z;

	return product;
}

Vector3D Vector3D::operator*(const Vector3D& inputVector)
{
	Vector3D product;

	product.x = x * inputVector.x;
	product.y = y * inputVector.y;
	product.z = z * inputVector.z;

	return product;
}
