#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

sf::Clock randclock;

float bulletFirerate{500};

int score{ 0 };
int regularScore{ 25 };
int speedyScore{ 50 };
int tankyScore{ 50 };
int bossScore{ 75 };

/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// 


int random_int(int min, int max) {
    std::srand(std::time(nullptr) + randclock.getElapsedTime().asMicroseconds());
    return min + std::rand() % (max - min + 1);
}

/*

void ExtractResource(const std::wstring& resourceName, const std::wstring& outputFilePath) {
    HRSRC resourceHandle = FindResource(nullptr, resourceName.c_str(), RT_RCDATA);
    if (!resourceHandle) {
        throw std::runtime_error("Failed to find resource.");
    }

    HGLOBAL resourceDataHandle = LoadResource(nullptr, resourceHandle);
    if (!resourceDataHandle) {
        throw std::runtime_error("Failed to load resource.");
    }

    void* pResourceData = LockResource(resourceDataHandle);
    DWORD resourceSize = SizeofResource(nullptr, resourceHandle);

    std::ofstream ofs(outputFilePath, std::ios::binary);
    ofs.write(static_cast<char*>(pResourceData), resourceSize);
    ofs.close();
}SSSSSSSSSSS

*/


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
    float normalSpeed{ 250.0f }; // Normal speed in pixels per second
    float sprintSpeed{ 500.0f }; // Sprint speed
    float speed{ normalSpeed };
    float stamina{ 10.0f }; // Stamina points
    float staminaCooldown{ 5.0f }; // Cooldown for stamina regeneration
    bool isrunning{ false };
    float health{ 1000.0f }; // Player's health
    float speedNegator{ 150.0f };
    bool godmode{ false };

    Player(float x, float y) {
        shape.setSize(sf::Vector2f(50.0f, 50.0f));
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(x, y);
    }
    void takeDamage(float damageAmount) {
        health -= damageAmount;
        if (health <= 0) {
            // Handle player death, like game over
        }
    }


    bool isDead() const {
        return health <= 0;
    }

    void update(float deltaTime) {
        // Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) shape.move(0, -speed * deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) shape.move(0, speed * deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) shape.move(-speed * deltaTime, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) shape.move(speed * deltaTime, 0);

        // Sprinting logic
        if ((stamina > 0.0f) && !isrunning && (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))) {
            speed = sprintSpeed;
            isrunning = true;
            stamina -= deltaTime; // Decrease stamina while running
        }
        else {
            speed = normalSpeed;
            isrunning = false;
            if (staminaCooldown <= 0) {
                stamina = std::min(stamina + deltaTime, 10.0f); // Regenerate stamina
            }
            else {
                staminaCooldown -= deltaTime; // Cooldown for stamina regeneration
            }
        }
        
        if (health < 1000) {

            if (normalSpeed >= 50) {
                normalSpeed = (health / 4) - speedNegator;
                sprintSpeed = (health / 4) - speedNegator * 0.5;
            }
        }

        if (godmode) {
            if (health <= 20)
                health = 50;
        }

    }
};


/// <summary>
/// This is the enemy class, allows creation of enemies and types of such enemies. 
/// 
/// 
/// </summary>
class Enemy {
public:
    sf::RectangleShape shape;
    float speed{ 25.0f }; // Adjust the speed as needed
    float health{ 50.0f }; // Example health value
    enum EnemyType {Regular, Speedy, Tanky, MiniBoss, MegaBoss, SpeedDemon, CURSED};
    EnemyType Type{};

    // Converts enemy into any available type.
    void convertEnemy(EnemyType typeOfEnemy = CURSED) {
        switch (typeOfEnemy) {
        case Regular:
            break;
        case Speedy:
            speed = 50.0f;
            shape.setFillColor(sf::Color::Color(51, 255, 187));
            break;
        case Tanky:
            speed = 10.0f;
            health = 75.0f;
            shape.setFillColor(sf::Color::Color(0, 204, 34));
            break;
        case MiniBoss:
            speed = 50.0f;
            health = 75.0f;
            shape.setFillColor(sf::Color::Color(0, 77, 50));
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
            break;
        default:
            throw new std::runtime_error("Illegal enemy type");
            break;
        }
    }
    

    Enemy(float x, float y, EnemyType typeOfEnemy = Regular) {
        
        Type = typeOfEnemy;
        shape.setOutlineColor(sf::Color::Red);
        shape.setSize(sf::Vector2f(40.0f, 40.0f)); // Size of the enemy
        convertEnemy(typeOfEnemy);
        
        if (typeOfEnemy == Regular) {
            
            shape.setFillColor(sf::Color::Green); // Color of the enemy
        }
        shape.setPosition(x, y);
        
    }
    void takeDamage(float damage) {
        health -= damage;
    }

