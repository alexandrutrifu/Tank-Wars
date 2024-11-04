#include "projectile.h"

const glm::vec3 projectile_colour = glm::vec3(0.0, 0.0, 0.0);
const glm::vec3 projectile_inactive_position = glm::vec3(-1, -1, 0);

projectile::Projectile::Projectile() = default;

projectile::Projectile::~Projectile() = default;

projectile::Projectile *projectile::Projectile::CreateProjectileModel(const std::string &name) {
    projectile::Projectile *projectile = new projectile::Projectile();

    projectile->projectileModel = objects::CreateDisk(name, PROJECTILE_RADIUS, 100,
        projectile_inactive_position, projectile_colour, true);
    projectile->onScreen = false;

    return projectile;
}

glm::mat3 projectile::Projectile::getRenderMatrix(float deltaTimeSeconds) {
    glm::mat3 modelMatrix = glm::mat3(1);

    // Update movement vector
    this->setCenterPosition(this->getCenterPosition().x + this->getMovementVector().x * deltaTimeSeconds,
                            this->getCenterPosition().y + this->getMovementVector().y * deltaTimeSeconds);
    this->setMovementVector(this->getMovementVector() + projectile::gAcceleration * deltaTimeSeconds);

    modelMatrix *= transform::Translate(this->getCenterPosition().x, this->getCenterPosition().y);
    
    // Place in origin
    modelMatrix *= transform::Translate(1, 1);

    return modelMatrix;
}

glm::vec2 projectile::Projectile::getCenterPosition() const{
    return centerPosition;
}

void projectile::Projectile::setCenterPosition(float x, float y){
    centerPosition = glm::vec2(x, y);
}

Mesh *projectile::Projectile::getProjectileModel() const
{
    return projectileModel;
}

bool projectile::Projectile::isOnScreen() const {
    return onScreen;
}

void projectile::Projectile::setOnScreen(bool onScreen) {
    projectile::Projectile::onScreen = onScreen;
}

float projectile::Projectile::getTimeToLive() const{
    return timeToLive;
}

void projectile::Projectile::setTimeToLive(float ttl){
    timeToLive = ttl;
}

glm::vec2 projectile::Projectile::getMovementVector() const {
    return movementVector;
}

void projectile::Projectile::setMovementVector(glm::vec2 movementVector) {
    projectile::Projectile::movementVector = movementVector;
}
