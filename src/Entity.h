/**
 * @file Entity.h
 * @brief Bazowa klasa dla wszystkich ruchomych obiektów w grze
 * @author Gabriel Boruń
 * @author Konrad Gębski
 * @date 25/04/2025
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <QPointF>
#include <QPoint>
#include <QPainter>

class GameBoard;
class Pacman;

/**
 * @brief Bazowa klasa dla wszystkich ruchomych obiektów w grze
 * 
 * Klasa abstrakcyjna definiująca wspólny interfejs i funkcjonalność
 * dla Pacmana, duchów i innych ruchomych obiektów.
 */
class Entity {
public:
    /**
     * @brief Enumeracja kierunków ruchu
     */
    enum Direction { 
        None,  ///< Brak ruchu
        Up,    ///< Ruch w górę
        Down,  ///< Ruch w dół
        Left,  ///< Ruch w lewo
        Right  ///< Ruch w prawo
    };

    /**
     * @brief Konstruktor encji
     * @param startPos Pozycja startowa encji
     */
    Entity(const QPointF &startPos);
    
    /**
     * @brief Wirtualny destruktor
     */
    virtual ~Entity() = default;

    /**
     * @brief Rysuje encję na ekranie
     * @param painter Obiekt do rysowania
     */
    virtual void draw(QPainter &painter) = 0;
    
    /**
     * @brief Porusza encją na planszy
     * @param board Wskaźnik na planszę gry
     * @param deltaTime Czas od ostatniej aktualizacji
     */
    virtual void move(GameBoard *board, float deltaTime) = 0;

    /**
     * @brief Zwraca pozycję encji na siatce
     * @return Pozycja na siatce jako QPoint
     */
    QPoint getGridPosition() const;
    
    /**
     * @brief Zwraca aktualną pozycję encji
     * @return Pozycja jako QPointF
     */
    QPointF getPosition() const { return position; }
    
    /**
     * @brief Ustawia nową pozycję encji
     * @param pos Nowa pozycja
     */
    void setPosition(const QPointF &pos) { position = pos; }

    /**
     * @brief Sprawdza czy encja jest w centrum komórki siatki
     * @return true jeśli encja jest wycentrowana
     */
    bool isAtGridCenter() const;
    
    /**
     * @brief Zwraca docelową pozycję encji
     * @return Docelowa pozycja jako QPointF
     */
    QPointF getTargetPosition() const { return targetPosition; }

protected:
    QPointF position; ///< Aktualna pozycja encji w pikselach
    QPointF targetPosition; ///< Docelowa pozycja na siatce
    Direction currentDirection; ///< Aktualny kierunek ruchu
    Direction nextDirection; ///< Następny kierunek ruchu (buforowany)

    float moveSpeed; ///< Prędkość ruchu w komórkach na sekundę

    static const int CELL_SIZE = 30; ///< Rozmiar pojedynczej komórki siatki w pikselach

    /**
     * @brief Oblicza następną pozycję na podstawie kierunku i czasu
     * @param dir Kierunek ruchu
     * @param deltaTime Czas od ostatniej aktualizacji
     * @return Obliczona pozycja
     */
    QPointF calculateNextPosition(Direction dir, float deltaTime) const;
    
    /**
     * @brief Sprawdza czy można przejść na daną pozycję
     * @param gridPos Pozycja na siatce do sprawdzenia
     * @param board Wskaźnik na planszę gry
     * @return true jeśli ruch jest możliwy
     */
    bool canMoveTo(const QPoint &gridPos, GameBoard *board) const;
    
    /**
     * @brief Aktualizuje docelową pozycję encji
     */
    void updateTargetPosition();
};

#endif ///ENTITY_H

