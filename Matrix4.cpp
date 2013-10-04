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

	m[3][3] = 1;
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

Matrix4* Matrix4::multiply(Matrix4 &a)

{
	double n[4][4];
	double temp_sum;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			temp_sum = 0;
			for (int x = 0; x < 4; ++x)
			{
				temp_sum+=m[x][j]*a.m[i][x];
			}
			n[i][j] = temp_sum;
		}
	}

	return &Matrix4(
		n[0][0], n[0][1], n[0][2], n[0][3], 
		n[1][0], n[1][1], n[1][2], n[1][3], 
		n[2][0], n[2][1], n[2][2], n[2][3], 
		n[3][0], n[3][1], n[3][2], n[3][3]
	);
}

Vector4* Matrix4::multiply(Vector4 &a)
{
	float n[4];
	float temp_sum;

	for (int i = 0; i < 4; ++i) 
	{
		temp_sum = 0;
		for (int j = 0; j < 4; ++j) 
		{
			temp_sum+=(float)m[i][j]*a.get(j);
		}
		n[i] = temp_sum;
	}

	return &Vector4(n[0], n[1], n[2], n[3]);
}

void Matrix4::rotateX(double angle)
{
	Matrix4 n = Matrix4(
		1, 0, 0, 0, 
		0, cos(angle), -sin(angle), 0,  
		0, sin(angle), cos(angle), 0, 
		0, 0, 0, 1
	);

	Matrix4 *result = n.multiply(*this);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m[i][j] = result->get(i, j);
		}
	}
}

void Matrix4::rotateCubeX(double angle)
{
	Matrix4 n = Matrix4(
		1, 0, 0, 0, 
		0, cos(angle), -sin(angle), 0,  
		0, sin(angle), cos(angle), 0, 
		0, 0, 0, 1
	);

	Matrix4 *result = this->multiply(n);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m[i][j] = result->get(i, j);
		}
	}
}
// angle in radians
void Matrix4::rotateY(double angle)
{
	Matrix4 n = Matrix4(
		cos(angle), 0, sin(angle), 0, 
		0, 1, 0, 0, 
		-sin(angle), 0, cos(angle), 0, 
		0, 0, 0, 1
	);

	Matrix4 *result = n.multiply(*this);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m[i][j] = result->get(i, j);
		}
	}
}

void Matrix4::rotateCubeY(double angle)
{
	Matrix4 n = Matrix4(
		cos(angle), 0, sin(angle), 0, 
		0, 1, 0, 0, 
		-sin(angle), 0, cos(angle), 0, 
		0, 0, 0, 1
	);

	Matrix4 *result = this->multiply(n);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m[i][j] = result->get(i, j);
		}
	}
}

void Matrix4::rotateZ(double angle)
{
	Matrix4 n = Matrix4(
		cos(angle), -sin(angle), 0, 0, 
		sin(angle), cos(angle), 0, 0, 
		0, 0, 1, 0, 
		0, 0, 0, 1
	);

	Matrix4 *result = n.multiply(*this);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m[i][j] = result->get(i, j);
		}
	}
}

void Matrix4::rotateCubeZ(double angle)
{
	Matrix4 n = Matrix4(
		cos(angle), -sin(angle), 0, 0, 
		sin(angle), cos(angle), 0, 0, 
		0, 0, 1, 0, 
		0, 0, 0, 1
	);

	Matrix4 *result = this->multiply(n);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m[i][j] = result->get(i, j);
		}
	}
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

/*
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
*/
void Matrix4::scale(double a, double b, double c)
{
	Matrix4 n = Matrix4(
		a, 0, 0, 0,
		0, b, 0, 0,
		0, 0, c, 0,
		0, 0, 0, 1
	);

	Matrix4* result = this->multiply(n);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m[i][j] = result->get(i, j);
		}
	}
}

void Matrix4::translate(double a, double b, double c)
{
	m[3][0] = a + m[3][0];
	m[3][1] = b + m[3][1];
	m[3][2] = c + m[3][2];
}

void Matrix4::print()
{

	for (int i=0; i<4; i++)
	{
		cout << setprecision(2) << fixed;

		Matrix4 tpose = Matrix4(*this);
		tpose.transpose();

		cout << "[";
		for (int j=0; j<4; j++)
		{
			cout << ("%f", tpose.m[i][j]);
			if (j != 3)
				cout << "\t";
		}

		cout << "]\n";
	}
	cout << "\n";
}

void Matrix4::transpose()
{
	double temp[4][4];
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			temp[i][j] = m[j][i];
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m[i][j] = temp[i][j];
		}
	}

}