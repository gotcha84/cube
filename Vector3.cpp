#include "Vector3.h"

#include <math.h>
#include <iostream> // to print to stdout
#include <sstream> // to convert float to string
#include <string>

using namespace std;
// this is a change.

// A SUPER CHANGE.

// OH MY GOD. ITS ANOTHER CHANGE. WHAT IS THIS
// test commiting with app
Vector3::Vector3() 
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}


Vector3::Vector3(float x0, float y0, float z0) 
{
	x = x0;
	y = y0;
	z = z0;
}

void Vector3::set(float x0, float y0, float z0) 
{
	x = x0;
	y = y0;
	z = z0;
}

float Vector3::get(int index)
{
	if (index == 0)
		return x;
	else if (index == 1)
		return y;
	else
		return z;
}

float Vector3::getX()
{
	return x;
}

float Vector3::getY()
{
	return y;
}

float Vector3::getZ()
{
	return z;
}

/*
//											---> FIX THIS! <---
float& Vector3::overload[](const int i)
{
	if (i == 0)
		return this->x;
	else if (i == 1)
		return this->y;
	else
		return this->z;
}
*/

void Vector3::add(Vector3 &a)
{
	x+=a.x;
	y+=a.y;
	z+=a.z;
}

void Vector3::add(Vector3 &a, Vector3 &b)
{
	x = a.x + b.x;
	y = a.y + b.y;
	z = a.z + b.z;
}

Vector3 Vector3::operator+(const Vector3 &other) const
{
	return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

void Vector3::subtract(Vector3 &a)
{
	x-=a.x;
	y-=a.y;
	z-=a.z;
}

void Vector3::subtract(Vector3 &a, Vector3 &b)
{
	x = a.x - b.x;
	y = a.y - b.y;
	z = a.z - b.z;
}

Vector3 Vector3::operator-(const Vector3 &other) const
{
	return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

void Vector3::negate()
{
	x = -x;
	y = -y;
	z = -z;
}

void Vector3::negate(Vector3 &a)
{
	x = -a.x;
	y = -a.y;
	z = -a.z;
}

void Vector3::scale(float s)
{
	x*=s;
	y*=s;
	z*=s;
}

void Vector3::scale(float s, Vector3 &a)
{
	x = s * a.x;
	y = s * a.y;
	z = s * a.z;
}

float Vector3::dot(Vector3 &a)
{
	return x*a.x + y*a.y + z*a.z;
}

void Vector3::cross(Vector3 &a, Vector3 &b)
{
	x = a.y*b.z - a.z*b.y;
	y = a.z*b.x - a.x*b.z;
	z = a.x*b.y - a.y*b.x;
}

float Vector3::magnitude()
{
	return sqrt(x*x + y*y + z*z);
}

void Vector3::normalize()
{
	scale(float(1.0)/magnitude());
}
	
void Vector3::print(Vector3 &a)
{
	cout << ("(%f, %f, %f)", a.x, a.y, a.z);
}

string Vector3::toString()
{
	ostringstream ss;
	ss << "(" << this->x << ", " << this->y << ", " << this->z << ")";
	return ss.str();
}