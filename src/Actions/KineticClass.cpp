#include "KineticClass.h"

void Kinetic::Init(Input &in)
{
  if (path.PBC)
    nImages = in.getAttribute<int>("nImages");
  else
    nImages = 0;

  // todo: spline maybe?

  normalization = path.nBead*path.nD/(2.*path.tau);
  out.Write("/Actions/"+name+"/nImages", nImages);
}

RealType Kinetic::DActionDBeta()
{
  RealType tot = 0.;
  Tvector gaussSum(path.nD), numSum(path.nD), numProd(path.nD), dr(path.nD);
  for (int iS=0; iS<path.nSpecies; iS++) {
    RealType lambda = path.speciesList[iS]->lambda;
    if (!fequal(lambda,0.,1e-10)) {
      RealType i4LambdaTau = 1./(4.*lambda*path.tau);
      RealType gaussProd, dist, dist2i4LambdaTau, expPart, scalarNumSum;
      for (int iP=0; iP<path.speciesList[iS]->nPart; iP++) {
        for (int iB=0; iB<path.nBead; iB++) {
          path.Dr(path(iS,iP,iB),path.GetNextBead(path(iS,iP,iB),1),dr);
          gaussProd = 1.;
          gaussSum.zeros();
          numSum.zeros();
          for (int iD=0; iD<path.nD; iD++) {
            for (int image=-nImages; image<=nImages; image++) {
              dist = dr(iD) + image*path.L;
              dist2i4LambdaTau = dist*dist*i4LambdaTau;
              expPart = path.fexp(-dist2i4LambdaTau);
              gaussSum(iD) += expPart;
              numSum(iD) += -(dist2i4LambdaTau/path.tau)*expPart;
            }
            gaussProd *= gaussSum(iD);
          }
          scalarNumSum = 0.;
          for (int iD=0; iD<path.nD; iD++) {
            numProd.ones(path.nD);
            for (int jD=0; jD<path.nD; jD++) {
              if (iD != jD)
                numProd(iD) *= gaussSum(jD);
              else
                numProd(iD) *= numSum(jD);
            }
            scalarNumSum += numProd(iD);
          }
          tot += scalarNumSum/gaussProd;
        }
        tot += path.nBead*path.nD/(2.*path.tau);
      }
    }
  }
  return tot;
}

RealType Kinetic::GetAction(int b0, int b1, vector< pair<int,int> > &particles, int level)
{
  int skip = 1<<level;
  RealType levelTau = skip*path.tau;
  RealType tot = 0.;
  Tvector dr(path.nD);
  Bead *beadA, *beadB, *beadC, *beadF;
  for (int p=0; p<particles.size(); ++p) {
    int iS = particles[p].first;
    int iP = particles[p].second;
    RealType lambda = path.speciesList[iS]->lambda;
    if (!fequal(lambda,0.,1e-10)) {
      RealType i4LambdaTau = 1./(4.*lambda*levelTau);
      RealType gaussProd, gaussSum, dist;
      beadA = path(iS,iP,b0);
      beadF = path.GetNextBead(beadA,b1-b0);
      while(beadA != beadF) {
        beadB = path.GetNextBead(beadA,skip);
        path.Dr(beadA,beadB,dr);
        gaussProd = 1.;
        for (int iD=0; iD<path.nD; iD++) {
          gaussSum = 0.;
          for (int image=-nImages; image<=nImages; image++) {
            dist = dr(iD) + image*path.L;
            gaussSum += path.fexp(-dist*dist*i4LambdaTau);
          }
          gaussProd *= gaussSum;
        }
        tot -= log(gaussProd);

        beadA = beadB;
      }
    }
  }

  return tot;
}

void Kinetic::Write()
{

}
