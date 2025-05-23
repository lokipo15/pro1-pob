//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QPainter>
#include <vector>
#include <set>

struct QPointCompare { // Porównanie QPoint'ów
    bool operator()(const QPoint& a, const QPoint& b) const {
        if (a.y() != b.y()) {
            return a.y() < b.y();
        }
        return a.x() < b.x();
    }
};

class GameBoard { // Plansza gry
public:
    GameBoard(); // Konstruktor planszy

    void draw(QPainter &painter); // Rysowanie planszy

    bool isWall(const QPoint &pos) const; // Sprawdzenie czy ściana
    bool isCollectible(const QPoint &pos) const; // Sprawdzenie czy punkt
    void removeCollectible(const QPoint &pos); // Usuwanie punktu z planszy

    QPoint getPacmanStartPosition() const; // Pozycja startowa Pacmana
    std::vector<QPoint> getGhostStartPositions() const; // Pozycje startowe duchów

private:
    static const int BOARD_WIDTH = 20; // szerokość planszy
    static const int BOARD_HEIGHT = 20; // wysokość planszy
    static const int CELL_SIZE = 30; // rozmiar pojedymczej komórki planszy

    // 0 = puste, 1 = ściana, 2 = punkt do zebrania, 3 = start Pacmana, 4 = start ducha
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    std::set<QPoint, QPointCompare> collectibles; // zbiór punktów do zebrania

    void initializeBoard(); // Inicjalizacja planszy (punkty ściany poz. startowe)
};


#endif //GAMEBOARD_H
