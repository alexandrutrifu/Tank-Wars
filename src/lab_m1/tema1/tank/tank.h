#ifndef TANK_H
#define TANK_H

#pragma once

#include "../transform.h"
#include "../objects/objects.h"
#include "../terrain/terrain.h"
#include "../projectile/projectile.h"
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

            // Builds Render Matrix
            glm::mat3 getRenderMatrix(Mesh *tankPart, std::vector<glm::vec3> terrainCoordinates);

            // Get the tank parts
            std::vector<Mesh *> getTankParts() const;

            // Get the tank y position
            float getTankY(std::vector<glm::vec3> terrainCoordinates, int terrainSegmentIndex);

            // Compute turret end position
            glm::vec2 computeProjectileStartPos();

            float getTurretAngle() const;
            void setTurretAngle(float angle);

            float getTankAngle() const;
            void setTankAngle(float angle);

            glm::vec2 getCenterPosition() const;
            void setCenterPosition(float x, float y);

            glm::vec2 getTurretPosition() const;
            void setTurretPosition(float x, float y);

        private:
            std::vector<Mesh *> tankParts{};
            glm::vec2 centerPosition{};
            glm::vec2 turretPosition{};
            float turretAngle{};
            float tankAngle{};
    };
}

#endif