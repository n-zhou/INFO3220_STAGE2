#pragma once

#include <iostream>
#include "gamebuilder.h"
#include "stagetwoplayablegame.h"

class StageTwoBuilder : public StageOneBuilder
{
public:
    StageTwoBuilder() : StageOneBuilder(new StageOneFactory()) {}

    /**
     * @brief getResult - retrieve the building
     * @return
     */
    AbstractPlayableGame* getResult();
};

