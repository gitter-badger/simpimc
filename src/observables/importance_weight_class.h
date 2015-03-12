#ifndef SIMPIMC_OBSERVABLES_IMPORTANCE_WEIGHT_CLASS_H_
#define SIMPIMC_OBSERVABLES_IMPORTANCE_WEIGHT_CLASS_H_

#include "observable_class.h"

class ImportanceWeight : public Observable
{
private:
  std::vector<std::shared_ptr<Action>> &action_list;
  vec<double> IWs;
protected:
public:
  ImportanceWeight(Path &path, std::vector<std::shared_ptr<Action>> &tmp_action_list, Input &in, IO &out)
    : action_list(tmp_action_list), Observable(path, in, out)
  {
    Init(in);
  }

  virtual void Init(Input &in);
  virtual void Reset();
  virtual void Accumulate();
  virtual void Write();
};

#endif // SIMPIMC_OBSERVABLES_IMPORTANCE_WEIGHT_CLASS_H_
