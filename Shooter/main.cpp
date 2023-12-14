#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>



float bulletFirerate{500};






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
    float stamina{ 10.0f }; // stamina points
    bool isrunning{ false };
    Player(float x, float y) {
        shape.setSize(sf::Vector2f(50.0f, 50.0f));
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(x, y);
    }

    void update(float deltaTime) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) shape.move(0, -speed * deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) shape.move(0, speed * deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) shape.move(-speed * deltaTime, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) shape.move(speed * deltaTime, 0);
        if ( stamina != 0.0 && !isrunning && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) { speed = speed * 2; isrunning = true; }
        else { speed = 250.0f; isrunning = false; }
    }
};

class Enemy {
public:
    sf::RectangleShape shape;
    float speed = 100.0f; // Adjust the speed as needed

    Enemy(float x, float y) {
        shape.setSize(sf::Vector2f(40.0f, 40.0f)); // Size of the enemy
        shape.setFillColor(sf::Color::Blue); // Color of the enemy
        shape.setPosition(x, y);
    }

    void update(float deltaTime) {
        // Example behavior: move down the screen
        shape.move(0, speed * deltaTime);
    }
};


class Bullet {
public:
    sf::RectangleShape shape;
    float speed = 1000.0f; // Speed of the bullet
    sf::Vector2f direction;

    Bullet(float x, float y, sf::Vector2f dir) : direction(dir) {
        shape.setSize(sf::Vector2f(10.0f, 5.0f));
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(x, y);

        // Calculate rotation
        float rotation = static_cast<float>(atan2(direction.y, direction.x) * 180 / 3.14159265);
        shape.setRotation(rotation);
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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && Reload(clockBullets.getElapsedTime().asMilliseconds())) {
            bullets.push_back(Bullet(playerPos.x + 25, playerPos.y + 25, direction)); // Adjust bullet spawn position if needed
            clockBullets.restart();
        }

        std::vector<Enemy> enemies;
        sf::Clock enemySpawnClock;

        // In your game loop
        if (enemySpawnClock.getElapsedTime().asSeconds() > 1.0f) { // Spawn an enemy every second
            enemies.push_back(Enemy(rand() % window.getSize().x, 0)); // Spawn at random x, top of the screen
            enemySpawnClock.restart();
        }


        window.clear(sf::Color::Color(0, 77, 13));

        // In your game loop
        for (auto& enemy : enemies) {
            enemy.update(deltaTime);
            window.draw(enemy.shape);
        }

        // Optional: Remove off-screen enemies
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&window](const Enemy& e) {
            return e.shape.getPosition().y > window.getSize().y;
            }), enemies.end());


        for (auto& bullet : bullets) {
            bullet.update(deltaTime);
            window.draw(bullet.shape);
        }

        window.draw(player.shape);

        window.display();
    }

    return 0;
}