/**
 * @file GameWindow.h
 * @brief Główne okno aplikacji gry Pacman
 * @author Gabriel Boruń, Konrad Gębski
 * @date 25/04/2025
 */

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "Game.h"
#include "MainMenu.h"
#include "GameOverScreen.h"
#include "WinScreen.h"
#include "ScoreboardWidget.h"

/**
 * @brief Klasa reprezentująca główne okno aplikacji
 * 
 * Zarządza przejściami między różnymi ekranami gry:
 * menu główne, gra, ekran końca gry, tablica wyników.
 */
class GameWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Konstruktor głównego okna
     * @param parent Rodzic okna
     */
    GameWindow(QWidget *parent = nullptr);
    /**
     * @brief Destruktor głównego okna
     */
    ~GameWindow();

private slots:
    /**
     * @brief Slot obsługujący żądanie rozpoczęcia gry
     */
    void onStartGameRequested();
    /**
     * @brief Slot obsługujący żądanie restartu gry
     */
    void onRestartRequested();
    /**
     * @brief Slot obsługujący żądanie powrotu do menu głównego
     */
    void onMainMenuRequested();
    /**
     * @brief Slot obsługujący żądanie wyjścia z gry
     */
    void onExitRequested();
    /**
     * @brief Slot obsługujący żądanie wyświetlenia tablicy wyników
     */
    void onScoreboardRequested();
    /**
     * @brief Slot obsługujący żądanie powrotu z tablicy wyników
     */
    void onScoreboardBackRequested();
    /**
     * @brief Slot obsługujący zmianę stanu gry
     * @param newState Nowy stan gry
     */
    void onGameStateChanged(GameState newState);
    /**
     * @brief Slot obsługujący żądanie zapisu wyniku po wygranej
     * @param playerName Imię gracza
     * @param score Wynik gracza
     */
    void onWinSaveScoreRequested(const QString &playerName, int score);
    /**
     * @brief Slot obsługujący żądanie tablicy wyników z ekranu wygranej
     */
    void onWinViewScoreboardRequested();
    /**
     * @brief Slot obsługujący żądanie ponownej gry z ekranu wygranej
     */
    void onWinPlayAgainRequested();
    /**
     * @brief Slot obsługujący żądanie wyjścia z ekranu wygranej
     */
    void onWinExitRequested();

private:
    QStackedWidget *stackedWidget;      ///< Widget do przełączania widoków
    Game *game;                         ///< Wskaźnik na główny obiekt gry
    MainMenu *mainMenu;                 ///< Wskaźnik na menu główne
    GameOverScreen *gameOverScreen;     ///< Wskaźnik na ekran końca gry
    WinScreen *winScreen;               ///< Wskaźnik na ekran wygranej
    ScoreboardWidget *scoreboardWidget; ///< Wskaźnik na tablicę wyników

    /**
     * @brief Konfiguruje interfejs użytkownika
     */
    void setupUI();
    /**
     * @brief Wyświetla menu główne
     */
    void showMainMenu();
    /**
     * @brief Wyświetla ekran gry
     */
    void showGame();
    /**
     * @brief Wyświetla ekran końca gry
     */
    void showGameOver();
    /**
     * @brief Wyświetla ekran wygranej
     */
    void showWin();
    /**
     * @brief Wyświetla tablicę wyników
     */
    void showScoreboard();
};

#endif ///GAMEWINDOW_H