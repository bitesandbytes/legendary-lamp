//
// Created by sauce on 16/9/16.
//

#ifndef LEGENDARY_LAMP_NLP_DICTIONARY_PARSER_H
#define LEGENDARY_LAMP_NLP_DICTIONARY_PARSER_H

#include <algorithm>
#include <array>
#include <fstream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include "../utils/utils.h"

#define SMOOTHING_ALPHA 0.5f
#define SMOOTHING_BETA 1.0f

// Using spelling-correction-program.pdf as reference.
class DictionaryParser {
 public:
  DictionaryParser(const std::string &filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    if (!file)
      throw std::runtime_error("");

    std::string line;
    while (std::getline(file, line, '\n')) {
      if (!line.empty())
        lines.push_back(line);
    }

    // Process each line.
    // Format : <WORD> <COUNT>
    long long total_count = 0;

    // Initialize.
    for (auto &val : this->char_p_)
      val = 0;
    for (const auto &word_count : lines) {


      // Obtain word, count
      const auto &splits = mylib::split(word_count, '\t');
      std::string word = splits[0];
      long long count = std::stol(splits[1]);
      total_count += count;

      // Convert word to lower case.
      std::transform(word.begin(), word.end(), word.begin(), ::tolower);

      // Insert into map.
      probs_[word] = count;

      // Obtain stats for char_p_ and char_pq_.
      this->UpdateSingleCharStats(word, count);
      this->UpdateDoubleCharStats(word, count);
    }

    // Smooth word_count with ALPHA = 0.5f.
    // Also normalize word_count.
    for (auto &word_count : this->probs_)
      word_count.second = (word_count.second + SMOOTHING_ALPHA) / total_count;

    // TODO(SaipraveenB) : Fix this. total_count is too high => int(ratio*count) = 0.
    const long double ratio = static_cast<float>(40000000) / static_cast<float>( total_count );
    // Smooth & normalize char occurrences.
    for (auto &char_freq : this->char_p_)
      char_freq = static_cast<int>(static_cast<long double>(char_freq + SMOOTHING_BETA) * ratio);

    // Smooth & normalize pair char occurrences.
    for (auto &pair_char : this->char_pq_)
      pair_char.second = static_cast<int>(static_cast<long double>(pair_char.second + SMOOTHING_BETA) * ratio);

  }
  std::array<float, 26> &GetCharProbs() {
    return this->char_p_;
  }
  std::map<std::string, float> &GetPairCharProbs() {
    return this->char_pq_;
  }
  std::map<std::string, float> &GetWordProbs() {
    return this->probs_;
  }

  std::array<float, 26> char_p_;
  std::map<std::string, float> char_pq_;
  std::map<std::string, float> probs_;

 private:
  void UpdateSingleCharStats(const std::string &word, long long freq) {
    // Increment occurrences of the letter word[i].
    for (const auto &letter : word)
      char_p_[static_cast<int>(letter - 'a')] += static_cast<float>(freq);

    return;
  }

  void UpdateDoubleCharStats(const std::string &word, long long freq) {
    std::string str1 = word.substr(1);

    // Increment occurrences of the pair (word[i],word[i+1]).
    for (int i = 0; i < str1.length(); i++)
      char_pq_[std::string(1, word[i]) + std::string(1, str1[i])] += static_cast<float>(freq);

    return;
  }
};

#endif //LEGENDARY_LAMP_NLP_DICTIONARY_PARSER_H
