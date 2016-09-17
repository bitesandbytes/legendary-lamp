//
// Created by sauce on 17/9/16.
//

#ifndef NLPASSIGNMENT_INSERTION_TRANSFORM_H
#define NLPASSIGNMENT_INSERTION_TRANSFORM_H
#include "Transform.h"

class DeletionTransform : public MyTransform<27> {
 public:
  DeletionTransform(CorpusWordDistribution *word_distr, CorpusCharDistribution *char_distr);
  std::vector<std::tuple<std::string, float, bool> > ApplyTransform(const std::tuple<std::string, float, bool> &input);

 public:
  std::vector<std::tuple<std::string, float, bool> > ApplyTransformSingle(const std::tuple<std::string,
                                                                                           float,
                                                                                           bool> &input, int pos);
  const CorpusWordDistribution *word_distr;
};

DeletionTransform::DeletionTransform(CorpusWordDistribution *word_distr, CorpusCharDistribution *char_distr) {
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

std::vector<std::tuple<std::string, float, bool> > DeletionTransform::ApplyTransformSingle(const std::tuple<std::string,
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

std::vector<std::tuple<std::string, float, bool> > DeletionTransform::ApplyTransform(const std::tuple<std::string, float, bool> &input) {
  std::vector<std::tuple<std::string, float, bool> > all_transforms;
  all_transforms.reserve(26 * std::get<0>(input).size());
  std::string word = std::get<0>(input);
  int strlen = (int) std::get<0>(input).size();


  for ( int j = 0; j < strlen; j++ ) {

    // Without a previous.
    for( int k = 0; k < 26; k++ ){

      std::string newstr = word;
      // Erase the j'th letter.
      newstr.erase(j,1);
      float p = this->transform_matrix_[26][k];
      all_transforms.push_back(std::make_tuple(newstr,p,this->word_distr->exists(newstr)));

    }

    if( j <= 0 )
      continue;

    // With a previous letter.
    char previous = word[j-1];
    for( int k = 0; k < 26; k++ ){

      std::string newstr = word;

      // Erase the jth letter.
      newstr.erase(j,1);
      float p = this->transform_matrix_[previous - 'a'][k];
      all_transforms.push_back(std::make_tuple(newstr,p,this->word_distr->exists(newstr)));

    }

  }


};
#endif //NLPASSIGNMENT_INSERTION_TRANSFORM_H
