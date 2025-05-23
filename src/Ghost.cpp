//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#include "Ghost.h"
#include <cstdlib>
#include <ctime>

Ghost::Ghost(const QPoint &startPos)
    : position(startPos), direction(static_cast<Direction>(rand() % 4)) { // Konstruktor klasy Ghost.

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

void Ghost::draw(QPainter &painter) { // Rysowanie ducha na planszy
    painter.setPen(Qt::NoPen); // Bez obramówki
    painter.setBrush(color); // Wypełnienia kolorem

    QRect rect(position.x() * CELL_SIZE, position.y() * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    painter.drawEllipse(rect); // Rysuj ducha jako koło
}
// Losowe poruszanie się ducha
void Ghost::move(GameBoard *board) {
    // Próba kontynuacji ruchu w aktualnym kierunku
    QPoint nextPos = position;

    switch (direction) { // Wyznaczenie następnej pozycji
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

    // Ruch / aktualizacja
    position = nextPos;

    // Losowa zmiana kierunku (10% szansa na zmianę)
    if (rand() % 10 == 0) {
        direction = getRandomDirection();
    }
}

QPoint Ghost::getPosition() const { // Zwraca aktualną pozycję ducha
    return position;
}

Ghost::Direction Ghost::getRandomDirection() { // Generuje kierunek losowo
    return static_cast<Direction>(rand() % 4);
}