//
// Created by sauce on 16/9/16.
//

#ifndef LEGENDARY_LAMP_NLP_DICTIONARY_PARSER_H
#define LEGENDARY_LAMP_NLP_DICTIONARY_PARSER_H

#include <string>

namespace {
void UpdateSingleCharStats(decltype(DictionaryParser::char_p_) &char_map, const std::string &word) {
  for (const auto &letter : word)
    char_map[static_cast<int>(letter - 'a')]++;

  return;
}

void UpdateDoubleCharStats(decltype(DictionaryParser::char_pq_) &twin_char_map, const std::string &word) {
  std::string str1 = word.substr(1);
  for (int i = 0; i < str1.length(); i++)
    twin_char_map[static_cast<int>(word[i] - 'a')][static_cast<int>(str1[i])]++;

  return;
}

} // namespace

// Using spelling-correction-program.pdf as reference.
class DictionaryParser {
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
  std::array<26, int> char_p_;
  std::array<26, std::array<26, int>> char_pq_;
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
    UpdateSingleCharStats(this->char_p_, word);
    UpdateDoubleCharStats(this->char_pq_, word);
  }

  for (auto &word_count : this->probs_)
    word_count.second /= total_count;
}

#endif //LEGENDARY_LAMP_NLP_DICTIONARY_PARSER_H
