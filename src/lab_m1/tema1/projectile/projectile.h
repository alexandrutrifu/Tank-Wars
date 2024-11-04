#ifndef PROJECTILE_H
#define PROJECTILE_H

#pragma once

#include "../transform.h"
#include "../objects/objects.h"
#include "../terrain/terrain.h"
#include "math.h"

#include <vector>
#include <string>
#include <iostream>

#include "core/engine.h"
#include "core/gpu/mesh.h"
#include "components/simple_scene.h"
#include "utils/glm_utils.h"

#define PROJECTILE_POOL_SIZE 10

extern const glm::vec3 projectile_colour;
extern const glm::vec3 projectile_inactive_position;

namespace projectile {
    class Projectile {
        public:
            Projectile();
            ~Projectile();

            // Returns a vector of meshes that form the projectile model
            static projectile::Projectile *CreateProjectileModel(const std::string &name);

            // Builds Render Matrix
            glm::mat3 getRenderMatrix(Mesh *projectilePart, float angle, std::vector<glm::vec3> terrainCoordinates);

            // Get the projectile parts
            std::vector<Mesh *> getProjectileParts() const;

            // Get the projectile y position
            float getProjectileY(std::vector<glm::vec3> terrainCoordinates, int terrainSegmentIndex);

            glm::vec2 getCenterPosition() const;
            void setCenterPosition(float x, float y);

            Mesh *getProjectileModel() const;

            bool isOnScreen() const;
            void setOnScreen(bool onScreen);

        private:
            Mesh *projectileModel{};
            glm::vec2 centerPosition{};
            bool onScreen = false;
    };
}

#endif // PROJECTILE_H