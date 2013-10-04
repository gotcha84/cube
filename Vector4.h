#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include <string>

using namespace std;

/*
	See slides on homogenous coordinates (slide 30):
	http://ivl.calit2.net/wiki/images/3/3a/02_TransformationsF13.pdf
*/
class Vector4 {
	//protected:
		//float x, y, z, w;

	
	public:
		float x, y, z, w;
		Vector4();
		// A constructor with three parameters for point coordinates
		Vector4(float, float, float);
		// A constructor with four parameters
		Vector4(float, float, float, float);

		// Element access 'set': set each coordinate separately
		void set(float, float, float, float);
		void setX(float);
		void setY(float);
		void setZ(float);
		void setW(float);

		// Element access 'get': return one of the four coordinates
		float get(int);
		float getX();
		float getY();
		float getZ();
		float getW();
		// Overload operator '[]' as alternative to 'get' method
		// overload [], i=0 -> x; i=1 -> y; i=2 -> z; i>=3 -> w
		float operator[] (const int);

		// Vector addition
		void add(Vector4&);
		void add(Vector4&, Vector4&);
		// Overload operator '+' for addition
		Vector4 operator+(const Vector4&) const;

		// Vector subtraction
		void subtract(Vector4&);
		void subtract(Vector4&, Vector4&);
		// Overload operator '-' for subtraction
		Vector4 operator-(const Vector4&) const;

		// Dehomogenize (make fourth component equal to 1)
		void dehomogenize();

		// Print (display the point's components numerically on the screen)
		void print();
		// string representation of components
		string toString();
};

#endif