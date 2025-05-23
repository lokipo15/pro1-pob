//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#include "Pinky.h"
#include "Pacman.h"

Pinky::Pinky(const QPointF &startPos) : Ghost(startPos) {
    normalColor = QColor(255, 184, 255);  // Różowy kolor
}

QPoint Pinky::calculateTarget(Pacman *pacman) {
    // Pinky celuje 4 komórki przed Pacmanem
    QPoint pacmanPos = pacman->getGridPosition();
    Entity::Direction pacmanDir = pacman->getCurrentDirection();

    QPoint target = pacmanPos;

    switch (pacmanDir) {
        case Entity::Up:
            target.setY(pacmanPos.y() - 4);
            break;
        case Entity::Down:
            target.setY(pacmanPos.y() + 4);
            break;
        case Entity::Left:
            target.setX(pacmanPos.x() - 4);
            break;
        case Entity::Right:
            target.setX(pacmanPos.x() + 4);
            break;
        default:
            target = pacmanPos;  // Jeśli Pacman stoi, celuj w niego
            break;
    }

    return target;
}

QPoint Pinky::getScatterCorner() const {
    // Lewy górny róg planszy
    return QPoint(1, 1);
}