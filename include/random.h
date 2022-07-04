#pragma once

#include <random>
#include <limits>

#define intDefaultRangeFrom 0
#define intDefaultRangeLast std::numeric_limits<int>::max()

#define floatDefaultRangeFrom 0.0f
#define floatDefaultRangeLast std::numeric_limits<float>::max()

#define timeDefaultRangeFrom 0.0f
#define timeDefaultRangeLast 100.0f

int RandomInt(const int inFirst, const int inLast);
float RandomFloat(const float inFirst, const float inLast);
int RandomInt();
float RandomFloat();
float RandomTime();


