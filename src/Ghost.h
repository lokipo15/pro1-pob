//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#ifndef GHOST_H
#define GHOST_H

#include "Entity.h"
#include <QColor>

class GameBoard;

class Ghost : public Entity { // Klasa ducha dziedzicząca po Entity
public:
    // Tryby zachowania ducha (przygotowanie na różne typy duchów)
    enum Mode { CHASE, SCATTER, FRIGHTENED, EATEN };

    Ghost(const QPointF &startPos); // Konstruktor przyjmuje teraz QPointF
    virtual ~Ghost() = default;

    // Implementacja metod wirtualnych z Entity
    void draw(QPainter &painter) override;
    void move(GameBoard *board, float deltaTime) override;

    // Metody specyficzne dla duchów
    void setMode(Mode mode) { currentMode = mode; }
    Mode getMode() const { return currentMode; }
    void setColor(const QColor &color) { normalColor = color; }

    // Wirtualna metoda do obliczania celu (dla różnych typów duchów)
    virtual QPoint calculateTarget(class Pacman *pacman) { return getGridPosition(); }

protected:
    Mode currentMode;
    QColor normalColor;     // Normalny kolor ducha
    QColor frightenedColor; // Kolor gdy przestraszony

    Direction lastValidDirection; // Ostatni prawidłowy kierunek
    float directionChangeTimer;   // Timer do losowej zmiany kierunku

    // Metody pomocnicze
    Direction getRandomDirection();
    Direction getOppositeDirection(Direction dir);
    bool isIntersection(const QPoint &pos, GameBoard *board);
    void chooseDirectionAtIntersection(GameBoard *board);
    void smoothMove(GameBoard *board, float deltaTime);
};

#endif
