//
// Created by sauce on 16/9/16.
//

#ifndef LEGENDARY_LAMP_NLP_DICTIONARY_PARSER_H
#define LEGENDARY_LAMP_NLP_DICTIONARY_PARSER_H

#include <string>
#include <array>

#define SMOOTHING_ALPHA 0.5f

namespace {
void UpdateSingleCharStats(decltype(DictionaryParser::char_p_) &char_map, const std::string &word, int freq) {
  // Increment occurrences of the letter word[i].
  for (const auto &letter : word)
    char_map[static_cast<int>(letter - 'a')] += freq;

  return;
}

void UpdateDoubleCharStats(decltype(DictionaryParser::char_pq_) &twin_char_map, const std::string &word, int freq) {
  std::string str1 = word.substr(1);

  // Increment occurrences of the pair (word[i],word[i+1]).
  for (int i = 0; i < str1.length(); i++)
    twin_char_map[static_cast<int>(word[i] - 'a')][static_cast<int>(str1[i])] += freq;

  return;
}

} // namespace

// Using spelling-correction-program.pdf as reference.
class DictionaryParser {
 public:
  DictionaryParser(const std::string &filename);
  decltype(char_p_) GetCharProbs() {
    return this->char_p_;
  }
  decltype(char_pq_) GetPairCharProbs() {
    return this->char_pq_;
  }
  decltype(probs_) GetWordProbs() {
    return this->probs_;
  }

 private:
  std::array<int, 26> char_p_;
  std::array<std::array<int, 26>, 26> char_pq_;
  std::map<std::string, float> probs_;
};

DictionaryParser::DictionaryParser(const std::string &filename) {
  std::vector<std::string> lines;
  std::ifstream file(filename);

  std::string line;
  while (std::getline(file, line)) {
    if (!line.empty())
      lines.push_back(line);
  }

  // Process each line.
  // Format : <WORD> <COUNT>
  long total_count = 0;
  for (const auto &word_count : lines) {
    // Obtain word, count
    auto &splits = split(word_count, ' ');
    std::string word = splits[0];
    long count = std::stol(splits[1]);
    total_count += count;

    // Convert word to lower case.
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);

    // Insert into map.
    probs_[word] = count;

    // Obtain stats for char_p_ and char_pq_.
    UpdateSingleCharStats(this->char_p_, word, count);
    UpdateDoubleCharStats(this->char_pq_, word, count);
  }

  // Smooth word_count with ALPHA = 0.5f.
  // Also normalize word_count.
  for (auto &word_count : this->probs_)
    word_count.second = (word_count.second + SMOOTHING_ALPHA) / total_count;

  const float ratio = static_cast<float>(40000000) / total_count;
  // Smooth & normalize char occurrences.
  for (auto &char_freq : this->char_p_)
    char_freq = static_cast<int>(static_cast<float>(char_freq + SMOOTHING_ALPHA) * ratio);

  // Smooth & normalize pair char occurrences.
  for (auto &pair_char_freq_row : this->char_pq_)
    for (auto &pair_char_freq : pair_char_freq_row)
      pair_char_freq = static_cast<int>(static_cast<float>(pair_char_freq + SMOOTHING_ALPHA) * ratio);
}

#endif //LEGENDARY_LAMP_NLP_DICTIONARY_PARSER_H
