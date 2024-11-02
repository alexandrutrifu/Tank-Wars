#include "tank.h"


const glm::vec3 tank_base_colour = glm::vec3(0.451, 0.392, 0.306);
const glm::vec3 tank_body_colour = glm::vec3(0.796, 0.686, 0.533);
const glm::vec3 tank_turret_colour = glm::vec3(0.227, 0.227, 0.235);

tanks::Tank::Tank() = default;

tanks::Tank::~Tank() = default;

tanks::Tank *tanks::Tank::CreateTankModel(const std::string &name, glm::vec3 leftBottomCorner) {
    tanks::Tank *tank = new tanks::Tank();

    // Create tank base
    Mesh *tankBase = objects::CreateTrapezoid(name + "_base", leftBottomCorner,
                TANK_BASE_LENGTH, TANK_BASE_HEIGHT, tank_base_colour, true);
    
    // Create tank body
    Mesh *tankBody = objects::CreateTrapezoid(name + "_body", leftBottomCorner,
                TANK_BODY_LENGTH, TANK_BODY_HEIGHT, tank_body_colour, true);

    // Create tank dome
    Mesh *tankDome = objects::CreateDiskHalf(name + "_dome", TANK_DOME_RADIUS,
                DISK_VERTEX_COUNT,
                leftBottomCorner + glm::vec3(DOME_CENTER_X, DOME_CENTER_Y, 0),
                tank_body_colour, true);

    // Create tank turret
    Mesh *tankTurret = objects::CreateSquare(name + "_turret", leftBottomCorner,
                TANK_TURRET_HEIGHT, tank_turret_colour, true);

    // Add tank parts to object vector (in the order they should be rendered)
    tank->tankParts.push_back(tankTurret);
    tank->tankParts.push_back(tankBase);
    tank->tankParts.push_back(tankBody);
    tank->tankParts.push_back(tankDome);

    return tank;
}

glm::mat3 tanks::Tank::getRenderMatrix(Mesh *tankPart, float turretAngle) {
    glm::mat3 modelMatrix = glm::mat3(1);

    modelMatrix *= transform::Translate(1000, 500);

    // Rotate base upside down
    if (std::string(tankPart->GetMeshID()).find("base") != std::string::npos) {
        modelMatrix *= transform::Translate(TANK_BASE_START_X, 0);
        modelMatrix *= transform::Scale(1, -1);
    }

    // Scale turret into rectangle shape and translate it on top of the dome
    if (std::string(tankPart->GetMeshID()).find("turret") != std::string::npos) {
        modelMatrix *= transform::Translate(DOME_CENTER_X, DOME_CENTER_Y);
        modelMatrix *= transform::Rotate(turretAngle);
        modelMatrix *= transform::Scale(TANK_TURRET_SCALE_FACTOR, 1);
    }

    return modelMatrix;
}

std::vector<Mesh *> tanks::Tank::getTankParts() const {
    return tankParts;
}

float tanks::Tank::getTurretAngle() const {
    return turretAngle;
}

void tanks::Tank::setTurretAngle(float angle) {
    turretAngle = angle;
}
