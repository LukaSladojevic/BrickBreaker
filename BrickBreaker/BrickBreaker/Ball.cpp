#include "Ball.h"
#include <cmath> 

// [1] KONSTRUKTOR: Inicijalizacija objekta.
// Ovdje postavljamo žutu boju i poèetnu brzinu (velocity). 
// Negativna vrijednost (-6.0f) na Y osi znaèi da loptica odmah leti PREMA GORE.
Ball::Ball(float startX, float startY) {
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(startX, startY);
    velocity = { 6.0f, -6.0f };
}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

// [2] UPDATE METODA: Osnovna fizika kretanja.
// shape.move(velocity) pomièe lopticu u svakom frameu. 
// std::abs koristimo da budemo sigurni da æe se loptica odbiti u pravom smjeru bez obzira na greške u koordinatama.
void Ball::update() {
    shape.move(velocity);
    if (shape.getPosition().x <= 0) {
        velocity.x = std::abs(velocity.x); // Odbijanje od lijevog zida
    }
    else if (shape.getPosition().x >= 800 - (2 * radius)) {
        velocity.x = -std::abs(velocity.x); // Odbijanje od desnog zida
    }
    if (shape.getPosition().y <= 0) {
        velocity.y = std::abs(velocity.y); // Odbijanje od plafona
    }
}

// [3] BOUNCE OFF PADDLE: Dinamièki kut odbijanja.
// Ovdje raèunamo razliku (diff) izmeðu sredine loptice i sredine palice. 
// Ako loptica udari u rub palice, odbit æe se pod oštrim kutom. To daje igraèu kontrolu.
void Ball::bounceOffPaddle(float paddleCenterX) {
    float ballCenterX = shape.getPosition().x + radius;
    float diff = ballCenterX - paddleCenterX;
    velocity.x = diff * 0.2f;
    velocity.y = -std::abs(velocity.y);
}

// [4] BOUNCE BRICK (AABB Logika): Detekcija i rješavanje sudara.
// overlap.width > overlap.height provjerava jesmo li ciglu udarili odozgo/odozdo ili sa strane.
// shape.setPosition je kljuèan jer on "izbacuje" lopticu van cigle da se ne dogodi dupli sudar.
void Ball::bounce(sf::FloatRect blockBounds) {
    sf::FloatRect ballBounds = shape.getGlobalBounds();
    sf::FloatRect overlap;

    if (ballBounds.intersects(blockBounds, overlap)) {
        if (overlap.width > overlap.height) {
            velocity.y = -velocity.y;
            if (ballBounds.top < blockBounds.top)
                shape.setPosition(shape.getPosition().x, blockBounds.top - ballBounds.height);
            else
                shape.setPosition(shape.getPosition().x, blockBounds.top + blockBounds.height);
        }
        else {
            velocity.x = -velocity.x;
            if (ballBounds.left < blockBounds.left)
                shape.setPosition(blockBounds.left - ballBounds.width, shape.getPosition().y);
            else
                shape.setPosition(blockBounds.left + blockBounds.width, shape.getPosition().y);
        }
    }
}

// [5] POMOÆNE METODE:
// speedUp poveæava brzinu za 1% nakon svake cigle, èime igra postaje sve teža.
// isLost provjerava granicu od 600 piksela (dno ekrana).
void Ball::speedUp() { velocity *= 1.01f; }
sf::FloatRect Ball::getBounds() { return shape.getGlobalBounds(); }
bool Ball::isLost() { return shape.getPosition().y > 600; }
void Ball::reset(float x, float y) { shape.setPosition(x, y); velocity = { 6.0f, -6.0f }; }