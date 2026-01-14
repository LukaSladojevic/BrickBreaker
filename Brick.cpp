#include "Brick.h"

Brick::Brick(float x, float y, bool isUnbreakable) : unbreakable(isUnbreakable) {
    mainShape.setSize(sf::Vector2f(70.0f, 20.0f));
    mainShape.setPosition(x, y);
    if (unbreakable) {
        mainShape.setFillColor(sf::Color::White); // Neuništive
    }
    else {
        mainShape.setFillColor(sf::Color(180, 0, 0));
        innerShape.setSize(sf::Vector2f(60.0f, 8.0f));
        innerShape.setFillColor(sf::Color(255, 60, 60));
        innerShape.setPosition(x + 5, y + 2);
    }
}
void Brick::draw(sf::RenderWindow& window) {
    if (!destroyed) {
        window.draw(mainShape);
        if (!unbreakable) window.draw(innerShape);
    }
}
bool Brick::isDestroyed() { return destroyed; }
bool Brick::isUnbreakable() { return unbreakable; }
void Brick::destroy() { if (!unbreakable) destroyed = true; }
sf::FloatRect Brick::getBounds() { return mainShape.getGlobalBounds(); }