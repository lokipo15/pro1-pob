//
// Created by Gabriel Boruń on 25/04/2025.
//

#include "Ghost.h"
#include <cstdlib>
#include <ctime>

Ghost::Ghost(const QPoint &startPos)
    : position(startPos), direction(static_cast<Direction>(rand() % 4)) {

    // Inicjalizacja generatora liczb losowych
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }

    // Losowy kolor
    int r = 128 + rand() % 128;
    int g = 128 + rand() % 128;
    int b = 128 + rand() % 128;
    color = QColor(r, g, b);
}

void Ghost::draw(QPainter &painter) {
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);

    QRect rect(position.x() * CELL_SIZE, position.y() * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    painter.drawEllipse(rect);
}

void Ghost::move(GameBoard *board) {
    // Próba kontynuacji ruchu w aktualnym kierunku
    QPoint nextPos = position;

    switch (direction) {
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
    }

    // Jeśli uderzył w ścianę, zmiana kierunku
    if (board->isWall(nextPos)) {
        direction = getRandomDirection();
        return;
    }

    // Ruch
    position = nextPos;

    // Czasami losowo zmienia kierunek
    if (rand() % 10 == 0) {
        direction = getRandomDirection();
    }
}

QPoint Ghost::getPosition() const {
    return position;
}

Ghost::Direction Ghost::getRandomDirection() {
    return static_cast<Direction>(rand() % 4);
}