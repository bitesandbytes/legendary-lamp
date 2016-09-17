//
// Created by sauce on 16/9/16.
//

#ifndef NLPASSIGNMENT_CORPUSDISTRIBUTION_H
#define NLPASSIGNMENT_CORPUSDISTRIBUTION_H

#include "distribution.h"
#include "../parsers/dictionary_parser.h"

class CorpusCharDistribution : public Distribution<char> {
 public:
  CorpusCharDistribution(DictionaryParser &dict_parser) : single_char_p_(dict_parser.GetCharProbs()) {}

  // Returns P(c) for input char.
  double eval(const char input) {
    return single_char_p_[static_cast<int>(input - 'a')];
  }

 private:
  decltype(DictionaryParser::char_p_) &single_char_p_;
};

class CorpusPairCharDistribution : public Distribution<std::string> {
 public:
  CorpusPairCharDistribution(DictionaryParser &dict_parser) : pair_char_p_(dict_parser.GetPairCharProbs()) {}

  // Returns P(ab) for input string :: "ab".
  double eval(const std::string input) {
    if (pair_char_p_.find(input) == pair_char_p_.end())
      throw std::runtime_error("CorpusPairCharDistribution::eval :: Invalid input - " + input);
    else
      return pair_char_p_[input];
  }

 private:
  decltype(DictionaryParser::char_pq_) &pair_char_p_;
};

class MatrixPairDistribution : public Distribution<std::pair<char, char>> {
 public:
  MatrixPairDistribution(DictionaryParser &dict_parser) : pair_char_p_(dict_parser.GetPairCharProbs()) {}

  // Returns P(ab) for input string :: "ab".
  double eval(const std::string input) {
    if (pair_char_p_.find(input) == pair_char_p_.end())
      throw std::runtime_error("CorpusPairCharDistribution::eval :: Invalid input - " + input);
    else
      return pair_char_p_[input];
  }

 private:
  decltype(DictionaryParser::char_pq_) &pair_char_p_;
};

class CorpusWordDistribution : public Distribution<std::string> {
 public:
  CorpusWordDistribution(DictionaryParser &dict_parser) : word_prob_map_(dict_parser.GetWordProbs()) {}

  bool exists(const std::string input) {
    return (word_prob_map_.count(input) != 0);
  }

  // Returns P(input) in corpus.
  double eval(const std::string input) {
    const auto iter = word_prob_map_.find(input);
    if (iter == word_prob_map_.cend())
      throw std::runtime_error("CorpusWordDistribution::eval() :: input not found."
                                   "Must call CorpusWordDistribution::exists() before "
                                   "CorpusWordDistribution::eval()");
    else
      return iter->second;
  }

 private:
  decltype(DictionaryParser::probs_) &word_prob_map_;
};

#endif //NLPASSIGNMENT_CORPUSDISTRIBUTION_H
