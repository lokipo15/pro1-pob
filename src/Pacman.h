//
// Created by Gabriel Boruń on 25/04/2025.
//

#ifndef PACMAN_H
#define PACMAN_H


#include "GameBoard.h"

class Pacman {
public:
    enum Direction { None, Up, Down, Left, Right };

    Pacman(const QPoint &startPos);

    void draw(QPainter &painter);
    void move(GameBoard *board);
    void setDirection(Direction dir);

    QPoint getPosition() const;

private:
    QPoint position;
    Direction currentDirection;
    Direction nextDirection;

    static const int CELL_SIZE = 30;
};


#endif //PACMAN_H
