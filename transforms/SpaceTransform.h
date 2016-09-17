//
// Created by Saipraveen B on 16/09/16.
//

#ifndef NLPASSIGNMENT_SPACETRANSFORM_H
#define NLPASSIGNMENT_SPACETRANSFORM_H

#include <string>
#include <vector>
#include "Transform.h"

class SpaceTransform : public MyTransform {
 public:
  SpaceTransform(CorpusWordDistribution *dict) : words(dict) {}
  std::vector<std::tuple<std::string, float, bool> > ApplyTransform(const std::tuple<std::string,
                                                                                     float,
                                                                                     bool> &input);
  float get_probability(std::string s);

 private:
  CorpusWordDistribution *words;
};

#endif //NLPASSIGNMENT_SPACETRANSFORM_H
