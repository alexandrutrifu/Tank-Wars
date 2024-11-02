#include "terrain.h"
#include "objects/objects.h"

#define max(x, y) ((x) >= (y) ? (x) : (y))

using namespace terrain;
using namespace objects;
using namespace std;


Terrain::Terrain() = default;

Terrain::~Terrain() = default;

void Terrain::initializeSingularSquare(int index, glm::vec3 pointA, glm::vec3 pointB,
                        std::unordered_map<std::string, Mesh *> &meshes) {
    glm::vec3 corner = glm::vec3(0, 0, 0);
    float segmentHeight = max(pointA.y, pointB.y);
    float segmentWidth = pointB.x - pointA.x;

    // Create standard square
    Mesh* square = CreateSquare("square" + std::to_string(index), corner, segmentWidth, glm::vec3(1, 0, 0), true);
    
    // Add square to the list
    if (square->GetMeshID())
    {
        meshes[square->GetMeshID()] = square;
    }

}

float Terrain::getTerrainY(float x) {
    return 20 * cos(50 * x + 25) + 20 * sin(3 * x + 1) + 500  + 30 * sin(4 * x);
    // return 500 + 50 * sin(x) + 30 * sin(4 * x) + sin(3 * x);
}

std::vector<glm::vec3> Terrain::getTerrainCoordinates(glm::ivec2 resolution) {
	std::vector<glm::vec3> terrainCoordinates;

    for (int xCoordinate = 0; xCoordinate < resolution.x; xCoordinate += 40) {
        float yCoordinate = getTerrainY(xCoordinate);
        terrainCoordinates.push_back(glm::vec3(xCoordinate, yCoordinate, 0));
    }

    return terrainCoordinates;
}

void Terrain::initializeTerrain(glm::ivec2 resolution, std::unordered_map<std::string, Mesh *> &meshes) {
    terrainCoordinates = getTerrainCoordinates(resolution);

    // printf("Terrain coordinates: %d\n", terrainCoordinates.size());

    for (int startIndex = 0; startIndex < terrainCoordinates.size() - 1; startIndex++) {
        glm::vec3 pointA = terrainCoordinates[startIndex];
        glm::vec3 pointB = terrainCoordinates[startIndex + 1];

        // printf("Point A: %f %f\n", pointA.x, pointA.y);
        // printf("Point B: %f %f\n", pointB.x, pointB.y);

        initializeSingularSquare(startIndex, pointA, pointB, meshes);
    }
}

void Terrain::renderTerrainSquare(int index, glm::vec3 pointA, glm::vec3 pointB,
                        std::unordered_map<std::string, Mesh *> &meshes) {
    modelMatrix = glm::mat3(1);

    // (1) Translation
    modelMatrix *= transform::Translate(pointA.x, pointA.y);

    // (2) Shearing
    float shearY = (pointB.y - pointA.y) / (pointB.x - pointA.x);
    modelMatrix *= transform::ShearOY(shearY);

    float segmentHeight = max(pointA.y, pointB.y);
    float segmentWidth = pointB.x - pointA.x;

    // (3) Scaling
    modelMatrix *= transform::Scale(segmentWidth, segmentHeight);

    RenderMesh2D(meshes["square" + std::to_string(index)], shaders["VertexColor"], modelMatrix);
}

void Terrain::renderTerrain(std::unordered_map<std::string, Mesh *> &meshes) {
    for (int startIndex = 0; startIndex < terrainCoordinates.size() - 1; startIndex++) {
        glm::vec3 pointA = terrainCoordinates[startIndex];
        glm::vec3 pointB = terrainCoordinates[startIndex + 1];

        renderTerrainSquare(startIndex, pointA, pointB, meshes);
    }
}