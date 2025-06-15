/**
 * @file ScoreboardWidget.h
 * @brief Widget wyświetlający tablicę najlepszych wyników
 * @author Gabriel Boruń, Konrad Gębski
 * @date 25/04/2025
 */

#ifndef SCOREBOARDWIDGET_H
#define SCOREBOARDWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QKeyEvent>
#include "ScoreManager.h"

/**
 * @brief Klasa widget'u tablicy wyników
 * 
 * Wyświetla listę najlepszych wyników graczy
 * z możliwością przewijania.
 */
class ScoreboardWidget : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Konstruktor widget'u tablicy wyników
     * @param parent Rodzic widget'u
     */
    explicit ScoreboardWidget(QWidget *parent = nullptr);
    /**
     * @brief Odświeża wyświetlaną listę wyników
     */
    void refreshScores();

signals:
    void backRequested();   ///< Sygnał żądania powrotu do poprzedniego ekranu

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
     * @brief Slot obsługujący kliknięcie przycisku powrotu
     */
    void onBackClicked();

private:
    QVBoxLayout *layout;            ///< Główny układ pionowy
    QLabel *titleLabel;             ///< Etykieta tytułu
    QScrollArea *scrollArea;        ///< Obszar przewijania
    QWidget *scoresWidget;          ///< Widget zawierający wyniki
    QVBoxLayout *scoresLayout;      ///< Układ wyników
    QPushButton *backButton;        ///< Przycisk powrotu

    ScoreManager scoreManager;      ///< Manager wyników

    /**
     * @brief Konfiguruje interfejs użytkownika
     */
    void setupUI();
    /**
     * @brief Aktualizuje wyświetlanie wyników
     */
    void updateScoreDisplay();
};

#endif ///SCOREBOARDWIDGET_H