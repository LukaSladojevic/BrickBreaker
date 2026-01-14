#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

using namespace std;

int main() {
    // Postavke prozora i brzine osvježavanja
    sf::RenderWindow window(sf::VideoMode(800, 600), "Brick Breaker - Luka & Brano");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        return -1; // Error ako font nedostaje
    }

    // Stanja igre
    int score = 0;
    int lives = 3;
    bool isGameOver = false;
    bool isVictory = false;
    bool gameStarted = false;

    // --- UI ELEMENTI ---
    sf::Text scoreText, livesText, watermark, startText;
    scoreText.setFont(font); scoreText.setCharacterSize(24); scoreText.setPosition(20, 10);
    livesText.setFont(font); livesText.setCharacterSize(24); livesText.setFillColor(sf::Color::Red); livesText.setPosition(680, 10);

    // Potpis Luka & Brano
    watermark.setFont(font); watermark.setString("Luka & Brano"); watermark.setCharacterSize(30);
    watermark.setFillColor(sf::Color(100, 100, 100)); watermark.setPosition(580, 550);

    // Poèetni ekran
    startText.setFont(font); startText.setString("PRESS SPACE TO START");
    startText.setCharacterSize(35); startText.setFillColor(sf::Color::Yellow); startText.setPosition(220, 280);

    // Završni ekrani (Overlay)
    sf::RectangleShape overlay(sf::Vector2f(400, 300));
    overlay.setFillColor(sf::Color(0, 0, 0, 230)); overlay.setOutlineThickness(3);
    overlay.setOutlineColor(sf::Color::White); overlay.setPosition(200, 150);

    sf::RectangleShape retryBtn(sf::Vector2f(160, 50));
    retryBtn.setFillColor(sf::Color::Green); retryBtn.setPosition(320, 380);

    sf::Text btnText;
    btnText.setFont(font); btnText.setString("RETRY"); btnText.setCharacterSize(24);
    btnText.setFillColor(sf::Color::Black); btnText.setPosition(365, 390);

    // --- OBJEKTI IGRE ---
    Paddle myPaddle(350, 560);
    Ball myBall(400, 300);
    vector<Brick> bricks;

    // Funkcija za kreiranje nivoa (Piramida i neuništivi blokovi)
    auto setupLevel = [&]() {
        bricks.clear();
        // Tri bijela neuništiva bloka
        bricks.push_back(Brick(250, 220, true));
        bricks.push_back(Brick(490, 220, true));
        bricks.push_back(Brick(370, 180, true));

        // Formacija crvenih cigli
        for (int j = 0; j < 5; j++) {
            for (int i = 0; i < 9 - j; i++) {
                bricks.push_back(Brick(i * 75.0f + (j * 37.5f) + 70.0f, j * 25.0f + 50.0f, false));
            }
        }
        };
    setupLevel();

    // --- GLAVNA PETLJA ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // Logika pokretanja i restarta
            if (!gameStarted && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) gameStarted = true;
            if ((isGameOver || isVictory) && event.type == sf::Event::MouseButtonPressed) {
                if (retryBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    score = 0; lives = 3; isGameOver = false; isVictory = false; gameStarted = false;
                    myBall.reset(400, 300); myPaddle.setPosition(350, 560); setupLevel();
                }
            }
        }

        if (gameStarted && !isGameOver && !isVictory) {
            // Kontrole palice
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) myPaddle.moveLeft();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) myPaddle.moveRight();

            myBall.update();

            // Sudar s palicom
            if (myBall.getBounds().intersects(myPaddle.getBounds())) {
                myBall.bounceOffPaddle(myPaddle.getCenterX());
            }

            // Sudar s ciglama
            for (auto& brick : bricks) {
                if (!brick.isDestroyed() && myBall.getBounds().intersects(brick.getBounds())) {
                    myBall.bounce(brick.getBounds()); // Pametno odbijanje

                    if (!brick.isUnbreakable()) {
                        brick.destroy();
                        myBall.speedUp(); // Ubrzanje loptice
                        score += 10;
                    }
                    break;
                }
            }

            // Provjera pobjede (Mora postojati barem jedan bod da se izbjegne instant win)
            int breakableCount = 0;
            for (auto& b : bricks) {
                if (!b.isUnbreakable() && !b.isDestroyed()) breakableCount++;
            }
            if (breakableCount == 0 && score > 0) isVictory = true;

            // Logika života
            if (myBall.isLost()) {
                lives--;
                if (lives <= 0) isGameOver = true;
                else myBall.reset(400, 300);
            }
        }

        // Ažuriranje teksta
        scoreText.setString("Score: " + to_string(score));
        livesText.setString("Lives: " + to_string(lives));

        // --- CRTANJE ---
        window.clear(sf::Color::Black);
        window.draw(watermark); window.draw(scoreText); window.draw(livesText);

        myPaddle.draw(window);
        myBall.draw(window);
        for (auto& b : bricks) b.draw(window);

        // Poèetne i završne poruke
        if (!gameStarted && !isGameOver && !isVictory) window.draw(startText);

        if (isGameOver || isVictory) {
            window.draw(overlay);
            sf::Text endText;
            endText.setFont(font); endText.setCharacterSize(45);
            endText.setString(isVictory ? "VICTORY!" : "GAME OVER");
            endText.setFillColor(isVictory ? sf::Color::Green : sf::Color::Red);
            endText.setPosition(isVictory ? 285 : 255, 180);
            window.draw(endText);

            sf::Text fs; fs.setFont(font); fs.setString("Final Score: " + to_string(score));
            fs.setCharacterSize(24); fs.setPosition(310, 270); window.draw(fs);

            window.draw(retryBtn); window.draw(btnText);
        }

        window.display();
    }

    return 0;
}