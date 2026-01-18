#include "Paddle.h"

// [1] KONSTRUKTOR: Postavljanje dimenzija i izgleda.
// Palica je dugaèka 100 i široka 15 piksela. Boja je Cyan (svijetlo plava) 
// kako bi se jasno razlikovala od crvenih i plavih cigli.
Paddle::Paddle(float startX, float startY) {
    shape.setSize(sf::Vector2f(100.0f, 15.0f));
    shape.setFillColor(sf::Color::Cyan);
    shape.setPosition(startX, startY);
}

// [2] CRTANJE: Standardna SFML funkcija za iscrtavanje oblika u prozor.
void Paddle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

// [3] KRETANJE S GRANICAMA: Pametno pomicanje.
// moveLeft() provjerava je li X > 0 (lijevi rub). 
// moveRight() provjerava je li X < 700 (800 širina prozora - 100 širina palice).
// Ovo sprjeèava da palica izaðe izvan ekrana.
void Paddle::moveLeft() {
    if (shape.getPosition().x > 0) shape.move(-speed, 0);
}
void Paddle::moveRight() {
    if (shape.getPosition().x < 800 - 100) shape.move(speed, 0);
}

// [4] POMOÆNE FUNKCIJE:
// getBounds() vraæa pravokutnik oko palice koji Ball koristi u intersects() funkciji.
// getCenterX() vraæa toèku na 50 piksela od poèetka palice (toèno sredina).
sf::FloatRect Paddle::getBounds() {
    return shape.getGlobalBounds();
}
float Paddle::getCenterX() {
    return shape.getPosition().x + 50.0f;
}

// [5] SETTER POZICIJE: Koristi se u setupLevel() iBall::isLost() dijelu maina.
void Paddle::setPosition(float x, float y) {
    shape.setPosition(x, y);
}