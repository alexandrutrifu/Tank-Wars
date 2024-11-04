#include "projectile.h"

const glm::vec3 projectile_colour = glm::vec3(0.0, 0.0, 0.0);
const glm::vec3 projectile_inactive_position = glm::vec3(-1, -1, 0);

projectile::Projectile::Projectile() = default;

projectile::Projectile::~Projectile() = default;

projectile::Projectile *projectile::Projectile::CreateProjectileModel(const std::string &name) {
    projectile::Projectile *projectile = new projectile::Projectile();

    projectile->projectileModel = objects::CreateDisk(name, 5, 100,
        projectile_inactive_position, glm::vec3(0.0, 0.0, 0.0), true);
    projectile->onScreen = false;

    return projectile;
}

Mesh *projectile::Projectile::getProjectileModel() const{
    return projectileModel;
}

bool projectile::Projectile::isOnScreen() const {
    return onScreen;
}

void projectile::Projectile::setOnScreen(bool onScreen) {
    projectile::Projectile::onScreen = onScreen;
}
