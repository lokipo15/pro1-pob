//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#ifndef PACMAN_H
#define PACMAN_H


#include "GameBoard.h"

class Pacman { // Klasa Pacman'a
public:
    enum Direction { None, Up, Down, Left, Right }; // Dozwolone kierunki ruchu

    Pacman(const QPoint &startPos); // Konstruktor

    void draw(QPainter &painter); // Rysowanie pacmana
    void move(GameBoard *board); // Poruszanie pacmana
    void setDirection(Direction dir); // Ustawianie kierunku Pacmana

    QPoint getPosition() const; // Getter obecnej pozycja pacmana

private:
    QPoint position; // Obecna pozycja pacmana
    Direction currentDirection; // Kierunek pacmana
    Direction nextDirection; // Następny krok pacmana

    static const int CELL_SIZE = 30; // Rozm. poj. komórki
};


#endif //PACMAN_H
