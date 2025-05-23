//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#include "Inky.h"
#include "Pacman.h"
#include "Blinky.h"

Inky::Inky(const QPointF &startPos, Blinky *blinky) : Ghost(startPos), blinkyRef(blinky) {
    normalColor = QColor(0, 255, 255);  // Cyan/niebieski kolor
}

QPoint Inky::calculateTarget(Pacman *pacman) {
    // Inky używa złożonego algorytmu z Blinky
    QPoint pacmanPos = pacman->getGridPosition();
    Entity::Direction pacmanDir = pacman->getCurrentDirection();

    // Punkt 2 komórki przed Pacmanem
    QPoint frontPoint = pacmanPos;
    switch (pacmanDir) {
        case Entity::Up:
            frontPoint.setY(pacmanPos.y() - 2);
            break;
        case Entity::Down:
            frontPoint.setY(pacmanPos.y() + 2);
            break;
        case Entity::Left:
            frontPoint.setX(pacmanPos.x() - 2);
            break;
        case Entity::Right:
            frontPoint.setX(pacmanPos.x() + 2);
            break;
        default:
            frontPoint = pacmanPos;
            break;
    }

    // Wektor od Blinky do punktu przed Pacmanem
    QPoint blinkyPos = blinkyRef->getGridPosition();
    int vectorX = frontPoint.x() - blinkyPos.x();
    int vectorY = frontPoint.y() - blinkyPos.y();

    // Podwój wektor (target to punkt przeciwny do Blinky przez punkt przed Pacmanem)
    QPoint target;
    target.setX(frontPoint.x() + vectorX);
    target.setY(frontPoint.y() + vectorY);

    return target;
}

QPoint Inky::getScatterCorner() const {
    // Prawy dolny róg planszy
    return QPoint(18, 18);
}