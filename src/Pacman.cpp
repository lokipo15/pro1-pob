//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#include "Pacman.h"

Pacman::Pacman(const QPoint &startPos)// Konstruktor klasy Pacman
    : position(startPos), currentDirection(None), nextDirection(None) {
}
// Rysuje Pacmana w aktualnej pozycji
void Pacman::draw(QPainter &painter) {
    painter.setPen(Qt::NoPen);// Brak obramowania
    painter.setBrush(Qt::yellow); // Kolor  żółty
    QRect rect(position.x() * CELL_SIZE, position.y() * CELL_SIZE, CELL_SIZE, CELL_SIZE);    // Tworzy prostokąt odpowiadający pozycji Pacmana na planszy
    painter.drawEllipse(rect); // Rysuje Pacmana jako żółte koło
}
// Przesuwanie Pacmana po planszy
void Pacman::move(GameBoard *board) {
    // Aktualizacja kierunku ruchu, jeśli to możliwe
    if (nextDirection != None) {
        QPoint nextPos = position;

        switch (nextDirection) { // Wyznacz pozycję po zmianie kierunku
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

        if (!board->isWall(nextPos)) { // Jeśli nowy kierunek nie prowadzi do ściany, zaakceptuj go
            currentDirection = nextDirection;
        }

        nextDirection = None; // Reset zaplanowanego kierunku
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

    if (!board->isWall(nextPos)) { // Zmiana pozycji, jeśli nie wchodzi na ściane
        position = nextPos;
    }
}

void Pacman::setDirection(Direction dir) { // Ustawia kierunek ruchu
    nextDirection = dir;
}

QPoint Pacman::getPosition() const { // Zwraca aktualną pozycję Pacmana na planszy
    return position;
}