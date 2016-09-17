//
// Created by sauce on 17/9/16.
//

#ifndef NLPASSIGNMENT_SUBSTITUTE_TRANSFORM_H
#define NLPASSIGNMENT_SUBSTITUTE_TRANSFORM_H

#include "Transform.h"

class SubstituteTransform : public MyTransform {
 public:
  SubstituteTransform(CorpusWordDistribution *dict, CorpusCharDistribution *char_p);
  std::vector<std::tuple<std::string, float, bool> > ApplyTransform(const std::tuple<std::string, float, bool> &input);
 private:
  std::vector<std::tuple<std::string, float, bool>> ApplyTransformSingle(const std::tuple<std::string,
                                                                                          float,
                                                                                          bool> &input, int pos);
  CorpusWordDistribution *dict_;
};

SubstituteTransform::SubstituteTransform(CorpusWordDistribution *dict, CorpusCharDistribution *char_p) {
  this->dict_ = dict;

  this->transform_matrix_ =
      decltype(this->transform_matrix_){
          {0, 0, 7, 1, 342, 0, 0, 2, 118, 0, 1, 0, 0, 3, 76, 0, 0, 1, 35, 9, 9, 0, 1, 0, 5, 0},
          {0, 0, 9, 9, 2, 2, 3, 1, 0, 0, 0, 5, 11, 5, 0, 10, 0, 0, 2, 1, 0, 0, 8, 0, 0, 0},
          {6, 5, 0, 16, 0, 9, 5, 0, 0, 0, 1, 0, 7, 9, 1, 10, 2, 5, 39, 40, 1, 3, 7, 1, 1, 0},
          {1, 10, 13, 0, 12, 0, 5, 5, 0, 0, 2, 3, 7, 3, 0, 1, 0, 43, 30, 22, 0, 0, 4, 0, 2, 0},
          {388, 0, 3, 11, 0, 2, 2, 0, 89, 0, 0, 3, 0, 5, 93, 0, 0, 14, 12, 6, 15, 0, 1, 0, 18, 0},
          {0, 15, 0, 3, 1, 0, 5, 2, 0, 0, 0, 3, 4, 1, 0, 0, 0, 6, 4, 12, 0, 0, 2, 0, 0, 0},
          {4, 1, 11, 11, 9, 2, 0, 0, 0, 1, 1, 3, 0, 0, 2, 1, 3, 5, 13, 21, 0, 0, 1, 0, 3, 0},
          {1, 8, 0, 3, 0, 0, 0, 0, 0, 0, 2, 0, 12, 14, 2, 3, 0, 3, 1, 11, 0, 0, 2, 0, 0, 0},
          {103, 0, 0, 0, 146, 0, 1, 0, 0, 0, 0, 6, 0, 0, 49, 0, 0, 0, 2, 1, 47, 0, 2, 1, 15, 0},
          {0, 1, 1, 9, 0, 0, 1, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0},
          {1, 2, 8, 4, 1, 1, 2, 5, 0, 0, 0, 0, 5, 0, 2, 0, 0, 0, 6, 0, 0, 0, .4, 0, 0, 3},
          {2, 10, 1, 4, 0, 4, 5, 6, 13, 0, 1, 0, 0, 14, 2, 5, 0, 11, 10, 2, 0, 0, 0, 0, 0, 0},
          {1, 3, 7, 8, 0, 2, 0, 6, 0, 0, 4, 4, 0, 180, 0, 6, 0, 0, 9, 15, 13, 3, 2, 2, 3, 0},
          {2, 7, 6, 5, 3, 0, 1, 19, 1, 0, 4, 35, 78, 0, 0, 7, 0, 28, 5, 7, 0, 0, 1, 2, 0, 2},
          {91, 1, 1, 3, 116, 0, 0, 0, 25, 0, 2, 0, 0, 0, 0, 14, 0, 2, 4, 14, 39, 0, 0, 0, 18, 0},
          {0, 11, 1, 2, 0, 6, 5, 0, 2, 9, 0, 2, 7, 6, 15, 0, 0, 1, 3, 6, 0, 4, 1, 0, 0, 0},
          {0, 0, 1, 0, 0, 0, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 14, 0, 30, 12, 2, 2, 8, 2, 0, 5, 8, 4, 20, 1, 14, 0, 0, 12, 22, 4, 0, 0, 1, 0, 0},
          {11, 8, 27, 33, 35, 4, 0, 1, 0, 1, 0, 27, 0, 6, 1, 7, 0, 14, 0, 15, 0, 0, 5, 3, 20, 1},
          {3, 4, 9, 42, 7, 5, 19, 5, 0, 1, 0, 14, 9, 5, 5, 6, 0, 11, 37, 0, 0, 2, 19, 0, 7, 6},
          {20, 0, 0, 0, 44, 0, 0, 0, 64, 0, 0, 0, 0, 2, 43, 0, 0, 4, 0, 0, 0, 0, 2, 0, 8, 0},
          {0, 0, 7, 0, 0, 3, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 8, 3, 0, 0, 0, 0, 0, 0},
          {2, 2, 1, 0, 1, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 7, 0, 6, 3, 3, 1, 0, 0, 0, 0, 0},
          {0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 2, 0, 15, 0, 1, 7, 15, 0, 0, 0, 2, 0, 6, 1, 0, 7, 36, 8, 5, 0, 0, 1, 0, 0},
          {0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 7, 5, 0, 0, 0, 0, 2, 21, 3, 0, 0, 0, 0, 3, 0}};

  for (int i = 0; i < 26; i++)
    for (int ch = 0; ch < 26; ch++)
      this->transform_matrix_[i][ch] /= char_p->eval(static_cast<char>(ch + 'a'));
}

std::vector<std::tuple<std::string,
                       float,
                       bool> > SubstituteTransform::ApplyTransformSingle(const std::tuple<std::string,
                                                                                          float,
                                                                                          bool> &input, int pos) {

  std::string str(std::get<0>(input));

  std::vector<std::tuple<std::string, float, bool> > sub_vec;
  sub_vec.reserve(26);

  std::string new_str(str);
  for (int i = 0; i < 26; i++) {
    new_str[pos] = static_cast<char>(i + 'a');
    sub_vec.push_back(std::make_tuple(std::string(new_str),
                                      this->transform_matrix_[i][static_cast<int>(str[pos] - 'a')]
                                          * std::get<1>(input),
                                      this->dict_->exists(new_str)));
    new_str[pos] = str[pos];
  }

  return sub_vec;
}

std::vector<std::tuple<std::string, float, bool> > SubstituteTransform::ApplyTransform(const std::tuple<std::string,
                                                                                                        float,
                                                                                                        bool> &input) {
  std::vector<std::tuple<std::string, float, bool> > sub_cands;
  sub_cands.reserve(std::get<0>(input).length() * 26);

  for (int i = 0; i < std::get<0>(input).length(); i++) {
    const auto &sub_pos = ApplyTransformSingle(input, i);
    sub_cands.insert(sub_cands.end(), sub_pos.begin(), sub_pos.end());
  }

  return sub_cands;
}
#endif //NLPASSIGNMENT_SUBSTITUTE_TRANSFORM_H
