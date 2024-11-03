#include "tank.h"


tanks::Tank::Tank() = default;

tanks::Tank::~Tank() = default;

tanks::Tank *tanks::Tank::CreateTankModel(const std::string &name, glm::vec3 leftBottomCorner) {
    tanks::Tank *tank = new tanks::Tank();

    // Create tank base + body + dome
    Mesh *tankNoTurret = objects::CreateTank(name + "_body", leftBottomCorner);

    // Create tank turret
    Mesh *tankTurret = objects::CreateSquare(name + "_turret", leftBottomCorner,
                TANK_TURRET_HEIGHT, tank_turret_colour, true);
    
    // Add tank parts to object vector (in the order they should be rendered)
    tank->tankParts.push_back(tankTurret);
    tank->tankParts.push_back(tankNoTurret);

    // Set tank initial position
    tank->setCenterPosition(500, 700);
    tank->setTurretPosition(500, 700 + DOME_CENTER_Y);
    tank->setTurretAngle(glm::radians(30.0f));

    return tank;
}

glm::mat3 tanks::Tank::getRenderMatrix(Mesh *tankPart, float turretAngle) {
    glm::mat3 modelMatrix = glm::mat3(1);

    // Body rendering
    if (std::string(tankPart->GetMeshID()).find("body") != std::string::npos) {
        // Set new center
        modelMatrix *= transform::Translate(this->getCenterPosition().x, this->getCenterPosition().y);

        // Translate to origin
        modelMatrix *= transform::Translate(-TANK_BODY_LENGTH / 2, 1);
    }

    // Turret rendering
    if (std::string(tankPart->GetMeshID()).find("turret") != std::string::npos) {
        // Set new center
        modelMatrix *= transform::Translate(this->getTurretPosition().x, this->getTurretPosition().y);

        modelMatrix *= transform::Rotate(this->getTurretAngle());
        modelMatrix *= transform::Scale(TANK_TURRET_SCALE_FACTOR, 1);

        // Translate to origin
        modelMatrix *= transform::Translate(0, 1 - TANK_TURRET_HEIGHT / 2);
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

glm::vec2 tanks::Tank::getCenterPosition() const {
    return centerPosition;
}

void tanks::Tank::setCenterPosition(float x, float y) {
    centerPosition = glm::vec2(x, y);
}

glm::vec2 tanks::Tank::getTurretPosition() const {
    return turretPosition;
}

void tanks::Tank::setTurretPosition(float x, float y) {
    turretPosition = glm::vec2(x, y);
}
