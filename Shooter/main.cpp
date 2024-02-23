#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include "player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Package.hpp"

sf::Clock randclock;

float bulletFirerate{500};

int score{ 0 };
int regularScore{ 25 };
int speedyScore{ 50 };
int tankyScore{ 50 };
int bossScore{ 75 };


int random_int(int min, int max) {
    std::srand(std::time(nullptr) + randclock.getElapsedTime().asMicroseconds());
    return min + std::rand() % (max - min + 1);
}






bool Reload(long long Time) {

    if (bulletFirerate <= Time) {
        return true;
    }
    else {
        return false;
    }
}

int WinMain() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Shooter");
    window.setFramerateLimit(60);
    Player player(400, 300);
    std::vector<Bullet> bullets{};
    std::vector<Package> packages{};
    bool paused{false};
    sf::Clock clocka;
    int waveElapse{};
    sf::Font font;
    sf::Clock packageClock;
    if (font.loadFromFile("resources/Orbitron-Regular.ttf")) {
        std::ofstream error;
        error.open("error.txt");
        error << "Font importing error - File does not exist (Orbitron.tff)";
        error.close();
        throw std::runtime_error("Font importing error");
    }
    sf::Text scoreDisplay;
    scoreDisplay.setFont(font);
    scoreDisplay.setCharacterSize(24);
    scoreDisplay.setString("MEOW IS LIKE SO COOL AND ALL AND OYU MIGHT AKSDWAKSJDWAKSDKWA");
    scoreDisplay.setPosition(100, 100);
    scoreDisplay.setFillColor(sf::Color::White);
    
    sf::Clock clock;
    sf::Clock clockBullets;
    std::vector<Enemy> enemies;
    sf::Clock enemySpawnClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (!window.hasFocus()) {
            continue;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || paused) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !paused) {
                paused = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                paused = false;
            }
            continue;
        }
        float deltaTime = clock.restart().asSeconds(); // Used for syncing

        if (player.isDead()) {
            // Handle player death
            // For example, break out of the loop to end the game
            break;
        }


        player.update(deltaTime);

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f playerPos = player.getShape().getPosition();

        sf::Vector2f direction = sf::Vector2f(mousePos.x - playerPos.x, mousePos.y - playerPos.y);
        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= magnitude; // Normalize the direction vector

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && Reload(clockBullets.getElapsedTime().asMilliseconds())) {
            bullets.push_back(Bullet(playerPos.x + 25, playerPos.y + 25, direction)); // Adjust bullet spawn position if needed
            clockBullets.restart();
        }


        waveElapse = clocka.getElapsedTime().asMilliseconds() / 100000;
        


        // In game loop
        if (waveElapse <= 4.9f) {
            if (enemySpawnClock.getElapsedTime().asSeconds() > 5.0f - waveElapse) { // Spawn an enemy every 5 seconds deducted by how long the game is open
                // Spawn at random x, top of the screen
                // Randomizes the enemies according to a rarity set
                int random{ random_int(0, 100) };
                if (random <= 40)
                    enemies.push_back(Enemy(rand() % window.getSize().x, 0, Enemy::Regular));
                else if (random <= 60)
                    enemies.push_back(Enemy(rand() % window.getSize().x, 0, Enemy::Speedy));
                else if (random <= 75)
                    enemies.push_back(Enemy(rand() % window.getSize().x, 0, Enemy::Tanky));
                else if (random <= 90)
                    enemies.push_back(Enemy(rand() % window.getSize().x, 0, Enemy::MiniBoss));
                else if (random <= 95)
                    enemies.push_back(Enemy(rand() % window.getSize().x, 0, Enemy::SpeedDemon));
                else if (random <= 100)
                    enemies.push_back(Enemy(rand() % window.getSize().x, 0, Enemy::MegaBoss));
                else
                    enemies.push_back(Enemy(rand() % window.getSize().x, 0, Enemy::CURSED));

                enemySpawnClock.restart();
            }
        }
        else {
            if (enemySpawnClock.getElapsedTime().asSeconds() > 0.1f) { // Spawn an enemy every tenth of a second
                // Spawn at random x, top of the screen
                // Randomizes the enemies according to a rarity set
                int random{ random_int(0, 100) };
                if (random <= 40)
                    enemies.push_back(Enemy(rand() % window.getSize().x, 0, Enemy::Regular));
                else if (random <= 60)
                    enemies.push_back(Enemy(rand() % window.getSize().x, 0, Enemy::Speedy));
                else if (random <= 75)
                    enemies.push_back(Enemy(rand() % window.getSize().x, 0, Enemy::Tanky));
                else if (random <= 90)
                    enemies.push_back(Enemy(rand() % window.getSize().x, 0, Enemy::MiniBoss));
                else if (random <= 95)
                    enemies.push_back(Enemy(rand() % window.getSize().x, 0, Enemy::SpeedDemon));
                //else if (random <= 100)
                    //enemies.push_back(Enemy(rand() % window.getSize().x, 0, Enemy::MegaBoss));
                else
                    enemies.push_back(Enemy(rand() % window.getSize().x, 0, Enemy::CURSED));

                enemySpawnClock.restart();
            }
        }

        window.clear(sf::Color::Color(0, 77, 13));


        for (auto& enemy : enemies) {
            enemy.update(deltaTime, player.getShape().getPosition());

            // Check for collision with player
            if (enemy.getShape().getGlobalBounds().intersects(player.getShape().getGlobalBounds())) {
                player.takeDamage(10.0f); // Example damage amount
            }

            window.draw(enemy.getShape());
        }
        // Remove dead enemies and used bullets
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& enemy) {
            if (enemy.isDead() && enemy.getType() == Enemy::Regular)
                score += regularScore;
            else if (enemy.isDead() && enemy.getType() == Enemy::Speedy)
                score += speedyScore;
            else if (enemy.isDead() && enemy.getType() == Enemy::Tanky)
                score += tankyScore;
            else if (enemy.isDead() && enemy.getType() == Enemy::MiniBoss)
                score += bossScore;
            else if (enemy.isDead() && enemy.getType() == Enemy::MegaBoss)
                score += bossScore * 3;
            else if (enemy.isDead() && enemy.getType() == Enemy::SpeedDemon)
                score += speedyScore * 3;
            else if (enemy.isDead())
                score -= -10000000000;
            return enemy.isDead();
            }), enemies.end());

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet) {
            return bullet.shouldBeRemoved();
            }), bullets.end());

        // Optional: Remove off-screen enemies
        //enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&window](const Enemy& e) {
        //    return e.shape.getPosition().y > window.getSize().y;
        //    }), enemies.end());

        // Rendering
        window.clear(sf::Color::Color(0, 77, 13));

        // Draw Enemies
        for (auto& enemy : enemies) {
            enemy.update(deltaTime, player.getShape().getPosition());

            // Check for collision with player
            if (enemy.getShape().getGlobalBounds().intersects(player.getShape().getGlobalBounds())) {
                player.takeDamage(10.0f); // Example damage amount
            }

            window.draw(enemy.getShape());
        }

        if (packageClock.getElapsedTime().asSeconds() >= 10.0f - waveElapse) {
            packages.push_back(Package(Package::Health, rand() % window.getSize().x, rand() % window.getSize().y));
            packageClock.restart();
        }

        for (auto& package : packages) {
            if (player.getShape().getGlobalBounds().intersects(package.getShape().getGlobalBounds())) {
                package.applyEffect(player); // This method will also mark the package for removal
            }
        }

        // Remove used packages
        packages.erase(
            std::remove_if(packages.begin(), packages.end(),
                [](const Package& p) { return p.shouldBeRemoved(); }),
            packages.end());


        for (auto& bullet : bullets) {
            bullet.update(deltaTime);
            window.draw(bullet.getShape());
        }


        for (auto& package : packages) {
            window.draw(package.getShape());
        }

        // Handle Bullet-Enemy Collisions
        for (auto& bullet : bullets) {
            for (auto& enemy : enemies) {
                if (bullet.getShape().getGlobalBounds().intersects(enemy.getShape().getGlobalBounds())) {
                    enemy.takeDamage(20.0f); // Example damage value
                    bullet.hit(); // Mark the bullet for removal
                }
            }
        }

            window.draw(player.getShape());
            window.draw(scoreDisplay);
            window.display();
        }
        // Saves score in file 'score.txt'
        std::ofstream myfile;
        myfile.open("score.txt");
        myfile << "Score: " << score;
        myfile.close(); 
    

    return 0;
}