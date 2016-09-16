//
// Created by Saipraveen B on 16/09/16.
//

#ifndef NLPASSIGNMENT_TRANSFORM_H
#define NLPASSIGNMENT_TRANSFORM_H

#include <string>
#include <map>
#include <vector>
#include "Distribution.h"

class Transform {

 protected:
  // The probability associated with this transform.
  float probability;

  // A mapping from strings to strings here.
  // Transform applies each of the transforms here to generate a final set of candidates.
  // Each element in the map is assumed to represent probability 'probability'
  // Thus if more than one element of the map( also if the same element is applied several times )
  // the probability is multiplied with themselves.
  // Note: Not used for the space transform.
  std::map<std::string, std::string> map;

  // Hold the probability distribution over the words here.
  Distribution<std::string> *words;
 public:
  Distribution<std::string> *getWords() const;

 public:
  void setWords(Distribution<std::string> *words);

 public:
  float getProbability() const;
  void setProbability(float probability);

  void addMapping(std::string src, std::string dest) {

    if (map.count(src))
      throw "This source has already been mapped";

    map[src] = map[dest];

  }

  virtual std::vector<std::tuple<std::string, float, bool> > applyAll(std::string str) const;
  virtual std::vector<std::tuple<std::string, float, bool> > applyOne(std::string str,
                                                                      unsigned int occurence = 0) const;

};

#endif //NLPASSIGNMENT_TRANSFORM_H
