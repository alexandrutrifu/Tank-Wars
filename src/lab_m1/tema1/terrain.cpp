#include "terrain.h"
#include "transform.h"
#include "math.h"

#include <vector>

#include "core/engine.h"

#define max(x, y) ((x) >= (y) ? (x) : (y))

using namespace terrain;


Mesh* Terrain::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

void Terrain::renderTerrainSquare(int index, glm::vec3 pointA, glm::vec3 pointB, glm::vec3 corner) {
    float segmentHeight = max(pointA.y, pointB.y);
    float segmentWidth = pointB.x - pointA.x;

    // Create standard square
    Mesh* square = CreateSquare("square" + index, corner, segmentWidth, glm::vec3(1, 0, 0), true);
    AddMeshToList(square);

    // (1) Scaling
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform::Scale(1, segmentHeight);

    // (2) Shearing
    float shearFactor = (pointB.y - pointA.y) / (pointB.x - pointA.x);
    modelMatrix *= transform::ShearOY(shearFactor);

    // (3) Translation
    modelMatrix *= transform::Translate(pointA.x, pointA.y);

    RenderMesh2D(meshes["square" + index], shaders["VertexColor"], modelMatrix);
}

float Terrain::getTerrainY(float x) {
    return cos(2 * x + 1) - cos(1.5 * x + 1.5) +
         0.2 * sin(3.4 * x + 1) + 2 + x / 20 + sin(0.4 * x);
}

std::vector<glm::vec3> Terrain::getTerrainCoordinates(glm::ivec2 resolution) {
	std::vector<glm::vec3> terrainCoordinates;

    for (int xCoordinate = 0; xCoordinate < resolution.x; xCoordinate += 10) {
        float yCoordinate = getTerrainY(xCoordinate);
        terrainCoordinates.push_back(glm::vec3(xCoordinate, yCoordinate, 0));
    }

    return terrainCoordinates;
}

void Terrain::initializeTerrain(glm::ivec2 resolution) {
    std::vector<glm::vec3> terrainCoordinates = getTerrainCoordinates(resolution);
    glm::vec3 corner = glm::vec3(0, 0, 0);

    for (int startIndex = 0; startIndex < terrainCoordinates.size() - 1; startIndex++) {
        glm::vec3 pointA = terrainCoordinates[startIndex];
        glm::vec3 pointB = terrainCoordinates[startIndex + 1];

        renderTerrainSquare(startIndex, pointA, pointB, corner);
    }
}