/* Copyright 2020 Igor Lyamin */

#pragma once

/* global */
#include <thread>
#include <mutex>

/* local */
#include "point.h"

int getCountOfThreads();  // available number of threads
double getDistance(const point& X, const point& Y);  // distance between 2 points
