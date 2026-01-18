#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

using namespace std;

int main() {
    // [1] POSTAVKE PROZORA: Kreiramo prozor rezolucije 800x600. 
    // setFramerateLimit(60) osigurava da igra radi glatko na 60 slièica u sekundi, 
    // a srand inicijalizira generator nasumiènih brojeva koristeæi trenutno vrijeme.
    sf::RenderWindow window(sf::VideoMode(800, 600), "Brick Breaker - Luka & Brano - FINAL");
    window.setFramerateLimit(60);
    srand(static_cast<unsigned>(time(0)));

    // [2] UCITAVANJE FONTA: font.ttf
    // Ako ne postoji, program se prekida kako ne bi došlo do rušenja sustava pri crtanju teksta.
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) return -1;

    // [3] UCITAVANJE ZVUKOVA: Koristimo SoundBuffer za uèitavanje datoteka u memoriju (RAM), 
    // a sf::Sound objekte za stvarnu reprodukciju zvukova tijekom sudara i gubitka života.
    sf::SoundBuffer bufPaddle, bufHit, bufBreak, bufLose;
    bufPaddle.loadFromFile("paddle.wav");
    bufHit.loadFromFile("hit.wav");
    bufBreak.loadFromFile("break.wav");
    bufLose.loadFromFile("lose.wav");

    sf::Sound sndPaddle(bufPaddle);
    sf::Sound sndHit(bufHit);
    sf::Sound sndBreak(bufBreak);
    sf::Sound sndLose(bufLose);

    // [4] STANJA IGRE: Varijable koje prate tijek igre. 
    // isGameOver i isVictory kontroliraju koji æe se ekran prikazati, 
    // dok gameStarted sprjeèava da loptica krene prije nego igraè pritisne Space.
    int score = 0;
    int lives = 3;
    int currentLevel = 1;
    bool isGameOver = false;
    bool isVictory = false;
    bool allLevelsCleared = false;
    bool gameStarted = false;

    // [5] UI ELEMENTI (TEKSTOVI): Postavljamo font, velièinu i poziciju za Score, Lives i Level. 
    // Dodali smo i watermark "Luka & Brano" u sivoj boji kako bi bio vidljiv, ali nenametljiv.
    sf::Text scoreText, livesText, levelText, watermark, startText, btnText;

    scoreText.setFont(font); scoreText.setCharacterSize(24); scoreText.setPosition(20, 10);
    livesText.setFont(font); livesText.setCharacterSize(24); livesText.setFillColor(sf::Color::Red); livesText.setPosition(680, 10);
    levelText.setFont(font); levelText.setCharacterSize(24); levelText.setFillColor(sf::Color::Cyan); levelText.setPosition(520, 10);

    watermark.setFont(font); watermark.setString("Luka & Brano");
    watermark.setCharacterSize(30); watermark.setFillColor(sf::Color(100, 100, 100)); watermark.setPosition(580, 550);

    startText.setFont(font); startText.setString("PRESS SPACE TO START");
    startText.setCharacterSize(35); startText.setFillColor(sf::Color::Yellow); startText.setPosition(220, 280);

    // [6] OVERLAY I GUMBI: Pravokutnici koji služe kao pozadina za kraj igre i gumb "Retry/Next". 
    // actionBtn je interaktivni element èije granice provjeravamo kod klika mišem.
    sf::RectangleShape overlay(sf::Vector2f(500, 350));
    overlay.setFillColor(sf::Color(0, 0, 0, 230));
    overlay.setOutlineThickness(3); overlay.setOutlineColor(sf::Color::White); overlay.setPosition(150, 125);

    sf::RectangleShape actionBtn(sf::Vector2f(160, 50));
    actionBtn.setFillColor(sf::Color::Green); actionBtn.setPosition(320, 380);

    btnText.setFont(font); btnText.setCharacterSize(24); btnText.setFillColor(sf::Color::Black);

    // [7] OBJEKTI IGRE: Inicijaliziramo palicu na dnu i lopticu. 
    // bricks je vektor (lista) u koju spremamo sve cigle odreðenog nivoa.
    Paddle myPaddle(350, 560);
    Ball myBall(400, 300);
    vector<Brick> bricks;

    // [8] SETUP NIVOA (Lambda funkcija): Centralno mjesto za dizajn 5 razlicitih levela. 
    // Koristimo switch statement. Level 4 je dizajniran kao "Space Invader" pomoæu matrice, 
    // dok je Level 5 potpuno sluèajan (random) za maksimalnu težinu.
    auto setupLevel = [&](int level) {
        bricks.clear();
        myBall.reset(400, 300);
        myPaddle.setPosition(350, 560);

        switch (level) {
        case 1: // LEVEL 1: Piramida + 2 Bijela bloka
            bricks.push_back(Brick(100.0f, 150.0f, 1, true));
            bricks.push_back(Brick(630.0f, 150.0f, 1, true));
            for (int j = 0; j < 4; j++) {
                for (int i = 0; i < 9 - j; i++) {
                    int hp = (rand() % 10 < 3) ? 2 : 1;
                    bricks.push_back(Brick(i * 75.0f + (j * 37.5f) + 70.0f, j * 25.0f + 60.0f, hp, false));
                }
            }
            break;

        case 2: // LEVEL 2: Stupci
            for (int j = 0; j < 5; j++) {
                for (int i = 0; i < 8; i++) {
                    if (i == 3 || i == 4) continue;
                    int hp = (rand() % 10 < 4) ? 2 : 1;
                    bricks.push_back(Brick(i * 85.0f + 70.0f, j * 30.0f + 60.0f, hp, false));
                }
            }
            break;

        case 3: // LEVEL 3: Sahovnica
            for (int j = 0; j < 5; j++) {
                for (int i = 0; i < 9; i++) {
                    bool unbreakable = (i % 4 == 0 && j == 2);
                    int hp = (rand() % 10 < 5) ? 2 : 1;
                    bricks.push_back(Brick(i * 75.0f + 65.0f, j * 30.0f + 60.0f, hp, unbreakable));
                }
            }
            break;

        case 4: { // LEVEL 4: SPACE INVADER (Ikona nacrtana ciglama)
            int invader[8][11] = {
                {0,0,1,0,0,0,0,0,1,0,0}, {0,0,0,1,0,0,0,1,0,0,0}, {0,0,1,1,1,1,1,1,1,0,0},
                {0,1,1,0,1,1,1,0,1,1,0}, {1,1,1,1,1,1,1,1,1,1,1}, {1,0,1,1,1,1,1,1,1,0,1},
                {1,0,1,0,0,0,0,0,1,0,1}, {0,0,0,1,1,0,1,1,0,0,0}
            };
            for (int j = 0; j < 8; j++) {
                for (int i = 0; i < 11; i++) {
                    if (invader[j][i] == 1) {
                        int hp = (rand() % 10 < 5) ? 2 : 1;
                        bricks.push_back(Brick(i * 68.0f + 30.0f, j * 25.0f + 60.0f, hp, false));
                    }
                }
            }
        } break;

        case 5: // LEVEL 5: TOTALNI RANDOM (Svaki put drugaèije)
            for (int j = 0; j < 7; j++) {
                for (int i = 0; i < 10; i++) {
                    int chance = rand() % 100;
                    bool unbreakable = (chance < 20);
                    int hp = (chance >= 20 && chance < 60) ? 2 : 1;
                    bricks.push_back(Brick(i * 75.0f + 30.0f, j * 25.0f + 50.0f, hp, unbreakable));
                }
            }
            break;
        }
        };

    setupLevel(currentLevel);

    // [9] GLAVNA PETLJA (Event Handling): Hvata unos igraèa. 
    // Tipke 1-5 su skriveni naèini za preskakanje levela (Hidden Keys). 
    // MouseButtonPressed detektira klik na gumb unutar overlay ekrana.
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num5) {
                    currentLevel = event.key.code - sf::Keyboard::Num1 + 1;
                    setupLevel(currentLevel);
                    gameStarted = false; isGameOver = false; isVictory = false; allLevelsCleared = false;
                }
                if (event.key.code == sf::Keyboard::Space) {
                    if (!gameStarted && !isGameOver && !isVictory && !allLevelsCleared) gameStarted = true;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (actionBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    if (isVictory && currentLevel < 5) {
                        currentLevel++; isVictory = false; gameStarted = false; setupLevel(currentLevel);
                    }
                    else if (isGameOver || allLevelsCleared) {
                        currentLevel = 1; score = 0; lives = 3;
                        isGameOver = false; isVictory = false; allLevelsCleared = false; gameStarted = false;
                        setupLevel(currentLevel);
                    }
                }
            }
        }

        // [10] LOGIKA IGRE: Ovdje se odvija kretanje i sudari. 
        // myBall.update() pomièe lopticu, a intersects funkcija provjerava sudare. 
        // Na svaki sudar puštamo odgovarajuæi zvuk (sndPaddle, sndHit, sndBreak).
        if (gameStarted && !isGameOver && !isVictory && !allLevelsCleared) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) myPaddle.moveLeft();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) myPaddle.moveRight();

            myBall.update();

            if (myBall.getBounds().intersects(myPaddle.getBounds())) {
                myBall.bounceOffPaddle(myPaddle.getCenterX());
                sndPaddle.play();
            }

            for (auto& brick : bricks) {
                if (!brick.isDestroyed() && myBall.getBounds().intersects(brick.getBounds())) {
                    myBall.bounce(brick.getBounds());
                    brick.hit();
                    if (brick.isDestroyed()) sndBreak.play(); else sndHit.play();

                    if (!brick.isUnbreakable() && brick.isDestroyed()) {
                        score += 10; myBall.speedUp();
                    }
                    break;
                }
            }

            int breakableCount = 0;
            for (auto& b : bricks) if (!b.isUnbreakable() && !b.isDestroyed()) breakableCount++;

            if (breakableCount == 0 && score > 0) {
                if (currentLevel < 5) isVictory = true; else allLevelsCleared = true;
            }

            if (myBall.isLost()) {
                lives--; sndLose.play();
                if (lives <= 0) isGameOver = true;
                else { myBall.reset(400, 300); gameStarted = false; }
            }
        }

        // [11] CRTANJE: Svaki frame èistimo ekran s window.clear(sf::Color::Black) i 
        // crtamo sve objekte (palicu, lopticu, cigle i UI tekstove).
        window.clear(sf::Color::Black);
        window.draw(watermark);

        scoreText.setString("Score: " + to_string(score));
        livesText.setString("Lives: " + to_string(lives));
        levelText.setString("Level: " + to_string(currentLevel));

        window.draw(scoreText); window.draw(livesText); window.draw(levelText);
        myPaddle.draw(window); myBall.draw(window);
        for (auto& b : bricks) b.draw(window);

        if (!gameStarted && !isGameOver && !isVictory && !allLevelsCleared) window.draw(startText);

        // [12] OVERLAYS (Kraj igre / Pobjeda): Ako je isGameOver ili isVictory true, 
        // crtamo dodatni sloj preko igre s porukom i gumbom za nastavak ili ponovni poèetak.
        if (isGameOver || isVictory || allLevelsCleared) {
            window.draw(overlay);
            sf::Text msg, subMsg;
            msg.setFont(font); msg.setCharacterSize(40);
            subMsg.setFont(font); subMsg.setCharacterSize(24);

            if (isGameOver) {
                msg.setString("GAME OVER"); msg.setFillColor(sf::Color::Red); msg.setPosition(270, 160);
                subMsg.setString("Final Score: " + to_string(score)); subMsg.setPosition(310, 250);
                btnText.setString("RETRY"); btnText.setPosition(365, 390);
            }
            else if (isVictory) {
                msg.setString("LEVEL " + to_string(currentLevel) + " CLEARED!"); msg.setFillColor(sf::Color::Green); msg.setPosition(210, 180);
                btnText.setString("NEXT"); btnText.setPosition(370, 390);
            }
            else if (allLevelsCleared) {
                msg.setString("CONGRATULATIONS!"); msg.setFillColor(sf::Color::Cyan); msg.setPosition(200, 160);
                subMsg.setString("YOU PASSED ALL LEVELS!\nFinal Score: " + to_string(score)); subMsg.setPosition(260, 240);
                btnText.setString("RESTART"); btnText.setPosition(355, 390);
            }
            window.draw(msg); if (isGameOver || allLevelsCleared) window.draw(subMsg);
            window.draw(actionBtn); window.draw(btnText);
        }
        window.display();
    }
    return 0;
}