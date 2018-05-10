#pragma once

#include <QJsonObject>
#include "abstractstagefactory.h"
#include "utils.h"
#include "pocket.h"
#include "stagetwotable.h"
#include "stagetwoball.h"

/**
 * @brief The StageTwoFactory class creates objects for an
 * amazing pool game.
 *
 * <p>
 *
 * </p>
 *
 * @author nzho8446
 * @see AbstractStageFactory
 * @see StageTwoBall
 * @see StageTwoTable
 * @since Stage 2
 */

class StageTwoFactory : public AbstractStageFactory {

public:

    /**
     * @brief makeBall - construct a ball based on the json provided
     * @param ballData - json that conforms to the spec
     * @return our newly created ball
     */
    virtual std::shared_ptr<Ball> makeBall(const QJsonObject& ballData) override;

    /**
     * @brief makeTable - construct a table based on json provided
     * @param tableData - json that conforms to the spec
     * @return our newly created table
     */
    virtual std::unique_ptr<Table> makeTable(const QJsonObject& tableData) override;

private:
    std::shared_ptr<Ball> makeBall(const Ball *parentBall,const QJsonObject &ballData);
};
