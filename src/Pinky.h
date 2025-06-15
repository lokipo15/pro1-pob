/**
 * @file Pinky.h
 * @brief Implementacja ducha Pinky
 * @author Gabriel Boruń, Konrad Gębski
 * @date 25/04/2025
 */

#ifndef PINKY_H
#define PINKY_H

#include "Ghost.h"

/**
 * @brief Klasa reprezentująca ducha Pinky (różowy duch)
 * 
 * Pinky to strategiczny duch, który próbuje zaatakować Pacmana
 * z przodu, celując 4 komórki przed nim.
 */
class Pinky : public Ghost {
public:
    /**
     * @brief Konstruktor ducha Pinky
     * @param startPos Pozycja startowa na planszy
     */
    Pinky(const QPointF &startPos);

    /**
     * @brief Oblicza cel dla Pinky - celuje 4 komórki przed Pacmanem
     * @param pacman Wskaźnik na obiekt Pacmana
     * @return Pozycja celu na siatce planszy
     */
    QPoint calculateTarget(Pacman *pacman) override;

    /**
     * @brief Zwraca róg planszy dla trybu SCATTER
     * @return Pozycja lewego górnego rogu planszy
     */
    QPoint getScatterCorner() const override;
};

#endif

