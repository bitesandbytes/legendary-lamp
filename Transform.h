//
// Created by Saipraveen B on 16/09/16.
//

#ifndef NLPASSIGNMENT_TRANSFORM_H
#define NLPASSIGNMENT_TRANSFORM_H

#include <string>
#include <map>
#include <vector>
class Transform {

 private:
  float probability;
  std::map<std::string, std::string> map;

 public:
  float getProbability() const;
  void setProbability(float probability);

  void addMapping( std::string src, std::string dest ){

    if( map.count( src ) )
      throw "This source has already been mapped";

    map[src] = map[dest];

  }

  std::vector< std::pair<std::string, float probability> > applyAll( std::string str ) const;
  std::vector< std::pair<std::string, float probability> > applyOne( std::string str, unsigned int occurence = 0 ) const;

};

#endif //NLPASSIGNMENT_TRANSFORM_H
