//
// Created by Gabriel Boruń on 25/04/2025.
//

#ifndef GHOST_H
#define GHOST_H


#include "GameBoard.h"

class Ghost {
public:
    enum Direction { Up, Down, Left, Right };

    Ghost(const QPoint &startPos);

    void draw(QPainter &painter);
    void move(GameBoard *board);

    QPoint getPosition() const;

private:
    QPoint position;
    Direction direction;
    QColor color;

    static const int CELL_SIZE = 30;

    Direction getRandomDirection();
};

#endif //GHOST_H
