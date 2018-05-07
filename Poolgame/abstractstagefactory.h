#pragma once

#include <memory>
#include "ball.h"
#include "table.h"

class AbstractStageFactory {
public:
    virtual ~AbstractStageFactory(){}
    /**
     * @brief makeBall - construct a ball based on the json provided
     * @param ballData - json that conforms to the spec
     * @return our newly created ball
     */
    virtual std::shared_ptr<Ball> makeBall(const QJsonObject& ballData) = 0;

    /**
     * @brief makeTable - construct a table based on json provided
     * @param tableData - json that conforms to the spec
     * @return our newly created table
     */
    virtual std::unique_ptr<Table> makeTable(const QJsonObject& tableData) = 0;
};
