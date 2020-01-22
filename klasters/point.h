/* Copyright 2020 Igor Lyamin */

#pragma once

/* global */
#include <random>
#include <valarray>
#include <istream>

struct point {
  std::valarray<float> v_arr;

  point();
  explicit point(uint16_t n);
  explicit point(const std::valarray<float>& income);

  bool operator==(const point& right) const;
  bool operator!=(const point& right) const;
  bool operator<(const point& right) const;

  friend std::istream& operator>>(std::istream& is, point& p);
  friend std::ostream& operator<<(std::ostream& is, const point& p);
};
