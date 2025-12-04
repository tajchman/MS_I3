#include "parameters.hxx"
#include "arguments.hxx"
#include "timer.hxx"

Parameters::Parameters(int argc, char **argv) : p_argc(argc), p_argv(argv) {
  
  Arguments parser;

  parser.add("n", 4096, "number of values");
  parser.add("imax", 10, "number of terms in sinus approximation");
  parser.add("threads", 1, "number of OpenMP threads");

  parser.parse(argc, argv);
    
  parser.get("n", n);
  parser.get("imax", iMax);
  parser.get("threads", nThreads); 
 }

