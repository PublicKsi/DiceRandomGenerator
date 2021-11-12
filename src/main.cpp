#include <stdint.h>
#include <iostream>
#include "dicerandomgenerator.h"

int main(int argc, char** argv) {

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
