/**
 * @file WinScreen.h
 * @brief Ekran wygranej z opcjami dla gracza
 * @author Gabriel Boruń, Konrad Gębski
 * @date 12/06/2025
 */

#ifndef WINSCREEN_H
#define WINSCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QKeyEvent>
#include "ScoreManager.h"

/**
 * @brief Klasa reprezentująca ekran wygranej
 * 
 * Wyświetla gratulacje, wynik gracza i opcje:
 * zapis wyniku, tablica wyników, ponowna gra, wyjście.
 */
class WinScreen : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Konstruktor ekranu wygranej
     * @param parent Rodzic widget'u
     */
    explicit WinScreen(QWidget *parent = nullptr);
    
    /**
     * @brief Ustawia wynik gracza
     * @param score Osiągnięty wynik
     */
    void setScore(int score);
    /**
     * @brief Ustawia manager wyników
     * @param manager Wskaźnik na obiekt ScoreManager
     */
    void setScoreManager(ScoreManager *manager);

signals:
    void saveScoreRequested(const QString &playerName, int score); ///< Sygnał zapisu wyniku
    void viewScoreboardRequested();         ///< Sygnał wyświetlenia tablicy wyników
    void playAgainRequested();              ///< Sygnał ponownej gry
    void exitRequested();                   ///< Sygnał wyjścia z gry

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
     * @brief Slot obsługujący kliknięcie przycisku zapisu wyniku
     */
    void onSaveScoreClicked();
    /**
     * @brief Slot obsługujący kliknięcie przycisku tablicy wyników
     */
    void onViewScoreboardClicked();
    /**
     * @brief Slot obsługujący kliknięcie przycisku ponownej gry
     */
    void onPlayAgainClicked();
    /**
     * @brief Slot obsługujący kliknięcie przycisku wyjścia
     */
    void onExitClicked();

private:
    QLabel *titleLabel;                 ///< Etykieta tytułu
    QLabel *scoreLabel;                 ///< Etykieta wyniku
    QLabel *namePromptLabel;            ///< Etykieta zachęty do wprowadzenia imienia
    QLineEdit *nameInput;               ///< Pole wprowadzania imienia
    QPushButton *saveScoreButton;       ///< Przycisk zapisu wyniku
    QPushButton *viewScoreboardButton;  ///< Przycisk tablicy wyników
    QPushButton *playAgainButton;       ///< Przycisk ponownej gry
    QPushButton *exitButton;            ///< Przycisk wyjścia
    
    QVBoxLayout *mainLayout;            ///< Główny układ pionowy
    QHBoxLayout *nameLayout;            ///< Układ poziomy dla imienia
    QHBoxLayout *buttonLayout;          ///< Układ poziomy dla przycisków

    int currentScore;                   ///< Aktualny wynik gracza
    ScoreManager *scoreManager;         ///< Wskaźnik na manager wyników
    int selectedButton;                 ///< Aktualnie wybrany przycisk (0-3)
    bool isHighScore;                   ///< Czy wynik to rekord
    
    /**
     * @brief Aktualizuje wizualny wybór przycisków
     */
    void updateButtonSelection();
    /**
     * @brief Sprawdza czy wynik to rekord
     */
    void checkIfHighScore();
    /**
     * @brief Konfiguruje układ widget'u
     */
    void setupLayout();
};

#endif /// WINSCREEN_H