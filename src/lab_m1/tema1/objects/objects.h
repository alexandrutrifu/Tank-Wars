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


namespace objects {
    // Create square with given bottom left corner, length and color
    Mesh *CreateSquare(const std::string &name, glm::vec3 leftBottomCorner,
                float length, glm::vec3 color, bool fill = false);
    
    // Create disk with given radius, vertex count, bottom left corner and color
    Mesh *CreateDisk(const std::string &name, float radius, float vertexCount,
                glm::vec3 leftBottomCorner, glm::vec3 color, bool fill);

    // Create trapezoid with given bottom left corner, length, height and color
    Mesh *CreateTrapezoid(const std::string &name, glm::vec3 leftBottomCorner,
                float length, float height, glm::vec3 color, bool fill = false);
}

#endif