    EnemyType Enemytype() const {
        return Type;
    }

    bool isDead() const {
        return health <= 0;
    }

    void update(float deltaTime, sf::Vector2f playerPosition) {
        sf::Vector2f movementDirection = playerPosition - shape.getPosition();
        float distance = std::sqrt(movementDirection.x * movementDirection.x + movementDirection.y * movementDirection.y);

        // Normalize the movement vector and update the position
        if (distance > 0) {
            movementDirection /= distance;
            shape.move(movementDirection * speed * deltaTime);
        }
    }
};



class Bullet {
public:
    sf::RectangleShape shape;
    float speed = 1000.0f; // Speed of the bullet
    sf::Vector2f direction;
    bool toBeRemoved{ false };

    Bullet(float x, float y, sf::Vector2f dir) : direction(dir) {
        shape.setSize(sf::Vector2f(10.0f, 5.0f));
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(x, y);

        // Calculate rotation
        float rotation = static_cast<float>(atan2(direction.y, direction.x) * 180 / 3.14159265);
        shape.setRotation(rotation);
    }



    // Call this method when a bullet hits an enemy
    void hit() {
        toBeRemoved = true;
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
    sf::RenderWindow window(sf::VideoMode(800, 600), "Shooter");
    window.setFramerateLimit(60);
    Player player(400, 300);
    std::vector<Bullet> bullets;
    bool paused{false};
    sf::Clock clocka;
    int waveElapse{};
   // ExtractResource(L"ID_MYFONT", L"temp_font.ttf");

    // Load the font using SFML
    // sf::Font font;
    // if (!font.loadFromFile("temp_font.ttf")) {
        // Handle error - Failed to load font
        // return -1;
    // }
    
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
        sf::Vector2f playerPos = player.shape.getPosition();

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
            if (enemySpawnClock.getElapsedTime().asSeconds() > 5.0f - waveElapse) { // Spawn an enemy every second
                // Spawn at random x, top of the screen
                // Randomizes the enemies
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
                // Randomizes the enemies
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

        window.clear(sf::Color::Color(0, 77, 13));


        for (auto& enemy : enemies) {
            enemy.update(deltaTime, player.shape.getPosition());

            // Check for collision with player
            if (enemy.shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
                player.takeDamage(10.0f); // Example damage amount
            }

            window.draw(enemy.shape);
        }
        // Remove dead enemies and used bullets
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& enemy) {
            if (enemy.isDead() && enemy.Enemytype() == Enemy::Regular)
                score += regularScore;
            else if (enemy.isDead() && enemy.Enemytype() == Enemy::Speedy)
                score += speedyScore;
            else if (enemy.isDead() && enemy.Enemytype() == Enemy::Tanky)
                score += tankyScore;
            else if (enemy.isDead() && enemy.Enemytype() == Enemy::MiniBoss)
                score += bossScore;
            else if (enemy.isDead() && enemy.Enemytype() == Enemy::MegaBoss)
                score += bossScore * 3;
            else if (enemy.isDead() && enemy.Enemytype() == Enemy::SpeedDemon)
                score += speedyScore * 3;
            else if (enemy.isDead())
                score -= -10000000000;
            return enemy.isDead();
            }), enemies.end());

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet) {
            return bullet.toBeRemoved;
            }), bullets.end());

        // Optional: Remove off-screen enemies
        //enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&window](const Enemy& e) {
        //    return e.shape.getPosition().y > window.getSize().y;
        //    }), enemies.end());

        // Rendering
        window.clear(sf::Color::Color(0, 77, 13));

        // Draw Enemies
        for (auto& enemy : enemies) {
            enemy.update(deltaTime, player.shape.getPosition());

            // Check for collision with player
            if (enemy.shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
                player.takeDamage(10.0f); // Example damage amount
            }

            window.draw(enemy.shape);
        }


        for (auto& bullet : bullets) {
            bullet.update(deltaTime);
            window.draw(bullet.shape);
        }

        // Handle Bullet-Enemy Collisions
        for (auto& bullet : bullets) {
            for (auto& enemy : enemies) {
                if (bullet.shape.getGlobalBounds().intersects(enemy.shape.getGlobalBounds())) {
                    enemy.takeDamage(20.0f); // Example damage value
                    bullet.hit(); // Mark the bullet for removal
                }
            }
        }

            window.draw(player.shape);

            window.display();
        }
        // Saves score in file 'score.txt'
        std::ofstream myfile;
        myfile.open("score.txt");
        myfile << "Score: " << score;
        myfile.close(); 
    

    return 0;
}