#ifndef _TIMER_H
#define _TIMER_H

#include <string>
#include <chrono>

class Timer {
    public:

        Timer(const char *s = "", int o = 0) : _name(s), _elapsed(0.0), _offset(o)
        {
          _start = std::chrono::high_resolution_clock::now();
        }

        const std::string & name() const { return _name; }
        void name(const char *newName) { _name = newName; }
        inline void start()
        {
          _start = std::chrono::high_resolution_clock::now();
        }
        inline void stop()
        {
          _end = std::chrono::high_resolution_clock::now();
          _diff = _end - _start;
          _elapsed += _diff.count();
        }
        double elapsed() const { return _elapsed; }
        void reset(const char * newName = nullptr, int o = -1)
        {
          if (newName)
            _name = newName;
          if (o >= 0)
            _offset = 0;
          _elapsed = 0.0;
          _start = std::chrono::high_resolution_clock::now();
          _end = _start;
        }
        void restart()
        {
          _elapsed = 0.0;
          _start = std::chrono::high_resolution_clock::now();
          _end = _start;
        }

        void offset(int n) { _offset = n; };
        int offset() const { return _offset; }

    private:
        std::string _name;
        int _offset;
        double _elapsed;
        std::chrono::time_point<std::chrono::high_resolution_clock> _start, _end;
        std::chrono::duration<double> _diff;

};

std::ostream & operator<< (std::ostream & f, Timer & t);

int AddTimer(const char *name);
Timer &  GetTimer(int n);
void PrintTimers(std::ostream &f);
void SaveTimers(const char *version);

#endif
