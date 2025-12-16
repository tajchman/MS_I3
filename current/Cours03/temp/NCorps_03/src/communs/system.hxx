#ifndef __System_H__
#define __System_H__

#include "type.hxx"

#include <filesystem>
#include <iostream>
#include <string>
#include "parameters.hxx"

#ifdef USE_GRAPHICS
#include "display.hxx"
#endif

class System
{
public:
  System(Parameters &p, const char *version, bool allocate=true);
  virtual ~System();

  int n() { return _n; }
  void save(bool binary = false);
  void load();
  void loop()
  {
    std::cerr << "\n";
  #ifdef USE_GRAPHICS
    Display *d = _p.graphics ? new Display(_p.p_argc, _p.p_argv, *this) : nullptr;
  #endif

    for (int i = 0; i < _p.nIterations; ++i) {
      update();
  #ifdef USE_GRAPHICS
      if (d && !d->draw()) break;
  #endif
    }

  }
  virtual void init();

  virtual void update();

  virtual REAL *pos()   { return _pos;    }
  virtual REAL *vel()   { return _vel;    }
  virtual REAL *mass()  { return _mass;   }
  virtual REAL *speed() { return _speed;  }
  virtual REAL *color() { return _color;  }

  REAL timestep() const { return _p.timeStep; }

  int current_it() { return _iteration; }
  int max_it() { return _p.nIterations; }

  const char * version() { return _version.c_str(); }
  
  Parameters & parameters() { return _p; }
  protected:

  virtual void randomize();
  virtual void applyForces(REAL dT) {}
  virtual void updatePositions(REAL dT) {}
  virtual void synchronize() {}
  Parameters & _p;
  
  int _iteration;
  
  bool _owner;
  std::string _version;
  std::filesystem::path _initFile, _endFile;

  int _n;
  REAL *_pos, *_vel, *_mass, *_speed, *_color;

  REAL _clusterScale, _velocityScale, _inner, _outer;

};

std::ostream &operator<<(std::ostream &f, System &S);

void stats(std::ostream & f, Parameters &p, const char * version);

#endif
