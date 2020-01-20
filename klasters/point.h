#pragma once
//global
#include <random>
#include <valarray>
#include <istream>

struct point
{
	std::valarray<float> v_arr;

	point();
	point(uint16_t n);
	point(const std::valarray<float>& income);

	bool operator==(const point& right) const;
	bool operator!=(const point& right) const;

	friend std::istream& operator>>(std::istream& is, point& p);
	friend std::ostream& operator<<(std::ostream& is, point& p);
};

