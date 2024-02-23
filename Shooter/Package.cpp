#include "Package.hpp"

Package::Package(PackageType type, float x, float y)
    : type(type), toBeRemoved(false) {
    initializeShape();
    shape.setPosition(x, y);
}

void Package::applyEffect(Player& player) {
    switch (type) {
    case Health:
        player.increaseHealth(250); // Example: increase player's health
        break;
    case SpeedBoost:
        // player.setSpeedBoost(true); // Example: set player's speed boost flag
        break;
    case Shield:
        // player.activateShield(true); // Example: activate player's shield
        break;
    case Firepower:
        // player.upgradeFirepower(); // Example: upgrade player's firepower
        break;
    }
    toBeRemoved = true;
}

bool Package::shouldBeRemoved() const {
    return toBeRemoved;
}

const sf::CircleShape& Package::getShape() const {
    return shape;
}

void Package::initializeShape() {
    shape.setRadius(20.0f); // Example radius
    switch (type) {
    case Health:
        shape.setFillColor(sf::Color::Red);
        break;
    case SpeedBoost:
        shape.setFillColor(sf::Color::Blue);
        break;
    case Shield:
        shape.setFillColor(sf::Color::Green);
        break;
    case Firepower:
        shape.setFillColor(sf::Color::Yellow);
        break;
    }
}
