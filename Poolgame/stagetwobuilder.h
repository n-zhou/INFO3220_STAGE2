#pragma once

#include <iostream>
#include "gamebuilder.h"
#include "stagetwoplayablegame.h"
#include "stagetwofactory.h"

/**
 * @brief The StageTwoBuilder class
 *
 * @author nzho8446
 * @see StageOneBuilder
 * @see GameBuilder
 * @since Stage 1
 */
class StageTwoBuilder : public StageOneBuilder {
public:
    StageTwoBuilder() : StageOneBuilder(new StageTwoFactory()) {}

    /**
     * @brief getResult - retrieve the building
     * @return
     */
    std::unique_ptr<AbstractPlayableGame> getResult();
};

