///
/// Created by Gabriel Boruń on 25/04/2025.
/// Co-authored by Konrad Gębski on 25/04/2025.
///

#include "Entity.h"
#include "GameBoard.h"
#include <cmath>

Entity::Entity(const QPointF &startPos)
    : position(startPos),
      targetPosition(startPos),
      currentDirection(None),
      nextDirection(None),
      moveSpeed(5.0f) {  /// Domyślna prędkość: 5 komórek na sekundę
}

QPoint Entity::getGridPosition() const {
    /// Konwersja pozycji float na pozycję na siatce
    return QPoint(
        static_cast<int>(std::round(position.x())),
        static_cast<int>(std::round(position.y()))
    );
}

bool Entity::isAtGridCenter() const {
    /// Sprawdzenie czy encja jest wystarczająco blisko centrum komórki
    float epsilon = 0.3f;  /// Zwiększona tolerancja dla łatwiejszego skręcania
    float fracX = position.x() - std::floor(position.x());
    float fracY = position.y() - std::floor(position.y());

    /// Sprawdzamy czy jesteśmy blisko środka komórki (0.5, 0.5)
    bool nearCenterX = std::abs(fracX - 0.5f) < epsilon;
    bool nearCenterY = std::abs(fracY - 0.5f) < epsilon;

    /// Lub blisko krawędzi komórki (0.0 lub 1.0)
    bool nearEdgeX = fracX < epsilon || fracX > (1.0f - epsilon);
    bool nearEdgeY = fracY < epsilon || fracY > (1.0f - epsilon);

    return (nearCenterX || nearEdgeX) && (nearCenterY || nearEdgeY);
}

QPointF Entity::calculateNextPosition(Direction dir, float deltaTime) const {
    QPointF nextPos = position;
    float distance = moveSpeed * deltaTime;

    switch (dir) {
        case Up:
            nextPos.setY(position.y() - distance);
            break;
        case Down:
            nextPos.setY(position.y() + distance);
            break;
        case Left:
            nextPos.setX(position.x() - distance);
            break;
        case Right:
            nextPos.setX(position.x() + distance);
            break;
        default:
            break;
    }

    return nextPos;
}

bool Entity::canMoveTo(const QPoint &gridPos, GameBoard *board) const {
    return !board->isWall(gridPos);
}

void Entity::updateTargetPosition() {
    /// Aktualizuje pozycję docelową na podstawie obecnego kierunku
    QPoint currentGrid = getGridPosition();

    switch (currentDirection) {
        case Up:
            targetPosition = QPointF(currentGrid.x(), currentGrid.y() - 1);
            break;
        case Down:
            targetPosition = QPointF(currentGrid.x(), currentGrid.y() + 1);
            break;
        case Left:
            targetPosition = QPointF(currentGrid.x() - 1, currentGrid.y());
            break;
        case Right:
            targetPosition = QPointF(currentGrid.x() + 1, currentGrid.y());
            break;
        default:
            targetPosition = QPointF(currentGrid.x(), currentGrid.y());
            break;
    }
}