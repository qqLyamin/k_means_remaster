//global
#include <iostream>
#include <cstdint>
#include <list>
#include <vector> 
#include <thread>
#include <chrono>
#include <mutex>
#include <functional>
#include <windows.h>
#include <sstream>
#include <locale>

//file
#include <stdio.h>
#include <fstream>

//local
#include "point.h"
#include "Cluster.h"
#include "functions.h"

int main()
{
	auto begin = std::chrono::steady_clock::now();
	int numCPU = getCountOfThreads();

	std::ifstream ifs;
	ifs.open("input.txt", std::ifstream::in);

	std::string first_row;
	std::getline(ifs, first_row);
	std::istringstream ist(first_row);

	size_t dim = 0;
	float val;
	while (ist >> val) {
		++dim;
	}
	point first(dim);
	const uint16_t n = dim; //dimension			(n < 1000)

	std::istringstream iss(first_row);
	iss >> first;

	std::vector<point> points;
	points.push_back(first);
	point p(n);
	while (!ifs.eof()) {
		ifs >> p;
		points.push_back(p);
	}
	const uint32_t pointsCounter = points.size(); //		(pointsCounter <= 1 000 000)
	const uint16_t K = 3; //number of centers  (K < 1000)

	std::vector<uint32_t> partOfPoints(numCPU);
	for (auto& x : partOfPoints) {
		x = pointsCounter / numCPU;
	}
	partOfPoints[0] += pointsCounter % numCPU;

	std::mt19937_64 random_generator;
	uint32_t seed = std::random_device{}();
	random_generator.seed(seed);

	std::vector<point> cluster_centers;
	for (size_t i = 0; i < K; ++i) {
		size_t p = random_generator() % n;
		cluster_centers.emplace_back(points[p]);
		points.erase(points.begin() + p - 1, points.begin() + p);
	}

	std::vector<std::shared_ptr<Cluster>> clusters;
	clusters.reserve(K);
	for (size_t i = 0; i < cluster_centers.size(); ++i) {
		clusters.push_back(std::make_shared<Cluster>(n));
	}
	ifs.close();

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

	{
		std::ofstream ofs;
		ofs.open("output.txt");
		ofs << "\n...............\n";
		for (size_t i = 0; i < cluster_centers.size(); ++i) {
			ofs << cluster_centers[i];
		}
	}

	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

	std::cout << "The time: " << elapsed_ms.count() << " ms\n";
	std::cout << iterCounter << std::endl;

	int asdasd = 9302; //anchor =)
}