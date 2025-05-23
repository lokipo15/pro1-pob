//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#ifndef GHOST_H
#define GHOST_H


#include "GameBoard.h"

class Ghost { // Klasa ducha
public:
    enum Direction { Up, Down, Left, Right }; // Dozwolone kierunki

    Ghost(const QPoint &startPos); // Konstruktor

    void draw(QPainter &painter); // Rysowanie ducha
    void move(GameBoard *board); // Ruch ducha po planszy

    QPoint getPosition() const; // Zwrócenie aktualnej poz. ducha

private:
    QPoint position; // Pozycja ducha na planszy
    Direction direction; // Kierunek ducha
    QColor color; // Kolor ducha

    static const int CELL_SIZE = 30; // Rozm. poj. komórki

    Direction getRandomDirection(); // Losowanie kierunku
};

#endif //GHOST_H
