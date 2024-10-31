#ifndef TERRAIN_H
#define TERRAIN_H

#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace terrain
{
    // Create square with given bottom left corner, length and color
    Mesh *CreateSquare(const std::string &name, glm::vec3 leftBottomCorner,
                       float length, glm::vec3 color, bool fill = false);

	// Get the y coordinate of the terrain at a given x coordinate
    float getTerrainY(float x);

	// Initialize the terrain coordinates array
	std::vector<glm::vec3> initializeTerrain(glm::ivec2 resolution);
}

#endif
