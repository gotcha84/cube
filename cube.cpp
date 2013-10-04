#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

#include "cube.h"
#include "Matrix4.h"

using namespace std;

static Cube cube;
static double spin_angle = 0.001;
static double red = 0.0, green = 2.0, blue = 0.0;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback(void)
{
	cube.spin(spin_angle); // rotate cube; if it spins too fast try 0.001
  displayCallback(); // call display routine to re-draw cube
}

//----------------------------------------------------------------------------
// Callback method called when window is resized.
void Window::reshapeCallback(int w, int h)
{
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0); // set perspective projection viewing frustum
  glTranslatef(0, 0, -20);
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
void Window::displayCallback(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(cube.getMatrix().getPointer());

  // Draw sides of cube in object coordinate system:
  glBegin(GL_QUADS);
    glColor3f(red, green, blue);

    // Draw front face:
    glNormal3f(0.0, 0.0, 1.0);   
    glVertex3f(-5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0,  5.0);
    glVertex3f( 5.0, -5.0,  5.0);
    glVertex3f(-5.0, -5.0,  5.0);
    
    // Draw left side:
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-5.0,  5.0,  5.0);
    glVertex3f(-5.0,  5.0, -5.0);
    glVertex3f(-5.0, -5.0, -5.0);
    glVertex3f(-5.0, -5.0,  5.0);
    
    // Draw right side:
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f( 5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0, -5.0);
    glVertex3f( 5.0, -5.0, -5.0);
    glVertex3f( 5.0, -5.0,  5.0);
  
    // Draw back face:
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-5.0,  5.0, -5.0);
    glVertex3f( 5.0,  5.0, -5.0);
    glVertex3f( 5.0, -5.0, -5.0);
    glVertex3f(-5.0, -5.0, -5.0);
  
    // Draw top side:
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0, -5.0);
    glVertex3f(-5.0,  5.0, -5.0);
  
    // Draw bottom side:
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-5.0, -5.0, -5.0);
    glVertex3f( 5.0, -5.0, -5.0);
    glVertex3f( 5.0, -5.0,  5.0);
    glVertex3f(-5.0, -5.0,  5.0);
  glEnd();
  
  glFlush();  
  glutSwapBuffers();
}

Cube::Cube()
{
  angle = 0.0;
}

Matrix4& Cube::getMatrix()
{
  return matrix;
}

void Cube::setMatrix(Matrix4 &m)
{
	matrix = Matrix4(m);
}

double Cube::getAngle()
{
	return angle;
}

void Cube::setAngle(double a)
{
	angle = a;
}

void Cube::spin(double deg)
{
  if (cube.angle > 360.0 || cube.angle < -360.0) cube.angle = 0.0;
	cube.getMatrix().rotateCubeY(deg);
}

int main(int argc, char *argv[])
{
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position

  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(Window::width, Window::height);      // set initial window size
  glutCreateWindow("OpenGL Cube for CSE167");    	      // open window and set window title

  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
  glShadeModel(GL_SMOOTH);             	      // set shading to smooth
  glMatrixMode(GL_PROJECTION); 
  
  // Generate material properties:
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  
  // Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);

	// to avoid cube turning white on scaling down
	glEnable(GL_NORMALIZE);

	// Process keyboard input
	glutKeyboardFunc(Window::processNormalKeys);
    
  // Initialize cube matrix:
  cube.getMatrix().identity();
	
	cout << "initialized\t\t";
	Vector3 pos = Vector3(
		cube.getMatrix().m[3][0], 
		cube.getMatrix().m[3][1], 
		cube.getMatrix().m[3][2]
	);
	pos.print();
    
  glutMainLoop();
  return 0;
}

void Window::processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) 
	{
		case 'c':
			// reverse the direction of the spin
			spin_angle = -spin_angle;

			cout << "reverse spin\t\t";
			break;
		case 'x':
			// move cube left by a small amount
			cube.getMatrix().translate(-1, 0, 0);
			
			cout << "move left\t\t";
			break;
		case 'X':
			// move cube right by a small amount
			cube.getMatrix().translate(1, 0, 0);

			cout << "move right\t\t";
			break;
		case 'y':
			// move cube down by a small amount
			cube.getMatrix().translate(0, -1, 0);

			cout << "move down\t\t";
			break;
		case 'Y':
			// move cube up by a small amount
			cube.getMatrix().translate(0, 1, 0);

			cout << "move up\t\t\t";
			break;
		case 'z':
			// move cube into of the screen by a small amount
			cube.getMatrix().translate(0, 0, -1);

			cout << "move in\t\t\t";
			break;
		case 'Z':
			// move cube out of the screen by a small amount
			cube.getMatrix().translate(0, 0, 1);

			cout << "move out\t\t";
			break;
		case 'r':
			// reset cube position and size to its initial position
			cube.getMatrix().identity();
			cube.setAngle(0);

			cout << "reset\t\t";
			break;
		case 'a':
			// rotate cube about the OpenGL window's z axis by a small number of degrees counterclockwise
			// The z axis crosses the screen in its center.
			if (cube.angle > 360.0 || cube.angle < -360.0) cube.angle = 0.0;
			cube.getMatrix().rotateZ(-100*spin_angle);

			cout << "rotate CW window z-axis\t";
			break;
		case 'A':
			// rotate cube about the OpenGL window's z axis by a small number of degrees clockwise
			// The z axis crosses the screen in its center.
			if (cube.angle > 360.0 || cube.angle < -360.0) cube.angle = 0.0;
			cube.getMatrix().rotateZ(100*spin_angle);

			cout << "rotate CCW window z-axis";
			break;
		case 's':
			// scale cube down (about its center, not the center of the screen)
			cube.getMatrix().scale(
				0.95, 
				0.95, 
				0.95
			);

			cout << "scale down\t\t";
			break;
		case 'S':
			// scale cube up (about its center, not the center of the screen)
			cube.getMatrix().scale(
				1.05, 
				1.05, 
				1.05
			);

			cout << "scale up\t\t";
			break;
		case '1':
			// change the color of the cube's faces to red
			red = 2.0;
			green = 0.0;
			blue = 0.0;
			cout << "color RED\t\t";
			break;
		case '2':
			// change the color of the cube's faces to green
			red = 0.0;
			green = 2.0;
			blue = 0.0;
			cout << "color GREEN\t\t";
			break;
		case '3':
			// change the color of the cube's faces to blue
			red = 0.0;
			green = 0.0;
			blue = 2.0;
			cout << "color BLUE\t\t";
			break;
		case '4':
			// change the color of the cube's faces to yellow
			red = 3.0;
			green = 3.0;
			blue = 0.0;
			cout << "color YELLOW\t\t";
			break;
	}

	Vector3 pos = Vector3(
		cube.getMatrix().m[3][0], 
		cube.getMatrix().m[3][1], 
		cube.getMatrix().m[3][2]
	);

	pos.print();
}