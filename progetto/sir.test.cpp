#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "sir.hpp"

TEST_CASE("Testing Parameters") {
  epidemy::Parameters par;
  epidemy::Sir sir{90, par};

  SUBCASE("1") {
    par.gamma = 0.07;
    par.beta = 0.5;
    CHECK(sir.starting(par) == true);
  }

  SUBCASE("2") {
    par.gamma = 0.04;
    par.beta = 0.6;
    CHECK(sir.starting(par) == true);
  }

  SUBCASE("3") {
    par.gamma = 0.5;
    par.beta = 0.1;
    CHECK(sir.starting(par) == false);
  }
}

TEST_CASE("Testing Parameters 2") {
  epidemy::Parameters par = {-3., -5.};
  CHECK_THROWS_WITH(epidemy::Sir(90, par), "Invalid parameters!\n");

  par = {1.5, 0.9};
  CHECK_THROWS_WITH(epidemy::Sir(90, par), "Invalid parameter: gamma!\n");

  par = {0.07, 1.4};
  CHECK_THROWS_WITH(epidemy::Sir(90, par), "Invalid parameter: beta!\n");
}

TEST_CASE("Testing Measures") {
  int S = 199900;
  int I = 100;
  int R = 0;
  epidemy::Parameters par {0.07, 0.4};
  epidemy::Sir sir{90, par};
  epidemy::Model mod{S, I, R};
  {
    epidemy::Measure mes_1{'l', 90};
    CHECK_THROWS(sir.epidemic_evolution(mod, 2e5, mes_1));
  }
  {
    epidemy::Measure mes_2{'v', 91};
    CHECK_THROWS(sir.epidemic_evolution(mod, 2e5, mes_2));
  }
}
