//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "Game.h"

class GameWindow : public QMainWindow { // Główne okno gry
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr); // Konstruktor
    ~GameWindow(); // Destruktor

private:
    Game *game; // wskaźnik na główny element interfejsu - obiekt Game
};



#endif //GAMEWINDOW_H
