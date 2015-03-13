#ifndef SIMPIMC_OBSERVABLES_CONTACT_DENSITY_CLASS_H_
#define SIMPIMC_OBSERVABLES_CONTACT_DENSITY_CLASS_H_

#include "observable_class.h"

class ContactDensity : public Observable
{
private:
  std::vector<std::shared_ptr<Action>> action_list, &full_action_list;
  std::string species_a, species_b;
  uint32_t species_a_i, species_b_i;
  uint32_t z_a;
  double total;
protected:
public:
  ContactDensity(Path &path, std::vector<std::shared_ptr<Action>>& tmp_action_list, Input &in, IO &out)
    : full_action_list(tmp_action_list), Observable(path, in, out)
  {
    Init(in);
    std::string data_type = "scalar";
    out.Write(prefix+"/data_type",data_type);
  }

  virtual void Init(Input &in);
  virtual void Reset();
  virtual void Accumulate();
  virtual void Write();
};

#endif // SIMPIMC_OBSERVABLES_CONTACT_DENSITY_CLASS_H_