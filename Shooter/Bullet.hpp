#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(float x, float y, sf::Vector2f dir);

    void update(float deltaTime);
    void hit(); // Method to call when bullet hits a target
    bool shouldBeRemoved() const;
    const sf::RectangleShape& getShape() const;

private:
    sf::RectangleShape shape;
    sf::Vector2f direction;
    float speed;
    bool toBeRemoved;

    void initializeShape();
};

#endif // BULLET_HPP
