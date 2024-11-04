#include "terrain.h"

#define max(x, y) ((x) >= (y) ? (x) : (y))

using namespace terrain;
using namespace objects;
using namespace std;


Terrain::Terrain() = default;

Terrain::~Terrain() = default;

float terrain::Terrain::getCorrespondingY(std::vector<glm::vec3 *> terrainCoordinates, int terrainSegmentIndex, float x){
    float temp = (x - terrainCoordinates[terrainSegmentIndex]->x) /
                    (terrainCoordinates[terrainSegmentIndex + 1]->x - terrainCoordinates[terrainSegmentIndex]->x);
    
    return terrainCoordinates[terrainSegmentIndex]->y + temp *
        (terrainCoordinates[terrainSegmentIndex + 1]->y - terrainCoordinates[terrainSegmentIndex]->y);
}

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
    return 150 * sin((M_PI / 640) * x) + 100 * sin((M_PI / 320) * x) +
            50 * sin((M_PI / 160) * x) + 75 * sin((M_PI / 500) * x) +
            30 * sin((M_PI / 100) * x) + 600;
}

std::vector<glm::vec3*> Terrain::getTerrainCoordinates(glm::ivec2 resolution) {
    std::vector<glm::vec3*> terrainCoordinates;

    for (int xCoordinate = 0; xCoordinate < resolution.x; xCoordinate += SEGMENT_SIZE) {
        float yCoordinate = getTerrainY(xCoordinate);
        terrainCoordinates.push_back(new glm::vec3(xCoordinate, yCoordinate, 0));
    }

    return terrainCoordinates;
}

// void Terrain::initializeTerrain(glm::ivec2 resolution, std::unordered_map<std::string, Mesh *> &meshes) {
//     terrainCoordinates = getTerrainCoordinates(resolution);

//     for (int startIndex = 0; startIndex < terrainCoordinates.size() - 1; startIndex++) {
//         glm::vec3 pointA = terrainCoordinates[startIndex];
//         glm::vec3 pointB = terrainCoordinates[startIndex + 1];

//         initializeSingularSquare(startIndex, pointA, pointB, meshes);
//     }
// }

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

void terrain::Terrain::destroyTerrain(std::vector<glm::vec3 *> terrainCoordinates, float x) {
    int startSegmentIndex = getTerrainSegmentIndex(x - COLLISION_RADIUS);
    int endSegmentIndex = getTerrainSegmentIndex(x + COLLISION_RADIUS);

    float yCenter = getCorrespondingY(terrainCoordinates, getTerrainSegmentIndex(x), x);

    for (int segmentIndex = startSegmentIndex; segmentIndex <= endSegmentIndex; segmentIndex++) {
        glm::vec3 *hitPoint = terrainCoordinates[segmentIndex];

        // Check if the point is within the collision radius
        if (terrainCoordinates[segmentIndex]->y >
                sqrt(pow(COLLISION_RADIUS, 2) - pow(hitPoint->x - x, 2)) + yCenter ||
                    pow(hitPoint->x - x, 2) + pow(terrainCoordinates[segmentIndex]->y - yCenter, 2) < pow(COLLISION_RADIUS, 2)) {
            printf("Old y: %f\n", terrainCoordinates[segmentIndex]->y);
            terrainCoordinates[segmentIndex]->y = -sqrt(pow(COLLISION_RADIUS, 2) - pow(hitPoint->x - x, 2)) + yCenter;
            printf("New y: %f\n", terrainCoordinates[segmentIndex]->y);
        }
    }
}

int terrain::Terrain::getTerrainSegmentIndex(float x)
{
    return floor(x / SEGMENT_SIZE);
}

float terrain::Terrain::getTankAngle(std::vector<glm::vec3 *> terrainCoordinates, int terrainSegmentIndex) {
    return atan2(terrainCoordinates[terrainSegmentIndex + 1]->y - terrainCoordinates[terrainSegmentIndex]->y,
            (terrainCoordinates[terrainSegmentIndex + 1]->x - terrainCoordinates[terrainSegmentIndex]->x));
}
