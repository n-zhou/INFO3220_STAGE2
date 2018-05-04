#pragma once

#include <iostream>
#include <QJsonObject>
#include "abstractstagefactory.h"
#include "utils.h"
#include "pocket.h"

class StageTwoFactory : public AbstractStageFactory
{
public:

    /**
     * @brief makeBall - construct a ball based on json
     * @param ballData - our json data for this table
     * @return
     */
    virtual std::shared_ptr<Ball> makeBall(const QJsonObject& ballData) override;

    /**
     * @brief makeTable - construct a table based on json
     * @param tableData - our json data for this table
     * @return
     */
    virtual Table* makeTable(const QJsonObject& tableData) override;
};
