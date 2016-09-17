#include <iostream>
#include <algorithm>
#include <queue>
#include "parsers/dictionary_parser.h"
#include "distributions/corpus_distributions.h"
#include "transforms/Transform.h"
#include "transforms/insertion_transform.h"
#include "transforms/deletion_transform.h"
#include "transforms/reversal_transform.h"
#include "transforms/substitute_transform.h"
#include "transforms/SpaceTransform.h"

#define MAX_NUM_RESULTS 4
#define MAX_NUM_ITERATIONS 10

typedef std::tuple<std::string, float, bool> ResultType;

int main(int argc, char **argv) {
  if (argc != 2)
    throw std::runtime_error("Usage:: \n <exec> <corpus>");

  // Load corpus and extract values.
  DictionaryParser dict_parser(argv[1]);

  // Create distributions.
  CorpusWordDistribution word_distr(dict_parser);
  CorpusCharDistribution char_distr(dict_parser);
  CorpusPairCharDistribution pair_char_distr(dict_parser);

  // Important for transforms.
  std::array<std::vector<ResultType>, 4> transform_results;
  std::array<MyTransform *, 4> transforms = {new InsertionTransform(&word_distr, &char_distr),
                                             new DeletionTransform(&word_distr, &pair_char_distr),
                                             new SubstituteTransform(&word_distr, &char_distr),
                                             new ReversalTransform(&word_distr, &pair_char_distr)};

  SpaceTransform *space_transform = new SpaceTransform(&word_distr);

  // Maps.
  std::map<std::string, float> dict_words;
  std::map<std::string, float> out_of_dict_words;

  while (true) {
    // Obtain wrongly spelled word.
    std::string input;
    std::cin >> input;
    std::cout << "\nCandidates : \n";
    if (word_distr.exists(input)) {
      std::cout << input << "100.0";
      continue;
    }

    // Run Space Transform first.
    const auto &space_transformed = space_transform->ApplyTransform(std::make_tuple(input, 1.0f, false));
    if (!space_transformed.empty()) {
      for (int i = 0; i < space_transformed.size(); i++)
        std::cout << i << ". " << std::get<0>(space_transformed[i]) << "\n";

      continue;
    }

    // Input to be sent to all transforms.
    // Can be modified to use some output from SpaceTransform.
    std::string str(input);

    // Init condition.
    out_of_dict_words[str] = 1.0f;

    for (int i = 0; i < MAX_NUM_ITERATIONS; i++) {
      // Find max probability word.
      std::string cur_cand = "";
      float cur_cand_prob = 0.0f;
      for (const auto &cand : out_of_dict_words)
        if (cand.second > cur_cand_prob) {
          cur_cand = cand.first;
          cur_cand_prob = cand.second;
        }

      // Apply 4 transforms.
      for (int i = 0; i < 4; i++) {
        transform_results[i] = transforms[i]->ApplyTransform(std::make_tuple(cur_cand, cur_cand_prob, false));
      }

      // Condense results into the two maps.
      for (const auto &result : transform_results)
        for (const auto &candidate : result) {
          std::string cand_word = std::get<0>(candidate);
          float cand_prob = std::get<1>(candidate);
          // If in dictionary, add to map.
          if (std::get<2>(candidate)) {
            if (dict_words.find(cand_word) == dict_words.end())
              dict_words[cand_word] = cand_prob;
            else
              dict_words[cand_word] += cand_prob;
          } else {
            if (out_of_dict_words.find(cand_word) == dict_words.end())
              out_of_dict_words[cand_word] = cand_prob;
            else
              out_of_dict_words[cand_word] += cand_prob;
          }
        }
    }

    // Insert map into vector.
    std::vector<std::pair<std::string, float>> cand_probs;
    cand_probs.reserve(dict_words.size());
    for (const auto &dict_word : dict_words) {
      cand_probs.push_back(std::make_pair(dict_word.first, dict_word.second));
    }

    // Sort results in decreasing order of scores.
    std::sort(cand_probs.begin(), cand_probs.end(), [](auto &left, auto &right) {
      return right.second < left.second;
    });

    for (int i = 0; i < MAX_NUM_RESULTS && i < cand_probs.size(); i++) {
      std::cout << i << ". " << cand_probs[i].first << "  <-> " << cand_probs[i].second << "\n";
    };
  };
}