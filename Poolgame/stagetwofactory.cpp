#include "stagetwofactory.h"

#include <QJsonObject>
#include <QVector2D>
#include "stagetwopocket.h"
#include <cassert>

std::shared_ptr<Ball> StageTwoFactory::makeBall(const QJsonObject &ballData) {
    std::string colour = Default::Ball::colour;
    double xpos = Default::Ball::xPosition;
    double ypos = Default::Ball::yPosition;
    double xvel = Default::Ball::xVelocity;
    double yvel = Default::Ball::yVelocity;
    double mass = Default::Ball::mass;
    double radius = Default::Ball::radius;
    double strength = Default::Ball::strength;

    //check for ball colour
    if (ballData.contains("colour")) {
        colour = ballData["colour"].toString().toStdString();
    } else {
        std::cerr << "missing ball colour" << std::endl;
    }

    //check for ball mass
    if (ballData.contains("mass")) {
        mass = ballData["mass"].toDouble();
    } else {
        std::cerr << "missing ball mass" << std::endl;
    }

    //check for ball strength
    if (ballData.contains("strength")) {
        strength = ballData["strength"].toDouble();
    } else {
        std::cerr << "missing ball strength" << std::endl;
    }

    //check for ball radius
    if (ballData.contains("radius")) {
        radius = ballData["radius"].toDouble();
    } else {
        std::cerr << "ball radius missing" << std::endl;
    }

    //check the ball position
    if (ballData.contains("position")) {
        QJsonObject ballPosition = ballData["position"].toObject();

        //check the ball's x position
        if (ballPosition.contains("x") && ballPosition["x"].isDouble()) {
            xpos = ballPosition["x"].toDouble();
        } else {
            std::cerr << "missing ball x position or invalid x value" << std::endl;
        }

        //check the ball's y position
        if (ballPosition.contains("y") && ballPosition["y"].isDouble()) {
            ypos = ballPosition["y"].toDouble();
        } else {
            std::cerr << "missing ball y position or invalid y value" << std::endl;
        }
    } else {
        std::cerr << "missing both ball position" << std::endl;
    }

    if (ballData.contains("velocity")) {
        QJsonObject ballVelocity = ballData["velocity"].toObject();

        //check the ball's x position
        if (ballVelocity.contains("x") && ballVelocity["x"].isDouble()) {
            xvel = ballVelocity["x"].toDouble();
        } else {
            std::cerr << "missing ball x velocity or invalid value" << std::endl;
        }

        //check the ball's y position
        if (ballVelocity.contains("y") && ballVelocity["y"].isDouble()) {
            yvel = ballVelocity["y"].toDouble();
        } else {
            std::cerr << "missing ball y velocity key or invalid value" << std::endl;
        }
    } else {
        std::cerr << "ball velocity not provided" << std::endl;
    }

    std::shared_ptr<StageTwoBall> ret = std::shared_ptr<StageTwoBall>(
                new StageTwoBall(QColor(colour.c_str()), QVector2D(xpos, ypos), QVector2D(xvel, yvel),
                                 mass, radius, strength));
    QJsonArray ballArray = ballData["balls"].toArray();
    for (int i = 0; i < ballArray.size(); ++i) {
        //add the inner balls to the parent ball
        ret->addBall(makeBall(ret.get(), ballArray[i].toObject()));
        std::vector<std::shared_ptr<Ball>> &children = ret->getBalls();
        std::shared_ptr<Ball> lastBall = children.back();
        if (ret->getPosition().distanceToPoint(lastBall->getPosition()) + lastBall->getRadius() > ret->getRadius()) {
            //erase the last child we added if it is outside of the parent ball
            children.erase(children.end()-1, children.end());
        }
    }
    //return our newly created parent ball
    return ret;
}

