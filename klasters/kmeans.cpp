//global
#include <iostream>
#include <list>
#include <vector> 
#include <thread>
#include <chrono>
#include <mutex>
#include <windows.h>
#include <sstream>
#include <locale>
#include <set>

//file
#include <stdio.h>
#include <fstream>

//local
#include "point.h"
#include "cluster.h"
#include "functions.h"

int main()
{
	auto begin = std::chrono::steady_clock::now(); //timer
	int numCPU = getCountOfThreads(); //current number of threads

	/////////////////input reading//////////////////////////
	std::ifstream ifs;
	ifs.open("input.txt", std::ifstream::in);
	std::string first_row;
	std::getline(ifs, first_row);
	std::istringstream ist(first_row);

	size_t dimension = 0;
	float val;
	while (ist >> val) {
		++dimension;
	}
	point first(dimension);
	const uint16_t n = dimension; // < 1000
	

	std::istringstream iss(first_row);
	iss >> first;

	std::vector<point> points;
	points.push_back(first);
	point p(n);
	while (!ifs.eof()) {
		ifs >> p;
		points.push_back(p);
	}
	const uint32_t pointsCounter = points.size(); // < 1 000 000
	ifs.close();

	const uint16_t K = 3; //number of centers  (K < 1000)

	//select the centers randomly from the vector of points//
	size_t a = 0;
	std::vector<point> cluster_centers;
	for (size_t i = 0; i < K; ++i) {
		if (std::find(cluster_centers.begin(), cluster_centers.end(), points[i + a]) != cluster_centers.end()) {
			--i;
			++a;
		} else {
			cluster_centers.push_back(points[i + a]);
		}
	}

	/////////////////making K clusters//////////////////////
	std::vector<std::shared_ptr<cluster>> clusters;
	clusters.reserve(K);
	for (size_t i = 0; i < cluster_centers.size(); ++i) {
		clusters.push_back(std::make_shared<cluster>(n));
	}

	////////////////////reculculation///////////////////////
	int iterCounter = 0;
	while (true) {
		std::vector<std::thread> pkThreads;
		pkThreads.reserve(numCPU);

		for (size_t i = 0; i < numCPU; ++i) {
			pkThreads.emplace_back([i, numCPU, &cluster_centers, &clusters, &points] {
				for (size_t j = i; j < points.size(); j += numCPU) {
					double minDistance = getDistance(points[j], cluster_centers[0]);
					size_t clusterIndex = 0;
					for (size_t k = 1; k < cluster_centers.size(); ++k) {
						double d = getDistance(points[j], cluster_centers[k]);
						if (d < minDistance) {
							minDistance = d;
							clusterIndex = k;
						}
					}
					clusters[clusterIndex]->add(points[j]);
				}
			});
		}
		for (auto& t : pkThreads) t.join();

		bool stop = true; //did we find the solution?
		float epsilon = 0.001;
		for (size_t i = 0; i < clusters.size(); ++i) {
			point p = clusters[i]->getCenter();
			clusters[i]->reset();
			stop &= getDistance(p, cluster_centers[i]) < epsilon; //is center changed? (== analog)
			cluster_centers[i] = p;
		}

		++iterCounter;

		if (stop) {
			break;
		}
	}

	///////////////////output writing///////////////////////
	{
		std::ofstream ofs;
		ofs.open("output.txt");
		std::sort(cluster_centers.begin(), cluster_centers.end());
		for (size_t i = 0; i < cluster_centers.size(); ++i) {
			ofs << cluster_centers[i];
		}
	}

	///////////////////time checking////////////////////////
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

	std::cout << "The time: " << elapsed_ms.count() << " ms\n";
	std::cout << iterCounter << std::endl;
}