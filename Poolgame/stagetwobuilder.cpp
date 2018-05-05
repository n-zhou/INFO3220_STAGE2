#include "stagetwobuilder.h"

AbstractPlayableGame* StageTwoBuilder::getResult()
{
    // no-one called addBall
    if (m_buildingBalls == nullptr) {
        // soft fail
        std::cerr << "warning! pool game without balls created...\n";
        m_buildingBalls = new std::vector<std::shared_ptr<Ball>>();
    }
    // likewise for table
    if (m_buildingTable == nullptr) {
        throw std::invalid_argument("builder finished with no table supplied");
    }

    AbstractPlayableGame *retGame = new StageTwoPlayableGame(m_buildingTable, m_buildingBalls);
    //need to reset for when we build next
    m_buildingBalls = nullptr;
    m_buildingTable = nullptr;
    return retGame;
}
