/**
 * @file Inky.h
 * @brief Implementacja ducha Inky
 * @author Gabriel Boruń
 * @date 23/05/2025
 */

#ifndef INKY_H
#define INKY_H

#include "Ghost.h"

class Blinky;

/**
 * @brief Klasa reprezentująca ducha Inky (niebieski duch)
 * 
 * Inky to najbardziej nieprzewidywalny duch, który używa
 * inteligentnej strategii opierającej się na pozycji Blinky'ego.
 */
class Inky : public Ghost {
public:
    /**
     * @brief Konstruktor ducha Inky
     * @param startPos Pozycja startowa na planszy
     * @param blinky Wskaźnik na ducha Blinky (potrzebny do obliczeń)
     */
    Inky(const QPointF &startPos, Blinky *blinky);

    /**
     * @brief Oblicza cel dla Inky - inteligentne określanie ruchu
     * 
     * Używa pozycji Blinky'ego do obliczenia zaawansowanej strategii atakojącej.
     * @param pacman Wskaźnik na obiekt Pacmana
     * @return Pozycja celu na siatce planszy
     */
    QPoint calculateTarget(Pacman *pacman) override;

    /**
     * @brief Zwraca róg planszy dla trybu SCATTER
     * @return Pozycja prawego dolnego rogu planszy
     */
    QPoint getScatterCorner() const override;

private:
    Blinky *blinkyRef;  ///< Referencja do Blinky'ego do obliczeń strategii
};

#endif ///INKY_H
