#ifndef SIR_HPP
#define SIR_HPP

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace epidemy {

struct Model {
  int S;
  int I;
  int R;
};

struct Parameters {
  double gamma;
  double beta;
};

struct Measure {
  char x;
  int day_x;
};

class Sir {
 private:
  using Simulation = std::vector<Model>;

  int const m_days;
  Parameters m_par;

 public:
  Sir(int const days, Parameters par) : m_days{days}, m_par{par} {
    if (m_par.gamma <= 0. || m_par.gamma > 1.) {
      if (m_par.beta < 0. || m_par.beta > 1.) {
        throw std::invalid_argument("Invalid parameters!\n");
      } else {
        throw std::invalid_argument("Invalid parameter: gamma!\n");
      }
    }
    if (m_par.beta < 0. || m_par.beta > 1.) {
      throw std::invalid_argument("Invalid parameter: beta!\n");
    }
  }

  bool starting(Parameters const& m_par) const noexcept;

  Simulation epidemic_evolution(Model const& initial, int const N,
                                Measure const& mes);

  Model lockdown(Model& m_mod) noexcept;

  Model vaccination(Model& m_mod) noexcept;
};

}  // namespace epidemy

#endif