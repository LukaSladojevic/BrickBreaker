#pragma once
#include <SFML/Graphics.hpp>

class Brick {
private:
    // [1] 3D DIZAJN: Imamo dva pravokutnika. 
    sf::RectangleShape mainShape;
    sf::RectangleShape innerShape;

    // [2] STANJA CIGLE: 
    // destroyed - je li cigla nestala?
    // unbreakable - je li to bijeli "neuništivi" blok?
    // health - koliko još udaraca trpi (2 = plava, 1 = crvena).
    bool destroyed = false;
    bool unbreakable = false;
    int health;

public:
    // [3] KONSTRUKTOR: Prima X i Y poziciju, HP (živote) i informaciju je li neuništiva.
    Brick(float x, float y, int hp, bool isUnbreakable);

    // [4] JAVNE METODE: 
    // draw - iscrtava oba oblika ako cigla nije uništena.
    // hit - mozak razbijanja cigle.
    void draw(sf::RenderWindow& window);
    void hit();

    // [5] POMOÆNE FUNKCIJE (Getteri): 
    // Služe main.cpp-u da sazna je li cigla uništena ili gdje se toèno nalazi za sudar.
    bool isDestroyed();
    bool isUnbreakable();
    sf::FloatRect getBounds();
};