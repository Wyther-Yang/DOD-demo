#include "cars.h"

// on ubuntu 20.2, ld.so seems buggy, changing entry point 
// cause segment fault when the stage of return to glibc
int main(int args, char** argv)
{
#ifdef OOD
        DoSimilateForOOD(args, argv);
#else
        DoSimilateForDOD(args, argv);
#endif
}