#include "Paddle.h"

Paddle::Paddle(float startX, float startY) {
    shape.setSize(sf::Vector2f(100.0f, 15.0f));
    shape.setFillColor(sf::Color::Cyan);
    shape.setPosition(startX, startY);
}
void Paddle::draw(sf::RenderWindow& window) { window.draw(shape); }
void Paddle::moveLeft() { if (shape.getPosition().x > 0) shape.move(-speed, 0); }
void Paddle::moveRight() { if (shape.getPosition().x < 800 - 100) shape.move(speed, 0); }
sf::FloatRect Paddle::getBounds() { return shape.getGlobalBounds(); }
float Paddle::getCenterX() { return shape.getPosition().x + 50.0f; }
void Paddle::setPosition(float x, float y) { shape.setPosition(x, y); }