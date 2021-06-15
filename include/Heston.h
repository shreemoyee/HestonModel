#ifndef __HESTON_H__
#define __HESTON_H__

#include <cmath>
#include <vector>
#include <memory>
#include "Asian.h"

/// The HestonEuler class
class HestonEuler {
 private:
  using asianPtr = std::shared_ptr<AsianOption>;
  asianPtr pOption;
  double kappa;
  double theta;
  double xi;
  double rho;

 public:
  HestonEuler(asianPtr pOption_,
              double kappa_, double theta_,
              double xi_, double rho_);
  virtual ~HestonEuler() = default;

  // Calculate the volatility path
  void calc_vol_path(const std::vector<double>& vol_draws,
                     std::vector<double>& vol_path);

  // Calculate the asset price path
  void calc_spot_path(const std::vector<double>& spot_draws,
                      const std::vector<double>& vol_path,
                      std::vector<double>& spot_path);
};

#endif
