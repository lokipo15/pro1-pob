//
// Created by Gabriel Boruń on 23/05/2025.
//

#ifndef BLINKY_H
#define BLINKY_H

#include "Ghost.h"

class Blinky : public Ghost {
public:
    Blinky(const QPointF &startPos);

    // Override target calculation - chase Pacman directly
    QPoint calculateTarget(Pacman *pacman) override;

    // Override scatter corner - top right
    QPoint getScatterCorner() const override;
};



#endif //BLINKY_H
