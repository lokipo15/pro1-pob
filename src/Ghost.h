//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#ifndef GHOST_H
#define GHOST_H

#include "Entity.h"
#include <QColor>

class GameBoard;
class Pacman;

class Ghost : public Entity { // Klasa ducha dziedzicząca po Entity
public:
    // Tryby zachowania ducha
    enum Mode { CHASE, SCATTER, FRIGHTENED, EATEN };

    Ghost(const QPointF &startPos); // Konstruktor przyjmuje teraz QPointF
    virtual ~Ghost() = default;

    // Implementacja metod wirtualnych z Entity
    void draw(QPainter &painter) override;
    void move(GameBoard *board, float deltaTime) override;

    // Nowa metoda move z parametrem Pacman
    virtual void move(GameBoard *board, float deltaTime, Pacman *pacman);

    // Metody specyficzne dla duchów
    void setMode(Mode mode) { currentMode = mode; }
    Mode getMode() const { return currentMode; }
    void setColor(const QColor &color) { normalColor = color; }

    // Update mode timing
    void updateModeTimer(float deltaTime);
    void resetModeTimer() { modeTimer = 0.0f; }

    // Frightened mode methods
    void enterFrightenedMode(float duration);
    void updateFrightenedMode(float deltaTime);
    bool isVulnerable() const { return currentMode == FRIGHTENED; }
    void eatGhost(); // Gdy duch zostaje zjedzony

    // Wirtualna metoda do obliczania celu (dla różnych typów duchów)
    virtual QPoint calculateTarget(Pacman *pacman) { return getGridPosition(); }

    // Wirtualna metoda do określenia rogu scatter mode
    virtual QPoint getScatterCorner() const { return QPoint(0, 0); }

protected:
    Mode currentMode;
    QColor normalColor;     // Normalny kolor ducha
    QColor frightenedColor; // Kolor gdy przestraszony

    Direction lastValidDirection; // Ostatni prawidłowy kierunek
    float directionChangeTimer;   // Timer do losowej zmiany kierunku

    // Mode timing
    float modeTimer;
    static const float SCATTER_TIME;  // Czas trybu scatter
    static const float CHASE_TIME;    // Czas trybu chase

    // Frightened mode timing
    float frightenedTimer;
    float frightenedDuration;
    float blinkTimer; // Timer for blinking when frightened time is ending

    // Metody pomocnicze
    Direction getRandomDirection();
    Direction getOppositeDirection(Direction dir);
    bool isIntersection(const QPoint &pos, GameBoard *board);
    void chooseDirectionAtIntersection(GameBoard *board);
    void smoothMove(GameBoard *board, float deltaTime);
    void chooseTargetBasedDirection(const QPoint &target, GameBoard *board);
};

#endif