std::unique_ptr<Table> StageTwoFactory::makeTable(const QJsonObject &tableData) {
    int width = Default::Table::x;
    int height = Default::Table::y;
    std::string colour = Default::Table::colour;
    double friction = Default::Table::friction;
    std::vector<std::unique_ptr<Pocket>> pockets;

    //if the table is missing from the config file we operate like stage one
    if (tableData.empty()) {
        std::cerr << "table missing from config file...initialising to default";
        return std::unique_ptr<Table>(new StageTwoTable(width, height, QColor(colour.c_str()), friction, pockets));
    }


    //check the size key
    QJsonObject sizeData = tableData["size"].toObject();
    if (sizeData.isEmpty()) {
        std::cerr << "missing size data";
    } else {

        if (sizeData.contains("x") && sizeData["x"].isDouble()) {
            if (sizeData["x"].toDouble() > 0) {
                width = sizeData["x"].toDouble();
            } else {
                std::cerr << "invalid table width, setting to default" << std::endl;
            }

        } else {
            std::cerr << "missing or invalid table width, initializing to default" << std::endl;
        }

        //check table height
        if (sizeData.contains("y") && sizeData["y"].isDouble()) {
            if (sizeData["y"].toDouble() > 0) {
                height = sizeData["y"].toDouble();
            } else {
                std::cerr << "invalid table height, setting to default" << std::endl;
            }
        } else {
            std::cerr << "missing or invalid table height value initializing to default" << std::endl;
        }
    }

    if (tableData.contains("colour") && tableData["colour"].isString()) {
        colour = tableData["colour"].toString().toStdString();
    } else {
        std::cerr << "missing or invalid table colour, making it green" << std::endl;
    }

    if (tableData.contains("friction")) {
        if (tableData["friction"].toDouble() >= 0) {
            friction = tableData["friction"].toDouble();
        } else {
            std::cerr << "Cannot have negative friction values" << std::endl;
        }

    } else {
        std::cerr << "missing friction setting to default" << std::endl;
    }

    //check for table pockets
    if (tableData.contains("pockets")) {
        QJsonArray pocketData = tableData["pockets"].toArray();
        for (int i = 0; i < pocketData.size(); ++i) {
            QJsonObject pocket = pocketData[i].toObject();

            double radius = Default::Table::Pocket::radius;
            if (pocket.contains("radius") && pocket["radius"].isDouble()) {
                radius = pocket["radius"].toDouble();

            } else {
                std::cerr << "Missing pocket radius or invalid value. Setting to default." << std::endl;
            }


            QJsonObject position = pocket["position"].toObject();
            //check pocket position
            if (position.contains("x") && position.contains("y")
                    && position["x"].isDouble() && position["y"].isDouble()) {
                int pX = position["x"].toDouble();
                int pY = position["y"].toDouble();

                pockets.push_back(std::unique_ptr<StageTwoPocket>(new StageTwoPocket(QVector2D(pX, pY), radius)));
            } else {
                std::cerr << "Missing pocket data or invalid pocket values. Pocket ignored." << std::endl;
            }
        }
    }

    //remove pockets that aren't partially or fully in the boundary of the table
    pockets.erase(
                std::remove_if(pockets.begin(), pockets.end(),
                               [&width, &height](const std::unique_ptr<Pocket> &p)
                { return ((p->getPos().x() + p->getRadius() < 0) || (p->getPos().x() - p->getRadius() > width)
                                || (p->getPos().y() + p->getRadius() < 0) || (p->getPos().y() - p->getRadius() > height)); }),
                pockets.end());
    return std::unique_ptr<Table>(new StageTwoTable(width, height, QColor(colour.c_str()), friction, pockets));
}

std::shared_ptr<Ball> StageTwoFactory::makeBall(const Ball *parentBall, const QJsonObject &ballData) {
    //initialize the properties of the inner ball to default values before we change them
    std::string colour = parentBall->getColour().name().toStdString();
    QVector2D pos(Default::Ball::xPosition, Default::Ball::yPosition);
    QVector2D vel(Default::Ball::xVelocity, Default::Ball::yVelocity);
    double mass = Default::Ball::mass;
    double radius = Default::Ball::radius;
    double strength = Default::Ball::strength;

    if (ballData.contains("colour")) {
        colour = ballData["colour"].toString().toStdString();
    } else {
        std::cerr << "missing ball colour" << std::endl;
    }

    if (ballData.contains("mass")) {

        mass = ballData["mass"].toDouble();
    } else {
        std::cerr << "missing ball mass" << std::endl;
    }

    if (ballData.contains("strength")) {
        strength = ballData["strength"].toDouble();
    } else {
        std::cerr << "missing ball strength" << std::endl;
    }

    if (ballData.contains("radius")) {
        radius = ballData["radius"].toDouble();
    } else {
        std::cerr << "ball radius missing" << std::endl;
    }

    if (ballData.contains("position")) {
        QJsonObject ballPosition = ballData["position"].toObject();

        if (ballPosition.contains("x")) {
            pos.setX(ballPosition["x"].toDouble());
        } else {
            std::cerr << "missing ball x position" << std::endl;
        }

        if (ballPosition.contains("y")) {
            pos.setY(ballPosition["y"].toDouble());
        } else {
            std::cerr << "missing ball y position" << std::endl;
        }
    } else {
        std::cerr << "missing both ball position" << std::endl;
    }

    //make the position of inner ball relative to the parent
    pos += parentBall->getPosition();
    std::unique_ptr<StageTwoBall> ret = std::unique_ptr<StageTwoBall>(
                new StageTwoBall(QColor(colour.c_str()),
                                 pos,
                                 vel,
                                 mass,
                                 radius,
                                 strength));
    if (parentBall->getPosition().distanceToPoint(ret->getPosition()) + ret->getRadius() > parentBall->getRadius()) {
        //if the new ball we are creating is outside the parent ball we stop don't make the inner balls of this ball
        return ret;
    }
    QJsonArray ballArray = ballData["balls"].toArray();
    for (int i = 0; i < ballArray.size(); ++i) {
        //recursively make the inner balls
        ret->addBall(this->makeBall(ret.get(), ballArray[i].toObject()));
        std::vector<std::shared_ptr<Ball>> &children = ret->getBalls();
        std::shared_ptr<Ball> lastBall = children.back();
        if (ret->getPosition().distanceToPoint(lastBall->getPosition()) + lastBall->getRadius() > ret->getRadius()) {
            //remove the ball we just added if it outside the boundary of the parent ball
            children.erase(children.end()-1);
        }
    }
    return ret;
}
