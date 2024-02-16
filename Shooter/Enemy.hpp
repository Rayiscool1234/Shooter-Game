#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

class Enemy {
public:
    enum EnemyType { Regular, Speedy, Tanky, MiniBoss, MegaBoss, SpeedDemon, CURSED };

    Enemy(float x, float y, EnemyType type = Regular);

    void takeDamage(float damage);
    bool isDead() const;
    void update(float deltaTime, sf::Vector2f playerPosition);

    const sf::RectangleShape& getShape() const;
    EnemyType getType() const;

private:
    sf::RectangleShape shape;
    float speed;
    float health;
    EnemyType type;

    void initializeShape(Enemy::EnemyType typeOfEnemy);
    void updateMovement(float deltaTime, sf::Vector2f playerPosition);
};

#endif // ENEMY_HPP
