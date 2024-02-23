#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Gun.hpp"
#include <SFML/Graphics.hpp>

class Player {
public:
    Player(float x, float y);

    void takeDamage(float damageAmount);
    bool isDead() const;
    void update(float deltaTime);
    void equipGun(Gun* gun);
    void shoot(sf::Vector2f direction);
    void increaseHealth(int healthAmount);
    // Accessor methods
    const sf::RectangleShape& getShape() const;

private:
    sf::RectangleShape shape;
    float normalSpeed;
    float sprintSpeed;
    float speed;
    float stamina;
    float staminaCooldown;
    bool isRunning;
    float health;
    float speedNegator;
    bool godMode;
    Gun* currentGun;

    void handleMovement(float deltaTime);
    void handleSprinting(float deltaTime);
    void handleSpeed();
};

#endif // PLAYER_HPP
