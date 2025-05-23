//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#include "GameWindow.h"
#include <QApplication>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Pacman"); // Ustawia tytuł okna na "Pacman"
    setFixedSize(600, 650); // Ustawia stały rozmiar okna na 600x650 pikseli

    game = new Game(this);// Tworzy nową instancję gry
    setCentralWidget(game); // ustawia ją jako centralny widget okna głównego
}
// Destruktor
GameWindow::~GameWindow() {
    // Game będzie automatycznie usunięty, ponieważ jest widgetem potomnym
}