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

  // Use this->words[word] to get probabilities for the words.
  // Use this->words.count( word ) to check if the word is in the dictionary.
  // Use this->probability to get the probability of this transform.


  // Return a set of candidates along with their probabilities. The boolean should be True for a valid condidate and False for an invalid( but potentially valid ) candidate.
  // Do not consider multiple instances of the transform.
  // For example if the transform is "ab"->"a" and "ab" occurs twice, then there should be 2 candidates( one for each separately, but none for both together )
  return std::vector<std::tuple<std::string, float, bool>>();
}
Distribution<std::string> *Transform::getWords() const {
  return words;
}

