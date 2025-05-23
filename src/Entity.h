//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#ifndef ENTITY_H
#define ENTITY_H

#include <QPointF>
#include <QPoint>
#include <QPainter>

class GameBoard;
class Pacman;

class Entity {
public:
    // Kierunki ruchu wspólne dla wszystkich encji
    enum Direction { None, Up, Down, Left, Right };

    Entity(const QPointF &startPos);
    virtual ~Entity() = default;

    // Wirtualne metody, aby była możliwość ich różnych implementacji w klasach pochodnych
    virtual void draw(QPainter &painter) = 0;
    virtual void move(GameBoard *board, float deltaTime) = 0;

    // Wspólne metody dla wszystkich encji
    QPoint getGridPosition() const;  // Konwersja pozycji float na siatkę
    QPointF getPosition() const { return position; }
    void setPosition(const QPointF &pos) { position = pos; }

    bool isAtGridCenter() const;  // Sprawdza czy encja jest w centrum komórki
    QPointF getTargetPosition() const { return targetPosition; }

protected:
    QPointF position;
    QPointF targetPosition;    // Docelowa pozycja na siatce
    Direction currentDirection;
    Direction nextDirection;

    float moveSpeed;          // Prędkość w komórkach na sekundę

    static const int CELL_SIZE = 30;  // Rozmiar pojedynczej komórki

    // Pomocnicze metody dla klas pochodnych
    QPointF calculateNextPosition(Direction dir, float deltaTime) const;
    bool canMoveTo(const QPoint &gridPos, GameBoard *board) const;
    void updateTargetPosition();
};

#endif //ENTITY_H

