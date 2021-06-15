#include "../include/Heston.h"


HestonEuler::HestonEuler(asianPtr pOption_,
              double kappa_, double theta_,
              double xi_, double rho_) :
  pOption(std::move(pOption_)), kappa(kappa_), theta(theta_), xi(xi_), rho(rho_) {}

void HestonEuler::calc_vol_path(const std::vector<double>& vol_draws,
                                std::vector<double>& vol_path) {
  size_t vec_size = vol_draws.size();
  double dt = pOption->T/static_cast<double>(vec_size);

  // Iterate through the correlated random draws vector and
  // use the 'Full Truncation' scheme to create the volatility path
  for (int i=1; i<vec_size; i++) {
    double v_max = std::max(vol_path[i-1], 0.0);
    vol_path[i] = vol_path[i-1] + kappa * dt * (theta - v_max) +
      xi * sqrt(v_max * dt) * vol_draws[i-1];
  }
}

void HestonEuler::calc_spot_path(const std::vector<double>& spot_draws,
                                 const std::vector<double>& vol_path,
                                 std::vector<double>& spot_path) {
  size_t vec_size = spot_draws.size();
  double dt = pOption->T/static_cast<double>(vec_size);

  // Create the spot price path making use of the volatility
  // path. Uses a similar Euler Truncation method to the vol path.
  for (int i=1; i<vec_size; i++) {
    double v_max = std::max(vol_path[i-1], 0.0);
    spot_path[i] = spot_path[i-1] * exp( (pOption->r - 0.5*v_max)*dt +
        sqrt(v_max*dt)*spot_draws[i-1]);
  }
}

