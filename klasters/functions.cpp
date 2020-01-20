#include "functions.h"

int getCountOfThreads()
{
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	int numCPU = sysinfo.dwNumberOfProcessors;
	numCPU = std::thread::hardware_concurrency() == 0 ? numCPU : std::thread::hardware_concurrency();
	return numCPU - 1;
}

int getDistance(const point& X, const point& Y)
{
	double distance = 0;
	for (size_t tmp = 0; tmp < X.v_arr.size(); ++tmp) {
		distance += pow(abs(static_cast<double>((X.v_arr[tmp] - Y.v_arr[tmp]))), 2);
	}
	return distance; //probably i can return without sqrt 
}

point generatePoint(const uint16_t n, std::mt19937_64 & random_generator)
{
	point tmp;
	tmp.v_arr.resize(n);
	for (size_t index = 0; index < n; ++index) {
		int rand = random_generator();
		tmp.v_arr[index] = *reinterpret_cast<float*>( &rand );
	}
	return tmp;
}

