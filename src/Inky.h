//
// Created by Gabriel Boruń on 23/05/2025.
//

#ifndef INKY_H
#define INKY_H

#include "Ghost.h"

class Blinky;

class Inky : public Ghost {
public:
    Inky(const QPointF &startPos, Blinky *blinky);

    // Override target calculation - complex targeting using Blinky
    QPoint calculateTarget(Pacman *pacman) override;

    // Override scatter corner - bottom right
    QPoint getScatterCorner() const override;

private:
    Blinky *blinkyRef;  // Referencja do Blinky'ego do obliczeń
};

#endif //INKY_H
