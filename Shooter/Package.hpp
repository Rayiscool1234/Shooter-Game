#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include <SFML/Graphics.hpp>
#include "Player.hpp" // Include the Player class for applying package effects

class Package {
public:
    enum PackageType { Health, SpeedBoost, Shield, Firepower };

    Package(PackageType type, float x, float y);

    void applyEffect(Player& player); // Method to apply the package's effect
    bool shouldBeRemoved() const;
    const sf::CircleShape& getShape() const;

private:
    sf::CircleShape shape;
    PackageType type;
    bool toBeRemoved;

    void initializeShape();
};

#endif // PACKAGE_HPP