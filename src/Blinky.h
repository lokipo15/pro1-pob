/**
 * @file Blinky.h
 * @brief Implementacja ducha Blinky
 * @author Gabriel Boruń
 * @date 23/05/2025
 */

#ifndef BLINKY_H
#define BLINKY_H

#include "Ghost.h"

/**
 * @brief Klasa reprezentująca ducha Blinky (czerwony duch)
 * 
 * Blinky to najagresywniejszy duch, który bezpośrednio goni Pacmana.
 * Jest najszybszy i najbardziej niebezpieczny w trybie CHASE.
 */
class Blinky : public Ghost {
public:
    /**
     * @brief Konstruktor ducha Blinky
     * @param startPos Pozycja startowa na planszy
     */
    Blinky(const QPointF &startPos);

    /**
     * @brief Oblicza cel dla Blinky - goni Pacmana bezpośrednio
     * @param pacman Wskaźnik na obiekt Pacmana
     * @return Pozycja celu na siatce planszy
     */
    QPoint calculateTarget(Pacman *pacman) override;

    /**
     * @brief Zwraca róg planszy dla trybu SCATTER
     * @return Pozycja prawego górnego rogu planszy
     */
    QPoint getScatterCorner() const override;
};



#endif ///BLINKY_H
