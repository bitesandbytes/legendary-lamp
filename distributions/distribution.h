//
// Created by Saipraveen B on 16/09/16.
//

#ifndef NLPASSIGNMENT_DISTRIBUTION_H
#define NLPASSIGNMENT_DISTRIBUTION_H

#include <vector>
#include <map>

/*
 * Extend this class to implement the source of the distribution.
 * Like HardCodedDistribution<std::pair<char,char>> for hard coded probability values
 * and FileDistribution<std::string> for loading the probaiblities from a file.
 * Note that you have to convert frequencies into probabilities for them to work.
 */
template<typename T>
class Distribution {

 public:
  // Evaluate the floating point probability of the the input.
  virtual double eval(const T inp) = 0;

  virtual bool exists(const T inp) {
    return true;
  }

  // FUNCTIONS TO MODIFY THE DISTRIUTION.
  // NO NEED TO IMPLEMENT IF HARD-CODED OR IF IT DOES NOT CHANGE
  // DURING THE EXECUTION.

  // Add a data point to the distribution. Probabilities are recomputed completely here. Could be inefficeient.
  virtual float data(T data) {
    return 0.0f;
  }
  // Process batch data. Probabilities are recomputed after a batch of inputs.
  virtual float batchData(std::map<T, unsigned int> vec) {
    return 0.0f;
  }
};

#endif //NLPASSIGNMENT_DISTRIBUTION_H
