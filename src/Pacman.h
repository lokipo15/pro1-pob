/**
 * @file Pacman.h
 * @brief Klasa reprezentująca główną postać gracza - Pacmana
 * @author Gabriel Boruń
 * @author Konrad Gębski
 * @date 25/04/2025
 */

#ifndef PACMAN_H
#define PACMAN_H

#include "Entity.h"

class GameBoard;

/**
 * @brief Klasa reprezentująca Pacmana - główną postać sterowaną przez gracza
 * 
 * Klasa dziedziczy po Entity i implementuje specyficzne zachowania Pacmana,
 * takie jak animacja ust i reagowanie na sterowanie gracza.
 */
class Pacman : public Entity {
public:
    /**
     * @brief Konstruktor Pacmana
     * @param startPos Pozycja startowa jako QPointF
     */
    Pacman(const QPointF &startPos);

    /**
     * @brief Rysuje Pacmana na ekranie z animacją ust
     * @param painter Obiekt do rysowania
     */
    void draw(QPainter &painter) override;
    
    /**
     * @brief Porusza Pacmanem na planszy
     * @param board Wskaźnik na planszę gry
     * @param deltaTime Czas od ostatniej aktualizacji
     */
    void move(GameBoard *board, float deltaTime) override;

    /**
     * @brief Ustawia kierunek ruchu Pacmana
     * @param dir Nowy kierunek ruchu
     */
    void setDirection(Direction dir);

    /**
     * @brief Zwraca aktualny kierunek ruchu Pacmana
     * @return Aktualny kierunek ruchu
     */
    Direction getCurrentDirection() const { return currentDirection; }

private:
    float mouthAngle; ///< Kąt otwarcia ust do animacji
    bool mouthOpening; ///< Flaga określająca czy usta się otwierają

    /**
     * @brief Wykonuje płynny ruch Pacmana
     * @param board Wskaźnik na planszę gry
     * @param deltaTime Czas od ostatniej aktualizacji
     */
    void smoothMove(GameBoard *board, float deltaTime);
    
    /**
     * @brief Sprawdza czy można skręcić w danej pozycji
     * @param pos Pozycja do sprawdzenia
     * @param dir Kierunek skrętu
     * @param board Wskaźnik na planszę gry
     * @return true jeśli można skręcić
     */
    bool canTurnAt(const QPointF &pos, Direction dir, GameBoard *board) const;
    
    /**
     * @brief Zwraca wyrównaną pozycję przy zmianie kierunku
     * @param fromDir Kierunek z którego się poruszamy
     * @param toDir Kierunek do którego się poruszamy
     * @return Wyrównana pozycja
     */
    QPointF getAlignedPosition(Direction fromDir, Direction toDir) const;
    
    /**
     * @brief Aktualizuje animację otwierania i zamykania ust
     * @param deltaTime Czas od ostatniej aktualizacji
     */
    void updateMouthAnimation(float deltaTime);
};

#endif
