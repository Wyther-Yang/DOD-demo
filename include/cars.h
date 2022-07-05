#pragma once

#include "DOD_car.h"

#include "OOD_car.h"


#define likely(x) __builtin_expect ((x), 1)
#define unlikely(x) __builtin_expect ((x), 0)


void DoSimilateForDOD(int args, char** argv);

void DoSimilateForOOD(int args, char** argv);