/**
 * @file PowerPellet.h
 * @brief Implementacja power-pellet (duży punkt mocy)
 * @author Gabriel Boruń
 * @date 23/05/2025
 */

#ifndef POWERPELLET_H
#define POWERPELLET_H

#include "PowerUp.h"

/**
 * @brief Klasa reprezentująca power-pellet (duży punkt mocy)
 * 
 * Power-pellet to specjalny rodzaj power-up, który pozwala Pacmanowi
 * na krótki czas zjeść duchy. Ma animację migania.
 */
class PowerPellet : public PowerUp {
public:
    /**
     * @brief Konstruktor power-pelletu
     * @param position Pozycja na planszy
     */
    PowerPellet(const QPointF &position);

    /**
     * @brief Rysuje power-pellet na ekranie z animacją
     * @param painter Obiekt do rysowania
     */
    void draw(QPainter &painter) override;
    /**
     * @brief Aktywuje efekt power-pelletu na Pacmanie
     * @param pacman Wskaźnik na obiekt Pacmana
     */
    void activate(Pacman *pacman) override;
    /**
     * @brief Zwraca punkty za zebranie power-pelletu
     * @return Liczba punktów (50)
     */
    int getScore() const override;

private:
    float animationTimer;                   ///< Timer animacji migania
    bool visible;                           ///< Aktualny stan widoczności

    static const int SCORE_VALUE = 50;      ///< Wartość punktowa
    static const float FRIGHTENED_DURATION; ///< Czas trwania trybu frightened
};

#endif ///POWERPELLET_H
