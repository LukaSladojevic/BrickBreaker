#pragma once // Sprjeèava višestruko ukljuèivanje istog filea
#include <SFML/Graphics.hpp> // SFML grafika za crtanje oblika

class Brick {
private:
    // Dvije komponente za bolji vizualni izgled (efekt dubine)
    sf::RectangleShape mainShape;  // Glavni okvir cigle
    sf::RectangleShape innerShape; // Unutarnji dio za "3D" efekt (samo za crvene)

    bool destroyed = false;   // Stanje: je li cigla razbijena ili ne
    bool unbreakable = false; // Tip: je li cigla neuništiva prepreka (bijela)

public:
    // Konstruktor: prima poziciju (x, y) i podatak je li neuništiva
    Brick(float x, float y, bool isUnbreakable);

    void draw(sf::RenderWindow& window); // Crta ciglu samo ako nije uništena

    // "Getteri" - metode koje daju informaciju o stanju cigle izvana
    bool isDestroyed();   // Provjerava treba li loptica uopæe gledati sudar
    bool isUnbreakable(); // Provjerava treba li dodati bodove i ubrzati lopticu

    void destroy();       // Oznaèava ciglu kao uništenu (ako nije bijela)
    sf::FloatRect getBounds(); // Vraæa granice za detekciju sudara
};

/*Višestruka namjena jedne klase:

"Umjesto da radimo dvije zasebne klase, koristimo jedan bool unbreakable. 
Ako je true, cigla se boja u bijelo i loptica se od nje samo odbija bez uništenja, što nam je omoguæilo kreiranje kompleksnijih nivoa."

Vizualni dizajn (Layering):

"Koristimo dva pravokutnika (mainShape i innerShape) unutar jedne cigle kako bismo postigli retro arkadni izgled sjenèanja, što izgleda puno bolje od obiènih jednobojnih blokova."

Optimizacija sudara:

"Metoda isDestroyed() je kljuèna za performanse.
U main.cpp petlji loptica provjerava sudar samo s onim ciglama koje još uvijek imaju ovo stanje postavljeno na false."*/