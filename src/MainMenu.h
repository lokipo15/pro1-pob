/**
 * @file MainMenu.h
 * @brief Menu główne gry Pacman
 * @author Gabriel Boruń, Konrad Gębski
 * @date 25/04/2025
 */

#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QKeyEvent>

/**
 * @brief Klasa reprezentująca menu główne gry
 * 
 * Wyświetla opcje: start gry, tablica wyników, wyjście.
 * Obsługuje nawigację klawiaturą i myszką.
 */
class MainMenu : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Konstruktor menu głównego
     * @param parent Rodzic widget'u
     */
    explicit MainMenu(QWidget *parent = nullptr);

signals:
    void startGameRequested();      ///< Sygnał żądania rozpoczęcia gry
    void scoreboardRequested();     ///< Sygnał wyświetlenia tablicy wyników
    void exitRequested();           ///< Sygnał wyjścia z gry

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
     * @brief Slot obsługujący kliknięcie przycisku start
     */
    void onStartGameClicked();
    /**
     * @brief Slot obsługujący kliknięcie przycisku tablicy wyników
     */
    void onScoreboardClicked();
    /**
     * @brief Slot obsługujący kliknięcie przycisku wyjścia
     */
    void onExitClicked();

private:
    QPushButton *startButton;           ///< Przycisk rozpoczęcia gry
    QPushButton *scoreboardButton;      ///< Przycisk tablicy wyników
    QPushButton *exitButton;            ///< Przycisk wyjścia
    QLabel *titleLabel;                 ///< Etykieta tytułu gry
    QVBoxLayout *layout;                ///< Główny układ pionowy

    int selectedButton;                 ///< Aktualnie wybrany przycisk (0-2)
    
    /**
     * @brief Aktualizuje wizualny wybór przycisków
     */
    void updateButtonSelection();
};

#endif ///MAINMENU_H