#include "tank.h"

healthBar::HealthBar::HealthBar() = default;

healthBar::HealthBar::~HealthBar() = default;

healthBar::HealthBar *healthBar::HealthBar::CreateHealthBarModel(const std::string &name, glm::vec3 leftBottomCorner,
        const glm::vec3 &health_bar_colour) {
    HealthBar *healthBar = new HealthBar();

    // Contour
    healthBar->healthBarParts.push_back(objects::CreateSquare(name + "_contour", leftBottomCorner, HEALTH_BAR_HEIGHT, health_bar_colour, false));
    // Health fill
    healthBar->healthBarParts.push_back(objects::CreateSquare(name + "_fill", leftBottomCorner, HEALTH_BAR_HEIGHT, health_bar_colour, true));

    healthBar->setHealth(100);

    return healthBar;
}

float healthBar::HealthBar::getHealth() const
{
    return health;
}

void healthBar::HealthBar::setHealth(float health) {
    this->health = health;
}

glm::vec2 healthBar::HealthBar::getCenterPosition() const
{
    return centerPosition;
}

void healthBar::HealthBar::setCenterPosition(float x, float y) {
    centerPosition = glm::vec2(x, y);
}

std::vector<Mesh *> healthBar::HealthBar::getHealthBarParts() const{
    return healthBarParts;
}
