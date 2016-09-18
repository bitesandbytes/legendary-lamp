//
// Created by Saipraveen B on 17/09/16.
//

#ifndef NLPASSIGNMENT_TRIE_H
#define NLPASSIGNMENT_TRIE_H

#include <array>
#include <string>
/*
 * A base class for the letter based trie.
 */
class TrieNode{
 public:
  std::array<TrieNode*, 26> children;
  TrieNode* parent;
  double total_probability;
  double terminal_probability;
  bool terminal; // If there's a word that ends in this node.
  int branch_index; // The index to use to get to this node from it's parent.
  std::string word; // The word at this TN.
  TrieNode(bool terminal, TrieNode* parent, char c ):parent(parent),terminal(terminal){
    branch_index = c - 'a';
    word = (parent != NULL) ? (parent->word + c) : "";
    total_probability = 0;
    terminal_probability = 0;

    for( int i = 0; i < children.size(); i++ ){
      children[i] = NULL;
    }
  }

  void addWord(std::string str, double d) {

    if( str.size() == 0 ){
      this->terminal = true;
      this->terminal_probability = d;
      return;
    }

    if( !children[str[0] - 'a'] )
      children[str[0] - 'a'] = new TrieNode( false, this, str[0] );

    this->total_probability += d;
    children[str[0] - 'a']->addWord(str.substr(1), d);

  }
};

#endif //NLPASSIGNMENT_TRIE_H
