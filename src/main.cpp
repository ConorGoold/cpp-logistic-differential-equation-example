/*
 * Run an instance of the logistic model
 */

#include "rk4.hpp"
#include "ABC_rejection.hpp"
#include <vector>
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
  
  bool estimate; 
  std::cout << "Do you want to run the simulation (0) of estimate parameters from data (1)? ";  
  std::cin >> estimate;
  std::cout << std::endl;

  if(!estimate){
      
      int n_ts;
      double r;
      double K;
      double y0;
      double dt;

      // ask user to enter the parameters
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
  }//end if

  else{

     // open a file to save the outputs
     std::ofstream parameter_estimates;
     parameter_estimates.open("outputs/estimates.txt");
     parameter_estimates << "t" << "," <<
                            "r" << "," << 
                            "K" << std::endl;
    
     std::vector<double> r_estimates;
     std::vector<double> K_estimates;
     int n_particles;
     std::cout << "How many particles do you want to run? ";
     std::cin >> n_particles;
     std::cout << std::endl;

     std::string data_file = "data/data.txt";
     double epsilon;
     double y0;
     double dt;
     int n_ts;
     std::cout << "What degree of error do you need? ";
     std::cin >> epsilon;
     std::cout << std::endl;

     // ask user to enter the parameters
     std::cout << "How many simulations do you want? ";
     std::cin >> n_ts;
     std::cout << std::endl;
     std::cout << "Enter the initial population size: ";
     std::cin >> y0;
     std::cout << std::endl;
     std::cout << "Enter the integration interval: ";
     std::cin >> dt;
     std::cout << std::endl;
  
      
     // run the rejection algorithm    
     ABC_reject(n_particles, data_file, epsilon, r_estimates, K_estimates, dt, n_ts, y0);    

     // save the results to file
     for(int i = 0; i < n_particles; ++i){
         parameter_estimates << i << "," <<
                             r_estimates[i] << "," << 
                             K_estimates[i] << std::endl;
     } 
  }//end estimate

  return 0;
}
