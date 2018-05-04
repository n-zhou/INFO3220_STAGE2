#include "stagetwofactory.h"

std::shared_ptr<Ball> StageTwoFactory::makeBall(const QJsonObject &ballData)
{
    std::string colour = Default::Ball::colour;
    double xpos = Default::Ball::xPosition;
    double ypos = Default::Ball::yPosition;
    double xvel = Default::Ball::xVelocity;
    double yvel = Default::Ball::yVelocity;
    double mass = Default::Ball::mass;
    double radius = Default::Ball::radius;

    //new StageOneBall(QColor(col), QVector2D(xpos, ypos), QVector2D(xvel, yvel), mass, radius)
}

Table* StageTwoFactory::makeTable(const QJsonObject &tableData)
{
    int width = Default::Table::x;
    int height = Default::Table::y;
    std::string colour = Default::Table::colour;
    double friction = Default::Table::friction;
    std::vector<std::shared_ptr<Pocket>> *pockets = new std::vector<std::shared_ptr<Pocket>>();

    //if the table is missing from the config file we operate like stage one
    if (tableData.empty()) {
        std::cerr << "table missing from config file...initialising to default";
        //return new StageOneTable(width, height, colour, friction);
    }

}
