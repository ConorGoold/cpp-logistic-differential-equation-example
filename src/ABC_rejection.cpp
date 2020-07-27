/*
 * Implementation of the ABC rejection algorithm
 */

#include "ABC_rejection.hpp"
#include "utilities.hpp"
#include <vector>
#include <string>
#include <math.h>
#include <fstream>
#include <iostream>

void ABC_reject(int& n_particles, std::string data_file, double epsilon, 
                std::vector<double>& r_particles, std::vector<double>& K_particles,
                double& dt, int& n_ts, double& y0)
{

    //open the data file
    std::ifstream data_input(data_file);
    // d = data
    std::vector<double> d;
    
    if(!data_input.is_open()){ 
        std::cout << "Missing data file!" << std::endl;
    }
    else{
        std::cout << "Data file opened successfully!" << std::endl;
    }

    double num = 0.0;
    while(data_input >> num){
        d.push_back(num);
    }

    // counter for the number of particles retained
    int i = 1;
    // counter for the number of particles attempted
    int j = 1;
    
    // ask the user to set the r and K parameter prior values
    double r_mu, r_sigma;
    double K_mu, K_sigma;
    std::cout << "Please set the prior location and scale parameters: " << std::endl 
              << "r_mu: ";
    std::cin >> r_mu;
    std::cout << std::endl << "r_sigma: ";
    std::cin >> r_sigma;
    std::cout << std::endl << "K_mu: ";
    std::cin >> K_mu;
    std::cout << std::endl << "K_sigma: ";
    std::cin >> K_sigma;
    std::cout << std::endl;

    while((signed)r_particles.size() < n_particles-1){
      // sample parameters from the priors
      double r_star = rnormal(1, r_mu, r_sigma); 
      double K_star = rnormal(1, K_mu, K_sigma);       

      /* run an instance of the model */

      // initialise a vector to hold the model results
      std::vector<double> out;

      // initialise a model
      LogisticModel logistic(r_star, K_star);

      // setup a new RK4 integration scheme
      RK4 solve(dt, logistic, y0);

      int sim_t = n_ts * 1/dt;

      // run the model
      for(int t = 0; t < sim_t; ++t){
          out.push_back(solve.integrate());
      }

      // calculate the distance 
      double squared_error = 0.0;
      for(int i = 0; i < sim_t; ++i){
          squared_error += pow(out[i] - d[i], 2);
      }
      double distance = sqrt(squared_error);
      
      if( distance < epsilon ){
          // accept the particle
          r_particles.push_back(r_star);
          K_particles.push_back(K_star);
          // update the counter
          i += 1;
      }//if
      
      // update j
      j += 1;
      
    }//while

    double acceptance_ratio = (double)i / j;

    // notify the user that the simulation has finished, and the acceptance ratio
    std::cout << "ABC simulation finished! Acceptance ratio was: " << acceptance_ratio << " (" 
              << i << " particles stored, " << j << " particles attempted)" << std::endl;

}  
