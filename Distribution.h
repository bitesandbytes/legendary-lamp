//
// Created by Saipraveen B on 16/09/16.
//

#ifndef NLPASSIGNMENT_DISTRIBUTION_H
#define NLPASSIGNMENT_DISTRIBUTION_H

#include <vector>
#include <map>
template<typename T>
class Distribution<T> {

 public:
  // Evaluate the floating point probability of the the input.
  virtual float eval( T inp );
  // Add a data point to the distribution. Probabilities are recomputed completely here. Could be inefficeient.
  virtual float data( T data );
  // Process batch data. Probabilities are recomputed after a batch of inputs.
  virtual float batchData( std::map<T,unsigned int> vec );

};

#endif //NLPASSIGNMENT_DISTRIBUTION_H
