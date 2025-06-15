///
/// Created by Gabriel Boruń on 25/04/2025.
/// Co-authored by Konrad Gębski on 25/04/2025.
///

#include "PowerUp.h"
#include <cmath>

PowerUp::PowerUp(const QPointF &position) : position(position) {
}

QPoint PowerUp::getGridPosition() const {
    return QPoint(
        static_cast<int>(std::round(position.x())),
        static_cast<int>(std::round(position.y()))
    );
}