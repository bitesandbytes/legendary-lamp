//
// Created by Saipraveen B on 16/09/16.
//

#include <set>
#include <unordered_set>
#include <algorithm>
#include <iterator>
#include <sstream>
#include "SpaceTransform.h"
std::vector<std::vector<std::vector<std::vector<std::string>>>> table;

namespace {
std::vector<std::vector<std::string>> get_strings(std::string str,
                                                  int start,
                                                  int end,
                                                  Distribution<std::string> *words) {
  if (start > end)
    throw std::runtime_error("start > end for " + str);
  if (start == end) {
    if (words->exists(str.substr(start, 1)))
      return std::vector<std::vector<std::string>>();
    else
      return std::vector<std::vector<std::string>>(1, std::vector<std::string>(1, str.substr(start, 1)));
  }
  std::vector<std::vector<std::string>> collection;
  decltype(collection) temp1;
  decltype(collection) temp2;
  if (!table[start][end].empty())
    return table[start][end];
  for (int index = start; index < end; index++) {
    temp1 = get_strings(str, start, index, words);
    temp2 = get_strings(str, index + 1, end, words);
    if (temp1.empty() || temp2.empty())
      continue;
    for (const auto &iter1 : temp1) {
      for (const auto &iter2 : temp2) {
        auto tmp = iter1;
        tmp.insert(tmp.end(), iter2.begin(), iter2.end());
        collection.push_back(tmp);
      }
    }
  }
  if (words->exists(str.substr(start, end - start + 1))) {
    std::vector<std::string> abc;
    //std::cout << abc.size() << std::endl;
    abc.push_back(str.substr(start, end - start + 1));
    collection.push_back(abc);
  }
  table[start][end] = collection;
  return collection;
}
} // namespace

float SpaceTransform::get_probability(std::string s) const {
  float prob = 1;
  const auto &splits = mylib::split(s, ' ');
  int spaces = static_cast<int>(splits.size()) - 1;
  for (auto iter : splits) {
    prob *= this->words->eval(iter);
  }
  return prob * std::pow(this->probability, spaces);
}

std::vector<std::tuple<std::string, float, bool> > SpaceTransform::ApplyTransform(const std::tuple<std::string,
                                                                                                   float,
                                                                                                   bool> &input) {
  // Use this->words->eval(word) to get probabilities for the words.
  // Use this->words->exists( word ) to check if the word is in the dictionary.
  // Use this->probability to get the probability of space.

  std::vector<std::tuple<std::string, float, bool>> collection;
  std::string str(std::get<0>(input));

  auto col = get_strings(str, 0, str.length() - 1, this->words);
  std::unordered_set<std::string> uniques;
  std::stringstream ss;
  for (const auto &iter1 : col) {
    std::copy(iter1.begin(), iter1.end(), std::ostream_iterator<std::string>(ss, " "));
    uniques.insert(ss.str());
    ss.clear();
    ss.str("");
  }

  for (std::string iter : uniques)
    collection.push_back(std::make_tuple(iter, get_probability(iter), true));

  // Return a set of candidates along with their probabilities. The boolean should be True for a valid condidate and False for an invalid( but potentially valid ) candidate.
  return std::vector<std::tuple<std::string, float, bool>>();

}


