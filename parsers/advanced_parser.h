//
// Created by Saipraveen B on 17/09/16.
//

#ifndef NLPASSIGNMENT_ADVANCED_PARSER_H_H
#define NLPASSIGNMENT_ADVANCED_PARSER_H_H

#include <string>
#include <vector>
#include <fstream>
#include "../utils/utils.h"
#include "trie.h"
class DataParser{
 public:
  TrieNode *root;
  DataParser(const std::string &filename) {
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

    root = new TrieNode(false, NULL, 0);
    for (const auto &word_count : lines) {


      // Obtain word, count
      const auto &splits = mylib::split(word_count, '\t');
      std::string word = splits[0];
      long long count = std::stol(splits[1]);
      total_count += count;

    }

    for (const auto &word_count : lines) {
      const auto &splits = mylib::split(word_count, '\t');
      std::string word = splits[0];
      long long count = std::stol(splits[1]);
      // Convert word to lower case.
      std::transform(word.begin(), word.end(), word.begin(), ::tolower);
      root->addWord(word, static_cast<double>(count) / static_cast<double>(total_count));
    }

  }
};

#endif //NLPASSIGNMENT_ADVANCED_PARSER_H_H
