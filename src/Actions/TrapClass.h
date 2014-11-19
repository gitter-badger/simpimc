#ifndef TrapClass_H
#define TrapClass_H

#include "ActionClass.h"

class Trap : public Action
{
private:
  int nImages;
  int nOrder;
  RealType omega;
  string species;
  int iSpecies;
  int maxLevel;
protected:

public:
  // Constructor
  Trap(Path &path, Input &in, IOClass &out)
    : Action(path,in,out)
  {
    Init(in);
  }

  // Functions
  virtual void Init(Input &in);
  virtual RealType DActionDBeta();
  virtual RealType GetAction(int b0, int b1, vector< pair<int,int> > &particles, int level);
  virtual void Write();
};

#endif
