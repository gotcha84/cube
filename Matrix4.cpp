#include "Matrix4.h"
#include <math.h>
#include <iostream> // to print to stdout
#include <sstream> // to convert float to string
#include <iomanip> // to round floats
#include <string>

using namespace std;

Matrix4::Matrix4()
{
	for (int i=0; i<4; ++i)
	{
		for (int j=0; j<4; ++j)
		{
			m[i][j] = 0;
		}
	}
}

Matrix4::Matrix4(
	double m00, double m01, double m02, double m03,
	double m10, double m11, double m12, double m13,
	double m20, double m21, double m22, double m23,
	double m30, double m31, double m32, double m33 )
{
	// row major ordering
	m[0][0] = m00;
	m[0][1] = m01;
	m[0][2] = m02;
	m[0][3] = m03;
	m[1][0] = m10;
	m[1][1] = m11;
	m[1][2] = m12;
	m[1][3] = m13;
	m[2][0] = m20;
	m[2][1] = m21;
	m[2][2] = m22;
	m[2][3] = m23;
	m[3][0] = m30;
	m[3][1] = m31;
	m[3][2] = m32;
	m[3][3] = m33;

	/*
	// column major ordering
	m[0][0] = m00;
	m[1][0] = m01;
	m[2][0] = m02;
	m[3][0] = m03;
	m[0][1] = m10;
	m[1][1] = m11;
	m[2][1] = m12;
	m[3][1] = m13;
	m[0][2] = m20;
	m[1][2] = m21;
	m[2][2] = m22;
	m[3][2] = m23;
	m[0][3] = m30;
	m[1][3] = m31;
	m[2][3] = m32;
	m[3][3] = m33;
	*/
}

Matrix4::Matrix4(Matrix4 &a)
{
	m[0][0] = a.m[0][0];
	m[0][1] = a.m[0][1];
	m[0][2] = a.m[0][2];
	m[0][3] = a.m[0][3];
	m[1][0] = a.m[1][0];
	m[1][1] = a.m[1][1];
	m[1][2] = a.m[1][2];
	m[1][3] = a.m[1][3];
	m[2][0] = a.m[2][0];
	m[2][1] = a.m[2][1];
	m[2][2] = a.m[2][2];
	m[2][3] = a.m[2][3];
	m[3][0] = a.m[3][0];
	m[3][1] = a.m[3][1];
	m[3][2] = a.m[3][2];
	m[3][3] = a.m[3][3];
}

double* Matrix4::getPointer()
{
	return &m[0][0];
}

double Matrix4::get(int index1, int index2)
{
	return m[index1][index2];
}

void Matrix4::identity()
{
	double ident[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
	for (int i=0; i<4; ++i)
	{
		for (int j=0; j<4; ++j)
		{
			m[i][j] = ident[i][j];
		}
	}
}

void Matrix4::multiply(Matrix4 &a)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			double tmp_sum = 0;
			for (int x = 0; x < 4; ++x)
			{
				tmp_sum+=m[i][x]*a.m[x][j];
			}
			m[i][j] = tmp_sum;
	
		}
	}
}

Vector4* Matrix4::multiply(Vector4 &a)
{
	float tmp_array[4];
	for (int i = 0; i < 4; ++i) 
	{
		float tmp_sum = 0;
		for (int j = 0; j < 4; ++j) 
		{
			tmp_sum+=m[i][j]*a.get(j);
		}
		tmp_array[i] = tmp_sum;
	}
	return &Vector4(tmp_array[0], tmp_array[1], tmp_array[2], tmp_array[3]);
}

// angle in radians
void Matrix4::rotateX(double angle)
{
	// slide 43
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;

	m[1][0] = 0;
	m[1][1] = cos(angle);
	m[1][2] = -sin(angle);
	m[1][3] = 0;

	m[2][0] = 0;
	m[2][1] = sin(angle);
	m[2][2] = cos(angle);
	m[2][3] = 0;

	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}


