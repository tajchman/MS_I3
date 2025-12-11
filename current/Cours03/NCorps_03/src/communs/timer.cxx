
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include "timer.hxx"
#include "parameters.hxx"

std::map<IdTimers, Timer *> _Timers;

Timer * newTimer(IdTimers id, const char *name)
{
#ifdef TIMERS
  Timer * T = new Timer(name);
  _Timers[id] = T;
  return T;
#else
  return nullptr;
#endif
}

Timer * getTimer(IdTimers id)
{
#ifdef TIMERS
  return _Timers[id];
#else
  return nullptr;
#endif
}

void releaseTimers()
{
#ifdef TIMERS
  for (auto t : _Timers)
    delete t.second;
#endif
}


std::ostream & operator<< (std::ostream & f, Timer & t)
{
#ifdef TIMERS
  for (int o = 0; o < t.offset() ; o++)
    f << "\t";

  f << std::right << std::setw(24);
  if (t.name().size() > 0)
    f << t.name();
  else
    f << "timer";

  f <<  "  " << std::fixed << t.elapsed() << " s";
#endif
  return f;
}

double printTimers(std::ostream & f)
{
#ifdef TIMERS
  double s = 0.0;
  for (auto & it: _Timers) {
    auto * t = it.second;
    f << std::setw(24) << t->name() << " time:" << std::setw(12) << std::setprecision(6) << t->elapsed() << " s\n";
    s += t->elapsed();
  }
  return s;
#else
  return 0.0;
#endif
}
