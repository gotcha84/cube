#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include <string>

using namespace std;

/*
	See slides on homogenous coordinates (slide 30):
	http://ivl.calit2.net/wiki/images/3/3a/02_TransformationsF13.pdf
*/
class Vector4 {
	public:
		float x, y, z, w;

		// A constructor with three parameters for point coordinates
		Vector4(float x0, float y0, float z0);
		// A constructor with four parameters
		Vector4(float x0, float y0, float z0, float w0);

		// Element access 'set': set each coordinate separately
		void set(float x0, float y0, float z0, float w0);
		void setX(float x0);
		void setY(float y0);
		void setZ(float z0);
		void setW(float w0);
		// Element access 'get': return one of the four coordinates
		void get(int index);
		void getX();
		void getY();
		void getZ();
		void getW();
		// Overload operator '[]' as alternative to 'get' method
		// overload [], i=0 -> x; i=1 -> y; i=2 -> z; i>=3 -> w
		//float& overload[](const int i);				---> FIX THIS! <---

		// Vector addition
		void add(Vector4 &a);
		void add(Vector4 &a, Vector4 &b);
		// Overload operator '+' for addition
		Vector4 operator+(const Vector4 &other) const;

		// Vector subtraction
		void subtract(Vector4 &a);
		void subtract(Vector4 &a, Vector4 &b);
		// Overload operator '-' for subtraction
		Vector4 operator-(const Vector4 &other) const;

		// Dehomogenize (make fourth component equal to 1)
		void dehomogenize();

		// Print (display the point's components numerically on the screen)
		void print(Vector4 &a);
};

#endif