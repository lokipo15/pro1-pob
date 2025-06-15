/**
 * @file Clyde.h
 * @brief Implementacja ducha Clyde
 * @author Gabriel Boruń
 * @date 23/05/2025
 */

#ifndef CLYDE_H
#define CLYDE_H

#include "Ghost.h"

/**
 * @brief Klasa reprezentująca ducha Clyde (pomarańczowy duch)
 * 
 * Clyde to nieprzewidywalny duch, który zmienia zachowanie
 * w zależności od odległości do Pacmana.
 */
class Clyde : public Ghost {
public:
    /**
     * @brief Konstruktor ducha Clyde
     * @param startPos Pozycja startowa na planszy
     */
    Clyde(const QPointF &startPos);

    /**
     * @brief Oblicza cel dla Clyde - zachowanie zależne od odległości
     * @param pacman Wskaźnik na obiekt Pacmana
     * @return Pozycja celu na siatce planszy
     */
    QPoint calculateTarget(Pacman *pacman) override;

    /**
     * @brief Zwraca róg planszy dla trybu SCATTER
     * @return Pozycja lewego dolnego rogu planszy
     */
    QPoint getScatterCorner() const override;

private:
    static const float RETREAT_DISTANCE;  ///< Odległość przy której Clyde ucieka
};

#endif ///CLYDE_H
