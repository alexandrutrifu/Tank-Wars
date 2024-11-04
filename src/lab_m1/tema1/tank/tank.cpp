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
    tank->setTurretPosition(500, 700 + TANK_BASE_HEIGHT + DOME_CENTER_Y);
    tank->setTurretAngle(glm::radians(30.0f));

    return tank;
}

glm::mat3 tanks::Tank::getRenderMatrix(Mesh *tankPart, std::vector<glm::vec3> terrainCoordinates) {
    glm::mat3 modelMatrix = glm::mat3(1);

    // Get portion of terrain that is under the tank
    int terrainSegmentIndex = terrain::Terrain::getTerrainSegmentIndex(this->getCenterPosition().x);
    this->setTankAngle(terrain::Terrain::getTankAngle(terrainCoordinates, terrainSegmentIndex));

    // Get tank y position
    float tankY = this->getTankY(terrainCoordinates, terrainSegmentIndex);

    // Set new center
    // Compute new turret position according to angle
    float tempDistance = (TANK_BASE_HEIGHT + DOME_CENTER_Y);
    float tempAngle = this->getTankAngle() + glm::radians(90.0f);

    // this->setTurretAngle(this->tankAngle + glm::radians(90.0f));

    this->setCenterPosition(this->getCenterPosition().x, tankY);
    this->setTurretPosition(this->getCenterPosition().x + tempDistance * cos(tempAngle),
                            this->getCenterPosition().y + tempDistance * sin(tempAngle));

    printf("Turret angle: %f\n", glm::degrees(this->getTurretAngle()));

    // Body rendering
    if (std::string(tankPart->GetMeshID()).find("body") != std::string::npos) {
        // Set new center
        modelMatrix *= transform::Translate(this->getCenterPosition().x, this->getCenterPosition().y);
        
        // Rotate tank
        modelMatrix *= transform::Rotate(this->getTankAngle());

        // Translate center to origin
        modelMatrix *= transform::Translate(-TANK_BODY_LENGTH / 2, 1 + TANK_BASE_HEIGHT);
    }

    // Turret rendering
    if (std::string(tankPart->GetMeshID()).find("turret") != std::string::npos) {
        // Set new center
        modelMatrix *= transform::Translate(this->getTurretPosition().x, this->getTurretPosition().y);

        printf("Tank angle: %f\n", glm::degrees(this->getTankAngle()));

        modelMatrix *= transform::Rotate(this->getTankAngle() + this->getTurretAngle());
        
        modelMatrix *= transform::Scale(TANK_TURRET_SCALE_FACTOR, 1);

        // Translate to origin
        modelMatrix *= transform::Translate(0, 1 - TANK_TURRET_HEIGHT / 2);
    }


    return modelMatrix;
}

std::vector<Mesh *> tanks::Tank::getTankParts() const {
    return tankParts;
}

float tanks::Tank::getTankY(std::vector<glm::vec3> terrainCoordinates, int terrainSegmentIndex){
    float temp = (this->getCenterPosition().x - terrainCoordinates[terrainSegmentIndex].x) /
                    (terrainCoordinates[terrainSegmentIndex + 1].x - terrainCoordinates[terrainSegmentIndex].x);
    
    return terrainCoordinates[terrainSegmentIndex].y + temp *
        (terrainCoordinates[terrainSegmentIndex + 1].y - terrainCoordinates[terrainSegmentIndex].y);
}

glm::vec2 tanks::Tank::computeProjectileStartPos() {
    float distance = TANK_TURRET_HEIGHT * TANK_TURRET_SCALE_FACTOR + 1.5 * PROJECTILE_OFFSET;

    return glm::vec2(this->getTurretPosition().x + distance * cos(this->getTurretAngle() + this->getTankAngle()),
                     this->getTurretPosition().y + distance * sin(this->getTurretAngle() + this->getTankAngle()));
}

float tanks::Tank::getTurretAngle() const
{
    return turretAngle;
}

void tanks::Tank::setTurretAngle(float angle) {
    turretAngle = angle;
}

float tanks::Tank::getTankAngle() const{
    return tankAngle;
}

void tanks::Tank::setTankAngle(float angle){
    tankAngle = angle;
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
