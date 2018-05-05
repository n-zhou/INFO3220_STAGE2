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
        return new StageTwoTable(width, height, QColor(colour.c_str()), friction, pockets);
    }


    QJsonObject sizeData = tableData["size"].toObject();
    if (sizeData.isEmpty()) {
        std::cerr << "missing size data";
    } else {
        if (sizeData.contains("x")) {
            if (sizeData["x"].toDouble() > 0) {
                width = sizeData["x"].toDouble();
            } else {
                std::cerr << "invalid table width, setting to default";
            }

        } else {
            std::cerr << "missing table width, initializing to default";
        }

        if (sizeData.contains("y")) {
            if (sizeData["y"].toDouble() > 0) {
                height = sizeData["y"].toDouble();
            } else {
                std::cerr << "invalid table height, setting to default";
            }
        } else {
            std::cerr << "missing table height, initializing to default";
        }
    }

    if (tableData.contains("colour")) {

    } else {
        std::cerr << "missing table colour, giving it default value";
    }

    if (tableData.contains("pockets")) {
        QJsonArray pocketData = tableData["pockets"].toArray();
        for (int i = 0; i < pocketData.size(); ++i) {
            QJsonObject pocket = pocketData[i].toObject();
            if (pocket.contains("x") && pocket.contains("y")) {
                int pX = pocket["x"].toDouble();
                int pY = pocket["y"].toDouble();
                double radius = Default::Table::Pocket::radius;
                if (pocket.contains("radius")) {
                    radius = pocket["radius"].toDouble();
                }
                pockets->push_back(std::make_shared<Pocket>(Pocket(QVector2D(pX, pY), radius)));
            } else {
                std ::cerr << "missing pocket data, pocket ignored.";
            }
        }
    }

    return new StageTwoTable(width, height, QColor(colour.c_str()), friction, pockets);


}
