#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <string>

using namespace std;

class Vector3 {
	public:
		float x, y, z;

		// {x=0.0; y=0.0; z=0.0;}
		Vector3();
		// {x=x0; y=y0; z=z0;}
		Vector3(float x0, float y0, float z0);
		
		// {x=x0; y=y0; z=z0;}
		void set(float x0, float y0, float z0);
		// index=0 -> x; index=1 -> y; index>=2 -> z
		float get(int index);
		// get X value
		float getX();
		// get Y value
		float getY();
		// get Z value
		float getZ();
		// overload [], i=0 -> x; i=1 -> y; i>=2 -> z
		//float& overload[](const int i);				---> FIX THIS! <---

		// {x+=a.x; y+=a.y; z+=a.z;}
		void add(Vector3 &a);
		// {x=a.x+b.x; y=a.y+b.y; z=a.z+b.z;}
		void add(Vector3 &a, Vector3 &b);
		// overload +
		Vector3 operator+(const Vector3 &other) const;

		// {x-=a.x; y-=a.y; z-=a.z;}
		void subtract(Vector3 &a);
		// {x=a.x-b.x; y=a.y-b.y; z=a.z-b.z;}
		void subtract(Vector3 &a, Vector3 &b);
		// overload -
		Vector3 operator-(const Vector3 &other) const;

		// {x=-x; y=-y; z=-z;}
		void negate();
		// {x=-a.x; y=-a.y; z=-a.z;}
		void negate(Vector3 &a);
		
		// {x*=s; y*=s; z*=s;}
		void scale(float s);
		// {x=s*a.x; y=s*a.y; z=s*a.z;}
		void scale(float s, Vector3 &a);

		// {return x*a.x+y*a.y+z*a.z;}
		float dot(Vector3 &a);
		// {x=a.y*b.z-a.z*b.y; y=a.z*b.x-a.x*b.z; z=a.x*b.y-a.y*b.x;}
		void cross(Vector3 &a, Vector3 &b);
		
		// {return sqrt(x*x+y*y+z*z);}
		float magnitude();
		// {scale(1.0/magnitude());}
		void normalize();
		
		// print components
		void print(Vector3 &a);
		// string representation of components
		string toString();
};

#endif