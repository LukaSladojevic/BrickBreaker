#include "Brick.h"

// [1] KONSTRUKTOR I 3D POZICIONIRANJE: 
// Postavljamo velièinu ruba (70x20) i unutarnjeg dijela (60x8). 
// innerShape je pomaknut za (5, 2) unutar mainShapea kako bismo dobili 3D dubinu.
Brick::Brick(float x, float y, int hp, bool isUnbreakable) : health(hp), unbreakable(isUnbreakable) {
    mainShape.setSize(sf::Vector2f(70.0f, 20.0f));
    mainShape.setPosition(x, y);

    innerShape.setSize(sf::Vector2f(60.0f, 8.0f));
    innerShape.setPosition(x + 5, y + 2);

    // [2] LOGIKA BOJA: 
    // Ako je neuništiva -> Bijela/Siva.
    // Ako ima 2 HP -> Plava (tamna sjena, svijetla sredina).
    // Ako ima 1 HP -> Crvena (tamna sjena, svijetla sredina).
    if (unbreakable) {
        mainShape.setFillColor(sf::Color(150, 150, 150));
        innerShape.setFillColor(sf::Color::White);
    }
    else {
        if (health == 2) {
            mainShape.setFillColor(sf::Color(0, 0, 150));
            innerShape.setFillColor(sf::Color(60, 60, 255));
        }
        else {
            mainShape.setFillColor(sf::Color(150, 0, 0));
            innerShape.setFillColor(sf::Color(255, 60, 60));
        }
    }
}

// [3] HIT METODA (Sustav napretka): 
// Ako je bijela, loptica se samo odbije (return). 
// Ako je plava (HP 2), smanji HP na 1 i ODMAH promijeni boju u crvenu.
// Ako je crvena (HP 1), postavi destroyed = true.
void Brick::hit() {
    if (unbreakable) return;
    health--;
    if (health == 1) {
        mainShape.setFillColor(sf::Color(150, 0, 0));
        innerShape.setFillColor(sf::Color(255, 60, 60));
    }
    else if (health <= 0) {
        destroyed = true;
    }
}

// [4] CRTANJE: Iscrtava samo ako destroyed nije true. 
// Crta prvo mainShape (sjena), pa innerShape (boja) preko njega.
void Brick::draw(sf::RenderWindow& window) {
    if (!destroyed) {
        window.draw(mainShape);
        window.draw(innerShape);
    }
}

// [5] DETEKCIJA SUDARA: 
// getBounds vraæa GlobalBounds od mainShapea (ukupni pravokutnik cigle) 
// koji loptica koristi u svojoj intersects funkciji.
bool Brick::isDestroyed() { return destroyed; }
bool Brick::isUnbreakable() { return unbreakable; }
sf::FloatRect Brick::getBounds() { return mainShape.getGlobalBounds(); }