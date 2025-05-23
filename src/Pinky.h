//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#ifndef PINKY_H
#define PINKY_H

#include "Ghost.h"

class Pinky : public Ghost {
public:
    Pinky(const QPointF &startPos);

    // Override target calculation - target 4 cells ahead of Pacman
    QPoint calculateTarget(Pacman *pacman) override;

    // Override scatter corner - top left
    QPoint getScatterCorner() const override;
};

#endif

