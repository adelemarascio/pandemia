#include "sir.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

using Simulation = std::vector<epidemy::Model>;

bool epidemy::Sir::starting(Parameters const& m_par) const noexcept {
  double R = m_par.beta / m_par.gamma;
  return (R > 1);
}

Simulation epidemy::Sir::epidemic_evolution(Model const& initial, int const N,
                                            Measure const& mes) {
  Simulation result{initial};

  int s_0 = initial.S;
  int i_0 = initial.I;
  int r_0 = initial.R;

  assert(s_0 + i_0 + r_0 == N);
  assert(!result.empty());

  int s, i, r;
  Model mod_0 = initial;
  Model mod;

  for (int c = 0; c < m_days; ++c) {
    if (mes.day_x >= m_days) throw std::runtime_error{"Too late!\n"};
    if (mes.x == 'l' && c == mes.day_x) {
      mod = lockdown(mod_0);
      s_0 = mod.S;
      r_0 = mod.R;
    } else {
      if (mes.x == 'v' && c >= mes.day_x) {
        mod = vaccination(mod_0);
        s_0 = mod.S;
        r_0 = mod.R;
      }
    }

    s = round(s_0 * (1 - (m_par.beta / N) * i_0));
    i = round(i_0 * (1 - m_par.gamma + (m_par.beta * s_0) / N));
    r = round(r_0 + i_0 * m_par.gamma);

    if (s + i + r != N) r = N - (s + i);
    assert(s + i + r == N);

    Model model{s, i, r};
    result.push_back(model);

    s_0 = s;
    i_0 = i;
    r_0 = r;
    mod_0 = {s_0, i_0, r_0};
  }

  return result;
}



epidemy::Model epidemy::Sir::lockdown(epidemy::Model& m_mod) noexcept {
  auto s = m_mod.S;
  m_mod.S = round(m_mod.S * 0.3);
  m_mod.R += round(s*0.7);
  return m_mod;
}

epidemy::Model epidemy::Sir::vaccination(epidemy::Model& m_mod) noexcept {
  auto s = m_mod.S;
  m_mod.S = round(m_mod.S * 0.99);
  m_mod.R += round(s*0.01);
  return m_mod; 
} 