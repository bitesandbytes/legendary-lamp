//
// Created by Saipraveen B on 16/09/16.
//

#include<iostream>
#include <vector>
#include <map>
#include <queue>
#include "distributions/distribution.h"
#include "Transform.h"

#ifndef NLPASSIGNMENT_SPELLCORRECTOR_H
#define NLPASSIGNMENT_SPELLCORRECTOR_H

/*
 * SpellCorrector - Main calss for spelling correction.
 */
class SpellCorrector {
 private:
  // Main string frequency list.
  //std::map<std::string, unsigned int> frequencies;

  // Probability distribution over words.
  Distribution<std::string> *words;
 public:
  Distribution<std::string> *getWords() const;
  void setWords(Distribution<std::string> *words);
  Distribution<std::pair<char, char>> *getReverse() const;
  void setReverse(Distribution<std::pair<char, char>> *reverse);
  Distribution<std::pair<char, char>> *getAddition() const;
  void setAddition(Distribution<std::pair<char, char>> *addition);
  Distribution<std::pair<char, char>> *getDeletion() const;
  void setDeletion(Distribution<std::pair<char, char>> *deletion);
  Distribution<std::pair<char, char>> *getReplace() const;
  void setReplace(Distribution<std::pair<char, char>> *replace);
  Distribution<char> *getSpace() const;
  void setSpace(Distribution<char> *space);

  SpellCorrector();

  void populate();

  std::vector<std::string> correctWord( std::string word ){
    // Do the correction thing here.

  }


 private:
  Distribution<std::pair<char,char>> *reverse;
  Distribution<std::pair<char,char>> *addition;
  Distribution<std::pair<char,char>> *deletion;
  Distribution<std::pair<char,char>> *replace;

  // Probabilty of a space.
  Distribution<char> *space;


  static const auto comparator = [](Transform* t){t->getProbability();};
  // Transformations for manipulating a string arranged in order of their probabilities.
  std::priority_queue<Transform*, std::vector<Transform*>, decltype( comparator )> transforms;


};

#endif //NLPASSIGNMENT_SPELLCORRECTOR_H
