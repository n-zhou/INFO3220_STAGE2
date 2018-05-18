#pragma once

#include <QJsonObject>
#include "abstractstagefactory.h"
#include "utils.h"
#include "pocket.h"
#include "stagetwotable.h"
#include "stagetwoball.h"

/**
 * @brief The StageTwoFactory class creates objects for an amazing pool game.
 *
 * <p>
 * This factory is designed to create objects that have attributes defined in
 * Assignment 2 specs. If there is any missing data or invalid data, it will
 * use the default value as per stage 2 defined.
 * </p>
 *
 * <p>
 * Parent balls that are missing any position attribute are invalid but will be
 * created regardless. This is because we cannot guaruantee all the boundries of
 * the table.
 * </p>
 *
 * <p>
 * Pockets that are out of bounds can however be removed before we create the table. This
 * is because the json data pockets is contained as a value of the table object. Thus we will
 * know the dimensions of the table ahead of time and as such we can ignore the pocket if necessary.
 * </p>
 *
 * @author nzho8446
 * @see AbstractStageFactory
 * @see StageOneFactory
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

    /**
     * @brief makeBall - construct a ball based on the provided json and parent ball
     * @param parentBall - the ball which will contain the ball we are making
     * @param ballData - json that conforms to the spec
     * @return our newly created child ball which may possibly be outside the the parentball
     */
    std::shared_ptr<Ball> makeBall(const Ball *parentBall,const QJsonObject &ballData);
};
