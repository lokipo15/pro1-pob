//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#include "Ghost.h"
#include "GameBoard.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

Ghost::Ghost(const QPointF &startPos)
    : Entity(startPos), currentMode(CHASE), frightenedColor(Qt::blue),
      lastValidDirection(None), directionChangeTimer(0.0f) {

    // Inicjalizacja generatora liczb losowych
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }

    // Losowy kolor
    int r = 128 + rand() % 128;
    int g = 128 + rand() % 128;
    int b = 128 + rand() % 128;
    normalColor = QColor(r, g, b);

    moveSpeed = 6.0f;  // Duchy są wolniejsze od Pacmana
    currentDirection = getRandomDirection();
}

void Ghost::draw(QPainter &painter) {
    painter.setPen(Qt::NoPen);

    // Wybór koloru w zależności od trybu
    if (currentMode == FRIGHTENED) {
        painter.setBrush(frightenedColor);
    } else if (currentMode == EATEN) {
        painter.setBrush(QColor(200, 200, 200, 100));  // Przezroczysty
    } else {
        painter.setBrush(normalColor);
    }

    // Konwersja pozycji float na piksele
    int pixelX = static_cast<int>(position.x() * CELL_SIZE);
    int pixelY = static_cast<int>(position.y() * CELL_SIZE);

    // Rysowanie ducha
    QRect bodyRect(pixelX, pixelY, CELL_SIZE, CELL_SIZE);

    // Górna część (półkole)
    painter.drawPie(bodyRect, 0, 180 * 16);

    // Dolna część (prostokąt z falowanym dołem)
    QRect lowerRect(pixelX, pixelY + CELL_SIZE/2, CELL_SIZE, CELL_SIZE/2);
    painter.drawRect(lowerRect);

    // Oczy (tylko gdy nie jest zjedzony)
    if (currentMode != EATEN) {
        painter.setBrush(Qt::white);
        QRect leftEye(pixelX + CELL_SIZE/4 - 3, pixelY + CELL_SIZE/3, 6, 6);
        QRect rightEye(pixelX + 3*CELL_SIZE/4 - 3, pixelY + CELL_SIZE/3, 6, 6);
        painter.drawEllipse(leftEye);
        painter.drawEllipse(rightEye);

        // Źrenice
        painter.setBrush(Qt::black);
        QRect leftPupil(leftEye.x() + 2, leftEye.y() + 2, 2, 2);
        QRect rightPupil(rightEye.x() + 2, rightEye.y() + 2, 2, 2);
        painter.drawEllipse(leftPupil);
        painter.drawEllipse(rightPupil);
    }
}

void Ghost::move(GameBoard *board, float deltaTime) {
    directionChangeTimer -= deltaTime;

    // Sprawdź czy jesteśmy na skrzyżowaniu i czy trzeba wybrać nowy kierunek
    if (isAtGridCenter()) {
        QPoint currentGrid = getGridPosition();

        if (isIntersection(currentGrid, board) ||
            !canMoveTo(currentGrid + QPoint(
                currentDirection == Left ? -1 : currentDirection == Right ? 1 : 0,
                currentDirection == Up ? -1 : currentDirection == Down ? 1 : 0
            ), board)) {
            chooseDirectionAtIntersection(board);
        }
    }

    // Płynny ruch
    smoothMove(board, deltaTime);
}

