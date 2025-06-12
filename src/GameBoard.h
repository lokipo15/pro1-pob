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
    bool isPowerUp(const QPoint &pos) const; // Sprawdzenie czy power-up
    void removeCollectible(const QPoint &pos); // Usuwanie punktu z planszy
    void removePowerUp(const QPoint &pos); // Usuwanie power-up z planszy

    QPoint getPacmanStartPosition() const; // Pozycja startowa Pacmana
    std::vector<QPoint> getGhostStartPositions() const; // Pozycje startowe duchów
    std::vector<QPoint> getPowerUpPositions() const; // Pozycje power-upów
    const std::set<QPoint, QPointCompare>& getCollectibles() const { return collectibles; }

private:
    static const int BOARD_WIDTH = 20; // szerokość planszy
    static const int BOARD_HEIGHT = 20; // wysokość planszy
    static const int CELL_SIZE = 30; // rozmiar pojedymczej komórki planszy

    // 0 = puste, 1 = ściana, 2 = punkt do zebrania, 3 = start Pacmana, 4 = start ducha, 5 = power-up
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    std::set<QPoint, QPointCompare> collectibles; // zbiór punktów do zebrania
    std::set<QPoint, QPointCompare> powerUps; // zbiór power-upów

    void initializeBoard(); // Inicjalizacja planszy (punkty ściany poz. startowe)
};

#endif //GAMEBOARD_H