#ifndef WritesClass_H
#define WritesClass_H

#include "EventClass.h"

class Writes : public Event
{
private:
  int iBlock;
  double initial, start, end;
protected:
  // Output
  IOClass &Out;

  // Event list
  vector<Event*> &events;
public:
  // Constructor
  Writes(IOClass &tmpOut, vector<Event*> &tmpEvents)
    : Event(), Out(tmpOut), events(tmpEvents)
  {
    name = "Write";
    iBlock = 0;
    struct timeval time;
    gettimeofday(&time, NULL); // Start Time
    initial = time.tv_sec + (time.tv_usec / 1000000.);
    end = time.tv_sec + (time.tv_usec / 1000000.);
  }

  // Functions
  void DoEvent();
  virtual void Write() {};
};

#endif
