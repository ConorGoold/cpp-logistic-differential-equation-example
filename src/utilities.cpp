/*
 * Implementation of utility functions
 */

#include "utilities.hpp"

#include <vector>
#include <random>

double rnormal(int i, double mu, double sigma){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> normal_dist(mu, sigma);
    double x;
    x = normal_dist(gen);
    return x;
}

