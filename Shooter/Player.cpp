#include "player.hpp"
#include <algorithm>

Player::Player(float x, float y)
    : normalSpeed(250.0f), sprintSpeed(500.0f), speed(normalSpeed),
    stamina(10.0f), staminaCooldown(5.0f), isRunning(false),
    health(1000.0f), speedNegator(150.0f), godMode(false) {
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
}

void Player::takeDamage(float damageAmount) {
    if (!godMode) {
        health -= damageAmount;
    }
}

void Player::equipGun(Gun* gun) {
    currentGun = gun;
}

bool Player::isDead() const {
    return health <= 0;
}

void Player::update(float deltaTime) {
    handleMovement(deltaTime);
    handleSprinting(deltaTime);
    handleSpeed();
}

const sf::RectangleShape& Player::getShape() const {
    return shape;
}

void Player::handleMovement(float deltaTime) {
    // Movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) shape.move(0, -speed * deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) shape.move(0, speed * deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) shape.move(-speed * deltaTime, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) shape.move(speed * deltaTime, 0);
}

void Player::handleSprinting(float deltaTime) {
    // Sprinting logic
    if ((stamina > 0.0f) && !isRunning && (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))) {
        speed = sprintSpeed;
        isRunning = true;
        stamina -= deltaTime; // Decrease stamina while running
    }
    else {
        speed = normalSpeed;
        isRunning = false;
        if (staminaCooldown <= 0) {
            stamina = std::min(stamina + deltaTime, 10.0f); // Regenerate stamina
        }
        else {
            staminaCooldown -= deltaTime; // Cooldown for stamina regeneration
        }
    }
}

void Player::handleSpeed() {
    // speed penalty as health lowers
    if (health < 1000) {

        if (normalSpeed >= 50) {
            normalSpeed = (health / 4) - speedNegator;
            sprintSpeed = (health / 4) - speedNegator * 0.5;
        }
    }

    if (godMode) {
        if (health <= 20)
            health = 50;
    }
}
