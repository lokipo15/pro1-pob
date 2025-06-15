///
/// Created by Gabriel Boruń on 25/04/2025.
/// Co-authored by Konrad Gębski on 25/04/2025.
///

#include "PowerPellet.h"
#include "Pacman.h"

const float PowerPellet::FRIGHTENED_DURATION = 10.0f; /// 10 sekund trybu frightened

PowerPellet::PowerPellet(const QPointF &position)
    : PowerUp(position), animationTimer(0.0f), visible(true) {
}

void PowerPellet::draw(QPainter &painter) {
    if (!visible) return;

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);

    /// Konwersja pozycji na piksele
    int pixelX = static_cast<int>(position.x() * CELL_SIZE);
    int pixelY = static_cast<int>(position.y() * CELL_SIZE);

    /// Rysowanie większego pellet (power pellet)
    int pelletSize = CELL_SIZE / 3;
    QRect rect(pixelX + CELL_SIZE/2 - pelletSize/2,
               pixelY + CELL_SIZE/2 - pelletSize/2,
               pelletSize, pelletSize);

    painter.drawEllipse(rect);
}

void PowerPellet::activate(Pacman *pacman) {
    /// Power pellet nie wpływa bezpośrednio na Pacmana
    /// Logika frightened mode będzie w klasie Game
}

int PowerPellet::getScore() const {
    return SCORE_VALUE;
}