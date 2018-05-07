#include "stagetwobuilder.h"

AbstractPlayableGame* StageTwoBuilder::getResult()
{

    // likewise for table
    if (m_buildingTable == nullptr) {
        throw std::invalid_argument("builder finished with no table supplied");
    }

    AbstractPlayableGame *retGame = new StageTwoPlayableGame(m_buildingTable, m_buildingBalls);
    //need to reset for when we build next
    m_buildingBalls.clear();
    m_buildingTable = nullptr;
    return retGame;
}
