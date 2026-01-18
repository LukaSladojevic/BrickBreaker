#pragma once 
#include <SFML/Graphics.hpp> 

class Ball {
private:
    // [1] PRIVATNI ÈLANOVI: Encapsulation (Enkapsulacija). 
    // Ovi podaci su skriveni. Nitko izvan klase ne može sluèajno promijeniti 
    // radijus ili brzinu, što sprjeèava bugove u igri.
    sf::CircleShape shape;
    sf::Vector2f velocity;
    const float radius = 8.0f;

public:
    // [2] KONSTRUKTOR I JAVNE METODE: Suèelje klase.
    // Ovo su "naredbe" koje main.cpp koristi kako bi upravljao lopticom.
    Ball(float startX, float startY);
    void draw(sf::RenderWindow& window);
    void update();
    void bounceOffPaddle(float paddleCenterX);

    // [3] PAMETNI SUDAR (AABB Fix): 
    // Ova metoda sprjeèava da loptica "zapne" unutar cigle, što je èest problem u igrama.
    void bounce(sf::FloatRect blockBounds);

    void speedUp();
    sf::FloatRect getBounds();
    bool isLost();
    void reset(float x, float y);
};