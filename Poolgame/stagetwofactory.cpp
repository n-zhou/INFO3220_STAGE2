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

    //check for ball colour
    if (ballData.contains("colour")) {

    } else {
        std::cerr << << std::endl;
    }

    new StageOneBall(QColor(colour.c_str()), QVector2D(xpos, ypos), QVector2D(xvel, yvel), mass, radius);
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


    //check the size key
    QJsonObject sizeData = tableData["size"].toObject();
    if (sizeData.isEmpty()) {
        std::cerr << "missing size data";
    } else {

        //check table width
        if (sizeData.contains("x")) {
            if (sizeData["x"].toDouble() > 0) {
                width = sizeData["x"].toDouble();
            } else {
                std::cerr << "invalid table width, setting to default" << std::endl;
            }

        } else {
            std::cerr << "missing table width, initializing to default" << std::endl;
        }

        //check table height
        if (sizeData.contains("y")) {
            if (sizeData["y"].toDouble() > 0) {
                height = sizeData["y"].toDouble();
            } else {
                std::cerr << "invalid table height, setting to default" << std::endl;
            }
        } else {
            std::cerr << "missing table height, initializing to default" << std::endl;
        }
    }

    //check for table colour
    if (tableData.contains("colour")) {
        colour = tableData["colour"].toString().toStdString();
    } else {
        std::cerr << "missing table colour, giving it default value" << std::endl;
    }

    //check for table friction
    if (tableData.contains("friction")) {
        friction = tableData["friction"].toDouble();
    } else {
        std::cerr << "missing friction, setting to default" << std::endl;
    }

    //check for table pockets
    if (tableData.contains("pockets")) {
        QJsonArray pocketData = tableData["pockets"].toArray();
        for (int i = 0; i < pocketData.size(); ++i) {
            QJsonObject pocket = pocketData[i].toObject();

            double radius = Default::Table::Pocket::radius;
            if (pocket.contains("radius")) {
                radius = pocket["radius"].toDouble();
            }


            QJsonObject position = pocket["position"].toObject();
            //check pocket position
            if (position.contains("x") && position.contains("y")) {
                int pX = position["x"].toDouble();
                int pY = position["y"].toDouble();

                pockets->push_back(std::make_shared<Pocket>(Pocket(QVector2D(pX, pY), radius)));
            } else {
                std::cerr << "missing pocket data, pocket ignored." << std::endl;
            }
        }
    }

    return new StageTwoTable(width, height, QColor(colour.c_str()), friction, pockets);


}
