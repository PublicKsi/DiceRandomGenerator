#include "mersenne.h"
#include <stdio.h>
#include <sys/param.h>

void Mersenne::RandomInit(uint32 seed) {
    // re-seed generator
    mt[0] = seed;
    for (mti = 1; mti < MERS_N; mti++) {
        mt[mti] = (1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
#if defined(__LP64__) && __LP64__
        mt[mti] &= 0xffffffff;
#endif
    }

#if defined(__LP64__) && __LP64__
#define size 1
#else
#define size 2
#endif
    // detect computer architecture
    union {
        double f;
        unsigned long i[size];
    } convert;

    convert.f = 1.0;

#if defined(__LP64__) && __LP64__
    convert.i[0] >>= 32;
#endif

    // Note: Old versions of the Gnu g++ compiler may make an error here,
    // compile with the option  -fenum-int-equiv  to fix the problem
    if (convert.i[size - 1] == 0x3FF00000) {
        Architecture = LITTLEENDIAN;
    } else if (convert.i[0] == 0x3FF00000) {
        Architecture = BIGENDIAN;
    } else {
        Architecture = NONIEEE;
    }
}

// generate 32 random bits
uint32 Mersenne::BRandom() {
    uint32 y;

    if (mti >= MERS_N) {
        // generate MERS_N words at one time
        const uint32 LOWER_MASK = ((1LU << MERS_R) - 1) & 0xffffffff; // lower MERS_R bits
        const uint32 UPPER_MASK = (-1L  << MERS_R) & 0xffffffff;      // upper (32 - MERS_R) bits
        static const uint32 mag01[2] = {0, MERS_A};

        int kk;
        for (kk = 0; kk < MERS_N - MERS_M; kk++) {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + MERS_M] ^ (y >> 1) ^ mag01[y & 1];
        }

        for (; kk < MERS_N - 1; kk++) {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + (MERS_M - MERS_N)] ^ (y >> 1) ^ mag01[y & 1];
        }

        y = (mt[MERS_N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
        mt[MERS_N - 1] = mt[MERS_M - 1] ^ (y >> 1) ^ mag01[y & 1];
        mti = 0;
    }

    y = mt[mti++];

    // Tempering (May be omitted):
    y ^=  y >> MERS_U;
    y ^= (y << MERS_S) & MERS_B;
    y ^= (y << MERS_T) & MERS_C;
    y ^=  y >> MERS_L;
    return y;
}
//-------------------------------------------------------------------------------------------
// output random float number in the interval 0 <= x < 1
double Mersenne::Random() {

#if defined(__LP64__) && __LP64__
#define size 1
#else
#define size 2
#endif
    // detect computer architecture
    union {
        double f;
        unsigned long i[size];
    } convert;

    unsigned long r = BRandom(); // get 32 significant random bits
    // The fastest way to convert random bits to floating point is as follows:
    // Set the binary exponent of a floating point number to 1+bias and set
    // the mantissa to random bits. This will give a random number in the 
    // interval [1,2). Then subtract 1.0 to get a random number in the interval
    // [0,1). This procedure requires that we know how floating point numbers
    // are stored. The storing method is tested in function RandomInit and saved 
    // in the variable Architecture. The following switch statement can be
    // omitted if the architecture is known. (A PC running Windows or Linux uses
    // LITTLEENDIAN architecture):

    const unsigned long low = r << 20;
    const unsigned long high =  (r >> 12) | 0x3FF00000;

    switch (Architecture) {
        case LITTLEENDIAN:

#if defined(__LP64__) && __LP64__
            convert.i[0] = (high << 32) | low;
#else
            convert.i[0] = low;
            convert.i[1] = high;
#endif
            return convert.f - 1.0;
        case BIGENDIAN:
#if defined(__LP64__) && __LP64__
            convert.i[0] = (low << 32) | high;
#else
            convert.i[0] = high;
            convert.i[1] = low;

#endif
            return convert.f - 1.0;
        case NONIEEE:
        default:;
    }
    // This somewhat slower method works for all architectures, including 
    // non-IEEE floating point representation:
    double result = (double) r * (1. / ((double) (unsigned long) (-1L & 0xffffffff) + 1.));

    return result;
}

//-------------------------------------------------------------------------------------------
// output random unsigned long in the interval min <= x <= max
unsigned long Mersenne::IRandom(unsigned long min, unsigned long max) {
    if (max < min) {
        return 0x80000000;
    }

    double rnd = Random();
    unsigned long diap = (max - min + 1);
    unsigned long r = (unsigned long) (diap * rnd) + min; // multiply interval with random and truncate
    if (r > max)
        r = max;

    return r;
}

//-------------------------------------------------------------------------------------------
// output random integer in the interval min <= x <= max
int Mersenne::IRandom(int min, int max) {
    if (max < min) {
        return 0x80000000;
    }

    double rnd = Random();
    unsigned int diap = (unsigned int) (max - min) + 1;
    int r = (unsigned int) (diap * rnd) + min; // multiply interval with random and truncate
    if (r > max) r = max;

    return r;
}
