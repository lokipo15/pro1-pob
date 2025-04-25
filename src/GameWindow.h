//
// Created by Gabriel Boruń on 25/04/2025.
//

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "Game.h"

class GameWindow : public QMainWindow {
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private:
    Game *game;
};



#endif //GAMEWINDOW_H
