//
// Created by sauce on 17/9/16.
//

#ifndef NLPASSIGNMENT_INSERTION_TRANSFORM_H
#define NLPASSIGNMENT_INSERTION_TRANSFORM_H
#include "Transform.h"

class InsertionTransform : public MyTransform<27> {
 public:
  InsertionTransform(CorpusWordDistribution *word_distr, CorpusCharDistribution *char_distr);
  std::vector<std::tuple<std::string, float, bool> > ApplyTransform(const std::tuple<std::string, float, bool> &input);

 private:
  std::vector<std::tuple<std::string, float, bool> > ApplyTransformSingle(const std::tuple<std::string,
                                                                                           float,
                                                                                           bool> &input, int pos);
  const CorpusWordDistribution *word_distr;
};

InsertionTransform::InsertionTransform(CorpusWordDistribution *word_distr, CorpusCharDistribution *char_distr) {
  this->word_distr = word_distr;

  // TODO(bitesandbytes) : Fill this in with the transform matrix.
  this->transform_matrix_ = {{0}};

  // TODO(bitesandbytes | SaipraveenB) : Normalize the transform matrix.

  // Add corpus info.
  for (int i = 0; i < 26; i++)
    for (int ch = 0; ch < 26; ch++)
      this->transform_matrix_[i][ch] /= char_distr->eval(static_cast<char>(ch + 'a'));

  return;
}

std::vector<std::tuple<std::string, float, bool> > ApplyTransformSingle(const std::tuple<std::string,
                                                                                         float,
                                                                                         bool> &input, int pos) {
  std::stirng str(std::get<0>(input));
  decltype(InsertionTransform::ApplyTransformSingle()) transforms_single;
  transforms_single.reserve(52);
  for (int i = 0; i < 26; i++) {
    std::string new_str(str);
    new_str.insert(pos, 1, static_cast<char>(i + 'a'));
    transforms_single.push_back(std::make_tuple(new_str,
                                                transform_matrix_[static_cast<int>(str[pos] - 'a')][i]
                                                    * std::get<1>(input),
                                                this->word_distr->exists(new_str)));
  }

  return transforms_single;
}

std::vector<std::tuple<std::string, float, bool> > ApplyTransform(const std::tuple<std::string, float, bool> &input) {
  decltype(InsertionTransform::ApplyTransform()) all_transforms;
  all_transforms.reserve(26 * str.size());
  for (int i = 0; i <= str.size(); i++) {
    // TODO(SaipraveenB) : Complete this.
  }
};
#endif //NLPASSIGNMENT_INSERTION_TRANSFORM_H
