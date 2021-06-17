#include "../include/CorrelatedWiener.h"
#include <iostream>
#include <cmath>

CorrelatedWiener::CorrelatedWiener(const double _rho,
                         const std::shared_ptr<std::vector<double> > uncorr_draws_)
  : rho(_rho), uncorr_draws(std::move(uncorr_draws_)) {}


void CorrelatedWiener::correlation_calc(std::vector<double>& dist_draws) {
    for (size_t i=0; i<dist_draws.size(); i++) {
      dist_draws[i] = rho * (*uncorr_draws)[i] + dist_draws[i] * sqrt(1-rho*rho);
    }
}

void CorrelatedWiener::random_draws(const std::vector<double>& uniform_draws,
                            std::vector<double>& dist_draws) {

  if (uniform_draws.size() != dist_draws.size()) {
    std::cout << "Unequal sizes not acceptable." << std::endl;
    return;
  }

  if (uniform_draws.size() % 2 != 0) {
    std::cout << "Uniform draw size not an even number." << std::endl;
    return;
  }

  for (int i=0; i<uniform_draws.size() / 2; i++) {
    dist_draws[2*i] = sqrt(-2.0*log(uniform_draws[2*i])) * sin(2*M_PI*uniform_draws[2*i+1]);
    dist_draws[2*i+1] = sqrt(-2.0*log(uniform_draws[2*i])) * cos(2*M_PI*uniform_draws[2*i+1]);
  }

  correlation_calc(dist_draws);

  return;
}
