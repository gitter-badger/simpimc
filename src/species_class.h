#ifndef SIMPIMC_SPECIES_CLASS_H_
#define SIMPIMC_SPECIES_CLASS_H_

#include "bead_class.h"

/// Container class for a single species. Holds all the bead objects of that species.
class Species
{
private:

protected:

public:
  // Constructor
  Species(Input &in, IO &out, int t_s_i, int t_n_d, int t_n_bead)
    : s_i(t_s_i), n_d(t_n_d), n_bead(t_n_bead)
  {
    Init(in, out);
  };

  void Init(Input &in, IO &out);
  void InitPaths(Input &in, IO &out, RNG &rng, const uint32_t proc_i, const double L);

  // Beads
  field<std::shared_ptr<Bead> > bead;
  std::string init_type;

  // Given global constants
  uint32_t n_part, n_d, n_bead, s_i;
  std::string name;
  double lambda;

  // Fermions
  bool fermi, fixed_node;

  // Rho_k
  bool need_update_rho_k;
};

#endif // SIMPIMC_SPECIES_CLASS_H_
