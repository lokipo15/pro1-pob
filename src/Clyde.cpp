//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#include "Clyde.h"
#include "Pacman.h"
#include <cmath>

const float Clyde::RETREAT_DISTANCE = 8.0f;  // 8 komórek

Clyde::Clyde(const QPointF &startPos) : Ghost(startPos) {
    normalColor = QColor(255, 184, 82);  // Pomarańczowy kolor
}

QPoint Clyde::calculateTarget(Pacman *pacman) {
    QPoint pacmanPos = pacman->getGridPosition();
    QPoint myPos = getGridPosition();

    // Oblicz odległość do Pacmana
    float dx = pacmanPos.x() - myPos.x();
    float dy = pacmanPos.y() - myPos.y();
    float distance = sqrt(dx*dx + dy*dy);

    if (distance > RETREAT_DISTANCE) {
        // Jeśli daleko od Pacmana, goni jak Blinky
        return pacmanPos;
    } else {
        // Jeśli blisko Pacmana, ucieka do swojego rogu
        return getScatterCorner();
    }
}

QPoint Clyde::getScatterCorner() const {
    // Lewy dolny róg planszy
    return QPoint(1, 18);
}