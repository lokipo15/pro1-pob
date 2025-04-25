//
// Created by Gabriel Boruń on 25/04/2025.
//

#include "GameWindow.h"
#include <QApplication>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Pacman");
    setFixedSize(600, 650);

    game = new Game(this);
    setCentralWidget(game);
}

GameWindow::~GameWindow() {
    // Game będzie automatycznie usunięty, ponieważ jest widgetem potomnym
}