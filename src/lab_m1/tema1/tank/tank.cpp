#include "tank.h"


const glm::vec3 tank_body_colour = glm::vec3(0.796, 0.686, 0.533);

tanks::Tank::Tank() = default;

tanks::Tank::~Tank() = default;

tanks::Tank tanks::Tank::CreateTankModel(const std::string &name, glm::vec3 leftBottomCorner) {
    tanks::Tank tank{};
    
    // Create tank body
    Mesh *tankBody = objects::CreateTrapezoid(name + "_body", leftBottomCorner,
                TANK_BODY_LENGTH, TANK_BODY_HEIGHT, tank_body_colour, true);

    // Create tank dome
    Mesh *tankDome = objects::CreateDiskHalf(name + "_dome", TANK_DOME_RADIUS,
                DISK_VERTEX_COUNT,
                leftBottomCorner + glm::vec3(DOME_CENTER_X, DOME_CENTER_Y, 0),
                tank_body_colour, true);

    tank.tankParts.push_back(tankBody);
    tank.tankParts.push_back(tankDome);

    return tank;
}

std::vector<Mesh *> tanks::Tank::getTankParts() const {
    return tankParts;
}