/*
 * Definition of Runge-Kutta 4 numerical integration scheme
 */

#ifndef RK4_H_
#define RK4_H_

#include "logistic.hpp" // we need the model
#include <vector>
#include <memory>

class RK4{

  public:
    RK4();
    RK4(double& dt, LogisticModel& model, double& initial_state);

  private:
    // holds a unique pointer (sole owner) of the model to be integrated
    std::unique_ptr<LogisticModel> model_;
    // integration interval
    double dt_;
    // state calculation
    double state_;

  public:
    // integrates the model
    double integrate();
    // show parameters of the model
    std::vector<double> show_parameters();
};

#endif
