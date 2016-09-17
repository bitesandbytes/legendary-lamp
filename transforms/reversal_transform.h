//
// Created by sauce on 17/9/16.
//

#ifndef NLPASSIGNMENT_REVERSAL_TRANSFORM_H
#define NLPASSIGNMENT_REVERSAL_TRANSFORM_H

#include "Transform.h"

class ReversalTransform : public MyTransform {
 public:
  ReversalTransform(CorpusWordDistribution *dict, CorpusPairCharDistribution *char_p);
  std::vector<std::tuple<std::string, float, bool> > ApplyTransform(const std::tuple<std::string, float, bool> &input);
 private:
  std::tuple<std::string, float, bool> ApplyTransformSingle(const std::tuple<std::string, float, bool> &input,
                                                            const int pos);
  CorpusWordDistribution *dict_;
};

ReversalTransform::ReversalTransform(CorpusWordDistribution *dict, CorpusPairCharDistribution *char_pair) {
  this->dict_ = dict;

  this->transform_matrix_ =
      decltype(this->transform_matrix_){
          {0, 0, 2, 1, 1, 0, 0, 0, 19, 0, 1, 14, 4, 25, 10, 3, 0, 27, 3, 5, 31, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1, 1, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 1, 0, 0, 1, 85, 0, 0, 15, 0, 0, 13, 0, 0, 0, 3, 0, 7, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0},
          {1, 0, 4, 5, 0, 0, 0, 0, 60, 0, 0, 21, 6, 16, 11, 2, 0, 29, 5, 0, 85, 0, 0, 0, 2, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 12, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          {4, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1, 0, 15, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0},
          {12, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0},
          {15, 8, 31, 3, 66, 1, 3, 0, 0, 0, 0, 9, 0, 5, 11, 0, 1, 13, 42, 35, 0, 6, 0, 0, 0, 3},
          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          {11, 0, 0, 12, 20, 0, 1, 0, 4, 0, 0, 0, 0, 0, 1, 3, 0, 0, 1, 1, 3, 9, 0, 0, 7, 0},
          {9, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0},
          {15, 0, 6, 2, 12, 0, 8, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 6, 4, 0, 0, 0, 0, 0, 0},
          {5, 0, 2, 0, 4, 0, 0, 0, 5, 0, 0, 1, 0, 5, 0, 1, 0, 11, 1, 1, 0, 0, 7, 1, 0, 0},
          {17, 0, 0, 0, 4, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 5, 3, 6, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          {12, 0, 0, 0, 24, 0, 3, 0, 14, 0, 2, 2, 0, 7, 30, 1, 0, 0, 0, 2, 10, 0, 0, 0, 2, 0},
          {4, 0, 0, 0, 9, 0, 0, 5, 15, 0, 0, 5, 2, 0, 1, 22, 0, 0, 0, 1, 3, 0, 0, 0, 16, 0},
          {4, 0, 3, 0, 4, 0, 0, 21, 49, 0, 0, 4, 0, 0, 3, 0, 0, 5, 0, 0, 11, 0, 2, 0, 0, 0},
          {22, 0, 5, 1, 1, 0, 2, 0, 2, 0, 0, 2, 1, 0, 20, 2, 0, 11, 11, 2, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 1, 2, 0, 0, 0, 1, 0, 0, 0, 0, 3, 0, 0, 0, 2, 0, 1, 10, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  // 2-char string.
  std::string str("..");
  for (int i = 0; i < 26; i++)
    for (int ch = 0; ch < 26; ch++) {
      str[0] = static_cast<char>(i + 'a');
      str[1] = static_cast<char>(ch + 'a');
      this->transform_matrix_[i][ch] /= char_pair->eval(str);
    }
}

std::tuple<std::string, float, bool> ReversalTransform::ApplyTransformSingle(const std::tuple<std::string,
                                                                                              float,
                                                                                              bool> &input, int pos) {
  using std::swap;

  std::string str = std::get<0>(input);

  std::string new_str(str);

  swap(new_str[pos], new_str[pos + 1]);

  return std::make_tuple(new_str,
                         this->transform_matrix_[static_cast<int>(str[pos] - 'a')][static_cast<int>(str[pos + 1]
                             - 'a')] * std::get<1>(input),
                         this->dict_->exists(new_str));
}

std::vector<std::tuple<std::string, float, bool> > ReversalTransform::ApplyTransform(const std::tuple<std::string,
                                                                                                      float,
                                                                                                      bool> &input) {
  std::vector<std::tuple<std::string, float, bool> > rev_cands;
  rev_cands.reserve(std::get<0>(input).length() - 1);

  for (int i = 0; i < std::get<0>(input).length() - 1; i++)
    rev_cands.push_back(ApplyTransformSingle(input, i));

  return rev_cands;
}
#endif //NLPASSIGNMENT_REVERSAL_TRANSFORM_H
