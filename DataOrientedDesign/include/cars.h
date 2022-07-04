#pragma once

#include <DOD_car.h>


#define likely(x) __builtin_expect ((x), 1)
#define unlikely(x) __builtin_expect ((x), 0)

void DoSimilateForDOD(int ioNumOfCars, int ioNumOfFrame);

void DoSimilateForOOD(int ioNumOfCars, int ioNumOfFrame);