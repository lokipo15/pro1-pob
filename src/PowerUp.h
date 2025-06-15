/**
 * @file PowerUp.h
 * @brief Klasa bazowa dla wszystkich power-upów
 * @author Gabriel Boruń
 * @date 23/05/2025
 */

#ifndef POWERUP_H
#define POWERUP_H

#include <QPointF>
#include <QPainter>

class Pacman;

/**
 * @brief Abstrakcyjna klasa bazowa dla power-upów
 * 
 * Definiuje interfejs dla wszystkich rodzajów power-upów
 * w grze Pacman (np. power-pellet).
 */
class PowerUp {
public:
    /**
     * @brief Konstruktor power-upu
     * @param position Pozycja na planszy
     */
    PowerUp(const QPointF &position);
    /**
     * @brief Wirtualny destruktor
     */
    virtual ~PowerUp() = default;

    /**
     * @brief Rysuje power-up na ekranie (implementacja w klasach potomnych)
     * @param painter Obiekt do rysowania
     */
    virtual void draw(QPainter &painter) = 0;
    /**
     * @brief Aktywuje efekt power-upu (implementacja w klasach potomnych)
     * @param pacman Wskaźnik na obiekt Pacmana
     */
    virtual void activate(Pacman *pacman) = 0;
    /**
     * @brief Zwraca punkty za zebranie power-upu (implementacja w klasach potomnych)
     * @return Liczba punktów
     */
    virtual int getScore() const = 0;

    /**
     * @brief Pobiera pozycję power-upu
     * @return Pozycja na planszy
     */
    QPointF getPosition() const { return position; }
    /**
     * @brief Pobiera pozycję na siatce planszy
     * @return Pozycja w układzie siatki
     */
    QPoint getGridPosition() const;

protected:
    QPointF position;                   ///< Pozycja power-upu na planszy
    static const int CELL_SIZE = 30;    ///< Rozmiar komórki planszy
};

#endif ///POWERUP_H
