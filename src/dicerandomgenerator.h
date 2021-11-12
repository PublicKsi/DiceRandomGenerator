#ifndef DICERANDOMGENERATOR_H
#define DICERANDOMGENERATOR_H

#include <memory>
#include "mersenne.h"

class DiceRandomGenerator {
public:
    const int GAMMON_DICE_MAX_VALUE = 6;
    
public:
    DiceRandomGenerator(uint32 seed = 0, int seedOffset = 0);
    DiceRandomGenerator(const DiceRandomGenerator& orig);
    
    uint32 GetSeed() const { return m_seed; }
    int GetSeedOffset() const { return m_seed_offset; }
       
    int getDice();
    
    void setSeedAndOffset(uint32 seed, int seedOffset);
    
protected:
    void setSeed(uint32 seed);
    void moveByOffset(int seedOffset);
    
private:
    uint32 m_seed;
    int m_seed_offset;
    std::unique_ptr<Mersenne> m_rg;
};

#endif /* DICERANDOMGENERATOR_H */

