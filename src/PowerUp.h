//
// Created by Gabriel Boruń on 23/05/2025.
//

#ifndef POWERUP_H
#define POWERUP_H

#include <QPointF>
#include <QPainter>

class Pacman;

class PowerUp {
public:
    PowerUp(const QPointF &position);
    virtual ~PowerUp() = default;

    // Wirtualne metody do implementacji w klasach pochodnych
    virtual void draw(QPainter &painter) = 0;
    virtual void activate(Pacman *pacman) = 0;
    virtual int getScore() const = 0;

    // Gettery
    QPointF getPosition() const { return position; }
    QPoint getGridPosition() const;

protected:
    QPointF position;
    static const int CELL_SIZE = 30;
};

#endif //POWERUP_H
