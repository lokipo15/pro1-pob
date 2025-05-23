//
// Created by Gabriel Boruń on 23/05/2025.
//

#ifndef POWERPELLET_H
#define POWERPELLET_H

#include "PowerUp.h"

class PowerPellet : public PowerUp {
public:
    PowerPellet(const QPointF &position);

    // Implementacja metod wirtualnych z PowerUp
    void draw(QPainter &painter) override;
    void activate(Pacman *pacman) override;
    int getScore() const override;

private:
    float animationTimer;
    bool visible;

    static const int SCORE_VALUE = 50;
    static const float FRIGHTENED_DURATION;
};

#endif //POWERPELLET_H
