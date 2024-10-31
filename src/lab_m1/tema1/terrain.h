#ifndef TERRAIN_H
#define TERRAIN_H

#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "components/simple_scene.h"
#include "utils/glm_utils.h"


namespace terrain
{
    class Terrain : public gfxc::SimpleScene {
        public:
            Terrain();
            ~Terrain() override;

            // Create square with given bottom left corner, length and color
            Mesh *CreateSquare(const std::string &name, glm::vec3 leftBottomCorner,
                            float length, glm::vec3 color, bool fill = false);

            // Render a terrain square
            void renderTerrainSquare(int index, glm::vec3 pointA, glm::vec3 pointB, glm::vec3 corner);

            // Get the y coordinate of the terrain at a given x coordinate
            float getTerrainY(float x);

            // Initialize the terrain coordinates array
            std::vector<glm::vec3> getTerrainCoordinates(glm::ivec2 resolution);

            // Initialize terrain
            void initializeTerrain(glm::ivec2 resolution);

        protected:
            glm::mat3 modelMatrix{};
    };
}

#endif
