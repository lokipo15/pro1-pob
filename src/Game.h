/**
 * @file Game.h
 * @brief Główna klasa zarządzająca logiką gry Pacman
 * @author Gabriel Boruń
 * @author Konrad Gębski
 * @date 25/04/2025
 */

#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include "GameBoard.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"
#include "PowerUp.h"
#include "PowerPellet.h"
#include "AudioManager.h"
#include <vector>

/**
 * @brief Enumeracja stanów gry
 */
enum GameState {
    MENU,       ///< Stan menu głównego
    PLAYING,    ///< Stan rozgrywki
    PAUSED,     ///< Stan pauzy
    GAME_OVER,  ///< Stan przegranej
    WIN         ///< Stan wygranej
};

/**
 * @brief Główna klasa zarządzająca logiką gry Pacman
 * 
 * Klasa odpowiedzialna za kontrolę stanu gry, aktualizację obiektów,
 * obsługę kolizji i renderowanie interfejsu gry.
 */
class Game : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy Game
     * @param parent Wskaźnik na rodzica widget'u
     */
    Game(QWidget *parent = nullptr);
    
    /**
     * @brief Destruktor klasy Game
     */
    ~Game();

    /**
     * @brief Rozpoczyna nową grę
     */
    void startGame();
    
    /**
     * @brief Zatrzymuje grę (pauza)
     */
    void pauseGame();
    
    /**
     * @brief Wznawia zatrzymaną grę
     */
    void resumeGame();
    
    /**
     * @brief Resetuje grę do stanu początkowego
     */
    void resetGame();
    
    /**
     * @brief Zwraca aktualny stan gry
     * @return Aktualny stan gry
     */
    GameState getCurrentState() const { return currentState; }
    
    /**
     * @brief Zwraca aktualny wynik gracza
     * @return Liczba zdobytych punktów
     */
    int getScore() const { return score; }
    
    /**
     * @brief Zwraca liczbę pozostałych żyć
     * @return Liczba żyć gracza
     */
    int getLives() const { return lives; }
    
    /**
     * @brief Zwraca wskaźnik na menedżer audio
     * @return Wskaźnik na AudioManager
     */
    AudioManager* getAudioManager() { return audioManager; }

signals:
    /**
     * @brief Sygnał emitowany przy zmianie stanu gry
     * @param newState Nowy stan gry
     */
    void gameStateChanged(GameState newState);
    
    /**
     * @brief Sygnał emitowany przy zmianie wyniku
     * @param newScore Nowy wynik
     */
    void scoreChanged(int newScore);
    
    /**
     * @brief Sygnał emitowany przy zmianie liczby żyć
     * @param newLives Nowa liczba żyć
     */
    void livesChanged(int newLives);

protected:
    /**
     * @brief Obsługuje zdarzenie rysowania
     * @param event Zdarzenie rysowania
     */
    void paintEvent(QPaintEvent *event) override;
    
    /**
     * @brief Obsługuje naciśnięcie klawisza
     * @param event Zdarzenie klawiatury
     */
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    /**
     * @brief Slot aktualizujący stan gry
     */
    void update();

private:
    GameState currentState; ///< Aktualny stan gry

    QTimer *timer; ///< Timer do aktualizacji gry
    QElapsedTimer elapsedTimer; ///< Timer do pomiaru czasu delta
    qint64 lastUpdateTime; ///< Czas ostatniej aktualizacji w milisekundach

    GameBoard *board; ///< Wskaźnik na planszę gry
    Pacman *pacman; ///< Wskaźnik na obiekt Pacmana
    std::vector<Ghost*> ghosts; ///< Wektor wskaźników na wszystkie duchy

    Blinky *blinky; ///< Wskaźnik na ducha Blinky (czerwony)
    Pinky *pinky; ///< Wskaźnik na ducha Pinky (różowy)
    Inky *inky; ///< Wskaźnik na ducha Inky (niebieski)
    Clyde *clyde; ///< Wskaźnik na ducha Clyde (pomarańczowy)

    std::vector<PowerUp*> powerUps; ///< Wektor power-upów na planszy
    float powerUpTimer; ///< Timer aktywności power-upów w sekundach
    bool powerUpActive; ///< Flaga aktywności power-upu
    int ghostEatenMultiplier; ///< Mnożnik punktów za zjedzenie duchów

    int score; ///< Aktualny wynik gracza
    int lives; ///< Pozostała liczba żyć
    bool gameOver; ///< Flaga oznaczająca koniec gry
    
    AudioManager *audioManager; ///< Menedżer odtwarzania dźwięków

    /**
     * @brief Inicjalizuje wszystkie komponenty gry
     */
    void initializeGame();
    
    /**
     * @brief Sprawdza kolizje między obiektami
     */
    void checkCollisions();
    
    /**
     * @brief Rysuje wynik na ekranie
     * @param painter Obiekt do rysowania
     */
    void drawScore(QPainter &painter);
    
    /**
     * @brief Rysuje ekran pauzy
     * @param painter Obiekt do rysowania
     */
    void drawPauseScreen(QPainter &painter);
    
    /**
     * @brief Odrodzi Pacmana po stracie życia
     */
    void respawnPacman();
    
    /**
     * @brief Sprawdza warunki wygranej
     */
    void checkWinCondition();
    
    /**
     * @brief Aktualizuje tryby zachowania duchów
     * @param deltaTime Czas od ostatniej aktualizacji
     */
    void updateGhostModes(float deltaTime);
    
    /**
     * @brief Aktywuje efekt power-upu
     */
    void activatePowerUp();
    
    /**
     * @brief Aktualizuje timer aktywności power-upów
     * @param deltaTime Czas od ostatniej aktualizacji
     */
    void updatePowerUpTimer(float deltaTime);
};


#endif ///GAME_H