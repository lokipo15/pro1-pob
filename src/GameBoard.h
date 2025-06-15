/**
 * @file GameBoard.h
 * @brief Klasa reprezentująca planszę gry Pacman
 * @author Gabriel Boruń, Konrad Gębski
 * @date 25/04/2025
 */

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QPainter>
#include <vector>
#include <set>

/**
 * @brief Struktura porównująca obiekty QPoint dla kontenerów STL
 * 
 * Umożliwia użycie QPoint jako klucza w zbiorach i mapach.
 */
struct QPointCompare {
    /**
     * @brief Operator porównania punktów
     * @param a Pierwszy punkt do porównania
     * @param b Drugi punkt do porównania
     * @return True jeśli punkt a jest mniejszy niż punkt b
     */
    bool operator()(const QPoint& a, const QPoint& b) const {
        if (a.y() != b.y()) {
            return a.y() < b.y();
        }
        return a.x() < b.x();
    }
};

/**
 * @brief Klasa reprezentująca planszę gry Pacman
 * 
 * Zarządza strukturą planszy, ścianami, punktami do zebrania,
 * power-upami oraz pozycjami startowymi postaci.
 */
class GameBoard {
public:
    /**
     * @brief Konstruktor planszy gry
     */
    GameBoard();

    /**
     * @brief Rysuje planszę na ekranie
     * @param painter Obiekt do rysowania
     */
    void draw(QPainter &painter);

    /**
     * @brief Sprawdza czy dana pozycja to ściana
     * @param pos Pozycja do sprawdzenia
     * @return True jeśli pozycja to ściana
     */
    bool isWall(const QPoint &pos) const;
    /**
     * @brief Sprawdza czy dana pozycja zawiera punkt do zebrania
     * @param pos Pozycja do sprawdzenia
     * @return True jeśli pozycja zawiera punkt
     */
    bool isCollectible(const QPoint &pos) const;
    /**
     * @brief Sprawdza czy dana pozycja zawiera power-up
     * @param pos Pozycja do sprawdzenia
     * @return True jeśli pozycja zawiera power-up
     */
    bool isPowerUp(const QPoint &pos) const;
    /**
     * @brief Usuwa punkt do zebrania z planszy
     * @param pos Pozycja punktu do usunięcia
     */
    void removeCollectible(const QPoint &pos);
    /**
     * @brief Usuwa power-up z planszy
     * @param pos Pozycja power-up do usunięcia
     */
    void removePowerUp(const QPoint &pos);

    /**
     * @brief Pobiera pozycję startową Pacmana
     * @return Pozycja startowa Pacmana na planszy
     */
    QPoint getPacmanStartPosition() const;
    /**
     * @brief Pobiera pozycje startowe duchów
     * @return Wektor pozycji startowych duchów
     */
    std::vector<QPoint> getGhostStartPositions() const;
    /**
     * @brief Pobiera pozycje power-upów na planszy
     * @return Wektor pozycji power-upów
     */
    std::vector<QPoint> getPowerUpPositions() const;
    /**
     * @brief Pobiera zbiór wszystkich punktów do zebrania
     * @return Referencja do zbioru punktów do zebrania
     */
    const std::set<QPoint, QPointCompare>& getCollectibles() const { return collectibles; }

private:
    static const int BOARD_WIDTH = 20;      ///< Szerokość planszy w komórkach
    static const int BOARD_HEIGHT = 20;     ///< Wysokość planszy w komórkach
    static const int CELL_SIZE = 30;        ///< Rozmiar pojedynczej komórki w pikselach

    /**
     * Tablica reprezentująca planszę:
     * 0 = puste pole, 1 = ściana, 2 = punkt do zebrania,
     * 3 = pozycja startowa Pacmana, 4 = pozycja startowa ducha, 5 = power-up
     */
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    
    std::set<QPoint, QPointCompare> collectibles;   ///< Zbiór punktów do zebrania
    std::set<QPoint, QPointCompare> powerUps;       ///< Zbiór power-upów

    /**
     * @brief Inicjalizuje planszę z ścianami, punktami i pozycjami startowymi
     */
    void initializeBoard();
};

#endif ///GAMEBOARD_H