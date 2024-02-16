#include "Bullet.hpp"
#include <cmath> // For math operations if needed

Bullet::Bullet(float x, float y, sf::Vector2f dir)
    : direction(dir), speed(1000.0f), toBeRemoved(false) {
    initializeShape();
    shape.setPosition(x, y);

    float rotation = std::atan2(direction.y, direction.x) * 180.0f / static_cast<float>(M_PI);
    shape.setRotation(rotation);
}

void Bullet::update(float deltaTime) {
    shape.move(direction * speed * deltaTime);
}

void Bullet::hit() {
    toBeRemoved = true;
}

bool Bullet::shouldBeRemoved() const {
    return toBeRemoved;
}

const sf::RectangleShape& Bullet::getShape() const {
    return shape;
}

void Bullet::initializeShape() {
    shape.setSize(sf::Vector2f(10.0f, 5.0f));
    shape.setFillColor(sf::Color::Yellow);
}
