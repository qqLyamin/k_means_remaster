#include "Cluster.h"

Cluster::Cluster()
{
	n_ = 0;
	sum_ = point();
}

Cluster::Cluster(const point& point)
{
	n_ = 1;
	sum_ = point;
}

Cluster::Cluster(const int dimension) : n_(0)
{
	std::valarray<float> tmp;
	tmp.resize(dimension, 0);
	sum_.v_arr = tmp;
}

void Cluster::reset()
{
	sum_.v_arr.resize(sum_.v_arr.size(), 0);
	n_ = 0;
}

void Cluster::add(const point& p)
{
	std::lock_guard<std::mutex> lock(mutex_);
	sum_.v_arr += p.v_arr;
	++n_;
}

point Cluster::getCenter() const
{	
	point center = sum_;
	if (n_ != 0 && n_ != 1) {
		center.v_arr /= n_;
	} 

	return center;
}



