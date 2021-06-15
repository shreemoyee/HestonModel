#ifndef __CORRELATED_WIENER_H__
#define __CORRELATED_WIENER_H__

#include <memory>
#include "StandardNormalDistribution.h"


/// The purpose of this class is to generate two correlated gaussian distributions
class CorrelatedWiener : public StandardNormalDistribution {
 protected:
  double rho;
  const std::shared_ptr<std::vector<double> > uncorr_draws;

  // Modify an uncorrelated set of distribution draws to be correlated
  virtual void correlation_calc(std::vector<double>& dist_draws);

 public:
  CorrelatedWiener(const double _rho,
                const std::shared_ptr<std::vector<double> >  _uncorr_draws);
  CorrelatedWiener(const CorrelatedWiener& correlatedWiener) = delete;
  CorrelatedWiener& operator=(const CorrelatedWiener& correlatedWiener) = delete;
  virtual ~CorrelatedWiener() = default;

  // Obtain a sequence of correlated random draws from another set of SND draws
  virtual void random_draws(const std::vector<double>& uniform_draws,
                            std::vector<double>& dist_draws);
};

#endif
