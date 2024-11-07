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

std::vector<Mesh *> tanks::Trajectory::getTrajectoryVertices() const{
    return trajectoryVertices;
}

std::vector<unsigned int> tanks::Trajectory::getIndices() const {
    return indices;
}
