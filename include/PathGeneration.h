#ifndef __PATH_GENERATION_H__
#define __PATH_GENERATION_H__

#include <vector>
#include <cmath>

namespace {
static double gaussian_box_muller() {
  double x = 0.0;
  double y = 0.0;
  double euclid_sq = 0.0;

  do {
    x = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    y = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    euclid_sq = x*x + y*y;
  } while (euclid_sq >= 1.0);

  return x*sqrt(-2*log(euclid_sq)/euclid_sq);
}

static void calc_path_spot_prices(std::vector<double>& spot_prices,  // Vector of spot prices to be filled in
                           const double& r,   // Risk free interest rate (constant)
                           const double& v,   // Volatility of underlying (constant)
                           const double& T) { // Expiry
  // Since the drift and volatility of the asset are constant
  // we will precalculate as much as possible for maximum efficiency
  double dt = T/static_cast<double>(spot_prices.size());
  double drift = exp(dt*(r-0.5*v*v));
  double vol = sqrt(v*v*dt);
  for (size_t i=1; i<spot_prices.size(); i++) {
    double gauss_bm = gaussian_box_muller();
    spot_prices[i] = spot_prices[i-1] * drift * exp(vol*gauss_bm);
  }
}
}
#endif
