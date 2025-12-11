#ifndef _TIMER_H
#define _TIMER_H

#include <string>
#include <chrono>
#include <vector>
#include <map>

class Timer {
  public:

    Timer(const char *s = "", int o = 0) : 
      _name(s), 
      _elapsed(0.0), 
      _offset(o), 
      _running(false)
    {
    }
    virtual ~Timer() {}

    const std::string & name() const { return _name; }
    void name(const char *newName) { _name = newName; }
    inline void start()
    {
      if (_running) return;
      _start = std::chrono::high_resolution_clock::now();
      _running = true;
    }
    inline void stop()
    {
      if (!_running) return;
      _end = std::chrono::high_resolution_clock::now();
      _diff = _end - _start;
      _elapsed += _diff.count();
      _running = false;
    }

    inline double elapsed() const { return _elapsed; }
    inline void reset(const char * newName = nullptr, int o = -1)
    {
      if (newName)
        _name = newName;
      if (o >= 0)
        _offset = 0;
      _elapsed = 0.0;
      _running = false;
      }

    inline void offset(int n) { _offset = n; };
    inline int offset() const { return _offset; }

  protected:
    bool _running;
    std::string _name;
    int _offset;
    double _elapsed;
    std::chrono::time_point<std::chrono::high_resolution_clock> _start, _end;
    std::chrono::duration<double> _diff;
};

enum IdTimers
{
  TimeAllocate,
  TimeDeallocate,
  TimeCompute,
  TimeCopy,
  TimeIO
};

std::ostream & operator<< (std::ostream & f, Timer & t);
Timer * newTimer(IdTimers id, const char *name);
Timer * getTimer(IdTimers id);
void releaseTimers();
double printTimers(std::ostream &f);

#endif
