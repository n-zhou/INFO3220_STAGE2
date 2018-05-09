#pragma once

#include <iostream>
#include "gamebuilder.h"
#include "stagetwoplayablegame.h"
#include "stagetwofactory.h"

class StageTwoBuilder : public StageOneBuilder {
public:
    StageTwoBuilder() : StageOneBuilder(new StageTwoFactory()) {}

    /**
     * @brief getResult - retrieve the building
     * @return
     */
    std::unique_ptr<AbstractPlayableGame> getResult();
};

