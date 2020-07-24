/*
 * Definition of the logistic model
 */

#ifndef LOGISTIC_
#define LOGISTIC_

#include <vector>

class LogisticModel
{

  public:
    LogisticModel();
    LogisticModel(const double& r, const double& K);

  private:
    // r parameter
    double r_;
    // K parameter
    double K_;

  // METHODS
  public:
    double derivative(double y);
    double show_r();
    double show_K();
};

#endif
