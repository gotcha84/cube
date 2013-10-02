LIBS = -lglut -lGLU -lGL -lXmu -lXext -lX11 -lm -lXi

default: cube

cube: cube.cpp cube.h Matrix4.h Matrix4.cpp
	g++ -o cube cube.cpp Matrix4.cpp $(LIBS)

clean :
	rm cube.o Matrix4.o cube
