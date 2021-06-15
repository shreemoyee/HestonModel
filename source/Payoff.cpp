#include "../include/Payoff.h"

PayOff::PayOff() {}

PayOffCall::PayOffCall(const double& K_) { K = K_; }

double PayOffCall::operator() (const double& S) const {
  return std::max(S-K, 0.0); // Standard European call pay-off
}

PayOffPut::PayOffPut(const double& _K) {
  K = _K;
}

double PayOffPut::operator() (const double& S) const {
  return std::max(K-S, 0.0); // Standard European put pay-off
}
