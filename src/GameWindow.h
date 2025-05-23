//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "Game.h"
#include "MainMenu.h"
#include "GameOverScreen.h"
#include "ScoreboardWidget.h"

class GameWindow : public QMainWindow { // Główne okno gry
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr); // Konstruktor
    ~GameWindow(); // Destruktor

private slots:
    void onStartGameRequested();
    void onRestartRequested();
    void onMainMenuRequested();
    void onExitRequested();
    void onScoreboardRequested();
    void onScoreboardBackRequested();
    void onGameStateChanged(GameState newState);

private:
    QStackedWidget *stackedWidget; // Widget do przełączania widoków
    Game *game; // wskaźnik na główny element interfejsu - obiekt Game
    MainMenu *mainMenu; // wskaźnik na menu główne
    GameOverScreen *gameOverScreen; // wskaźnik na ekran końca gry
    ScoreboardWidget *scoreboardWidget; // wskaźnik na tablicę wyników

    void setupUI(); // Konfiguracja interfejsu użytkownika
    void showMainMenu();
    void showGame();
    void showGameOver();
    void showScoreboard();
};

#endif //GAMEWINDOW_H