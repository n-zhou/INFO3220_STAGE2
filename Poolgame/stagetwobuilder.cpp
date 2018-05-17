#include "stagetwobuilder.h"

std::unique_ptr<AbstractPlayableGame> StageTwoBuilder::getResult() {

    // likewise for table
    if (m_buildingTable == nullptr) {
        throw std::invalid_argument("builder finished with no table supplied");
    }

    if (m_buildingBalls.empty()) {
        //no balls were built then we'll put a white one in the middle of the table
        m_buildingBalls.push_back(std::shared_ptr<Ball>(
                                      new StageTwoBall(QColor("White"), QVector2D(m_buildingTable->getWidth()/2, m_buildingTable->getHeight()/2),
                                                       QVector2D(0, 0), 1.0, 10, FLT_MAX)));
        std::cerr << "No balls provided, using default values..." << std::endl;
    }

    std::unique_ptr<AbstractPlayableGame> retGame = std::unique_ptr<AbstractPlayableGame>(
                new StageTwoPlayableGame(std::move(m_buildingTable), m_buildingBalls));
    //need to reset for when we build next
    m_buildingBalls.clear();
    m_buildingTable = nullptr;
    return retGame;
}
