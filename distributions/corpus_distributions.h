//
// Created by sauce on 16/9/16.
//

#ifndef NLPASSIGNMENT_CORPUSDISTRIBUTION_H
#define NLPASSIGNMENT_CORPUSDISTRIBUTION_H

#include "distribution.h"
#include "../parsers/dictionary_parser.h"

class CorpusCharDistribution : public Distribution<char> {
 public:
  CorpusCharDistribution(const DictionaryParser &dict_parser) {
    this->single_char_p_ = dict_parser.GetCharProbs();
  }

  // Returns P(c) for input char.
  float eval(const char input) {
    return single_char_p_[static_cast<int>(input - 'a')];
  }

 private:
  const decltype(DictionaryParser::char_p_) &single_char_p_;
};

class CorpusPairCharDistribution : public Distribution<std::string> {
 public:
  CorpusPairCharDistribution(const DictionaryParser &dict_parser) {
    this->pair_char_p_ = dict_parser.GetPairCharProbs();
  }

  // Returns P(ab) for input string :: "ab".
  float eval(const std::string input) {
    return pair_char_p_[static_cast<int>(input[0] - 'a')][static_cast<int>(input[1] - 'a')];
  }

 private:
  const decltype(DictionaryParser::char_pq_) &pair_char_p_;
};

class MatrixPairDistribution : public Distribution<std::pair<char,char>> {
 public:
  CorpusPairCharDistribution(const DictionaryParser &dict_parser, in) {
    this->pair_char_p_ = dict_parser.GetPairCharProbs();
  }

  // Returns P(ab) for input string :: "ab".
  float eval(const std::string input) {
    return pair_char_p_[static_cast<int>(input[0] - 'a')][static_cast<int>(input[1] - 'a')];
  }

 private:
  const decltype(DictionaryParser::char_pq_) &pair_char_p_;
};

class CorpusWordDistribution : public Distribution<std::string> {
 public:
  CorpusPairCharDistribution(const DictionaryParser &dict_parser) {
    this->word_prob_map_ = dict_parser.GetWordProbs();
  }

  bool exists(const std::string input) {
    return (word_prob_map_.find(input) != word_prob_map_.end());
  }

  // Returns P(input) in corpus.
  float eval(const std::string input) {
    const auto iter = word_prob_map_.find(input);
    if (iter == word_prob_map_.cend())
      throw std::runtime_error("CorpusWordDistribution::eval() :: input not found."
                                   "Must call CorpusWordDistribution::exists() before "
                                   "CorpusWordDistribution::eval()");
    else
      return iter->second;
  }

 private:
  const decltype(DictionaryParser::probs_) &word_prob_map_;
};

#endif //NLPASSIGNMENT_CORPUSDISTRIBUTION_H
