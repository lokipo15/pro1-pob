//
// Created by Gabriel Boruń on 25/04/2025.
//

#include "Pacman.h"
Pacman::Pacman(const QPoint &startPos)
    : position(startPos), currentDirection(None), nextDirection(None) {
}

void Pacman::draw(QPainter &painter) {
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::yellow);

    QRect rect(position.x() * CELL_SIZE, position.y() * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    painter.drawEllipse(rect);
}

void Pacman::move(GameBoard *board) {
    // Aktualizacja kierunku ruchu, jeśli to możliwe
    if (nextDirection != None) {
        QPoint nextPos = position;

        switch (nextDirection) {
            case Up:
                nextPos.setY(position.y() - 1);
            break;
            case Down:
                nextPos.setY(position.y() + 1);
            break;
            case Left:
                nextPos.setX(position.x() - 1);
            break;
            case Right:
                nextPos.setX(position.x() + 1);
            break;
            default:
                break;
        }

        if (!board->isWall(nextPos)) {
            currentDirection = nextDirection;
        }

        nextDirection = None;
    }

    // Ruch w aktualnym kierunku
    QPoint nextPos = position;

    switch (currentDirection) {
        case Up:
            nextPos.setY(position.y() - 1);
        break;
        case Down:
            nextPos.setY(position.y() + 1);
        break;
        case Left:
            nextPos.setX(position.x() - 1);
        break;
        case Right:
            nextPos.setX(position.x() + 1);
        break;
        default:
            break;
    }

    if (!board->isWall(nextPos)) {
        position = nextPos;
    }
}

void Pacman::setDirection(Direction dir) {
    nextDirection = dir;
}

QPoint Pacman::getPosition() const {
    return position;
}