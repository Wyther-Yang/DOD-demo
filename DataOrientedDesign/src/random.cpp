#include "random.h"

static std::random_device gRandomDevice;
static std::mt19937 mt(gRandomDevice());

int RandomInt(const int inFirst, const int inLast)
{
        std::uniform_int_distribution<int> distribution(inFirst, inLast);
        return distribution(mt);
}

float RandomFloat(const float inFirst, const float inLast)
{
        std::uniform_real_distribution<float> distribution(inFirst, inLast);
        return distribution(mt);
}


int RandomInt()
{
        return RandomInt(intDefaultRangeFrom, intDefaultRangeLast);
}

float RandomFloat()
{
        return RandomFloat(floatDefaultRangeFrom, floatDefaultRangeLast);
}

float RandomTime()
{
        return RandomFloat(timeDefaultRangeFrom, timeDefaultRangeLast);
}
