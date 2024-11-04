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


namespace healthBar {
    const glm::vec3 health_bar_colour = glm::vec3(1, 1, 1);

    class HealthBar {
        public:
            HealthBar();
            ~HealthBar();

            // Returns a vector of meshes that form the health bar model
            static HealthBar *CreateHealthBarModel(const std::string &name, glm::vec3 leftBottomCorner,
                        const glm::vec3 &health_bar_colour);

            float getHealth() const;
            void setHealth(float health);

            glm::vec2 getCenterPosition() const;
            void setCenterPosition(float x, float y);

            std::vector<Mesh *> getHealthBarParts() const;

        private:
            std::vector<Mesh *> healthBarParts{};
            glm::vec2 centerPosition{};
            float health{};
    };
}

namespace tanks {
    const glm::vec3 tankA_base_colour = glm::vec3(0.451, 0.392, 0.306);
    const glm::vec3 tankA_body_colour = glm::vec3(0.796, 0.686, 0.533);
    const glm::vec3 tankA_turret_colour = glm::vec3(0.227, 0.227, 0.235);

    const glm::vec3 tankB_base_colour = glm::vec3(0.349, 0.392, 0.2);
    const glm::vec3 tankB_body_colour = glm::vec3(0.698, 0.796, 0.545);
    const glm::vec3 tankB_turret_colour = glm::vec3(0.227, 0.227, 0.235);

    class Tank {
        public:
            Tank();
            ~Tank();

            // Returns a vector of meshes that form the tank model
            static tanks::Tank *CreateTankModel(const std::string &name, glm::vec3 leftBottomCorner,
                        const glm::vec3 &tank_body_colour, const glm::vec3 &tank_base_colour,
                        const glm::vec3 &tank_turret_colour);

            // Builds Render Matrix
            glm::mat3 getRenderMatrix(Mesh *tankPart, std::vector<glm::vec3 *> terrainCoordinates);

            // Builds Render Matrix for health bar
            glm::mat3 getHealthBarRenderMatrix(Mesh *healthBarPart);

            // Get the tank parts
            std::vector<Mesh *> getTankParts() const;

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

            healthBar::HealthBar *getHealthBar() const;
            void setHealthBar(healthBar::HealthBar *healthBar);

        private:
            std::vector<Mesh *> tankParts{};
            healthBar::HealthBar *healthBar{};
            glm::vec2 centerPosition{};
            glm::vec2 turretPosition{};
            float turretAngle{};
            float tankAngle{};
    };
}

#endif