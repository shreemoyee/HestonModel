#include <iostream>
#include <chrono>
#include <map>

#include "include/Payoff.h"
#include "include/Asian.h"
#include "include/CorrelatedWiener.h"
#include "include/Heston.h"

void generate_normal_correlation_paths(double rho,
    std::vector<double>& spot_normals, std::vector<double>& cor_normals) {
  unsigned vals = spot_normals.size();

  // Create the Standard Normal Distribution and random draw vectors
  StandardNormalDistribution snd;
  std::vector<double> snd_uniform_draws(vals, 0.0);

  // Simple random number generation method based on RAND
  for (size_t i=0; i<snd_uniform_draws.size(); i++) {
    snd_uniform_draws[i] = rand() / static_cast<double>(RAND_MAX);
  }

  // Create standard normal random draws
  snd.random_draws(snd_uniform_draws, spot_normals);

  // Create the correlated standard normal distribution
  auto shared_spot = std::make_shared<std::vector<double> >(spot_normals);
  CorrelatedWiener csnd(rho, shared_spot);
  std::vector<double> csnd_uniform_draws(vals, 0.0);

  // Uniform generation for the correlated SND
  for (size_t i=0; i<csnd_uniform_draws.size(); i++) {
    csnd_uniform_draws[i] = rand() / static_cast<double>(RAND_MAX);
  }

  // Now create the -correlated- standard normal draw series
  csnd.random_draws(csnd_uniform_draws, cor_normals);
}

int main(int argc, char **argv) {
  // First we create the parameter list
  // Note that you could easily modify this code to input the parameters
  // either from the command line or via a file
  unsigned num_sims = 500;   // Number of simulated asset paths


  unsigned num_intervals = 100;  // Number of intervals for the asset path to be sampled

  double S_0 = 100.0;    // Initial spot price
  double K = 100.0;      // Strike price
  double r = 0.02;     // Risk-free rate
  double v_0 = 0.25; // Initial volatility
  double T = 2.00;       // One year until expiry

  double rho = -0.4;     // Correlation of asset and volatility
  double kappa = 0.2;   // Mean-reversion rate
  double theta = 0.4;  // Long run average volatility
  double xi = 1;      // Vol of var
  std::map<unsigned, double> sims_price;
  // Create the PayOff, Option and Heston objects
  auto pPayOffCall = std::make_shared<PayOffCall>(K);
  auto pOption = std::make_shared<AsianOptionArithmetic>(K, r, T, pPayOffCall);
  HestonEuler hest_euler(pOption, kappa, theta, xi, rho);

  // Create the spot and vol initial normal and price paths
  std::vector<double> spot_draws(num_intervals, 0.0);  // Vector of initial spot normal draws
  std::vector<double> vol_draws(num_intervals, 0.0);   // Vector of initial correlated vol normal draws
  std::vector<double> spot_prices(num_intervals, S_0);  // Vector of initial spot prices
  std::vector<double> vol_prices(num_intervals, v_0);   // Vector of initial vol prices

  /// 1. Running for different number of paths
  std::cout<<"#1 \n";
  while(num_sims<300000){

  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  // Monte Carlo options pricing
  double payoff_sum = 0.0;
  for (unsigned i=0; i<num_sims; i++) {
    generate_normal_correlation_paths(rho, spot_draws, vol_draws);
    hest_euler.calc_vol_path(vol_draws, vol_prices);
    hest_euler.calc_spot_path(spot_draws, vol_prices, spot_prices);
    payoff_sum += pOption->pay_off->operator()(spot_prices[num_intervals-1]);
  }
  double option_price = (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  if(num_sims%1000==0){
  std::cout<<"Running for "<<num_sims <<" number of paths\n";
  std::cout << "Option Price: " << option_price << std::endl;
  std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()<<" milli seconds"<< std::endl;
  }
  sims_price[num_sims] = option_price;
  num_sims *= 2;
  }

  /// 2. Running for different values of N
  std::cout<<"#2 \n";
  num_sims = 1000;
  while(num_intervals<10000){
  // Create the spot and vol initial normal and price paths
  std::vector<double> spot_draws(num_intervals, 0.0);  // Vector of initial spot normal draws
  std::vector<double> vol_draws(num_intervals, 0.0);   // Vector of initial correlated vol normal draws
  std::vector<double> spot_prices(num_intervals, S_0);  // Vector of initial spot prices
  std::vector<double> vol_prices(num_intervals, v_0);   // Vector of initial vol prices
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  double payoff_sum = 0.0;
  for (unsigned i=0; i<num_sims; i++) {
    generate_normal_correlation_paths(rho, spot_draws, vol_draws);
    hest_euler.calc_vol_path(vol_draws, vol_prices);
    hest_euler.calc_spot_path(spot_draws, vol_prices, spot_prices);
    payoff_sum += pOption->pay_off->operator()(spot_prices[num_intervals-1]);
  }
  double option_price = (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  std::cout<<"Running for "<<1num_intervals <<" interval\n";
  std::cout << "Option Price: " << option_price << std::endl;
  std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()<<" milli seconds"<< std::endl;
  num_intervals*=10;
  }
  return 0;
}
