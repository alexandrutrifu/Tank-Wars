#include "tank.h"


tanks::Tank::Tank() = default;

tanks::Tank::~Tank() = default;

tanks::Tank *tanks::Tank::CreateTankModel(const std::string &name, glm::vec3 leftBottomCorner,
                const glm::vec3 &tank_body_colour, const glm::vec3 &tank_base_colour,
                const glm::vec3 &tank_turret_colour) {
    tanks::Tank *tank = new tanks::Tank();

    // Create tank base + body + dome
    Mesh *tankNoTurret = objects::CreateTank(name + "_body", leftBottomCorner,
        tank_body_colour, tank_base_colour);

    // Create tank turret
    Mesh *tankTurret = objects::CreateSquare(name + "_turret", leftBottomCorner,
                TANK_TURRET_HEIGHT, tank_turret_colour, true);
    
    // Add tank parts to object vector (in the order they should be rendered)
    tank->tankParts.push_back(tankTurret);
    tank->tankParts.push_back(tankNoTurret);

    return tank;
}

glm::mat3 tanks::Tank::getRenderMatrix(Mesh *tankPart, std::vector<glm::vec3 *> terrainCoordinates) {
    glm::mat3 modelMatrix = glm::mat3(1);

    // Get portion of terrain that is under the tank
    int terrainSegmentIndex = terrain::Terrain::getTerrainSegmentIndex(this->getCenterPosition().x);
    this->setTankAngle(terrain::Terrain::getTankAngle(terrainCoordinates, terrainSegmentIndex));

    // Get tank y position
    float tankY = terrain::Terrain::getCorrespondingY(terrainCoordinates, terrainSegmentIndex, this->getCenterPosition().x);

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

glm::mat3 tanks::Tank::getHealthBarRenderMatrix(Mesh *healthBarPart) {
    glm::mat3 modelMatrix = glm::mat3(1);

    this->getHealthBar()->setCenterPosition(this->getCenterPosition().x, this->getCenterPosition().y + HEALTH_BAR_OFFSET);
    modelMatrix *= transform::Translate(this->getCenterPosition().x - TANK_BODY_LENGTH / 2,
                                            this->getCenterPosition().y + HEALTH_BAR_OFFSET);

    if (std::string(healthBarPart->GetMeshID()).find("contour") != std::string::npos) {
        modelMatrix *= transform::Scale(HEALTH_BAR_SCALE_FACTOR, 1);
    }

    if (std::string(healthBarPart->GetMeshID()).find("fill") != std::string::npos) {
        modelMatrix *= transform::Scale(HEALTH_BAR_SCALE_FACTOR * this->getHealthBar()->getHealth() / 100.0f, 1);
    }

    modelMatrix *= transform::Translate(0, 1 - HEALTH_BAR_HEIGHT / 2);

    return modelMatrix;
}

std::vector<Mesh *> tanks::Tank::getTankParts() const {
    return tankParts;
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

healthBar::HealthBar *tanks::Tank::getHealthBar() const{
    return healthBar;
}

void tanks::Tank::setHealthBar(healthBar::HealthBar *healthBar){
    this->healthBar = healthBar;
}

tanks::Trajectory *tanks::Tank::getTrajectory() const {
    return trajectory;
}

void tanks::Tank::setTrajectory(tanks::Trajectory *trajectory) {
    this->trajectory = trajectory;
}
