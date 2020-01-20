#pragma once

//global
#include <windows.h>
#include <thread>
#include <mutex>

//local
#include "point.h"

int getCountOfThreads(); //returns the available number of threads
int getDistance(const point& X, const point& Y); //returns the distance between 2 points
point generatePoint(const uint16_t n, std::mt19937_64 & random_generator);