/*
 * Implementation of Runge-Kutta 4 numerical integration scheme
 */

#include "rk4.hpp"
#include <vector>
#include <memory>
#include <iostream>

RK4::RK4(){ };

RK4::RK4(double& dt, LogisticModel& model, double& initial_state){
  dt_ = dt;
  model_ = std::make_unique<LogisticModel>(model); 
  state_ = initial_state;
}

double RK4::integrate()
{
  // create a vector to hold the intermediate steps
  std::vector<double> k;

  // constant
  double constant = 1.0/6.0;

  // updated y variable
  double new_y = 0;

  k.push_back( dt_ * model_->derivative(state_) );
  k.push_back( dt_ * model_->derivative(state_ + k[0]*0.5));
  k.push_back( dt_ * model_->derivative(state_ + k[1]*0.5));
  k.push_back( dt_ * model_->derivative(state_ + k[2]));

  new_y = state_ + constant * (k[0] + (k[1] + k[2])*2.0 + k[3]);

  state_ = new_y;

  // return the result
  return state_;
}

std::vector<double> RK4::show_parameters(){
  std::vector<double> parameters;
  parameters.push_back(model_->show_r());
  parameters.push_back(model_->show_K());
  return parameters;
}
