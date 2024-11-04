#ifndef TERRAIN_H
#define TERRAIN_H

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

#define SEGMENT_SIZE 1


namespace terrain
{
    class Terrain : public gfxc::SimpleScene {
        public:
            Terrain();
            ~Terrain() override;

            // Render a terrain square
            void initializeSingularSquare(int index, glm::vec3 pointA, glm::vec3 pointB,
                            std::unordered_map<std::string, Mesh *> &meshes);

            // Get the y coordinate of the terrain at a given x coordinate
            static float getTerrainY(float x);

            // Initialize the terrain coordinates array
            std::vector<glm::vec3> getTerrainCoordinates(glm::ivec2 resolution);

            // Initialize terrain
            void initializeTerrain(glm::ivec2 resolution,
                    std::unordered_map<std::string, Mesh *> &meshes);

            // Render a terrain square
            void renderTerrainSquare(int index, glm::vec3 pointA, glm::vec3 pointB,
                            std::unordered_map<std::string, Mesh *> &meshes);

            // Render the terrain
            void renderTerrain(std::unordered_map<std::string, Mesh *> &meshes);

            static int getTerrainSegmentIndex(float x);

            static float getTankAngle(std::vector<glm::vec3> terrainCoordinates, int terrainSegmentIndex);

            std::vector<glm::vec3> terrainCoordinates;

        protected:
            glm::mat3 modelMatrix{};
    };
}

#endif
