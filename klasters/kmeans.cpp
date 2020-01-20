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
	const uint16_t K = 2; //number of centers  (K < 1000)
	
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
		cluster_centers.emplace_back(generatePoint(n, random_generator));
	}

	std::vector<std::shared_ptr<Cluster>> clusters;
	clusters.reserve(K);
	for (size_t i = 0; i < cluster_centers.size(); ++i) {
		clusters.push_back(std::make_shared<Cluster>(cluster_centers[i]));
	}

	int iterCounter = 0;
	while (true) {
		std::mutex mt;
		std::vector<std::thread> pkThreads;
		pkThreads.reserve(numCPU);

		for (size_t i = 0; i < numCPU; ++i) {
			pkThreads.emplace_back([i, numCPU, &clusters, &points] {
				double minDistance = 0;
				int minIndex = 0;

				int q = 0;
				int theMostNearCluster = 0;

				for (size_t j = i; i < points.size(); j += numCPU) {
					for (auto& cl : clusters) {
						++q;
						if ((minDistance == 0 && (j % numCPU == 0 || j == 0)) || (minDistance > getDistance(points[j], cl->getCenter()))) {
							minDistance = getDistance(points[j], cl->getCenter());
							minIndex = j;
							theMostNearCluster = q;
						}
					}
				}
				clusters[theMostNearCluster]->add(points[minIndex]);

				minIndex = 0;
				minDistance = 0;
				});
		}
		for (auto& t : pkThreads) t.join();

		bool stop = true; //did we find the solution?
		for (size_t i = 0; i < clusters.size(); ++i) {
			point p = clusters[i]->getCenter();
			clusters[i].reset();
			stop &= (p == cluster_centers[i]); //is center changed?
			cluster_centers[i] = p;
		}

		++iterCounter;

		if (stop) {
			break;
		}
	}

	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

	std::cout << "The time: " << elapsed_ms.count() << " ms\n";
	std::cout << iterCounter << std::endl;

	int asdasd = 9302; //anchor =)
}