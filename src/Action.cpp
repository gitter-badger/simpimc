#include "PathClass.h"

// Get Kinetic Action
double Path::getK()
{
  double tot = 0.0;  
  for (unsigned int iPart = 0; iPart < nPart; iPart += 1)  {
    for (unsigned int iBead = 0; iBead < nBead; iBead += 1)  {
      dr = bead(iPart,iBead) -> r - (bead(iPart,iBead) -> next -> r);
      tot += dot( dr , dr );
    }
  }
  
  return oneOver4LamTau * tot;
}

// Get Single Particle Kinetic Action
double Path::getK( const int iPart )
{
  double tot = 0.0;
  dr = bead(iPart,0) -> r - (bead(iPart,0) -> prev -> r);
  tot += dot( dr , dr );  
  for (unsigned int iBead = 0; iBead < nBead; iBead += 1) {
    dr = bead(iPart,iBead) -> r - (bead(iPart,iBead) -> next -> r);
    tot += dot( dr , dr );
  }
  
  return oneOver4LamTau * tot;
}

// Get Single Bead Kinetic Action
double Path::getK( const int iPart , const int iBead )
{
  dr = bead(iPart,iBead) -> r - (bead(iPart,iBead) -> prev -> r);
  double dPrev = dot( dr , dr );  
  dr = bead(iPart,iBead) -> r - (bead(iPart,iBead) -> next -> r);
  double dNext = dot( dr , dr );
  
  return oneOver4LamTau * (dPrev + dNext);
}

// Get Single Bead Kinetic Action
double Path::getK( Bead *bi )
{
  dr = bi -> r - (bi -> prev -> r);
  double dPrev = dot( dr , dr );  
  dr = bi -> r - (bi -> next -> r);
  double dNext = dot( dr , dr );
  
  return oneOver4LamTau * (dPrev + dNext);
}

// Get Potential Action
double Path::getV()
{  
  double Vext = 0.0;
  double Vint = 0.0;
  for (unsigned int iPart = 0; iPart < nPart-1; iPart += 1) {
    for (unsigned int iBead = 0; iBead < nBead; iBead += 1) {
      for (unsigned int jPart = iPart+1; jPart < nPart; jPart += 1) {
        Vint += getVint( bead(iPart,iBead) , bead(jPart,iBead) );
      }
      Vext += dot( bead(iPart,iBead) -> r , bead(iPart,iBead) -> r );
    }
  }
  for (unsigned int iBead = 0; iBead < nBead; iBead += 1) {
    Vext += dot( bead(nPart-1,iBead) -> r , bead(nPart-1,iBead) -> r );
  }
  Vext *= halfTauOmega2;
      
  return Vext + Vint;
}

// Get Single Particle Potential Action
double Path::getV( const unsigned int iPart )
{  
  double Vext = 0.0;
  double Vint = 0.0;
  for (unsigned int iBead = 0; iBead < nBead; iBead += 1) {  
    for (unsigned int jPart = 0; jPart < iPart; jPart += 1)
      Vint += getVint( bead(iPart,iBead) , bead(jPart,iBead) );
    for (unsigned int jPart = iPart+1; jPart < nPart; jPart += 1) 
      Vint += getVint( bead(iPart,iBead) , bead(jPart,iBead) );

    Vext += dot( bead(iPart,iBead) -> r , bead(iPart,iBead) -> r );
  }
  Vext *= halfTauOmega2;
      
  return  Vext + Vint;
}

// Get Single Bead Potential Action
double Path::getV( const int unsigned iPart , const int iBead )
{  
  double Vext = 0.0;
  double Vint = 0.0;
  for (unsigned int jPart = 0; jPart < iPart; jPart += 1)
    Vint += getVint( bead(iPart,iBead) , bead(jPart,iBead) );
  for (unsigned int jPart = iPart+1; jPart < nPart; jPart += 1) 
    Vint += getVint( bead(iPart,iBead) , bead(jPart,iBead) );

  Vext += halfTauOmega2 * dot( bead(iPart,iBead) -> r , bead(iPart,iBead) -> r );

  return Vext + Vint;
}

// Get Single Bead Potential Action
double Path::getV( Bead *bi )
{  
  double Vext = 0.0;
  double Vint = 0.0;
  const unsigned int iPart = bi -> p;
  for (unsigned int jPart = 0; jPart < iPart; jPart += 1)
    Vint += getVint( bi , bead(jPart,bi -> b) );
  for (unsigned int jPart = iPart+1; jPart < nPart; jPart += 1) 
    Vint += getVint( bi , bead(jPart,bi -> b) );

  Vext += halfTauOmega2 * dot( bi -> r , bi -> r );

  return Vext + Vint;
}

// Get Two Bead Interaction Action
double Path::getVint( Bead *b1 , Bead *b2 )
{
  return 0;
}

// Get Single Bead Nodal Action
double Path::getN( const int iPart , const int iBead )
{
  if (!useNodeDist) return 0;
  return -log(1.0 - exp(-(bead(iPart,iBead) -> nDist)*(bead(iPart,iBead) -> next -> nDist)*oneOverLamTau));
}

// Get Single Bead Nodal Action
double Path::getN( Bead *b )
{
  return getN( b -> p , b -> b );
}

// Get Nodal Action of Bead Set
double Path::getN( std::vector<Bead*>& beads )
{
  double N(0.0);
  for (std::vector<Bead*>::const_iterator b = beads.begin(); b != beads.end(); ++b)
    N += getN((*b));
  return N;
}
