#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>



float bulletFirerate{100};






/// \brief Player Controller
/// 
/// This class has a premade character and controls along side it
///
/// 
/// 
/// 
class Player {
public:
    sf::RectangleShape shape;
    float speed{ 250.0f }; // Speed in pixels per second
    Player(float x, float y) {
        shape.setSize(sf::Vector2f(50.0f, 50.0f));
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(x, y);
    }

    void update(float deltaTime) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) shape.move(0, -speed * deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) shape.move(0, speed * deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) shape.move(-speed * deltaTime, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) shape.move(speed * deltaTime, 0);
    }
};


class Bullet {
public:
    sf::RectangleShape shape;
    float speed = 500.0f; // Adjust bullet speed as needed
    sf::Vector2f direction;

    Bullet(float x, float y, sf::Vector2f dir) : direction(dir) {
        shape.setSize(sf::Vector2f(10.0f, 5.0f));
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(x, y);
    }

    void update(float deltaTime) {
        shape.move(direction * speed * deltaTime);
    }
};

bool Reload(long long Time) {

    if (bulletFirerate <= Time) {
        return true;
    }
    else {
        return false;
    }
}

int WinMain() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Shooter Game");
    window.setFramerateLimit(60);
    Player player(400, 300);
    std::vector<Bullet> bullets;

    sf::Clock clock;
    sf::Clock clockBullets;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds(); // Used for syncing

        

        player.update(deltaTime);

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f playerPos = player.shape.getPosition();
        sf::Vector2f direction = sf::Vector2f(mousePos.x - playerPos.x, mousePos.y - playerPos.y);

        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= magnitude; // Normalize the direction vector

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && Reload(clockBullets.restart().asMilliseconds())) {
            bullets.push_back(Bullet(playerPos.x + 25, playerPos.y + 25, direction)); // Adjust bullet spawn position if needed
        }

        window.clear(sf::Color::Color(0, 77, 13));

        for (auto& bullet : bullets) {
            bullet.update(deltaTime);
            window.draw(bullet.shape);
        }

        window.draw(player.shape);

        window.display();
    }

    return 0;
}