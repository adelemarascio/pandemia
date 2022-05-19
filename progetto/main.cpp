#include <ctime>
#include <iomanip>
#include <iostream>

#include "graph.hpp"
#include "sir.hpp"

using Simulation = std::vector<epidemy::Model>;

void print(Simulation const& simulation) {
  std::cout << "+-----------+-----------+-----------+-----------+\n"
               "|    Day    |     S     |     I     |     R     |\n"
               "+-----------+-----------+-----------+-----------+\n";
  int size = simulation.size();
  for (int c = 0; c < size; ++c) {
    epidemy::Model model = simulation[c];
    std::cout << "| " << std::setw(9) << c << " | " << std::setw(9) << model.S
              << " | " << std::setw(9) << model.I << " | " << std::setw(9)
              << model.R << " |\n";
  }
  std::cout << "+-----------+-----------+-----------+-----------+\n";
}

int main() {
  try {
    srand(time(NULL));

    int const N = 200'000;
    int const days = 90;

    int i0 = rand() % 200 + 1;
    epidemy::Model const m0 = {N - i0, i0, 0};

    epidemy::Parameters p;
    epidemy::Measure mes;

    std::cout << "Enter gamma, beta :\n";
    std::cin >> p.gamma >> p.beta;

    epidemy::Sir sir{days, p};

    std::cout << "Population : " << N << " individuals\n"
              << "Simulation period : " << days << " days\n"
              << "Gamma : " << p.gamma << "\n"
              << "Beta : " << p.beta << "\n"
              << "Rate : " << p.beta / p.gamma << std::endl;

    if (!sir.starting(p) == true) {
      std::cerr << "Epidemic cannot evolve\n";
    } else {
      std::cout << "Decide resolution : \n";
      std::cin >> mes.x >> mes.day_x;

      Simulation simulation = sir.epidemic_evolution(m0, N, mes);

      switch (mes.x) {
        case 'l':
          std::cout << "70% lockdown starting from day " << mes.day_x
                    << std::endl;
          break;
        case 'v':
          std::cout << "1% of Susceptibles vaccinated everyday from day "
                    << mes.day_x << std::endl;
          break;
        default:
          std::cout << "No measure has been taken\n";
      }

      print(simulation);
      display(simulation);
    }
  } catch (std::invalid_argument const& e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }
  return 0;
}