//
// Created by Gabriel Boruń on 25/04/2025.
//

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QPoint>
#include <QPainter>
#include <vector>
#include <set>

struct QPointCompare {
    bool operator()(const QPoint& a, const QPoint& b) const {
        if (a.y() != b.y()) {
            return a.y() < b.y();
        }
        return a.x() < b.x();
    }
};

class GameBoard {
public:
    GameBoard();

    void draw(QPainter &painter);

    bool isWall(const QPoint &pos) const;
    bool isCollectible(const QPoint &pos) const;
    void removeCollectible(const QPoint &pos);

    QPoint getPacmanStartPosition() const;
    std::vector<QPoint> getGhostStartPositions() const;

private:
    static constexpr int BOARD_WIDTH = 20;
    static constexpr int BOARD_HEIGHT = 20;
    static constexpr int CELL_SIZE = 30;

    // 0 = puste, 1 = ściana, 2 = punkt do zebrania, 3 = start Pacmana, 4 = start ducha
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    std::set<QPoint, QPointCompare> collectibles;

    void initializeBoard();
};




#endif //GAMEBOARD_H
