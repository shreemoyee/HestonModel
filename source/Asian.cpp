#include <numeric>
#include <cmath>
#include "../include/Asian.h"


AsianOption::AsianOption(double K_, double r_,
               double T_, PayOffPtr pay_off_) : K(K_), r(r_), T(T_), pay_off(std::move(pay_off_)) {}

AsianOptionArithmetic::AsianOptionArithmetic(double K_, double r_,
               double T_, PayOffPtr pay_off_) : AsianOption(K_, r_, T_, pay_off_) {}

double AsianOptionArithmetic::pay_off_price(const std::vector<double>& spot_prices) const {
  unsigned num_times = spot_prices.size();
  double sum = std::accumulate(spot_prices.begin(), spot_prices.end(), 0);
  double arith_mean = sum / static_cast<double>(num_times);
  return (*pay_off)(arith_mean);
}


AsianOptionGeometric::AsianOptionGeometric(double K_, double r_,
               double T_, PayOffPtr pay_off_) : AsianOption(K_, r_, T_, pay_off_) {}


double AsianOptionGeometric::pay_off_price(const std::vector<double>& spot_prices) const {
  unsigned num_times = spot_prices.size();
  double log_sum = 0.0;
  for (int i=0; i<spot_prices.size(); i++) {
    log_sum += log(spot_prices[i]);
  }
  double geom_mean = exp(log_sum / static_cast<double>(num_times) );
  return (*pay_off)(geom_mean);
}
