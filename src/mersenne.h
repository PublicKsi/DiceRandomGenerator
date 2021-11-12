#ifndef RANDOMC_H
#define RANDOMC_H

#include <math.h>
#include <assert.h>
#include <stdint.h>

// Define 32 bit signed and unsigned integers.
// Change these definitions, if necessary, on 64 bit computers
#ifdef __LP64__
typedef int32_t int32;     
typedef uint32_t uint32;     
#else
// for backward compatibility with math libs in 32 bit systems
typedef long int32;     
typedef unsigned long uint32;     
#endif

class Mersenne {                // encapsulate random number generator
                                       // constants for MT19937:
        #define MERS_N   624
        #define MERS_M   397
        #define MERS_R   31
        #define MERS_U   11
        #define MERS_S   7
        #define MERS_T   15
        #define MERS_L   18
        #define MERS_A   0x9908B0DF
        #define MERS_B   0x9D2C5680
        #define MERS_C   0xEFC60000
public:
    Mersenne(uint32 seed) {       // constructor
        RandomInit(seed);
    }
    void RandomInit(uint32 seed);        // re-seed
    unsigned long IRandom(unsigned long min, unsigned long max); // output random integer [min, max]
    int IRandom(int min, int max);       // output random integer [min, max]
    double Random();                     // output random float
    uint32 BRandom();                    // output random bits

private:
    uint32 mt[MERS_N];                   // state vector
    uint32 mti;                          // index into mt
    enum TArch {LITTLEENDIAN, BIGENDIAN, NONIEEE};
    TArch Architecture;                  // conversion to float depends on computer architecture
};

#endif

