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
    StageTwoBuilder(AbstractStageFactory *factory = new StageTwoFactory()) :
        StageOneBuilder(factory) {}

    virtual ~StageTwoBuilder() {}

    /**
     * @brief getResult - retrieve the building
     * @return
     */
    virtual std::unique_ptr<AbstractPlayableGame> getResult();
};

