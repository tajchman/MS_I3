
#include <assert.h>
#include <memory.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <filesystem>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#include "system.hxx"
#include "os.hxx"

System::System(Parameters &p, const char*version, bool allocate) :
  _p(p),
  _version(version),
  _n(p.nBodies),
  _owner(allocate)
{
  newTimer(TimeCompute, "compute");
  newTimer(TimeAllocate, "allocation");
  Timer *T = newTimer(TimeDeallocate, "deallocation");
  newTimer(TimeIO, "I/O");

  _iteration = 0;
  
  if (T) T->start();

  if (_owner) {
    _pos = new REAL[3*_n];
    _vel = new REAL[3*_n];
    _mass = new REAL[_n];
    _speed = new REAL[_n];
    _color = new REAL[3*_n];
  }
  if (T) T->stop();
}

System::~System()
{
  if (_owner) {
    Timer *T = getTimer(TimeAllocate); 
    if (T) T->start();

    delete [] _pos;
    delete [] _vel;
    delete [] _mass;
    delete [] _speed;
    delete [] _color;

    if (T) T->stop();
  }
}

void System::randomize()
{
  REAL *p = pos();
  REAL *v = vel();
  REAL *m = mass();
  REAL *s = speed();
  REAL *c = color();
  REAL x_mean = 0.0, vx_mean = 0.0;
  REAL y_mean = 0.0, vy_mean = 0.0;
  REAL z_mean = 0.0, vz_mean = 0.0;

  _clusterScale = REAL(1.54);
  _velocityScale = REAL(8.0);
    
  if (_n <= 513) {
    _clusterScale = REAL(1.52);
    _velocityScale = REAL(0.02);
  }
  else if (_n < 1025)
  {
    _clusterScale = REAL(1.52);
    _velocityScale = REAL(0.1);
  }
  else if (_n < 2049)
  {
    _clusterScale = REAL(1.56);
    _velocityScale = REAL(0.05);
  }
  else if (_n < 4097)
  {
    _clusterScale = REAL(1.68);
    _velocityScale = REAL(0.05);
  }
  else if (_n < 8193)
  {
    _clusterScale = REAL(1.98);
    _velocityScale = REAL(2.9);
  }
  else if (_n < 16385)
  {
    _clusterScale = REAL(1.24);
    _velocityScale = REAL(12.);
  }
  else{
    _clusterScale = REAL(1.44);
    _velocityScale = REAL(12.0);
  }
  
  _velocityScale *= _clusterScale;
  _inner = REAL(2.5) * _clusterScale;
  _outer = REAL(4.0) * _clusterScale;

  for(int i=0; i<_n; i++) {

    REAL rho  = _inner + (_outer -_inner) * rand() / (REAL)RAND_MAX;
    REAL phi = REAL(2*M_PI * rand()) / REAL(RAND_MAX); 
    REAL theta = REAL(M_PI * rand()) / REAL(RAND_MAX);

    x_mean += p[3*i]   = rho * sin(theta) * cos(phi);
    y_mean += p[3*i+1] = rho * sin(theta) * sin(phi);
    z_mean += p[3*i+2] = rho * cos(theta);

    vx_mean += v[3*i]   = _velocityScale * p[3*i+1];
    vy_mean += v[3*i+1] = - _velocityScale * p[3*i];
    vz_mean += v[3*i+2] = 0.0;
  }

  x_mean /= _n;
  y_mean /= _n;
  z_mean /= _n;
  vx_mean /= _n;
  vy_mean /= _n;
  vz_mean /= _n;

  for (int i = 0; i < _n; i++)
  {
    p[3*i]   -= x_mean;
    p[3*i+1] -= y_mean;
    p[3*i+2] -= z_mean;
    v[3*i]   -= vx_mean;
    v[3*i+1] -= vy_mean;
    v[3*i+1] -= vz_mean;
  }

  for (int i = 0; i < _n; i++) {
    m[i] = 1.0;
    s[i] = SQRT(v[3*i]*v[3*i] + v[3*i+1]*v[3*i+1] + v[3*i+2]*v[3*i+2]);
    c[3*i] = REAL(1.0);
    c[3*i+1] = REAL(0.7);
    c[3*i+2] = REAL(0.7);
  }
}

void System::init() {

  std::filesystem::path f, d;

  if (_p.initFile == "") {
    d = std::filesystem::absolute("init");
    f = std::string("init_") + std::to_string(_n);

    #ifdef FLOAT
    f += "_float";
  #else
    f += "_double";
  #endif

  f += ".dat";
  }
  else {
    d = std::filesystem::absolute(_p.initFile).parent_path();
    f = std::filesystem::path(_p.initFile).filename();
  }
  std::filesystem::create_directory(d);
  _initFile = d / f;

  if (_p.outFile == "") {
    d = std::filesystem::absolute("output");
    f = "output_";
    f += std::to_string(_n);
    f += "_";
    f += std::to_string(_p.nIterations);

    #ifdef FLOAT
    f += "_float";
  #else
    f += "_double";
  #endif

    f += "_";
    f += _version;
    f += ".txt";
  }
  else {
    d = std::filesystem::absolute(_p.outFile).parent_path();
    f = std::filesystem::path(_p.outFile).filename();
  }
  std::filesystem::create_directory(d);
  _endFile = d / f;

  if (std::filesystem::exists(_initFile)) {
    load();
  }
  else {
    randomize();
    save(true);
  }
}

