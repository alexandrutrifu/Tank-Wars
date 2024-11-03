#include "tank.h"


tanks::Tank::Tank() = default;

tanks::Tank::~Tank() = default;

tanks::Tank *tanks::Tank::CreateTankModel(const std::string &name, glm::vec3 leftBottomCorner) {
    tanks::Tank *tank = new tanks::Tank();

    // // Create tank base
    // Mesh *tankBase = objects::CreateTrapezoid(name + "_base", leftBottomCorner,
    //             TANK_BASE_LENGTH, TANK_BASE_HEIGHT, tank_base_colour, true);
    
    // // Create tank body
    // Mesh *tankBody = objects::CreateTrapezoid(name + "_body", leftBottomCorner,
    //             TANK_BODY_LENGTH, TANK_BODY_HEIGHT, tank_body_colour, true);

    // // Create tank dome
    // Mesh *tankDome = objects::CreateDiskHalf(name + "_dome", TANK_DOME_RADIUS,
    //             DISK_VERTEX_COUNT, leftBottomCorner,
    //             tank_body_colour, true);

    // // Create tank turret
    // Mesh *tankTurret = objects::CreateSquare(name + "_turret", leftBottomCorner,
    //             TANK_TURRET_HEIGHT, tank_turret_colour, true);

    // // Add tank parts to object vector (in the order they should be rendered)
    // tank->tankParts.push_back(tankTurret);
    // tank->tankParts.push_back(tankBase);
    // tank->tankParts.push_back(tankBody);
    // tank->tankParts.push_back(tankDome);

    // Create tank base + body + dome
    Mesh *tankNoTurret = objects::CreateTank(name, leftBottomCorner);

    // Create tank turret
    Mesh *tankTurret = objects::CreateSquare(name + "_turret", leftBottomCorner,
                TANK_TURRET_HEIGHT, tank_turret_colour, true);
    
    // Add tank parts to object vector (in the order they should be rendered)
    tank->tankParts.push_back(tankTurret);
    tank->tankParts.push_back(tankNoTurret);

    return tank;
}

glm::mat3 tanks::Tank::getRenderMatrix(Mesh *tankPart, float turretAngle) {
    glm::mat3 modelMatrix = glm::mat3(1);

    modelMatrix *= transform::Translate(this->getCenterPosition().x, this->getCenterPosition().y);

    // Rotate base upside down
    if (std::string(tankPart->GetMeshID()).find("base") != std::string::npos) {
        modelMatrix *= transform::Translate(TANK_BASE_LENGTH / 2, TANK_BASE_HEIGHT / 2);
        modelMatrix *= transform::Translate(0, -TANK_BODY_HEIGHT / 2);
        modelMatrix *= transform::Translate(TANK_BASE_START_X, 0);
        modelMatrix *= transform::Scale(1, -1);
        // modelMatrix *= transform::Scale(0.5, 0.5);
        modelMatrix *= transform::Translate(-TANK_BASE_LENGTH / 2, -TANK_BASE_HEIGHT / 2);
    }

    // Render body
    if (std::string(tankPart->GetMeshID()).find("body") != std::string::npos) {
        modelMatrix *= transform::Translate(TANK_BODY_LENGTH / 2, TANK_BODY_HEIGHT / 2);
        // modelMatrix *= transform::Scale(0.5, 0.5);
        modelMatrix *= transform::Translate(-TANK_BODY_LENGTH / 2, -TANK_BODY_HEIGHT / 2);
    }

    // Render dome
    if (std::string(tankPart->GetMeshID()).find("dome") != std::string::npos) {
        modelMatrix *= transform::Translate(TANK_DOME_RADIUS / 2, TANK_DOME_RADIUS / 2);
        modelMatrix *= transform::Translate(DOME_CENTER_X, DOME_CENTER_Y);
        // modelMatrix *= transform::Scale(0.5, 0.5);
        modelMatrix *= transform::Translate(-TANK_DOME_RADIUS / 2, -TANK_DOME_RADIUS / 2);
    }

    // Scale turret into rectangle shape and translate it on top of the dome
    if (std::string(tankPart->GetMeshID()).find("turret") != std::string::npos) {
        // modelMatrix *= transform::Translate(this->getCenterPosition().x, this->getCenterPosition().y);
        modelMatrix *= transform::Translate(DOME_CENTER_X + TANK_TURRET_HEIGHT / 2, DOME_CENTER_Y * 1.1 / 0.9);
        modelMatrix *= transform::Rotate(turretAngle);
        modelMatrix *= transform::Scale(TANK_TURRET_SCALE_FACTOR, 1);
        // modelMatrix *= transform::Scale(0.5, 0.5);
        // modelMatrix *= transform::Translate(-this->getCenterPosition().x, -this->getCenterPosition().y);
    }

    // Scale tank parts
    // modelMatrix *= transform::Translate(this->getCenterPosition().x, this->getCenterPosition().y);
    // modelMatrix *= transform::Scale(0.5, 0.5);
    // modelMatrix *= transform::Translate(-this->getCenterPosition().x, -this->getCenterPosition().y);

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
