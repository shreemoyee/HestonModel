#ifndef __STANDARDNOMALDISTRIBTION_H__
#define __STANDARDNOMALDISTRIBTION_H__

#include <cmath>
#include <vector>
#include "StatisticalDistributions.h"

class StandardNormalDistribution : public StatisticalDistribution {
 public:
  StandardNormalDistribution();
  virtual ~StandardNormalDistribution();

  // Distribution functions
  virtual double pdf(const double& x) const;
  virtual double cdf(const double& x) const;

  // Inverse cumulative distribution function (aka the probit function)
  virtual double inv_cdf(const double& quantile) const;

  // Descriptive stats
  virtual double mean() const;   // equal to 0
  virtual double var() const;    // equal to 1
  virtual double stdev() const;  // equal to 1

  ///Box-Muller method
  virtual void random_draws(const std::vector<double>& uniform_draws,
                            std::vector<double>& dist_draws);
};

#endif
