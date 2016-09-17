//
// Created by Saipraveen B on 16/09/16.
//

#ifndef NLPASSIGNMENT_SPACETRANSFORM_H
#define NLPASSIGNMENT_SPACETRANSFORM_H

#include <string>
#include <vector>
#include "Transform.h"
class SpaceTransform : public Transform{

 public:

  virtual std::vector< std::tuple<std::string, float, bool> > applyAll( std::string str ) const;
};

#endif //NLPASSIGNMENT_SPACETRANSFORM_H
