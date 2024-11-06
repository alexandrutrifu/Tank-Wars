#include "tank.h"


tanks::Trajectory::Trajectory() = default;

tanks::Trajectory::~Trajectory() = default;

void tanks::Trajectory::initTrajectoryVertices() {
    for (int index = 0; index < TRAJECTORY_VERTEX_COUNT; index++) {
        trajectoryVertices.push_back(objects::CreateDisk("trajectory" + std::to_string(index), 4, 40,
            glm::vec3(-1, -1, 0), tanks::trajectory_colour, true));

        indices.push_back(index);
    }
}

// void tanks::Trajectory::updateTrajectoryVertices(glm::vec2 startPosition, float tankAngle) {
//     float angle = tankAngle;
//     glm::vec2 currentPosition = startPosition;
//     glm::vec2 movementVector = glm::vec2(INITIAL_MAGNITUDE * cos(angle),
//                                         INITIAL_MAGNITUDE * sin(angle));

//     for (int index = 0; index < TRAJECTORY_VERTEX_COUNT; index++) {
//         trajectoryVertices[index].position = glm::vec3(currentPosition.x + movementVector.x,
//                                                         currentPosition.y + movementVector.y, 0);

//         currentPosition += movementVector * 0.016f;
//         movementVector += projectile::gAcceleration * 0.016f;
//     }
// }

std::vector<Mesh *> tanks::Trajectory::getTrajectoryVertices() const{
    return trajectoryVertices;
}

std::vector<unsigned int> tanks::Trajectory::getIndices() const {
    return indices;
}
