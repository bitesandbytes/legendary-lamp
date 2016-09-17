//
// Created by Saipraveen B on 16/09/16.
//

#ifndef NLPASSIGNMENT_TRANSFORM_H
#define NLPASSIGNMENT_TRANSFORM_H

#include <string>
#include <map>
#include <vector>
#include "../distributions/distribution.h"
#include "../distributions/corpus_distributions.h"

class MyTransform {
 public:
  virtual std::vector<std::tuple<std::string, float, bool> > ApplyTransform(const std::tuple<std::string,
                                                                                             float,
                                                                                             bool> &input) = 0;

 protected:
  std::vector<std::vector<float>> transform_matrix_;
};

#endif //NLPASSIGNMENT_TRANSFORM_H
