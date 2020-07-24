/*
 * Run an instance of the logistic model
 */

#include "rk4.hpp"
#include <vector>
#include <iostream>

int main()
{
  int n_ts;
  double r;
  double K;
  double y0;
  double dt;

  // ask user the enter the parameters
  std::cout << "How many simulations do you want? ";
  std::cin >> n_ts;
  std::cout << std::endl;
  std::cout << "Enter the per-capita growth rate: ";
  std::cin >> r;
  std::cout << std::endl;
  std::cout << "Enter the carrying capacity: ";
  std::cin >> K;
  std::cout << std::endl;
  std::cout << "Enter the initial population size: ";
  std::cin >> y0;
  std::cout << std::endl;
  std::cout << "Enter the integration interval: ";
  std::cin >> dt;
  std::cout << std::endl;

  // initialise a vector to hold the model results
  std::vector<double> out;

  // initialise a model
  LogisticModel logistic(r, K);

  // setup a new RK4 integration scheme
  RK4 solve(dt, logistic, y0);

  // check parameters
  std::cout << "Initiated a LogisticModel with r & K parameters: ";
  for(int i = 0; i < 2; ++i){
    std::cout << solve.show_parameters()[i] << " ";
  }
  std::cout << std::endl;

  std::cout << "--------------------------------------" << std::endl;

  int sim_t = n_ts * 1/dt;

  // run the model
  for(int t = 0; t < sim_t; ++t){
    std::cout << "Solution after " << t * dt + dt << " time steps: " << solve.integrate() << std::endl;
    //std::cout << out[t] << std::endl;
  }

  return 0;
}
