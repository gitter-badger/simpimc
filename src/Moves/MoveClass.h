#ifndef MoveClass_H
#define MoveClass_H

#include "../EventClass.h"
#include "../PathClass.h"
#include "../Actions/ActionClass.h"

class Move : public Event
{
private:

protected:
  Path& path;
  RNG& rng;
  IOClass& out;

  vector<Action*> &actionList;
  string prefix;
public:
  // Constructor
  Move(Path &tmpPath, RNG &tmpRNG, vector<Action*> &tmpActionList, Input &in, IOClass &tmpOut)
    : Event(), path(tmpPath), rng(tmpRNG), actionList(tmpActionList), out(tmpOut)
  {
    name = in.getAttribute<string>("name");
    type = in.getAttribute<string>("type");
    prefix = "Moves/"+name;
    out.CreateGroup(prefix);
    out.Write(prefix+"/type",type);
    string data_type = "scalar";
    out.Write(prefix+"/data_type",data_type);
    firstTime = 1;
    Reset();
  }

  string type;
  virtual void DoEvent();

  // Moves
  virtual void Init(Input &in) {};
  virtual int Attempt() {};
  virtual void Accept() {};
  virtual void Reject() {};

  // Acceptance
  bool firstTime;
  unsigned int nAttempt, nAccept;
  virtual void Reset();

  // Write
  virtual void Write();

};

#endif
