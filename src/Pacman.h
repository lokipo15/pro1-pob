//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#ifndef PACMAN_H
#define PACMAN_H

#include "Entity.h"

class GameBoard;

class Pacman : public Entity { // Klasa Pacman'a dziedzicząca po Entity
public:
    Pacman(const QPointF &startPos); // Konstruktor przyjmuje teraz QPointF

    // Implementacja metod wirtualnych z Entity
    void draw(QPainter &painter) override;
    void move(GameBoard *board, float deltaTime) override;

    // Metody specyficzne dla Pacmana
    void setDirection(Direction dir);

    // Getter dla aktualnego kierunku (może być przydatny dla duchów)
    Direction getCurrentDirection() const { return currentDirection; }

private:
    // Animacja otwierania i zamykania ust
    float mouthAngle;
    bool mouthOpening;

    // Metoda pomocnicza do płynnego ruchu
    void smoothMove(GameBoard *board, float deltaTime);
    bool canTurnAt(const QPointF &pos, Direction dir, GameBoard *board) const;
    QPointF getAlignedPosition(Direction fromDir, Direction toDir) const;
    void updateMouthAnimation(float deltaTime);
};

#endif
