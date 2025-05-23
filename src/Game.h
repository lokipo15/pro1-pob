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
    int score; // Zdobyte punkty
    bool gameOver; // Flaga Game Over

    void checkCollisions(); // Sprawdza kolizje między Pacmanem-duchem i Pacmanem-punktem
    void drawScore(QPainter &painter); // Pokazuje/rysuje wynik gry
};

#endif //GAME_H