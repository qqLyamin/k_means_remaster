/* Copyright 2020 Igor Lyamin */

#pragma once

/* global */
#include <random>
#include <valarray>
#include <istream>

struct point {
  std::valarray<double> v_arr;

  point();
  explicit point(uint16_t n);
  explicit point(const std::valarray<double>& income);

  bool operator==(const point& right) const;
  bool operator!=(const point& right) const;
  bool operator<(const point& right) const;

  friend std::istream& operator>>(std::istream& is, point& p);
  friend std::ostream& operator<<(std::ostream& is, const point& p);
};
