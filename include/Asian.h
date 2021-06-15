#ifndef __ASIAN_H__
#define __ASIAN_H__

#include <vector>
#include <memory>
#include "Payoff.h"

class AsianOption {

 public:
  double K;
  double r;
  double T;
  using PayOffPtr = std::shared_ptr<PayOff>;
  PayOffPtr pay_off;
  AsianOption(double _K, double _r,
         double _T, PayOffPtr pay_off_);
  virtual ~AsianOption() {};

  // Pure virtual pay-off operator (this will determine arithmetic or geometric)
  virtual double pay_off_price(const std::vector<double>& spot_prices) const = 0;
};

class AsianOptionArithmetic : public AsianOption {
 public:
  AsianOptionArithmetic(double _K, double _r,
         double _T, PayOffPtr pay_off_);
  virtual ~AsianOptionArithmetic() {};

  // Override the pure virtual function to produce arithmetic Asian Options
  virtual double pay_off_price(const std::vector<double>& spot_prices) const;
};

class AsianOptionGeometric : public AsianOption {
 public:
  AsianOptionGeometric(double _K, double _r,
         double _T, PayOffPtr pay_off_);
  virtual ~AsianOptionGeometric() {};

  // Overide the pure virtual function to produce geometric Asian Options
  virtual double pay_off_price(const std::vector<double>& spot_prices) const;
};

#endif
