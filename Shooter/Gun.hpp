#ifndef GUN_HPP
#define GUN_HPP

#include <SFML/Graphics.hpp>
#include "Bullet.hpp" // Assuming Bullet class is used for shooting

class Gun {
public:
    enum GunType { Pistol, AssaultRifle, LMG, SniperRifle, Shotgun, Turret };

    Gun(GunType type);

    void shoot(sf::Vector2f position, sf::Vector2f direction);
    void update(float deltaTime);

private:
    GunType type;
    float fireRate;
    int magazineSize;
    float bulletSpeed;
    float bulletDamage;
    float lastShotTime;
    // Additional properties like reload time

    void initializeProperties();
};

#endif // GUN_HPP