// angle in radians
void Matrix4::rotateY(double angle)
{
	// slide 43
	m[0][0] = cos(angle);
	m[0][1] = 0;
	m[0][2] = sin(angle);
	m[0][3] = 0;

	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;

	m[2][0] = -sin(angle);
	m[2][1] = 0;
	m[2][2] = cos(angle);
	m[2][3] = 0;

	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

// angle in radians
void Matrix4::rotateZ(double angle)
{
	// slide 43
	m[0][0] = cos(angle);
	m[0][1] = -sin(angle);
	m[0][2] = 0;
	m[0][3] = 0;

	m[1][0] = sin(angle);
	m[1][1] = cos(angle);
	m[1][2] = 0;
	m[1][3] = 0;

	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;

	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void Matrix4::rotate(double angle, Vector3 &a)
{
	// slide 44
	Vector3 b = Vector3(a.getX(), a.getY(), a.getZ());
	b.normalize();

	m[0][0] = b.x*b.x + cos(angle)*(1-b.x*b.x);
	m[0][1] = b.x*b.y*(1-cos(angle)) - b.z*sin(angle);
	m[0][2] = b.x*b.z*(1-cos(angle)) + b.y*sin(angle);
	m[0][3] = 0;

	m[1][0] = b.x*b.y*(1-cos(angle)) + b.z*sin(angle);
	m[1][1] = b.y*b.y + cos(angle)*(1-b.y*b.y);
	m[1][2] = b.y*b.z*(1-cos(angle)) - b.x*sin(angle);
	m[1][3] = 0;

	m[2][0] = b.x*b.z*(1-cos(angle)) - b.y*sin(angle);
	m[2][1] = b.y*b.z*(1-cos(angle)) + b.x*sin(angle);
	m[2][2] = b.z*b.z + cos(angle)*(1-b.z*b.z);
	m[2][3] = 0;

	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
	
	/*
	m[0][0] = 1+((1-cos(angle))*((a.x*a.x)-1));
	m[0][1] = (-a.z*sin(angle))+((1-cos(angle))*a.x*a.y);
	m[0][2] = (a.y*sin(angle))+((1-cos(angle))*a.x*a.z);
	m[0][3] = 0;

	m[1][0] = (a.z*sin(angle))+((1-cos(angle))*a.y*a.x);
	m[1][1] = 1+((1-cos(angle))*((a.y*a.y)-1));
	m[1][2] = (-a.x*sin(angle))+((1-cos(angle))*a.y*a.z);
	m[1][3] = 0;

	m[2][0] = (-a.y*sin(angle))+((1-cos(angle))*a.z*a.x);
	m[2][1] = (a.x*sin(angle))+((1-cos(angle))*a.z*a.y);
	m[2][2] = 1+((1-cos(angle))*((a.z*a.z)-1));
	m[2][3] = 0;

	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1; // or is m[3][3] supossed to be 1?
	*/
}

void Matrix4::scale(double a, double b, double c)
{
	// slide 40
	m[0][0] = a;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;

	m[1][0] = 0;
	m[1][1] = b;
	m[1][2] = 0;
	m[1][3] = 0;

	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = c;
	m[2][3] = 0;

	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;

}

void Matrix4::translate(double a, double b, double c)
{
	// slide 38
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = a;

	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = b;

	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = c;

	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void Matrix4::print()
{

	for (int i=0; i<4; i++)
	{
		cout << setprecision(2) << fixed;

		cout << "[";
		for (int j=0; j<4; j++)
		{
			cout << ("%f", this->m[i][j]);
			if (j != 3)
				cout << "\t";
		}

		cout << "]\n";
	}
	cout << "\n";
}

void Matrix4::transpose()
{
	double tmp[4][4];
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			tmp[i][j] = m[j][i];
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m[i][j] = tmp[i][j];
		}
	}

}