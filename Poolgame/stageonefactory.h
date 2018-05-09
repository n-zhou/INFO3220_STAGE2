#pragma once
#include "abstractstagefactory.h"

/**
 * @brief The StageOneFactory class
 *
 * <p>
 * This class has been modified from returning raw pointers in its methods
 * to returning smart pointers. The original interface of this class returned
 * raw pointers. Since that interface was modified to return smart pointers of
 * objects, this class was modified such that it still conformed to the interface it
 * inherited from.
 * </p>
 *
 * @author "James Butcher"
 * @author nzho8446
 * @since Stage 1
 * @see AbstractStageFactory
 */
class StageOneFactory : public AbstractStageFactory {
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
    virtual std::unique_ptr<Table> makeTable(const QJsonObject& tableData) override;
};
