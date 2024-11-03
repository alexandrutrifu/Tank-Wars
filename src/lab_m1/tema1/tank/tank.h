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


namespace tanks {
    class Tank {
        public:
            Tank();
            ~Tank();

            // Returns a vector of meshes that form the tank model
            static tanks::Tank *CreateTankModel(const std::string &name, glm::vec3 leftBottomCorner);

            // Places tank at initial position
            glm::mat3 placeTankAtInitialPosition(Mesh *tankPart);

            // Builds Render Matrix
            glm::mat3 getRenderMatrix(Mesh *tankPart, float turretAngle);

            // Get the tank parts
            std::vector<Mesh *> getTankParts() const;

            float getTurretAngle() const;
            void setTurretAngle(float angle);

            glm::vec2 getCenterPosition() const;
            void setCenterPosition(float x, float y);

            glm::vec2 getTurretPosition() const;
            void setTurretPosition(float x, float y);

        private:
            std::vector<Mesh *> tankParts{};
            glm::vec2 centerPosition{};
            glm::vec2 turretPosition{};
            float turretAngle{};
    };
}

#endif