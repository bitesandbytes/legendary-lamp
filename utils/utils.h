//
// Created by sauce on 16/9/16.
//

#ifndef NLPASSIGNMENT_UTILS_H
#define NLPASSIGNMENT_UTILS_H

#include <sstream>
#include <iostream>
#include <string>
#include <array>

namespace mylib {
// Function to split strings with a delimiter.
inline std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  std::stringstream ss;
  ss.str(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}
/*
// Multidimensional array implementation.
template<class T, unsigned ... RestD>
struct array;
template<class T, unsigned PrimaryD>
struct array<T, PrimaryD> {
  typedef T type[PrimaryD];
  type data;

  T &operator[](unsigned i) { return data[i]; }

};

template<class T, unsigned PrimaryD, unsigned ... RestD>
struct array<T, PrimaryD, RestD...> {
  typedef typename array<T, RestD...>::type OneDimensionDownArrayT;
  typedef OneDimensionDownArrayT type[PrimaryD];
  type data;

  OneDimensionDownArrayT &operator[](unsigned i) { return data[i]; }
};*/

} // namespace mylib

#endif //NLPASSIGNMENT_UTILS_H
