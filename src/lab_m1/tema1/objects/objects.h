#ifndef OBJECTS_H
#define OBJECTS_H

#pragma once

#include "../transform.h"
#include "math.h"

#include <vector>
#include <string>
#include <iostream>

#include "core/engine.h"
#include "core/gpu/mesh.h"
#include "components/simple_scene.h"
#include "utils/glm_utils.h"

#define DISK_VERTEX_COUNT 100

#define TANK_BODY_LENGTH 160
#define TANK_BODY_HEIGHT 32

#define TANK_BASE_START_X (TANK_BODY_HEIGHT * 0.7)
#define TANK_BASE_LENGTH (TANK_BODY_LENGTH - TANK_BASE_START_X * 2)
#define TANK_BASE_HEIGHT (TANK_BODY_HEIGHT * 0.4)

#define TANK_DOME_RADIUS 32
#define DOME_CENTER_X (TANK_BODY_LENGTH / 2)
#define DOME_CENTER_Y (TANK_BODY_HEIGHT * 0.9)

#define TANK_TURRET_SCALE_FACTOR 8
#define TANK_TURRET_HEIGHT 10

#define TANK_INITIAL_CENTER_X (TANK_BODY_LENGTH / 2)
#define TANK_INITIAL_CENTER_Y (TANK_BODY_HEIGHT / 2)
#define TURRET_INITIAL_CENTER_X 0
#define TURRET_INITIAL_CENTER_Y (-1 + TANK_TURRET_HEIGHT / 2)

#define START_POS_X_1 1000
#define START_POS_Y_1 500


namespace objects {
    // Create square with given bottom left corner, length and color
    Mesh *CreateSquare(const std::string &name, glm::vec3 leftBottomCorner,
                float length, glm::vec3 color, bool fill = false);
    
    // Create disk with given radius, vertex count, bottom left corner and color
    Mesh *CreateDisk(const std::string &name, float radius, int vertexCount,
                glm::vec3 leftBottomCorner, glm::vec3 color, bool fill);

    // Create disk half with given radius, vertex count, bottom left corner and color
    Mesh *CreateDiskHalf(const std::string &name, float radius, int vertexCount,
                glm::vec3 leftBottomCorner, glm::vec3 color, bool fill);

    // Create trapezoid with given bottom left corner, length, height and color
    Mesh *CreateTrapezoid(const std::string &name, glm::vec3 leftBottomCorner,
                float length, float height, glm::vec3 color, bool fill = false);\
    
    // Create tank model
    Mesh *CreateTank(const std::string &name, glm::vec3 leftBottomCorner,
                const glm::vec3 &tank_body_colour, const glm::vec3 &tank_turret_colour);
                
}

#endif