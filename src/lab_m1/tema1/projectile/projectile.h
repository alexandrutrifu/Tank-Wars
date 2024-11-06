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
#define PROJECTILE_RADIUS 8
#define PROJECTILE_OFFSET (PROJECTILE_RADIUS * 2)
#define PROJECTILE_TTL 5    // seconds

#define INITIAL_MAGNITUDE 900

#define COLLISION_THRESHOLD (PROJECTILE_RADIUS * 2.5)

extern const glm::vec3 projectile_colour;
extern const glm::vec3 projectile_inactive_position;

namespace projectile {
    const glm::vec2 gAcceleration = glm::vec2(0, -980);

    class Projectile {
        public:
            Projectile();
            ~Projectile();

            // Returns a vector of meshes that form the projectile model
            static projectile::Projectile *CreateProjectileModel(const std::string &name);

            // Builds Render Matrix
            glm::mat3 getRenderMatrix(float deltaTimeSeconds);

            glm::vec2 getCenterPosition() const;
            void setCenterPosition(float x, float y);

            Mesh *getProjectileModel() const;

            bool isOnScreen() const;
            void setOnScreen(bool onScreen);

            float getTimeToLive() const;
            void setTimeToLive(float ttl);

            glm::vec2 getMovementVector() const;
            void setMovementVector(glm::vec2 movementVector);

            int getIdAtacker() const;
            void setIdAtacker(int idAtacker);

        private:
            Mesh *projectileModel{};
            glm::vec2 centerPosition{};
            bool onScreen = false;
            float timeToLive = PROJECTILE_TTL;
            int idAtacker;

            glm::vec2 movementVector{};
    };
}

#endif // PROJECTILE_H