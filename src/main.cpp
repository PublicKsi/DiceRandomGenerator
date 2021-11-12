#include <stdint.h>
#include <iostream>
#include "dicerandomgenerator.h"

//#include <random>


int main(int argc, char** argv) {

//    std::mersenne_twister_engine<std::uint_fast32_t, 32, 624, 397, 31,
//                                 0x9908b0df, 11,
//                                 0xffffffff, 7,
//                                 0x9d2c5680, 15,
//                                 0xefc60000, 18, 1812433253> engine;

//    engine.seed(0);

    uint32_t seed = 0;
    int dice_count = 500;

    std::cout << "Input seed: ";
    std::cin >> seed;
    std::cout << "Input count of dice: ";
    std::cin >> dice_count;

    DiceRandomGenerator generator(seed);
    std::cout << "Dices: ";
    for(int i = 1; i <= dice_count; ++i) {

        int dice = generator.getDice();
        if (i < dice_count)
            std::cout << dice << ", ";
        else
            std::cout << dice << "." << std::endl;
    }
    return 0;
}
