#ifndef __DISPLAY
#define __DISPLAY

#include <vector>
#ifdef __WIN32
#include <windows.h>
#endif
#include "GLFW/glfw3.h"

#include "type.hxx"
#include "timer.hxx"
class System;
struct GLFWwindow;

constexpr GLfloat colorTable[7][3] = {
  0.0f, 0.0f, 1.0f,
  0.0f, 0.5f, 0.5f,
  0.0f, 1.0f, 0.0f,
  0.5f, 0.5f, 0.0f,
  1.0f, 0.0f, 0.0f,
  1.0f, 1.0f, 0.0f,
  1.0f, 1.0f, 1.0f
};

struct Vertex
{
    GLfloat x, y, z;
};

struct Color
{
    GLfloat r, g, b;
};

class Display
{
public:
    Display(int argc, char ** argv, System & S);
    virtual ~Display();
    virtual bool draw();
    
protected:
    REAL _xmin[3], _xmax[3], _fx[3];
    System & _nbody;

    int _width = 0;
    int _height = 0;
    GLFWwindow* _window;
    virtual void adjustPoints();
    virtual void drawPoints();
    std::vector<Vertex> _vertices;
    std::vector<Color> _colors;

    GLuint _positions_VBO, _colors_VBO, _VAO;
    GLuint _shadersProgram;


};

#endif
