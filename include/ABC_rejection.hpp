/*
 * Definition of the approximate Bayesian computation (ABC) rejection algorithm
 */

#ifndef LOGISTIC_INCLUDE_ABC_REJECT_
#define LOGISTIC_INCLUDE_ABC_REJECT_

#include "rk4.hpp"
#include <vector>
#include <string>

void ABC_reject(int& n_particles, std::string data_file, double espilon, 
                std::vector<double>& r_particles, std::vector<double>& K_particles,
                double& dt, int& n_ts, double& y0);

#endif
