//
// Created by Saipraveen B on 16/09/16.
//

#include "SpellCorrector.h"
Distribution<std::string> *SpellCorrector::getWords() const {
  return words;
}

void SpellCorrector::setWords(Distribution<std::string> *words) {
  SpellCorrector::words = words;
}

Distribution<std::pair<char, char>> *SpellCorrector::getReverse() const {
  return reverse;
}

void SpellCorrector::setReverse(Distribution<std::pair<char, char>> *reverse) {
  SpellCorrector::reverse = reverse;
}

Distribution<std::pair<char, char>> *SpellCorrector::getAddition() const {
  return addition;
}

void SpellCorrector::setAddition(Distribution<std::pair<char, char>> *addition) {
  SpellCorrector::addition = addition;
}

Distribution<std::pair<char, char>> *SpellCorrector::getDeletion() const {
  return deletion;
}

void SpellCorrector::setDeletion(Distribution<std::pair<char, char>> *deletion) {
  SpellCorrector::deletion = deletion;
}

Distribution<std::pair<char, char>> *SpellCorrector::getReplace() const {
  return replace;
}

void SpellCorrector::setReplace(Distribution<std::pair<char, char>> *replace) {
  SpellCorrector::replace = replace;
}

Distribution<char> *SpellCorrector::getSpace() const {
  return space;
}

void SpellCorrector::setSpace(Distribution<char> *space) {
  SpellCorrector::space = space;
}

SpellCorrector::SpellCorrector() {
  // Do initialization and stuff here.
}

void SpellCorrector::populate() {
  // Populate the transformation matrices here.

  for( char c1 = 'a'; c1 <= 'z'; c1++ ){
    for( char c2 = 'a'; c2 <= 'z'; c2++ ){
      Transform *t = new Transform();
      t->setProbability( reverse->eval(std::make_pair(c1,c2)) );
      t->addMapping( ("" + c1) + c2, ( "" + c2 ) + c1 );
      this->transforms.push(t);
    }
  }

  // TODO: Repeat this logic for the other three types of transforms as well.

  // Add the space transform here.
  Transform *spaceT = new SpaceTransform();
  spaceT->setProbability(space->eval(' '));

}
