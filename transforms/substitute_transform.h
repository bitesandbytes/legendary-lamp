//
// Created by sauce on 17/9/16.
//

#ifndef NLPASSIGNMENT_SUBSTITUTE_TRANSFORM_H
#define NLPASSIGNMENT_SUBSTITUTE_TRANSFORM_H

#include "Transform.h"

class SubstituteTransform : public MyTransform<26> {
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

  // TODO(SaipraveenB) : Insert SUB matrix here.
  this->transform_matrix_ = {{0}};

  // TODO(SaipraveenB) : Normalize matrix here.

  for (int i = 0; i < 26; i++)
    for (int ch = 0; ch < 26; ch++)
      this->transform_matrix_[i][ch] /= char_p->eval(static_cast<char>(ch + 'a'));
}

std::vector<std::tuple<std::string, float, bool> > ApplyTransformSingle(const std::tuple<std::string,
                                                                                         float,
                                                                                         bool> &input, int pos) {

  std:
  string str(std::get<0>(input));

  decltype(SubstituteTransform::ApplyTransformSingle()) sub_vec;
  sub_vec.reserve(26);

  std::string new_str(str);
  for (int i = 0; i < 26; i++) {
    new_str[pos] = static_cast<char>(i + 'a');
    sub_vec.push_back(std::make_tuple(std::string(new_str),
                                      this->transform_matrix_[i][static_cast<int>(str[pos] - 'a')]
                                          * std::get<1>(input)),
                      this->dict_->exists(new_str));
    new_str[pos] = str[pos];
  }

  return sub_vec;
}

std::vector<std::tuple<std::string, float, bool> > ApplyTransform(const std::tuple<std::string, float, bool> &input) {
  decltype(SubstituteTransform::ApplyTransform()) sub_cands;
  sub_cands.reserve(std::get<0>(input).length() * 26);

  for (int i = 0; i < str.size(); i++) {
    const auto &sub_pos = ApplyTransformSingle(input, i);
    sub_cands.insert(sub_cands.end(), sub_pos.begin(), sub_pos.end());
  }

  return sub_cands;
}
#endif //NLPASSIGNMENT_SUBSTITUTE_TRANSFORM_H
