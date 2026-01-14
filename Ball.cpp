#include "Ball.h"
#include <cmath> // Obavezno za std::abs

Ball::Ball(float startX, float startY) {
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(startX, startY);
    velocity = { 6.0f, -6.0f }; //brzina
}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Ball::update() {
    shape.move(velocity);
    // Odbijanje od zidova ekrana
    if (shape.getPosition().x <= 0) {
        velocity.x = std::abs(velocity.x);
    }
    else if (shape.getPosition().x >= 800 - (2 * radius)) {
        velocity.x = -std::abs(velocity.x);
    }
    if (shape.getPosition().y <= 0) {
        velocity.y = std::abs(velocity.y);
    }
}

void Ball::bounceOffPaddle(float paddleCenterX) {
    float ballCenterX = shape.getPosition().x + radius;
    float diff = ballCenterX - paddleCenterX;
    velocity.x = diff * 0.2f;
    velocity.y = -std::abs(velocity.y);
}

void Ball::bounce(sf::FloatRect blockBounds) {
    sf::FloatRect ballBounds = shape.getGlobalBounds();
    sf::FloatRect overlap;

    // SFML funkcija koja raèuna toèno podruèje preklapanja
    if (ballBounds.intersects(blockBounds, overlap)) {
        // Ako je širina preklapanja veæa od visine -> udarac je odozgo ili odozdo
        if (overlap.width > overlap.height) {
            velocity.y = -velocity.y;
            // Trenutno izbacivanje loptice iz cigle da je ne "pojede"
            if (ballBounds.top < blockBounds.top)
                shape.setPosition(shape.getPosition().x, blockBounds.top - ballBounds.height);
            else
                shape.setPosition(shape.getPosition().x, blockBounds.top + blockBounds.height);
        }
        // Inaèe je boèni udarac
        else {
            velocity.x = -velocity.x;
            if (ballBounds.left < blockBounds.left)
                shape.setPosition(blockBounds.left - ballBounds.width, shape.getPosition().y);
            else
                shape.setPosition(blockBounds.left + blockBounds.width, shape.getPosition().y);
        }
    }
}
//Ubrzanje loptice 
void Ball::speedUp() { velocity *= 1.01f; }
sf::FloatRect Ball::getBounds() { return shape.getGlobalBounds(); }
bool Ball::isLost() { return shape.getPosition().y > 600; }
void Ball::reset(float x, float y) { shape.setPosition(x, y); velocity = { 6.0f, -6.0f }; }