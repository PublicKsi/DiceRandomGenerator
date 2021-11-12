#include <memory>
#include "mersenne.h"
#include "dicerandomgenerator.h"

DiceRandomGenerator::DiceRandomGenerator(uint32 seed, int seedOffset) {
    m_seed = seed;
    m_seed_offset = 0;
    
    m_rg.reset(new Mersenne(m_seed));
    moveByOffset(seedOffset);
}

DiceRandomGenerator::DiceRandomGenerator(const DiceRandomGenerator& orig) {    
    m_seed = orig.m_seed;
    m_seed_offset = 0;
            
    m_rg.reset(new Mersenne(m_seed));
    moveByOffset(orig.m_seed_offset);
}

int DiceRandomGenerator::getDice() {    
    int dice = m_rg->IRandom(1, GAMMON_DICE_MAX_VALUE);
    ++m_seed_offset;
    return dice;
}

void DiceRandomGenerator::setSeedAndOffset(uint32 seed, int seedOffset) {
    if( m_seed == seed && m_seed_offset == seedOffset )
        return;
    
    setSeed(seed);
    moveByOffset(seedOffset);
}

void DiceRandomGenerator::setSeed(uint32 seed) {
    m_seed = seed;
    m_seed_offset = 0;
    m_rg->RandomInit(m_seed);
}

void DiceRandomGenerator::moveByOffset(int seedOffset) {
    for(int offset = 0; offset < seedOffset; ++offset) 
    {
        m_rg->BRandom();
    }
    m_seed_offset += seedOffset;
}
