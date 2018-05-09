#pragma once
#include "stageonefactory.h"
#include "game.h"
#include "abstractplayablegame.h"
#include <memory>

/**
 * @brief The GameBuilder class
 *
 * @since Stage 1
 */
class GameBuilder {
protected:
    AbstractStageFactory* m_factory = nullptr;
public:
    virtual ~GameBuilder() { delete m_factory; }
    GameBuilder(AbstractStageFactory* factory) : m_factory(factory) {}
    /**
     * @brief addBall creates a ball to the current game being buil
     * @param ballData - json object that is simply an element of the array of balls provided in the
     */
    virtual void addBall(QJsonObject& ballData) = 0;

    /**
     * @brief addTable creates a table to the current game being built
     * @param tableData - json object that contains all properties of the table
     */
    virtual void addTable(QJsonObject& tableData) = 0;

    /**
     * @brief getResult - retrieve the building
     * @return
     */
    virtual std::unique_ptr<AbstractPlayableGame> getResult() = 0;
};

/**
 * @brief The StageOneBuilder class
 *
 * @author "James Butcher"
 *
 * @since Stage 1
 * @see GameBuilder
 */
class StageOneBuilder : public GameBuilder {
protected:
    std::vector<std::shared_ptr<Ball>> m_buildingBalls;
    std::unique_ptr<Table> m_buildingTable;
public:
    virtual ~StageOneBuilder();
    StageOneBuilder() : GameBuilder(new StageOneFactory()) {}

    /**
     * @brief StageOneBuilder - constructor takes in one argument and
     * makes the builder use a certain factory.
     * @param factory - the factory which we want the game builder to use.
     */
    StageOneBuilder(AbstractStageFactory *factory) : GameBuilder(factory) {}

    /**
     * @brief addBall creates a ball to the current game being buil
     * @param ballData - json object that is simply an element of the array of balls provided in the
     */
    void addBall(QJsonObject &ballData) override;

    /**
     * @brief addTable creates a table to the current game being built
     * @param tableData - json object that contains all properties of the table
     */
    void addTable(QJsonObject& tableData) override;

    /**
     * @brief getResult - retrieve the building
     * @return
     */
    virtual std::unique_ptr<AbstractPlayableGame> getResult() override;
};

/**
 * @brief The GameDirector class
 *
 * @author "James Butcher"
 * @author nzho8446
 * @since Stage 1
 */
class GameDirector {
    GameBuilder* m_builder;
    const QJsonObject* m_conf;
public:
    ~GameDirector() { delete m_builder; /* ): json object is owned by other */ }
    GameDirector(QJsonObject* conf) : m_conf(conf) {}
    /**
     * @brief setBuilder - change which builder should be used for construction
     * @param newBuilder - the new builder
     */
    void setBuilder(GameBuilder* newBuilder) { m_builder = newBuilder; }
    /**
     * @brief createGame - retrieve the building that our owned builder created
     * @return - the newly created game
     */
    std::unique_ptr<AbstractPlayableGame> createGame();
};
