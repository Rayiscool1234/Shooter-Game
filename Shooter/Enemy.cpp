#include "Enemy.hpp"
#include <cmath> // For std::sqrt and other mathematical operations

Enemy::Enemy(float x, float y, EnemyType type)
    : type(type), speed(25.0f), health(50.0f) {
    initializeShape(type);
    shape.setPosition(x, y);
}

void Enemy::takeDamage(float damage) {
    health -= damage;
}

bool Enemy::isDead() const {
    return health <= 0;
}

void Enemy::update(float deltaTime, sf::Vector2f playerPosition) {
    updateMovement(deltaTime, playerPosition);
}

const sf::RectangleShape& Enemy::getShape() const {
    return shape;
}

Enemy::EnemyType Enemy::getType() const {
    return type;
}

void Enemy::initializeShape(Enemy::EnemyType typeOfEnemy) {
    switch (typeOfEnemy) {
    case Regular:
        shape.setFillColor(sf::Color::Green);
        shape.setSize(sf::Vector2f(45.0f, 45.0f));
        break;
    case Speedy:
        speed = 50.0f;
        shape.setFillColor(sf::Color::Color(51, 255, 187));
        shape.setSize(sf::Vector2f(45.0f, 45.0f));
        break;
    case Tanky:
        speed = 10.0f;
        health = 75.0f;
        shape.setFillColor(sf::Color::Color(0, 204, 34));
        break;
        shape.setSize(sf::Vector2f(45.0f, 45.0f));
    case MiniBoss:
        speed = 50.0f;
        health = 75.0f;
        shape.setFillColor(sf::Color::Color(0, 77, 50));
        shape.setSize(sf::Vector2f(45.0f, 45.0f));
        break;
    case MegaBoss:
        speed = 75.0f;
        health = 125.0f;
        shape.setFillColor(sf::Color::Color(0, 77, 50));
        shape.setSize(sf::Vector2f(60.0f, 60.0f));
        break;
    case SpeedDemon:
        speed = 270.0f;
        health = 5.0f;
        shape.setFillColor(sf::Color::Color(255, 255, 255));
        shape.setSize(sf::Vector2f(45.0f, 45.0f));
        break;
    default:
        throw new std::runtime_error("Illegal enemy type");
        break;
    }
}

void Enemy::updateMovement(float deltaTime, sf::Vector2f playerPosition) {
    // Update the enemy's position and movement behavior
    sf::Vector2f movementDirection = playerPosition - shape.getPosition();
    float distance = std::sqrt(movementDirection.x * movementDirection.x + movementDirection.y * movementDirection.y);

    if (distance > 0) {
        movementDirection /= distance;
        shape.move(movementDirection * speed * deltaTime);
    }
}


/// <summary>
/// This is the enemy class, allows creation of enemies and types of such enemies. 
/// 
/// 
/// </summary>
//class Enemy {
//public:
//    sf::RectangleShape shape;
//    float speed{ 25.0f }; // Adjust the speed as needed
//    float health{ 50.0f }; // Example health value
//    enum EnemyType { Regular, Speedy, Tanky, MiniBoss, MegaBoss, SpeedDemon, CURSED };
//    EnemyType Type{};
//
//    // Converts enemy into any available type.
//    void convertEnemy(EnemyType typeOfEnemy = CURSED) {
//        switch (typeOfEnemy) {
//        case Regular:
//            break;
//        case Speedy:
//            speed = 50.0f;
//            shape.setFillColor(sf::Color::Color(51, 255, 187));
//            break;
//        case Tanky:
//            speed = 10.0f;
//            health = 75.0f;
//            shape.setFillColor(sf::Color::Color(0, 204, 34));
//            break;
//        case MiniBoss:
//            speed = 50.0f;
//            health = 75.0f;
//            shape.setFillColor(sf::Color::Color(0, 77, 50));
//            break;
//        case MegaBoss:
//            speed = 75.0f;
//            health = 125.0f;
//            shape.setFillColor(sf::Color::Color(0, 77, 50));
//            shape.setSize(sf::Vector2f(60.0f, 60.0f));
//            break;
//        case SpeedDemon:
//            speed = 270.0f;
//            health = 5.0f;
//            shape.setFillColor(sf::Color::Color(255, 255, 255));
//            break;
//        default:
//            throw new std::runtime_error("Illegal enemy type");
//            break;
//        }
//    }
//
//
//    Enemy(float x, float y, EnemyType typeOfEnemy = Regular) {
//
//        Type = typeOfEnemy;
//        shape.setOutlineColor(sf::Color::Red);
//        shape.setSize(sf::Vector2f(45.0f, 45.0f)); // Size of the enemy
//        convertEnemy(typeOfEnemy);
//
//        if (typeOfEnemy == Regular) {
//
//            shape.setFillColor(sf::Color::Green); // Color of the enemy
//        }
//        shape.setPosition(x, y);
//
//    }
//    void takeDamage(float damage) {
//        health -= damage;
//    }
//
//    EnemyType Enemytype() const {
//        return Type;
//    }
//
//    bool isDead() const {
//        return health <= 0;
//    }
//
//    void update(float deltaTime, sf::Vector2f playerPosition) {
//        sf::Vector2f movementDirection = playerPosition - shape.getPosition();
//        float distance = std::sqrt(movementDirection.x * movementDirection.x + movementDirection.y * movementDirection.y);
//
//        // Normalize the movement vector and update the position
//        if (distance > 0) {
//            movementDirection /= distance;
//            shape.move(movementDirection * speed * deltaTime);
//        }
//    }
//};