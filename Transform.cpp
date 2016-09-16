//
// Created by Saipraveen B on 16/09/16.
//

#include "Transform.h"
float Transform::getProbability() const {
  return probability;
}
void Transform::setProbability(float probability) {
  Transform::probability = probability;
}
void Transform::setWords(Distribution<std::string> *words) {
  Transform::words = words;
}
std::vector<std::tuple<std::string, float, bool> > Transform::applyAll(std::string str) const {

  return std::vector<std::tuple<std::string, float, bool>>();
}

