/*
 * Implementation of the logistic model
 */

#include "logistic.hpp"
#include <vector>

LogisticModel::LogisticModel() { }

LogisticModel::LogisticModel(const double& r, const double& K){
  r_ = r;
  K_ = K;
}

double LogisticModel::derivative(double y) {
  return r_ * y * ( 1 - y/K_);
}

double LogisticModel::show_r(){
  return r_;
}

double LogisticModel::show_K(){
  return K_;
}
