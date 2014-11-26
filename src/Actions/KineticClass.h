#ifndef KineticClass_H
#define KineticClass_H

#include "ActionClass.h"
#include <einspline/bspline.h>
#include <einspline/nubspline.h>

class Kinetic : public Action
{
private:
  int nImages;
  double normalization;

protected:

public:
  // Constructor
  Kinetic(Path &path, Input &in, IOClass &out)
    : Action(path,in,out)
  {
    Init(in);
  }

  // Functions
  virtual void Init(Input &in);
  virtual double DActionDBeta();
  virtual double GetAction(const int b0, const int b1, const vector< pair<int,int> > &particles, const int level);
  virtual void Write();
};

#endif
