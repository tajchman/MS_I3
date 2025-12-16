#include "parameters.hxx"
#include "arguments.hxx"
#include "timer.hxx"

Parameters::Parameters(int argc, char **argv) : p_argc(argc), p_argv(argv) {
  
  Arguments parser;

  #ifdef FLOAT
    float timeStep_default = 0.0016f;
    float softening_default = 0.035f;
    float damping_default = 0.995f;
  #else
    double timeStep_default = 0.0016;
    double softening_default = 0.035;
    double damping_default = 0.995;
  #endif

  parser.add("n", 4096, "number of bodies");
  parser.add("it", 300, "number of time iterations");
  #ifdef USE_GRAPHICS
  parser.add("g", false, "graphical display");
  #endif
  parser.add("s", false, "save final values");
  parser.add("dt", timeStep_default, "time step");
  parser.add("init", "", "file containing initial positions");
  parser.add("output", "", "file containing final positions");
  parser.add("threads", 1, "number of threads");
  parser.add("softening", softening_default, "softening");
  parser.add("damping", damping_default, "damping");

  parser.parse(argc, argv);
    
  parser.get("it", nIterations);
  parser.get("dt", timeStep);
#ifdef USE_GRAPHICS
  parser.get("g", graphics);
#endif
  parser.get("s", output);
  parser.get("n", nBodies);
  parser.get("init", initFile);
  parser.get("output", outFile);
  parser.get("threads", nThreads);
  parser.get("softening", softening);
  parser.get("damping", damping); 
 }

