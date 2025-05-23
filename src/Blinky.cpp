//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#include "Blinky.h"
#include "Pacman.h"

Blinky::Blinky(const QPointF &startPos) : Ghost(startPos) {
    normalColor = Qt::red;  // Czerwony kolor
}

QPoint Blinky::calculateTarget(Pacman *pacman) {
    // Blinky celuje bezpośrednio w pozycję Pacmana
    return pacman->getGridPosition();
}

QPoint Blinky::getScatterCorner() const {
    // Prawy górny róg planszy
    return QPoint(18, 1);
}