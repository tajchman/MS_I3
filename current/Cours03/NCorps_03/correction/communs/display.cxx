#include <iostream>
#include <signal.h>
#include <cmath>
#include <cstring>
#include <stdexcept>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "display.hxx"
#include "system.hxx"

static void error_callback(int error, const char* description)
{
    std::cerr << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

static void windowResize(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

bool Display::draw()
{
  adjustPoints();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
 
  glPointSize(4.0);
  drawPoints();

  glfwSwapBuffers(_window);
  glfwPollEvents();
  bool res = !glfwWindowShouldClose(_window);

  return res;
}

struct GraphicException: public std::exception
{
  GraphicException(const char *message) : _what(message) {}

  virtual const char* what() const throw()
  {
    return _what;
  }

  const char * _what;
};

const char *vertexShaderTxt = R"()
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;

out vec3 colour;

void main() {
  colour = vertex_colour;
  gl_Position = vec4(vertex_position, 1.0);
}
)";

const char *fragmentShaderTxt = R"()
in vec3 colour;
out vec4 frag_colour;

void main() {
  frag_colour = vec4(colour, 1.0);
}
)";

void createVBO(GLuint* VBO, GLenum target, uint size) {

	glGenBuffers(1, VBO);
	glBindBuffer(target, *VBO);
	glBufferData(target, size * sizeof(float), 0, GL_DYNAMIC_DRAW);
	glBindBuffer(target, 0);
}

Display::Display(int argc, char **argv, System &S) : _nbody(S)
{
  glEnable(GL_DEBUG_OUTPUT);
  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    throw GraphicException("Failed to initialize GLFW");
  }

  GLFWmonitor * monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);
  _height = mode->height/2;
  _width = mode->width/2;

  _window = glfwCreateWindow(_width, _height, "NCorps", NULL, NULL);
  if (_window == NULL)
  {
    glfwTerminate();
    throw GraphicException("Failed to create GLFW window");
  }
  glfwMakeContextCurrent(_window);
  GLenum err = glewInit();
  if (GLEW_OK != err && err != GLEW_ERROR_NO_GLX_DISPLAY)
  {
    std::cout << err << std::endl;
    std::cout << "GLEW Error: " << glewGetErrorString(err) << std::endl;
    exit(1);
  }
  glfwSetKeyCallback(_window, key_callback);

  std::cerr << "\tGPU model:            " << glGetString(GL_RENDERER) << std::endl;
  std::cerr << "\tGPU (OpenGL) driver:  " << glGetString(GL_VERSION) << std::endl;

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  
  int i;
  REAL *p = S.pos();
  _xmin[0] = _xmax[0] = p[0];
  _xmin[1] = _xmax[1] = p[1];
  _xmin[2] = _xmax[2] = p[2];

  for (i = 1, p += 3; i < S.n(); i++, p += 3)
  {
    if (p[0] > _xmax[0])
      _xmax[0] = p[0];
    else if (p[0] < _xmin[0])
      _xmin[0] = p[0];
    if (p[1] > _xmax[1])
      _xmax[1] = p[1];
    else if (p[1] < _xmin[1])
      _xmin[1] = p[1];
    if (p[2] > _xmax[2])
      _xmax[2] = p[2];
    else if (p[2] < _xmin[2])
      _xmin[2] = p[2];
  }
  _fx[0] = REAL(1.0f)/(_xmax[0] - _xmin[0]);
  _fx[1] = REAL(1.0f)/(_xmax[1] - _xmin[1]);
  _fx[2] = REAL(1.0f)/(_xmax[2] - _xmin[2]);
  
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  createVBO(&_positions_VBO, GL_ARRAY_BUFFER, 3 * S.n());
	createVBO(&_colors_VBO, GL_ARRAY_BUFFER, 3 * S.n());

  _VAO = 0;
  glGenVertexArrays(1, &_VAO);
  glBindVertexArray(_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, _positions_VBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, _colors_VBO);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderTxt, 0);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderTxt, 0);

  _shadersProgram = glCreateProgram();

  // Attach our shaders to our program
  glAttachShader(_shadersProgram, vertexShader);
  glAttachShader(_shadersProgram, fragmentShader);
  
  // Link our program
  glLinkProgram(_shadersProgram);
  glDetachShader(_shadersProgram, vertexShader);
  glDetachShader(_shadersProgram, fragmentShader);

}

void Display::adjustPoints()
{
  int i, n = _nbody.n();
  REAL *p0 = _nbody.pos(), *p;
  REAL *s0 = _nbody.speed(), *s;

  REAL vmin = s0[0], vmax = s0[0];
  for (i=1, s=s0+1; i<n; i++, s++)  {
    if (*s < vmin)
      vmin = *s;
    else if (*s > vmax)
      vmax = *s;  
  }
  if (_vertices.size() == 0) {
    _vertices.resize(n);
    _colors.resize(n);
  }
  for (i=0, p=p0, s=s0; i<n; i++, p+=3, s++)  {
    GLfloat t = GLfloat((*s - vmin)/(vmax - vmin + 0.01) * 6);
    int is = int(t);
    GLfloat ds = t - is;

    _vertices[i] = {
      GLfloat((p[0]-_xmin[0]) * _fx[0] - 0.5f),
      GLfloat((p[1]-_xmin[1]) * _fx[1] - 0.5f), 
      GLfloat((p[2]-_xmin[2]) * _fx[2] - 0.5f)
    };
    _colors[i] = {
      colorTable[is][0] * (1.f-ds) + colorTable[is+1][0] * ds,  
      colorTable[is][1] * (1.f-ds) + colorTable[is+1][1] * ds,  
      colorTable[is][2] * (1.f-ds) + colorTable[is+1][2] * ds
    };
  }

  void *ptr;
	glBindBuffer(GL_ARRAY_BUFFER, _positions_VBO);
  ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
  memcpy(ptr, _vertices.data(), sizeof(REAL) * _vertices.size());
  glUnmapBuffer(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ARRAY_BUFFER, _colors_VBO);
  ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
  memcpy(ptr, _colors.data(), sizeof(REAL) * _colors.size());
  glUnmapBuffer(GL_ARRAY_BUFFER); 
}

void Display::drawPoints()
{
	glBindBuffer(GL_ARRAY_BUFFER, _positions_VBO);
  glDrawArrays(GL_POINTS, 0, GLsizei(3 * _nbody.n()));
}


Display::~Display()
{
  glfwDestroyWindow(_window);
  glfwTerminate();
  
  glBindBuffer(1, _positions_VBO);
  glDeleteBuffers(1, &_positions_VBO);
  glBindBuffer(1, _colors_VBO);
  glDeleteBuffers(1, &_colors_VBO);
}


