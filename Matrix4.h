#ifndef _MATRIX4_H_
#define _MATRIX4_H_

class Matrix4
{
  protected:
    double m[4][4];   // matrix elements
    
  public:
    Matrix4();        // constructor
    Matrix4(double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double);
    double* getPointer();  // return pointer to matrix elements
    void identity();  // create identity matrix
    void rotateY(double); // rotation about y axis
};

#endif