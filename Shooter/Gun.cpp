#include "Gun.hpp"

Gun::Gun(GunType type) : type(type), lastShotTime(0.0f) {
    initializeProperties();
}

void Gun::shoot(sf::Vector2f position, sf::Vector2f direction) {
    float currentTime = /* method to get current time */;
    if (currentTime - lastShotTime >= 1.0f / fireRate) {
        // Create a new bullet
        Bullet bullet(position.x, position.y, direction * bulletSpeed);
        // Add bullet to a list or manage it for rendering and updates

        lastShotTime = currentTime;
        // Additional logic for ammo count and reloading if needed
    }
}

void Gun::update(float deltaTime) {
    // Implement any necessary update logic, like reloading
}

void Gun::initializeProperties() {
    switch (type) {
    case Pistol:
        fireRate = 2.0f; // Example: 2 shots per second
        bulletSpeed = 500.0f; // Example speed
        bulletDamage = 10.0f; // Example damage
        magazineSize = 12; // Example magazine size
        break;
    case AssaultRifle:
        // Initialize properties specific to Assault Rifle
        break;
    case LMG:
        // Initialize properties specific to LMG
        break;
        // ... other gun types ...
    }
}