void System::update()
{
  if (_n <= 10)
    std::cout << std::endl << *this << std::endl;

  Timer *T = getTimer(TimeCompute);
  if(T) T->start();
  
  applyForces(_p.timeStep);
  updatePositions(_p.timeStep);

  _iteration += 1;
  if (T) {
    synchronize();
    T->stop();
    std::cerr << "\r\t" << std::setw(6) << _iteration 
                << " update(s) : " << std::setw(15) << T->elapsed()/_iteration  
                << " seconds/update   ";
  }
}

void System::save(bool binary)
{
  Timer *T = getTimer(TimeIO);
  if(T) T->start();
 
  FILE * f = nullptr;
  if (binary) {
    f = fopen(_initFile.string().c_str(), "wb");
    fwrite(&_n, sizeof(int), 1, f);
    fwrite(pos(),   sizeof(REAL), 3*_n, f);
    fwrite(vel(),   sizeof(REAL), 3*_n, f);
    fwrite(mass(),  sizeof(REAL), _n, f);
    fwrite(speed(), sizeof(REAL), _n, f);
    fwrite(color(), sizeof(REAL), 3*_n, f);
  }
  else {
    f = fopen(_endFile.string().c_str(), "w");
    fprintf(f, "%d\n", _n); 
    (void) fprintf(f, "%20s %20s %20s %20s %20s %20s %20s\n",
       "x", "y", "z", "mass", "vx", "vy", "vz");

    REAL *p = pos(), *v = vel(), *m = mass(); 
    for (int i=0; i<_n; i++) {
      (void) fprintf(f, "%20.12le %20.12le %20.12le %20.12le %20.12le %20.12le %20.12le",
        p[i*3], p[i*3+1], p[i*3+2], m[i],
        v[i*3], v[i*3+1], v[i*3+2]);
    }
  }

  if (f)
    fclose(f);
  if (T) T->stop();
}

void System::load()
{
  Timer *T = getTimer(TimeIO);
  if(T) T->start();

  size_t r;
  FILE * f;
  f = fopen(_initFile.string().c_str(), "rb");
  r = fread(&_n, sizeof(int), size_t(1), f);
  if (r != 1) exit(-1);

  r = fread(pos(), sizeof(REAL), _n*3, f);
  if (r != 3*_n) exit(-1);
  r = fread(vel(), sizeof(REAL), _n*3, f);
  if (r != 3*_n) exit(-1);
  r = fread(mass(), sizeof(REAL), _n, f);
  if (r != _n) exit(-1);
  r = fread(speed(), sizeof(REAL), _n, f);
  if (r != _n) exit(-1);
  r = fread(color(), sizeof(REAL), 3*_n, f);
  if (r != 3*_n) exit(-1);
  
  if (T) T->stop();
}

std::ostream & operator<< (std::ostream & f, System & S)
{
    f << S.n() << " points" << std::endl;
    REAL * p = S.pos();
    REAL * v = S.vel();
    for (int i=0; i<S.n(); i++, p+=3, v+=3)
      f << std::setw(6) << i 
        << " " << std::setw(12) << p[0] 
        << " " << std::setw(12) << p[1] 
        << " " << std::setw(12) << p[2]
        << " " << std::setw(12) << v[0] 
        << " " << std::setw(12) << v[1] 
        << " " << std::setw(12) << v[2] << std::endl;

    return f;
}

void stats(std::ostream & f, Parameters &p, const char *version)
{
  int n = p.nBodies;
  f << "\n\t" << std::setw(6) << n << " bodies\n\n";

  const int flopsPerInteraction = 20;

  #ifdef TIMERS

  double totalTime = printTimers(f);
  double flop = 1 + 19 * double(n)*double(n) + 15 * double(n);
  double gflops = 1e-9 * flop * p.nIterations / totalTime;

  f << "\n" << std::setw(30) << "total time:" 
    << std::setw(12) << std::setprecision(6) << totalTime << " s\n\n";
  f << "\t" << std::fixed << std::setprecision(1) << gflops << " GFLOP/s\n\n";

  std::ostringstream fName;
  fName << "stat_" << version << ".json";
  std::ofstream fStats(fName.str(), std::ios::app);
  fStats << "{\n"
    << "  \"version\": \"" << version << "\",\n"
    << "  \"n\": " << n << ",\n"
    << "  \"iterations\": " << p.nIterations << ",\n"
    << "  \"compute time\": " << totalTime  << "\n"
    << "}\n";

  #endif
}
