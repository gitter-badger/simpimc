#ifndef PermutationClass_H
#define PermutationClass_H

#include "ObservableClass.h"

class Permutation : public Observable
{
private:
  vec<RealType> cycles;
  vector<int> sectors;
  string species;
  int iSpecies;
  bool firstSector;
protected:
public:
  Permutation(Path &tmpPath, Input &in, IOClass &out)
    : Observable(tmpPath, in, out)
  {
    Init(in);
  }

  virtual void Init(Input &in);
  virtual void Reset();
  virtual void Accumulate();
  virtual void Write();
};

#endif
