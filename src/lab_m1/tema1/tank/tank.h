#ifndef TANK_H
#define TANK_H

#pragma once

#include "../transform.h"
#include "../objects/objects.h"
#include "math.h"

#include <vector>
#include <string>
#include <iostream>

#include "core/engine.h"
#include "core/gpu/mesh.h"
#include "components/simple_scene.h"
#include "utils/glm_utils.h"

#define TANK_BODY_LENGTH 400
#define TANK_BODY_HEIGHT 70
#define TANK_DOME_RADIUS 80
#define TANK_TURRET_LENGTH 200

#define DOME_CENTER_X (TANK_BODY_LENGTH / 2)
#define DOME_CENTER_Y (TANK_BODY_HEIGHT * 0.9)

extern const glm::vec3 tank_body_colour;

namespace tanks {
    class Tank {
        public:
            Tank();
            ~Tank();

            // Returns a vector of meshes that form the tank model
            static tanks::Tank CreateTankModel(const std::string &name, glm::vec3 leftBottomCorner);

            // Get the tank parts
            std::vector<Mesh *> getTankParts() const;

        private:
            std::vector<Mesh *> tankParts{};
    };
}

#endif