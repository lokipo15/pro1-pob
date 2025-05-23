//
// Created by Gabriel Boruń on 23/05/2025.
//

#ifndef CLYDE_H
#define CLYDE_H

#include "Ghost.h"

class Clyde : public Ghost {
public:
    Clyde(const QPointF &startPos);

    // Override target calculation - distance-based behavior
    QPoint calculateTarget(Pacman *pacman) override;

    // Override scatter corner - bottom left
    QPoint getScatterCorner() const override;

private:
    static const float RETREAT_DISTANCE;  // Odległość przy której Clyde ucieka
};

#endif //CLYDE_H
