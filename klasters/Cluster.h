#pragma once
//global
#include <mutex>

//local
#include "point.h"

class cluster
{
	std::mutex mutex_;
	point sum_;
	size_t n_;

public:

	cluster();
	cluster(const point & point);
	cluster(const int dimension);
	~cluster() {};

	void reset();
	void add(const point& p);
	point getCenter() const;
};