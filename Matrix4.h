#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "Vector3.h"
#include "Vector4.h"

#include <string>

using namespace std;

class Matrix4
{
	//protected:
		//double m[4][4]; // matrix elements
		
	public:
		double m[4][4]; // matrix elements
		// given
		Matrix4(); // constructor
		// given
		// Constructor with 16 parameters to set the values of the matrix
		Matrix4(double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double);
		Matrix4(Matrix4&);
		
		// given
		// return pointer to matrix elements
		double* getPointer(); // given
		// 'get(x,y)' function to read any matrix element
		double get(int, int);

		// given
		// create identity matrix
		void identity();
		// Multiply (matrix-times-matrix)
		void multiply(Matrix4&);
		// Multiply (matrix-times-vector)
		Vector4* multiply(Vector4&);
	
		// Make a rotation matrix about the x axis
		void rotateX(double);
		// given
		// Make a rotation matrix about the y axis
		void rotateY(double);
		// Make a rotation matrix about the z axis
		void rotateZ(double);
		// Make a rotation matrix about an arbitrary (unit) axis
		void rotate(double, Vector3&);

		// Make a non-uniform scaling matrix
		void scale(double, double, double);

		// Make a translation matrix
		void translate(double, double, double);

		// Print the matrix (display all 16 matrix components numerically on the screen in a 4x4 array)
		void print();

		// Transpose the matrix
		void transpose();
};

#endif