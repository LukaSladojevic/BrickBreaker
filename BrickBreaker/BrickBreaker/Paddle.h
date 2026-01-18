#pragma once 
#include <SFML/Graphics.hpp> 

class Paddle {
private:
    // [1] ENKAPSULACIJA SVOJSTAVA: 
    // shape èuva izgled (boju i velièinu), a speed (12.0f) odreðuje koliko je palica brza. 
    // Privatno je jer ne želimo da main.cpp sluèajno promijeni brzinu usred igre.
    sf::RectangleShape shape;
    float speed = 12.0f;

public:
    // [2] KONSTRUKTOR I CRTANJE: Inicijalizacija i vizualizacija.
    Paddle(float startX, float startY);
    void draw(sf::RenderWindow& window);

    // [3] UPRAVLJANJE: Metode koje main.cpp poziva kada igraè pritisne strelice.
    void moveLeft();
    void moveRight();

    // [4] POMOÆNE METODE ZA FIZIKU: 
    // getBounds() služi za detekciju sudara s lopticom.
    // getCenterX() je kljuèan za izraèun kuta pod kojim loptica odlazi.
    sf::FloatRect getBounds();
    float getCenterX();

    // [5] RESETIRANJE: Vraæa palicu na sredinu nakon gubitka života.
    void setPosition(float x, float y);
};