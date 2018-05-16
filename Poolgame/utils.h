#pragma once

#include <QVector2D>
#include <string>
#include <cfloat>

/* filename of the config file */
constexpr char config_path[] = "config.json";


constexpr int animFrameMS = 16;
constexpr int drawFrameMS = 16;

/**
 * This namespace contains the default values used for stage 2
 */
namespace Default {

    /**
     * This namespace defines constants for the ball object.
     */
    namespace Ball {
        constexpr double strength = FLT_MAX;
        constexpr double mass = 1.0;
        constexpr double radius = 10;
        constexpr double xPosition = 0;
        constexpr double yPosition = 0;
        constexpr double xVelocity = 0;
        constexpr double yVelocity = 0;
        constexpr char const *colour = "white";
    }

    /**
     * This namespace defines constants for the table
     */
    namespace Table {
        constexpr size_t x = 600;
        constexpr size_t y = 300;
        constexpr double friction = 0.01;
        constexpr char const *colour = "green";

        /**
         *  This nested namespace defines constants for Pockets
         */
        namespace Pocket {
            constexpr double radius = 15;
        }
    }

}
