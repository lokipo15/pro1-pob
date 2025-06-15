/**
 * @file GameOverScreen.h
 * @brief Ekran końca gry z opcjami dla gracza
 * @author Gabriel Boruń, Konrad Gębski
 * @date 25/04/2025
 */

#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QKeyEvent>
#include "ScoreManager.h"

/**
 * @brief Klasa reprezentująca ekran końca gry
 * 
 * Wyświetla wynik gracza, opcje zapisu do tablicy wyników
 * oraz przyciski nawigacyjne (restart, menu główne, wyjście).
 */
class GameOverScreen : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Konstruktor ekranu końca gry
     * @param parent Rodzic widget'u
     */
    explicit GameOverScreen(QWidget *parent = nullptr);
    /**
     * @brief Ustawia wynik końcowy gracza
     * @param score Wynik gracza
     */
    void setScore(int score);
    /**
     * @brief Pobiera wskaźnik na manager wyników
     * @return Wskaźnik na obiekt ScoreManager
     */
    ScoreManager* getScoreManager() { return &scoreManager; }

signals:
    void restartRequested();        ///< Sygnał żądania restartu gry
    void mainMenuRequested();       ///< Sygnał powrotu do menu głównego
    void exitRequested();           ///< Sygnał wyjścia z gry
    void scoreboardRequested();     ///< Sygnał wyświetlenia tablicy wyników

protected:
    /**
     * @brief Obsługuje zdarzenia klawiatury
     * @param event Zdarzenie naciśnięcia klawisza
     */
    void keyPressEvent(QKeyEvent *event) override;
    /**
     * @brief Obsługuje malowanie widget'u
     * @param event Zdarzenie malowania
     */
    void paintEvent(QPaintEvent *event) override;

private slots:
    /**
     * @brief Slot obsługujący kliknięcie przycisku restart
     */
    void onRestartClicked();
    /**
     * @brief Slot obsługujący kliknięcie przycisku menu głównego
     */
    void onMainMenuClicked();
    /**
     * @brief Slot obsługujący kliknięcie przycisku wyjścia
     */
    void onExitClicked();
    /**
     * @brief Slot obsługujący kliknięcie przycisku tablicy wyników
     */
    void onScoreboardClicked();
    /**
     * @brief Slot obsługujący kliknięcie przycisku zapisu wyniku
     */
    void onSaveScoreClicked();

private:
    QPushButton *restartButton;         ///< Przycisk restartu gry
    QPushButton *mainMenuButton;        ///< Przycisk powrotu do menu
    QPushButton *exitButton;            ///< Przycisk wyjścia z gry
    QPushButton *scoreboardButton;      ///< Przycisk tablicy wyników
    QPushButton *saveScoreButton;       ///< Przycisk zapisu wyniku
    QLabel *gameOverLabel;              ///< Etykieta "Game Over"
    QLabel *scoreLabel;                 ///< Etykieta wyświetlająca wynik
    QLabel *nameLabel;                  ///< Etykieta do wprowadzania imienia
    QLineEdit *nameInput;               ///< Pole do wprowadzania imienia
    QVBoxLayout *layout;                ///< Główny układ pionowy
    QHBoxLayout *nameLayout;            ///< Układ poziomy dla imienia

    int selectedButton;                 ///< Aktualnie wybrany przycisk (0-3)
    int finalScore;                     ///< Końcowy wynik gracza
    bool isNewHighScore;                ///< Czy wynik to nowy rekord
    bool scoreSaved;                    ///< Czy wynik został już zapisany

    ScoreManager scoreManager;          ///< Manager wyników

    /**
     * @brief Aktualizuje wizualny wybór przycisków
     */
    void updateButtonSelection();
    /**
     * @brief Sprawdza czy wynik to nowy rekord
     */
    void checkHighScore();
    /**
     * @brief Konfiguruje pole do wprowadzania imienia
     */
    void setupNameInput();
    /**
     * @brief Ukrywa pole do wprowadzania imienia
     */
    void hideNameInput();
};

#endif ///GAMEOVERSCREEN_H