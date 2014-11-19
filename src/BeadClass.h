#ifndef BeadClass_H
#define BeadClass_H

#include "Utils/config.h"

class Bead
{
private:
  unsigned int nD;
protected:

public:
  // Constructor
  Bead(unsigned int tmpND, int tmpS, unsigned int tmpP, unsigned int tmpB, unsigned int tmpId)
    : nD(tmpND), s(tmpS), p(tmpP), b(tmpB), id(tmpId)
  {
    self = this;
    r.zeros(nD);
    r(0) = 0.5*(p - 1.);
    storeR();
  }

  inline void store();
  inline void restore();
  inline void storeR() { rC = r; };
  inline void restoreR() { r = rC; };
  inline void storeRhoK() { rhoKC = rhoK; };
  inline void restoreRhoK() { rhoK = rhoKC; };
  inline void storePrev() { prevC = prev; };
  inline void restorePrev() { prev = prevC; };
  inline void storeNext() { nextC = next; };
  inline void restoreNext() { next = nextC; };
  inline void storeNodeDistance() { nDistC = nDist; };
  inline void restoreNodeDistance() { nDist = nDistC; };
  inline void move( Tvector& dr ) { r += dr; };
  inline void storePartRecord();
  inline void restorePartRecord();
  Bead* nextB( unsigned int n );
  Bead* nextBC( unsigned int n );
  Bead* prevB( unsigned int n );
  Bead* prevBC( unsigned int n );

  unsigned int p;
  unsigned int b;
  unsigned int s;
  unsigned int id;
  RealType nDist, nDistC;
  Tvector r, rC;
  Cvector rhoK, rhoKC;
  Bead *self;
  Bead *next, *nextC;
  Bead *prev, *prevC;
};

#endif
