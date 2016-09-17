//
// Created by sauce on 17/9/16.
//

#ifndef NLPASSIGNMENT_REVERSAL_TRANSFORM_H
#define NLPASSIGNMENT_REVERSAL_TRANSFORM_H

#include "Transform.h"

class ReversalTransform : public MyTransform<26> {
  ReversalTransform(CorpusWordDistribution *dict, CorpusCharDistribution *char_p);
  std::vector<std::tuple<std::string, float, bool> > ApplyTransform(const std::tuple<std::string, float, bool> &input);
 private:
  std::tuple<std::string, float, bool> ApplyTransformSingle(const std::tuple<std::string, float, bool> &input,
                                                            const int pos);
  CorpusWordDistribution *dict_;
};

ReversalTransform::ReversalTransform(CorpusWordDistribution *dict, CorpusPairCharDistribution *char_pair) {
  this->dict_ = dict;

  // TODO(SaipraveenB) : Insert REV matrix here.
  this->transform_matrix_ = {{0}};

  // TODO(SaipraveenB) : Normalize matrix here.

  for (int i = 0; i < 26; i++)
    for (int ch = 0; ch < 26; ch++) {
      std::string str("..");
      str[0] = static_cast<char>(i + 'a');
      str[1] = static_cast<char>(ch + 'a');
      this->transform_matrix_[i][ch] /= char_pair->eval(str);
    }
}

std::tuple<std::string, float, bool> ApplyTransformSingle(const std::tuple<std::string, float, bool> &input, int pos) {
  using std::swap;

  std::string str = std::get<0>(input);

  std::string new_str(str);

  swap(new_str[pos], new_str[pos + 1]);

  return std::make_tuple(new_str,
                         this->transform_matrix_[static_cast<int>(str[pos] - 'a')][static_cast<int>(str[pos + 1]
                             - 'a')] * std::get<1>(input),
                         this->dict_->exists(new_str));
}

std::vector<std::tuple<std::string, float, bool> > ApplyTransform(const std::tuple<std::string, float, bool> &input) {
  decltype(ReversalTransform::ApplyTransform()) rev_cands;
  rev_cands.reserve(std::get<0>(input).length() - 1);

  for (int i = 0; i < std::get<0>(input).length() - 1; i++)
    rev_cands.push_back(ApplyTransformSingle(input, i));

  return sub_cands;
}
#endif //NLPASSIGNMENT_REVERSAL_TRANSFORM_H
