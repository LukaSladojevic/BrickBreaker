#pragma once // Osigurava da se ovaj file ukljuèi samo jednom pri kompajliranju
#include <SFML/Graphics.hpp> // Ukljuèivanje SFML biblioteke za grafiku

class Ball {
private:
    // PRIVATNA SVOJSTVA (Vidljiva samo unutar ove klase)
    sf::CircleShape shape;    // Grafièki oblik loptice (krug)
    sf::Vector2f velocity;   // Vektor brzine (smjer i jaèina kretanja)
    const float radius = 8.0f; // Fiksni radijus loptice

public:
    // JAVNE METODE (Ono što main.cpp može pozvati)
    Ball(float startX, float startY);         // Konstruktor: postavlja lopticu na poèetnu poziciju
    void draw(sf::RenderWindow& window);      // Iscrtava lopticu u prozoru igre
    void update();                            // Pomicanje loptice i odbijanje od rubova ekrana
    void bounceOffPaddle(float paddleCenterX); // Logika odbijanja od palice ovisno o kutu udarca

    // Pametna funkcija za sudar: rješava "jedenje" loptice od strane cigli
    void bounce(sf::FloatRect blockBounds);

    void speedUp();                           // Poveæava brzinu loptice za 1% nakon svake cigle
    sf::FloatRect getBounds();               // Vraæa pravokutnik oko loptice za detekciju sudara
    bool isLost();                           // Provjerava je li loptica pala ispod donjeg ruba ekrana
    void reset(float x, float y);             // Vraæa lopticu na sredinu i resetira brzinu
};

/*Enkapsulacija (Encapsulation):

Svojstva kao što su shape i velocity smo stavili u private sekciju. 
To znaèi da niko izvana ne može direktno mijenjati brzinu loptice, nego to radimo iskljuèivo preko naših metoda kao što je speedUp(). 
To je jedan od temelja OOP-a.

Logika kretanja i sudara:

"Metoda update() brine o stalnom kretanju, dok bounce(sf::FloatRect blockBounds) koristi SFML-ovu funkciju intersects kako bi detektirala sudar s ciglom. 
Dodali smo logiku koja lopticu odmah izbacuje iz cigle kako se ne bi 'zaglavila' unutar nje (tzv. AABB fix)."

Modularnost i skalabilnost:

"Ovim pristupom smo postigli da je loptica neovisna.
Ako sutra poželimo dodati drugu lopticu u igru, samo trebamo kreirati novi objekt klase Ball bez pisanja ijednog novog retka logike."*/