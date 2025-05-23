//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include "GameBoard.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"
#include "PowerUp.h"
#include "PowerPellet.h"
#include <vector>

class Game : public QWidget { // Główna klasa - logika gry
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr); // Konstruktor
    ~Game(); // Destruktor

protected:
    void paintEvent(QPaintEvent *event) override; // Obsługuje "rysowanie"
    void keyPressEvent(QKeyEvent *event) override; // Obsługuje naciśnięcie klawisza / keystroke

private slots: // Cykliczny slot do aktualizacji stanu gry / jej planszy
    void update();

private:
    QTimer *timer; // Timer do aktualizacji
    QElapsedTimer elapsedTimer; // Timer do pomiaru delta time
    qint64 lastUpdateTime; // Czas ostatniej aktualizacji

    GameBoard *board; // Wskaźnik na planszę
    Pacman *pacman; // Wskaźnik na Pacmana
    std::vector<Ghost*> ghosts; // Wektor wskaźników na duchy

    // Specific ghost references for complex behaviors
    Blinky *blinky;
    Pinky *pinky;
    Inky *inky;
    Clyde *clyde;

    // Power-up system
    std::vector<PowerUp*> powerUps; // Wektor power-upów
    float powerUpTimer; // Timer dla aktywnych power-upów
    bool powerUpActive; // Czy power-up jest aktywny
    int ghostEatenMultiplier; // Mnożnik punktów za zjedzenie duchów

    int score; // Zdobyte punkty
    bool gameOver; // Flaga Game Over

    void checkCollisions(); // Sprawdza kolizje między Pacmanem-duchem i Pacmanem-punktem
    void drawScore(QPainter &painter); // Pokazuje/rysuje wynik gry
    void updateGhostModes(float deltaTime); // Aktualizuje tryby duchów
    void activatePowerUp(); // Aktywuje power-up
    void updatePowerUpTimer(float deltaTime); // Aktualizuje timer power-upów
};


#endif //GAME_H