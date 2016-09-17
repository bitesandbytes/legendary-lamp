//
// Created by sauce on 17/9/16.
//

#ifndef NLPASSIGNMENT_DELETION_TRANSFORM_H
#define NLPASSIGNMENT_DELETION_TRANSFORM_H
#include "Transform.h"

class DeletionTransform : public MyTransform {
 public:
  DeletionTransform(CorpusWordDistribution *word_distr, CorpusPairCharDistribution *pair_char_distr, CorpusCharDistribution *char_distr);
  std::vector<std::tuple<std::string, float, bool> > ApplyTransform(const std::tuple<std::string, float, bool> &input);

 public:
  std::vector<std::tuple<std::string, float, bool> > ApplyTransformSingle(const std::tuple<std::string,
                                                                                           float,
                                                                                           bool> &input, int pos);
  CorpusWordDistribution *word_distr;
};

DeletionTransform::DeletionTransform(CorpusWordDistribution *word_distr, CorpusPairCharDistribution *char_pair, CorpusCharDistribution *char_distr) {
  this->word_distr = word_distr;

  this->transform_matrix_ =
      decltype(this->transform_matrix_){
          {0, 7, 58, 21, 3, 5, 18, 8, 61, 0, 4, 43, 5, 53, 0, 9, 0, 98, 28, 53, 62, 1, 0, 0, 2, 0},
          {2, 2, 1, 0, 22, 0, 0, 0, 183, 0, 0, 26, 0, 0, 2, 0, 0, 6, 17, 0, 6, 1, 0, 0, 0, 0},
          {37, 0, 70, 0, 63, 0, 0, 24, 320, 0, 9, 17, 0, 0, 33, 0, 0, 46, 6, 54, 17, 0, 0, 0, 1, 0},
          {12, 0, 7, 25, 45, 0, 10, 0, 62, 1, 1, 8, 4, 3, 3, 0, 0, 11, 1, 0, 3, 2, 0, 0, 6, 0},
          {80, 1, 50, 74, 89, 3, 1, 1, 6, 0, 0, 32, 9, 76, 19, 9, 1, 237, 223, 34, 8, 2, 1, 7, 1, 0},
          {4, 0, 0, 0, 13, 46, 0, 0, 79, 0, 0, 12, 0, 0, 4, 0, 0, 11, 0, 8, 1, 0, 0, 0, 1, 0},
          {25, 0, 0, 2, 83, 1, 37, 25, 39, 0, 0, 3, 0, 29, 4, 0, 0, 52, 7, 1, 22, 0, 0, 0, 1, 0},
          {15, 12, 1, 3, 20, 0, 0, 25, 24, 0, 0, 7, 1, 9, 22, 0, 0, 15, 1, 26, 0, 0, 1, 0, 1, 0},
          {26, 1, 60, 26, 23, 1, 9, 0, 1, 0, 0, 38, 14, 82, 41, 7, 0, 16, 71, 64, 1, 1, 0, 0, 1, 7},
          {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
          {4, 0, 0, 1, 15, 1, 8, 1, 5, 0, 1, 3, 0, 17, 0, 0, 0, 1, 5, 0, 0, 0, 1, 0, 0, 0},
          {24, 0, 1, 6, 48, 0, 0, 0, 217, 0, 0, 211, 2, 0, 29, 0, 0, 2, 12, 7, 3, 2, 0, 0, 11, 0},
          {15, 10, 0, 0, 33, 0, 0, 1, 42, 0, 0, 0, 180, 7, 7, 31, 0, 0, 9, 0, 4, 0, 0, 0, 0, 0},
          {21, 0, 42, 71, 68, 1, 160, 0, 191, 0, 0, 0, 17, 144, 21, 0, 0, 0, 127, 87, 43, 1, 1, 0, 2, 0},
          {11, 4, 3, 6, 8, 0, 5, 0, 4, 1, 0, 13, 9, 70, 26, 20, 0, 98, 20, 13, 47, 2, 5, 0, 1, 0},
          {25, 0, 0, 0, 22, 0, 0, 12, 15, 0, 0, 28, 1, 0, 30, 93, 0, 58, 1, 18, 2, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 0, 0, 0, 0, 0},
          {63, 4, 12, 19, 188, 0, 11, 5, 132, 0, 3, 33, 7, 157, 21, 2, 0, 277, 103, 68, 0, 10, 1, 0, 27, 0},
          {16, 0, 27, 0, 74, 1, 0, 18, 231, 0, 0, 2, 1, 0, 30, 30, 0, 4, 265, 124, 21, 0, 0, 0, 1, 0},
          {24, 1, 2, 0, 76, 1, 7, 49, 427, 0, 0, 31, 3, 3, 11, 1, 0, 203, 5, 137, 14, 0, 4, 0, 2, 0},
          {26, 6, 9, 10, 15, 0, 1, 0, 28, 0, 0, 39, 2, 111, 1, 0, 0, 129, 31, 66, 0, 0, 0, 0, 1, 0},
          {9, 0, 0, 0, 58, 0, 0, 0, 31, 0, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
          {40, 0, 0, 1, 11, 1, 0, 11, 15, 0, 0, 1, 0, 2, 2, 0, 0, 2, 24, 0, 0, 0, 0, 0, 0, 0},
          {1, 0, 17, 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 5, 0, 0, 0, 0, 1, 0},
          {2, 1, 34, 0, 2, 0, 1, 0, 1, 0, 0, 1, 2, 1, 1, 1, 0, 0, 17, 1, 0, 0, 1, 0, 0, 0},
          {1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
          {20, 14, 41, 31, 20, 20, 7, 6, 20, 3, 6, 22, 16, 5, 5, 17, 0, 28, 26, 6, 2, 1, 24, 0, 0, 2}};

  // 2-char string.
  std::string str("..");
  for (int i = 0; i < 27; i++)
    for (int ch = 0; ch < 26; ch++) {
      str[0] = static_cast<char>(i + 'a');
      str[1] = static_cast<char>(ch + 'a');
      if( i != 26 )
        this->transform_matrix_[i][ch] /= char_pair->eval(str);
      else
        this->transform_matrix_[i][ch] /= char_distr->eval(str[1]);
    }
}

std::vector<std::tuple<std::string, float, bool> > DeletionTransform::ApplyTransformSingle(const std::tuple<std::string,
                                                                                                            float,
                                                                                                            bool> &input,
                                                                                           int pos) {
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

std::vector<std::tuple<std::string, float, bool> > DeletionTransform::ApplyTransform(const std::tuple<std::string,
                                                                                                      float,
                                                                                                      bool> &input) {
  std::vector<std::tuple<std::string, float, bool> > all_transforms;
  all_transforms.reserve(26 * std::get<0>(input).size());
  std::string word = std::get<0>(input);
  int strlen = (int) std::get<0>(input).size();

  for (int j = 0; j < strlen; j++) {

    // Without a previous.
    for (int k = 0; k < 26; k++) {

      std::string newstr = word;
      // Erase the j'th letter.
      newstr.erase(j, 1);
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

      // Erase the jth letter.
      newstr.erase(j, 1);
      float p = this->transform_matrix_[previous - 'a'][k];
      bool b = this->word_distr->exists(newstr);

      if( b )
        p *= this->word_distr->eval(newstr);


      all_transforms.push_back(std::make_tuple(newstr, p, b));

    }
  }
  return all_transforms;
}
#endif //NLPASSIGNMENT_DELETION_TRANSFORM_H
