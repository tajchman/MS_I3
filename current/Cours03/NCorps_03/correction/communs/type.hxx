#ifndef REAL
  #ifdef FLOAT
    #define REAL float
    #define SQRT sqrtf
    #define GL_REAL GL_FLOAT
    #define GLREAL GLfloat
  #else
    #define REAL double
    #define SQRT sqrt
    #define GL_REAL GL_DOUBLE
    #define GLREAL GLdouble
  #endif
#endif
