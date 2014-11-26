#ifndef LoopClass_H
#define LoopClass_H

#include "EventClass.h"

class Loop : public Event
{
private:

protected:

public:
  // Constructor
  Loop() {};

  void Init(Input &In, vector<Event*> &eventList);
  void ReadLoop(Input &In, vector<Event*> &eventList);
  Event* FindEvent(string name, vector<Event*> &eventList);
  void DoEvent();

  int nSteps;
  vector<Event*> events;
};

#endif
