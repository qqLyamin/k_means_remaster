#pragma once
//global
#include <mutex>

//local
#include "point.h"

class Cluster
{
	std::mutex mutex_;
	point sum_;
	size_t n_;

public:

	Cluster();
	Cluster(const point & point);
	Cluster(const int dimension);
	~Cluster() {};

	void reset();
	void add(const point& p);
	point getCenter() const;
};