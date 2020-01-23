/* Copyright 2020 Igor Lyamin */

#pragma once

/* global */
#include <thread>
#include <mutex>

/* local */
#include "point.h"

int getCountOfThreads();  // available number of threads
int getDistance(const point& X, const point& Y);  // distance between 2 points
