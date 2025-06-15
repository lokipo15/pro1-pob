/**
 * @file Blinky.cpp
 * @brief Implementacja klasy Blinky - czerwonego ducha w grze Pacman
 * @author Gabriel Boruń, Konrad Gębski
 * @date 25/04/2025
 */

#include "Blinky.h"
#include "Pacman.h"

/**
 * @brief Konstruktor klasy Blinky
 * @param startPos Pozycja startowa ducha na planszy
 * 
 * Blinky jest czerwonym duchem, który bezpośrednio ściąga Pacmana.
 */
Blinky::Blinky(const QPointF &startPos) : Ghost(startPos) {
    normalColor = Qt::red;  /// Charakterystyczny czerwony kolor Blinky
}

/**
 * @brief Oblicza cel ruchu Blinky
 * @param pacman Wskaźnik na obiekt Pacmana
 * @return Pozycję docelową na siatce planszy
 * 
 * Blinky używa najprostszej strategii - bezpośrednio ściąga Pacmana.
 * To czyni go najbardziej agresywnym z duchow.
 */
QPoint Blinky::calculateTarget(Pacman *pacman) {
    /// Strategia: bezpośredni atak na aktualną pozycję Pacmana
    return pacman->getGridPosition();
}

/**
 * @brief Zwraca róg planszy dla trybu scatter
 * @return Pozycję prawego górnego rogu planszy
 * 
 * W trybie scatter Blinky kieruje się do prawego górnego rogu,
 * co sprawia, że krąży po obwodzie planszy.
 */
QPoint Blinky::getScatterCorner() const {
    /// Prawy górny róg planszy - charakterystyczny dla Blinky
    return QPoint(18, 1);
}