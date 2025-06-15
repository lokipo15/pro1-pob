/**
 * @file Ghost.h
 * @brief Klasa bazowa dla wszystkich duchów w grze
 * @author Gabriel Boruń, Konrad Gębski
 * @date 25/04/2025
 */

#ifndef GHOST_H
#define GHOST_H

#include "Entity.h"
#include <QColor>

class GameBoard;
class Pacman;

/**
 * @brief Klasa bazowa reprezentująca ducha w grze Pacman
 * 
 * Dziedziczy po Entity i implementuje zachowania specyficzne dla duchów:
 * różne tryby (CHASE, SCATTER, FRIGHTENED, EATEN), sztuczną inteligencję
 * i interakcje z Pacmanem.
 */
class Ghost : public Entity {
public:
    /**
     * @brief Wyliczenie trybów zachowania ducha
     */
    enum Mode { 
        CHASE,      ///< Tryb pogoni za Pacmanem
        SCATTER,    ///< Tryb rozproszenia - udają się do swoich rogów
        FRIGHTENED, ///< Tryb przestraszenia - można ich zjeść
        EATEN       ///< Tryb po zjedzeniu - wracają do bazy
    };

    /**
     * @brief Konstruktor ducha
     * @param startPos Pozycja startowa ducha na planszy
     */
    Ghost(const QPointF &startPos);
    /**
     * @brief Wirtualny destruktor
     */
    virtual ~Ghost() = default;

    /**
     * @brief Rysuje ducha na ekranie
     * @param painter Obiekt do rysowania
     */
    void draw(QPainter &painter) override;
    /**
     * @brief Porusza duchem na planszy
     * @param board Wskaźnik na planszę gry
     * @param deltaTime Czas który upłynął od ostatniej klatki
     */
    void move(GameBoard *board, float deltaTime) override;

    /**
     * @brief Porusza duchem z uwzględnieniem pozycji Pacmana
     * @param board Wskaźnik na planszę gry
     * @param deltaTime Czas który upłynął od ostatniej klatki
     * @param pacman Wskaźnik na obiekt Pacmana
     */
    virtual void move(GameBoard *board, float deltaTime, Pacman *pacman);

    /**
     * @brief Ustawia tryb zachowania ducha
     * @param mode Nowy tryb ducha
     */
    void setMode(Mode mode) { currentMode = mode; }
    /**
     * @brief Pobiera aktualny tryb ducha
     * @return Aktualny tryb zachowania
     */
    Mode getMode() const { return currentMode; }
    /**
     * @brief Ustawia kolor ducha
     * @param color Nowy kolor ducha
     */
    void setColor(const QColor &color) { normalColor = color; }

    /**
     * @brief Aktualizuje licznik czasu trybu
     * @param deltaTime Czas który upłynął od ostatniej klatki
     */
    void updateModeTimer(float deltaTime);
    /**
     * @brief Resetuje licznik czasu trybu
     */
    void resetModeTimer() { modeTimer = 0.0f; }

    /**
     * @brief Wprowadza ducha w tryb przestraszenia
     * @param duration Czas trwania trybu przestraszenia
     */
    void enterFrightenedMode(float duration);
    /**
     * @brief Aktualizuje tryb przestraszenia
     * @param deltaTime Czas który upłynął od ostatniej klatki
     */
    void updateFrightenedMode(float deltaTime);
    /**
     * @brief Sprawdza czy duch jest podatny na zjedzenie
     * @return True jeśli duch może zostać zjedzony
     */
    bool isVulnerable() const { return currentMode == FRIGHTENED; }
    /**
     * @brief Obsługuje zjedzenie ducha przez Pacmana
     */
    void eatGhost();

    /**
     * @brief Oblicza cel ruchu ducha (implementowane w klasach potomnych)
     * @param pacman Wskaźnik na obiekt Pacmana
     * @return Pozycja celu na siatce planszy
     */
    virtual QPoint calculateTarget(Pacman *pacman) { return getGridPosition(); }

    /**
     * @brief Zwraca róg planszy dla trybu SCATTER (implementowane w klasach potomnych)
     * @return Pozycja rogu na siatce planszy
     */
    virtual QPoint getScatterCorner() const { return QPoint(0, 0); }

protected:
    Mode currentMode;                   ///< Aktualny tryb zachowania ducha
    QColor normalColor;                 ///< Normalny kolor ducha
    QColor frightenedColor;             ///< Kolor gdy przestraszony

    Direction lastValidDirection;       ///< Ostatni prawidłowy kierunek ruchu
    float directionChangeTimer;         ///< Timer do losowej zmiany kierunku

    float modeTimer;                    ///< Licznik czasu aktualnego trybu
    static const float SCATTER_TIME;    ///< Czas trwania trybu scatter
    static const float CHASE_TIME;      ///< Czas trwania trybu chase

    float frightenedTimer;              ///< Licznik czasu trybu przestraszenia
    float frightenedDuration;           ///< Czas trwania trybu przestraszenia
    float blinkTimer;                   ///< Timer do animacji "błyskania"

    /**
     * @brief Zwraca losowy kierunek ruchu
     * @return Losowy kierunek
     */
    Direction getRandomDirection();
    /**
     * @brief Zwraca kierunek przeciwny do podanego
     * @param dir Kierunek wejściowy
     * @return Kierunek przeciwny
     */
    Direction getOppositeDirection(Direction dir);
    /**
     * @brief Sprawdza czy pozycja jest skrzyżowaniem
     * @param pos Pozycja do sprawdzenia
     * @param board Wskaźnik na planszę gry
     * @return True jeśli pozycja jest skrzyżowaniem
     */
    bool isIntersection(const QPoint &pos, GameBoard *board);
    /**
     * @brief Wybiera kierunek na skrzyżowaniu
     * @param board Wskaźnik na planszę gry
     */
    void chooseDirectionAtIntersection(GameBoard *board);
    /**
     * @brief Wykonuje płynny ruch ducha
     * @param board Wskaźnik na planszę gry
     * @param deltaTime Czas który upłynął od ostatniej klatki
     */
    void smoothMove(GameBoard *board, float deltaTime);
    /**
     * @brief Wybiera kierunek na podstawie pozycji celu
     * @param target Pozycja celu
     * @param board Wskaźnik na planszę gry
     */
    void chooseTargetBasedDirection(const QPoint &target, GameBoard *board);
};

#endif