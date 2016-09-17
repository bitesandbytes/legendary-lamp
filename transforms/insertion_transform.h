//
// Created by sauce on 17/9/16.
//

#ifndef NLPASSIGNMENT_INSERTION_TRANSFORM_H
#define NLPASSIGNMENT_INSERTION_TRANSFORM_H
#include "Transform.h"

class InsertionTransform : public MyTransform {
 public:
  InsertionTransform(CorpusWordDistribution *word_distr, CorpusCharDistribution *char_distr);
  std::vector<std::tuple<std::string, float, bool> > ApplyTransform(const std::tuple<std::string, float, bool> &input);

 private:
  std::vector<std::tuple<std::string, float, bool> > ApplyTransformSingle(const std::tuple<std::string,
                                                                                           float,
                                                                                           bool> &input, int pos);
  CorpusWordDistribution *word_distr;
};

InsertionTransform::InsertionTransform(CorpusWordDistribution *word_distr, CorpusCharDistribution *char_distr) {
  this->word_distr = word_distr;

  this->transform_matrix_ =
      decltype(this->transform_matrix_){
          {15, 1, 14, 7, 10, 0, 1, 1, 33, 1, 4, 31, 2, 39, 12, 4, 3, 28, 134, 7, 28, 0, 1, 1, 4, 1},
          {3, 11, 0, 0, 7, 0, 1, 0, 50, 0, 0, 15, 0, 1, 1, 0, 0, 5, 16, 0, 0, 3, 0, 0, 0, 0},
          {19, 0, 54, 1, 13, 0, 0, 18, 50, 0, 3, 1, 1, 1, 7, 1, 0, 7, 25, 7, 8, 4, 0, 1, 0, 0},
          {18, 0, 3, 17, 14, 2, 0, 0, 9, 0, 0, 6, 1, 9, 13, 0, 0, 6, 119, 0, 0, 0, 0, 0, 5, 0},
          {39, 2, 8, 76, 147, 2, 0, 1, 4, 0, 3, 4, 6, 27, 5, 1, 0, 83, 417, 6, 4, 1, 10, 2, 8, 0},
          {1, 0, 0, 0, 2, 27, 1, 0, 12, 0, 0, 10, 0, 0, 0, 0, 0, 5, 23, 0, 1, 0, 0, 0, 1, 0},
          {8, 0, 0, 0, 5, 1, 5, 12, 8, 0, 0, 2, 0, 1, 1, 0, 1, 5, 69, 2, 3, 0, 1, 0, 0, 0},
          {4, 1, 0, 1, 24, 0, 10, 18, 17, 2, 0, 1, 0, 1, 4, 0, 0, 16, 24, 22, 1, 0, 5, 0, 3, 0},
          {10, 3, 13, 13, 25, 0, 1, 1, 69, 2, 1, 17, 11, 33, 27, 1, 0, 9, 30, 29, 11, 0, 0, 1, 0, 1},
          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
          {2, 4, 0, 1, 9, 0, 0, 1, 1, 0, 1, 1, 0, 0, 2, 1, 0, 0, 95, 0, 1, 0, 0, 0, 4, 0},
          {3, 1, 0, 1, 38, 0, 0, 0, 79, 0, 2, 128, 1, 0, 7, 0, 0, 0, 97, 7, 3, 1, 0, 0, 2, 0},
          {11, 1, 1, 0, 17, 0, 0, 1, 6, 0, 1, 0, 102, 44, 7, 2, 0, 0, 47, 1, 2, 0, 1, 0, 0, 0},
          {15, 5, 7, 13, 52, 4, 17, 0, 34, 0, 1, 1, 26, 99, 12, 0, 0, 2, 156, 53, 1, 1, 0, 0, 1, 0},
          {14, 1, 1, 3, 7, 2, 1, 0, 28, 1, 0, 6, 3, 13, 64, 30, 0, 16, 59, 4, 19, 1, 0, 0, 1, 1},
          {23, 0, 1, 1, 10, 0, 0, 20, 3, 0, 0, 2, 0, 0, 26, 70, 0, 29, 52, 9, 1, 1, 1, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
          {15, 2, 1, 0, 89, 1, 1, 2, 64, 0, 0, 5, 9, 7, 10, 0, 0, 132, 273, 29, 7, 0, 1, 0, 10, 0},
          {13, 1, 7, 20, 41, 0, 1, 50, 101, 0, 2, 2, 10, 7, 3, 1, 0, 1, 205, 49, 7, 0, 1, 0, 7, 0},
          {39, 0, 0, 3, 65, 1, 10, 24, 59, 1, 0, 6, 3, 1, 23, 1, 0, 54, 264, 183, 11, 0, 5, 0, 6, 0},
          {15, 0, 3, 0, 9, 0, 0, 1, 24, 1, 1, 3, 3, 9, 1, 3, 0, 49, 19, 27, 26, 0, 0, 2, 3, 0},
          {0, 2, 0, 0, 36, 0, 0, 0, 10, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 5, 1, 0, 0, 0},
          {0, 0, 0, 1, 10, 0, 0, 1, 1, 0, 1, 1, 0, 2, 0, 0, 1, 1, 8, 0, 2, 0, 4, 0, 0, 0},
          {0, 0, 18, 0, 1, 0, 0, 6, 1, 0, 0, 0, 1, 0, 3, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0},
          {5, 1, 2, 0, 3, 0, 0, 0, 2, 0, 0, 1, 1, 6, 0, 0, 0, 1, 33, 1, 13, 0, 1, 0, 2, 0},
          {2, 0, 0, 0, 5, 1, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4},
          {46, 8, 9, 8, 26, 11, 14, 3, 5, 1, 17, 5, 6, 2, 2, 10, 0, 6, 23, 2, 11, 1, 2, 1, 1, 2}};

  // Add corpus info.
  for (int i = 0; i < 27; i++)
    for (int ch = 0; ch < 26; ch++)
      this->transform_matrix_[i][ch] /= char_distr->eval(static_cast<char>(ch + 'a'));

  return;
}

std::vector<std::tuple<std::string,
                       float,
                       bool> > InsertionTransform::ApplyTransformSingle(const std::tuple<std::string,
                                                                                         float,
                                                                                         bool> &input, int pos) {
  std::string str(std::get<0>(input));
  std::vector<std::tuple<std::string, float, bool> > transforms_single;
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

std::vector<std::tuple<std::string, float, bool> > InsertionTransform::ApplyTransform(const std::tuple<std::string,
                                                                                                       float,
                                                                                                       bool> &input) {
  std::vector<std::tuple<std::string, float, bool> > all_transforms;
  all_transforms.reserve(26 * std::get<0>(input).size());

  std::string word(std::get<0>(input));

  int strlen = (int) std::get<0>(input).size();

  for (int j = 0; j < strlen; j++) {
    // Without a previous letter.
    for (int k = 0; k < 26; k++) {

      std::string newstr = word;
      // Insert the letter k+'a' at location j.
      newstr.insert(j, 1, k + 'a');
      // Use the 27th entry in the transform matrix as the probability.
      float p = this->transform_matrix_[26][k];
      bool b = this->word_distr->exists(newstr);

      if( b )
        p *= this->word_distr->eval(newstr);

      all_transforms.push_back(std::make_tuple(newstr, p, b) );

    }

    if (j <= 0)
      continue;

    // With a previous letter.
    char previous = word[j - 1];

    for (int k = 0; k < 26; k++) {

      std::string newstr = word;
      // Insert the letter k+'a' at location j.
      newstr.insert(j, 1, k + 'a');
      // Use the appropriate entry in the matrix as the probability.
      float p = this->transform_matrix_[previous - 'a'][k];
      bool b = this->word_distr->exists(newstr);
      if( b )
        p *= this->word_distr->eval(newstr);

      all_transforms.push_back(std::make_tuple(newstr, p, b));

    }

  }

  return all_transforms;

};
#endif //NLPASSIGNMENT_INSERTION_TRANSFORM_H
