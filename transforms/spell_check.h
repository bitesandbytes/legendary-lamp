//
// Created by Saipraveen B on 17/09/16.
//

#ifndef NLPASSIGNMENT_SPELL_CHECK_H
#define NLPASSIGNMENT_SPELL_CHECK_H

#include <vector>
#include <queue>
#include <string>
#include <map>
#include <cmath>
#include "../parsers/trie.h"
class Traversal{

  // Hold traversal state here.

 public:
  // Node in the Trie that is the focus of this traversal.
  TrieNode* tn;

  // Index in the source string.
  int src_index;

  // Log probability weight.
  double weight;

  // Debug variable.
  std::string desc;

  double getTerminalWeight() const {
    return weight - log2( tn->terminal_probability );
  }
  double getBranchWeight() const {
    return weight - log2( tn->total_probability );
  }

  void setWeight(double weight) {
    Traversal::weight = weight;
  }

};

namespace quickutils{
  void prefill( std::vector<std::vector<double>>& v, int r, int c, double val ){
    for( int i = 0; i < r ;i ++ )
      v.push_back( std::vector<double>((unsigned long) c, val) );
  }
};
class SpellChecker{
  class traversalcomparision
  {

   public:
    bool operator() (Traversal* t1, Traversal* t2) const
    {
      return (t2->getBranchWeight()<t1->getBranchWeight());
    }
  };

  std::priority_queue< Traversal*, std::vector<Traversal*>, traversalcomparision > traversals;
  std::vector<std::vector<double>> substitute_wts;
  std::vector<std::vector<double>> addition_wts;
  std::vector<std::vector<double>> deletion_wts;
  std::vector<std::vector<double>> reverse_wts;
  TrieNode* root;
 public:
  // Default Spell Checker with no weights.
  SpellChecker( TrieNode* root ):root(root){

    double val = - log2(0.000005);
    quickutils::prefill( substitute_wts, 26, 26, val );
    quickutils::prefill( addition_wts, 27, 26, val );
    quickutils::prefill( deletion_wts, 27, 26, val );
    quickutils::prefill( reverse_wts, 26, 26, val );

    for( int i = 0; i < 26 ; i++ ){
      // This case is when a match occurs. No weight for this case.
      substitute_wts[i][i] = 0;
    }


  }
  std::map<std::string, double> correct( std::string source ){

    Traversal *t = new Traversal();
    t->tn = root;
    t->src_index = 0;
    t->weight = 0;
    traversals.push( t );

    std::map<std::string, double> candidates;
    while( candidates.size() < 20 ){

      std::vector<Traversal*> tlist = processTraversal(traversals.top(), source);
      traversals.pop();
      for( auto t : tlist ){

        // If we have a finished traversal.
        if( t->tn->terminal && (t->src_index == source.size()) ) {
          std::cout<<t->tn->word<<" <--> "<<t->weight<<","<<t->getTerminalWeight()<<" "<<t->desc<<std::endl;
          if (!candidates.count(t->tn->word))
            candidates[t->tn->word] = -t->getTerminalWeight();
          else
            candidates[t->tn->word] = log2( pow(2.0f, candidates[t->tn->word] ) + pow(2.0f, -t->getTerminalWeight() ) );
        }

        // Add to active traversals.
        traversals.push(t);

      }

    }
    return candidates;
  }

  std::vector<Traversal*> processTraversal( Traversal* t, std::string source ){
    std::vector<Traversal*> list;
    for( int i = 0 ; i < 26; i++ ){
      Traversal* substitute = new Traversal();
      Traversal* addition = new Traversal();

      addition->src_index = t->src_index;
      addition->tn = t->tn->children[i];
      if( addition->tn ) {
        int previous = ( addition->src_index != 0 ) ? source[addition->src_index-1] - 'a' : WORD_BEGINNING;
        addition->desc = t->desc + ";add " + (char)(i+'a');
        addition->weight = t->weight + addition_wts[previous][i];
        list.push_back(addition);
      }

      substitute->src_index = t->src_index + 1;
      substitute->tn = t->tn->children[i];

      if( substitute->tn && substitute->src_index <= source.size() ) {
        substitute->desc = t->desc + ";sub " + (char)(i+'a') + " with " + source[substitute->src_index-1];
        substitute->weight = t->weight + substitute_wts[i][source[substitute->src_index-1] - 'a'];
        list.push_back(substitute);
      }

    }

    Traversal* deletion = new Traversal();

    deletion->tn = t->tn;
    int previous = ( deletion->src_index != 0 ) ? source[deletion->src_index-1] - 'a' : WORD_BEGINNING;
    deletion->src_index = t->src_index + 1;

    if( deletion->src_index <= source.size() ) {
      deletion->weight = t->weight + deletion_wts[previous][source[deletion->src_index] - 'a'];
      deletion->desc = t->desc + ";del " + source[deletion->src_index];
      list.push_back(deletion);
    }

    Traversal* reverse = new Traversal();

    try {

      if( t->src_index >= source.size()-1 )
        throw 0;

      if( !t->tn->children[source[t->src_index+1] - 'a'] )
        throw 0;

      reverse->tn = t->tn->children[source[t->src_index+1] - 'a']->children[source[t->src_index] - 'a'];
      reverse->src_index = t->src_index + 2;

      if (reverse->tn && reverse->src_index <= source.size() && source[reverse->src_index-1] != source[reverse->src_index-2] ) {
        reverse->desc = t->desc + ";rev " + source[reverse->src_index-1] + source[reverse->src_index-2];
        reverse->weight = t->weight + reverse_wts[source[reverse->src_index-1]-'a'][source[reverse->src_index-2]-'a'];
        list.push_back(reverse);
      }

    } catch ( int e ) {
      // Skip reversal.
    }

    return list;
  }

  const char WORD_BEGINNING = 26;
};
#endif //NLPASSIGNMENT_SPELL_CHECK_H
