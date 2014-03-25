#include "BisectClass.h"

void Bisect::Init(Input &in)
{
  maxLevel = in.getAttribute<int>("maxLevel");
}

void Bisect::MakeMove()
{
  for (unsigned int iP = 0; iP < path.nPart; iP += 1) {
    nAccept += DoBisect(iP);
    nAttempt++;
  }
}

// Bisection Move
int Bisect::DoBisect(const int iP)
{
  unsigned int bead0 = rng.unifRand(path.nBead) - 1;  // Pick first bead at random
  unsigned int nLevel = maxLevel;
  //nLevel = 1;
  unsigned int nBisectBeads = 1<<nLevel; // Number of beads in bisection
  unsigned int bead1 = bead0 + nBisectBeads; // Set last bead in bisection
  bool rollOver = bead1 > (path.nBead-1);  // See if bisection overflows to next particle
  vector<int> particles;
  particles.push_back(iP);

  // Set up pointers
  Bead *beadI = path(iP,bead0);
  Bead *beadF = beadI -> nextB(nBisectBeads);

  // Store coordinates
  Bead *beadA;
  affBeads.clear();
  for(beadA = beadI; beadA != beadF; beadA = beadA -> next) {
    affBeads.push_back(beadA);
    beadA->storeR();
  }

  // Perform the bisection (move exactly through kinetic action)
  RealType vOld, vNew, dA[nLevel+1], dAold;
  dA[nLevel] = 0.0;
  dAold = 0.0;
  RealType lambda = beadI->species.lambda;
  Bead *beadB, *beadC;
  RealType prevActionChange = 0.;
  RealType prefactorOfSampleProb = 0.;
  for (int iLevel = nLevel-1; iLevel >= 0; iLevel -= 1) {
    int skip = 1<<iLevel; //pow(2,iLevel);
    RealType levelTau = path.tau*skip;
    RealType sigma2 = lambda*levelTau;
    RealType sigma = sqrt(sigma2);

    //RealType oldLogSampleProb = 0.;
    //RealType newLogSampleProb = 0.;
    //RealType oldAction = 0.;
    //RealType newAction = 0.;

    //beadA = beadI;
    //while(beadA != beadF) {
    //  beadB = beadA->nextB(skip);
    //  beadC = beadB->nextB(skip);

    //  // Old sampling
    //  path.SetMode(0);
    //  Tvector rBarOld(path.nD);
    //  path.RBar(beadC, beadA, rBarOld);
    //  Tvector deltaOld(path.nD);
    //  path.Dr(beadB, rBarOld, deltaOld);

    //  // Old action
    //  for (int i=0; i<actionList.size(); ++i)
    //    oldAction += actionList[i]->GetAction(beadA->b, beadA->b+2*skip, particles, iLevel);

    //  // New sampling
    //  path.SetMode(1);
    //  Tvector rBarNew(path.nD);
    //  path.RBar(beadC, beadA, rBarNew);
    //  Tvector deltaNew(path.nD);
    //  rng.normRand(deltaNew, 0, sigma);
    //  path.PutInBox(deltaNew);
    //  beadB->r = rBarNew + deltaNew;

    //  // New action
    //  for (int i=0; i<actionList.size(); ++i)
    //    newAction += actionList[i]->GetAction(beadA->b, beadA->b+2*skip, particles, iLevel);

    //  // Get sampling probs
    //  int numImages = 0; /// asfdljasd;lfjas;dlfjalskdfj
    //  RealType gaussProdOld = 1.;
    //  RealType gaussProdNew = 1.;
    //  for (int iD=0; iD<path.nD; iD++) {
    //    RealType gaussSumOld = 0.;
    //    RealType gaussSumNew = 0.;
    //    for (int image=-numImages; image<=numImages; image++) {
    //      RealType distOld = deltaOld(iD) + (RealType)image*path.L;
    //      RealType distNew = deltaNew(iD) + (RealType)image*path.L;
    //      gaussSumOld += exp(-0.5*distOld*distOld/sigma2);
    //      gaussSumNew += exp(-0.5*distNew*distNew/sigma2);
    //    }
    //    gaussProdOld *= gaussSumOld;
    //    gaussProdNew *= gaussSumNew;
    //  }
    //  oldLogSampleProb += prefactorOfSampleProb + log(gaussProdOld);
    //  newLogSampleProb += prefactorOfSampleProb + log(gaussProdNew);

    //  beadA = beadC;
    //}

    //RealType logSampleRatio = -newLogSampleProb + oldLogSampleProb;
    //RealType currActionChange = newAction - oldAction;
    //RealType logAcceptProb = logSampleRatio - currActionChange + prevActionChange;

    //if (logAcceptProb < log(rng.unifRand())) { // Reject if true
    //  path.restoreR(affBeads);
    //  return 0;
    //}

    //prevActionChange = currActionChange;

    beadA = beadI;
    while(beadA != beadF) {
      beadB = beadA->nextB(skip);
      beadC = beadB->nextB(skip);

      //for (int i=0; i<actionList.size(); ++i)
      //  vOld += actionList[i]->GetAction(beadB->b, beadB->b+skip, particles, iLevel);

      Tvector ac(path.nD);
      path.Dr(beadC,beadA,ac);
      Tvector dr(path.nD);
      rng.normRand(dr, 0, sigma);
      path.PutInBox(dr);
      beadB->r = beadA->r + 0.5*ac + dr;

      //for (int i=0; i<actionList.size(); ++i)
      //  vNew += actionList[i]->GetAction(beadB->b, beadB->b+skip, particles, iLevel);

      beadA = beadC;
    }

    dA[iLevel] = vNew - vOld;
    dAold = 0.5*(dAold + dA[iLevel+1]);
    if ((-dA[iLevel] + dAold) < log(rng.unifRand())) {
      path.restoreR(affBeads);
      return 0;
    }
  }

  // Move Accepted
  return 1;
}