void Ghost::smoothMove(GameBoard *board, float deltaTime) {
    if (currentDirection == None) {
        currentDirection = getRandomDirection();
        return;
    }

    // Oblicz następną pozycję
    QPointF nextPos = calculateNextPosition(currentDirection, deltaTime);

    // Sprawdź kolizję tak samo jak Pacman
    bool canMove = true;

    switch (currentDirection) {
        case Up: {
            if (nextPos.y() < position.y()) {
                int newGridY = static_cast<int>(std::floor(nextPos.y()));
                int currentGridY = static_cast<int>(std::floor(position.y()));
                if (newGridY < currentGridY) {
                    int checkX = static_cast<int>(std::floor(position.x() + 0.5f));
                    canMove = !board->isWall(QPoint(checkX, newGridY));
                }
            }
            break;
        }
        case Down: {
            if (nextPos.y() > position.y()) {
                int newGridY = static_cast<int>(std::floor(nextPos.y() + 0.999f));
                int currentGridY = static_cast<int>(std::floor(position.y() + 0.999f));
                if (newGridY > currentGridY) {
                    int checkX = static_cast<int>(std::floor(position.x() + 0.5f));
                    canMove = !board->isWall(QPoint(checkX, newGridY));
                }
            }
            break;
        }
        case Left: {
            if (nextPos.x() < position.x()) {
                int newGridX = static_cast<int>(std::floor(nextPos.x()));
                int currentGridX = static_cast<int>(std::floor(position.x()));
                if (newGridX < currentGridX) {
                    int checkY = static_cast<int>(std::floor(position.y() + 0.5f));
                    canMove = !board->isWall(QPoint(newGridX, checkY));
                }
            }
            break;
        }
        case Right: {
            if (nextPos.x() > position.x()) {
                int newGridX = static_cast<int>(std::floor(nextPos.x() + 0.999f));
                int currentGridX = static_cast<int>(std::floor(position.x() + 0.999f));
                if (newGridX > currentGridX) {
                    int checkY = static_cast<int>(std::floor(position.y() + 0.5f));
                    canMove = !board->isWall(QPoint(newGridX, checkY));
                }
            }
            break;
        }
        default:
            break;
    }

    if (canMove) {
        position = nextPos;
        lastValidDirection = currentDirection;
    } else {
        // Zatrzymaj i wybierz nowy kierunek
        QPoint currentGrid = getGridPosition();
        position = QPointF(currentGrid.x(), currentGrid.y());
        chooseDirectionAtIntersection(board);
    }
}

Entity::Direction Ghost::getRandomDirection() {
    return static_cast<Direction>((rand() % 4) + 1);  // 1-4 (pomijamy None)
}

Entity::Direction Ghost::getOppositeDirection(Direction dir) {
    switch (dir) {
        case Up: return Down;
        case Down: return Up;
        case Left: return Right;
        case Right: return Left;
        default: return None;
    }
}

bool Ghost::isIntersection(const QPoint &pos, GameBoard *board) {
    int possibleDirections = 0;

    // Sprawdź każdy kierunek
    if (canMoveTo(pos + QPoint(0, -1), board)) possibleDirections++;
    if (canMoveTo(pos + QPoint(0, 1), board)) possibleDirections++;
    if (canMoveTo(pos + QPoint(-1, 0), board)) possibleDirections++;
    if (canMoveTo(pos + QPoint(1, 0), board)) possibleDirections++;

    return possibleDirections > 2;  // Więcej niż 2 kierunki = skrzyżowanie
}

void Ghost::chooseDirectionAtIntersection(GameBoard *board) {
    QPoint currentGrid = getGridPosition();
    Direction opposite = getOppositeDirection(lastValidDirection);

    // Lista możliwych kierunków (bez zawracania)
    std::vector<Direction> possibleDirs;

    for (int d = 1; d <= 4; d++) {
        Direction dir = static_cast<Direction>(d);
        if (dir == opposite) continue;  // Nie zawracaj

        QPoint testPos = currentGrid;
        switch (dir) {
            case Up: testPos.setY(currentGrid.y() - 1); break;
            case Down: testPos.setY(currentGrid.y() + 1); break;
            case Left: testPos.setX(currentGrid.x() - 1); break;
            case Right: testPos.setX(currentGrid.x() + 1); break;
            default: break;
        }

        if (canMoveTo(testPos, board)) {
            possibleDirs.push_back(dir);
        }
    }

    // Wybierz losowy kierunek z dostępnych
    if (!possibleDirs.empty()) {
        currentDirection = possibleDirs[rand() % possibleDirs.size()];
    } else {
        // Jeśli brak opcji, zawróć
        currentDirection = opposite;
    }
}