#include "MoveClass.h"

void Move::Reset()
{
  nAccept = 0;
  nAttempt = 0;
}

RealType Move::getPerAccept()
{
  RealType perAccept = (nAccept*1.) / (nAttempt*1.);  // Percentage accepted
  return perAccept;
}

void Move::Write()
{
  if (firstTime) {
    firstTime = 0;
    out.CreateExtendableDataSet("/Moves/"+name+"/", "nAttempt", nAttempt);
    out.CreateExtendableDataSet("/Moves/"+name+"/", "nAccept", nAccept);
  } else {
    out.AppendDataSet("/Moves/"+name+"/", "nAttempt", nAttempt);
    out.AppendDataSet("/Moves/"+name+"/", "nAccept", nAccept);
  }

  Reset();
}
