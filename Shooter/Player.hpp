#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player {
public:
    Player(float x, float y);

    void takeDamage(float damageAmount);
    bool isDead() const;
    void update(float deltaTime);

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

    void handleMovement(float deltaTime);
    void handleSprinting(float deltaTime);
    void handleSpeed();
};

#endif // PLAYER_HPP
