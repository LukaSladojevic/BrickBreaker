#pragma once // Osigurava da se zaglavlje ukljuèi samo jednom pri prevoðenju
#include <SFML/Graphics.hpp> // Osnovna biblioteka za grafièke oblike

class Paddle {
private:
    sf::RectangleShape shape; // Pravokutni oblik koji predstavlja palicu u prozoru
    float speed = 12.0f;     // Brzina kretanja palice (tvoj specifièni balans igre)

public:
    // Konstruktor: postavlja poèetnu poziciju palice pri kreiranju objekta
    Paddle(float startX, float startY);

    void draw(sf::RenderWindow& window); // Iscrtava palicu na ekranu

    // Metode za upravljanje koje se pozivaju na pritisak strelica na tipkovnici
    void moveLeft();  // Pomièe palicu ulijevo pazeæi na rubove ekrana
    void moveRight(); // Pomièe palicu udesno pazeæi na rubove ekrana

    // Metode za interakciju s drugim objektima (lopticom)
    sf::FloatRect getBounds(); // Vraæa pravokutnik granica palice za detekciju sudara
    float getCenterX();        // Vraæa središnju X koordinatu (važno za kut odbijanja loptice)

    void setPosition(float x, float y); // Resetira poziciju palice nakon gubitka života ili restarta
};

/*Kontrola brzine:

"Brzinu palice smo fiksirali na 12.0f. 
Testiranjem smo zakljuèili da je to idealna brzina koja omoguæuje igraèu da stigne lopticu èak i kada ona ubrza nakon razbijanja cigli."

Logika odbijanja (getCenterX):

"Metoda getCenterX() je jedna od najvažnijih metoda u klasi. 
Ona omoguæuje loptici da izraèuna toèan kut odbijanja — ako loptica udari u rub palice, odbit æe se pod oštrijim kutom nego ako udari u sredinu."

Detekcija rubova:

"Unutar metoda moveLeft() i moveRight() implementirali smo provjere pozicije kako palica ne bi mogla 'pobjeæi' izvan vidljivog dijela prozora (koordinate 0 do 800)."*/