//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#include "Ghost.h"
#include "GameBoard.h"
#include "Pacman.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

// Mode timing constants
const float Ghost::SCATTER_TIME = 7.0f;  // 7 sekund w trybie scatter
const float Ghost::CHASE_TIME = 20.0f;   // 20 sekund w trybie chase

Ghost::Ghost(const QPointF &startPos)
    : Entity(startPos), currentMode(SCATTER), frightenedColor(Qt::blue),
      lastValidDirection(None), directionChangeTimer(0.0f), modeTimer(0.0f) {

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
        // Mruganie pod koniec trybu frightened
        if (frightenedTimer > frightenedDuration * 0.7f) {
            // Mrugaj między niebieskim a białym
            if (static_cast<int>(blinkTimer * 8) % 2 == 0) {
                painter.setBrush(frightenedColor);
            } else {
                painter.setBrush(Qt::white);
            }
        } else {
            painter.setBrush(frightenedColor);
        }
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

        // Źrenice - kierunek zależy od trybu
        painter.setBrush(Qt::black);
        if (currentMode == FRIGHTENED) {
            // W trybie frightened oczy są większe i "przestraszone"
            QRect leftPupil(leftEye.x() + 1, leftEye.y() + 3, 4, 2);
            QRect rightPupil(rightEye.x() + 1, rightEye.y() + 3, 4, 2);
            painter.drawEllipse(leftPupil);
            painter.drawEllipse(rightPupil);
        } else {
            QRect leftPupil(leftEye.x() + 2, leftEye.y() + 2, 2, 2);
            QRect rightPupil(rightEye.x() + 2, rightEye.y() + 2, 2, 2);
            painter.drawEllipse(leftPupil);
            painter.drawEllipse(rightPupil);
        }
    }
}

// Stara metoda move (bez Pacmana) - używa losowego ruchu
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

// Nowa metoda move (z Pacmanem) - używa inteligentnego ruchu
void Ghost::move(GameBoard *board, float deltaTime, Pacman *pacman) {
    // Aktualizuj tryb frightened jeśli aktywny
    updateFrightenedMode(deltaTime);

    directionChangeTimer -= deltaTime;

    // Sprawdź czy jesteśmy na skrzyżowaniu i czy trzeba wybrać nowy kierunek
    if (isAtGridCenter()) {
        QPoint currentGrid = getGridPosition();

        if (isIntersection(currentGrid, board) ||
            !canMoveTo(currentGrid + QPoint(
                currentDirection == Left ? -1 : currentDirection == Right ? 1 : 0,
                currentDirection == Up ? -1 : currentDirection == Down ? 1 : 0
            ), board)) {

            if (currentMode == FRIGHTENED) {
                chooseDirectionAtIntersection(board);
            } else if (currentMode == EATEN) {
                // W trybie eaten kieruj się do pozycji startowej
                // Dla uproszczenia używamy pozycji (10, 10)
                chooseTargetBasedDirection(QPoint(10, 10), board);
            } else {
                // POPRAWKA: Prawidłowa logika wyboru targetu
                QPoint target;
                if (currentMode == SCATTER) {
                    target = getScatterCorner();
                } else { // CHASE
                    target = calculateTarget(pacman);
                }
                chooseTargetBasedDirection(target, board);
            }
            }
    }

    // Płynny ruch
    smoothMove(board, deltaTime);
}

void Ghost::updateModeTimer(float deltaTime) {
    if (currentMode == FRIGHTENED || currentMode == EATEN) {
        return; // Nie aktualizuj timera w specjalnych trybach
    }

    modeTimer += deltaTime;

    if (currentMode == SCATTER && modeTimer >= SCATTER_TIME) {
        currentMode = CHASE;
        modeTimer = 0.0f;
    } else if (currentMode == CHASE && modeTimer >= CHASE_TIME) {
        currentMode = SCATTER;
        modeTimer = 0.0f;
    }
}

void Ghost::chooseTargetBasedDirection(const QPoint &target, GameBoard *board) {
    QPoint currentGrid = getGridPosition();
    Direction opposite = getOppositeDirection(lastValidDirection);

    std::vector<Direction> possibleDirs;
    std::vector<float> distances;

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

            // Oblicz odległość do celu
            float dx = testPos.x() - target.x();
            float dy = testPos.y() - target.y();
            distances.push_back(sqrt(dx*dx + dy*dy));
        }
    }

    // Wybierz kierunek z najmniejszą odległością do celu
    if (!possibleDirs.empty()) {
        int bestIndex = 0;
        for (int i = 1; i < possibleDirs.size(); i++) {
            if (distances[i] < distances[bestIndex]) {
                bestIndex = i;
            }
        }
        currentDirection = possibleDirs[bestIndex];
    } else {
        // Jeśli brak opcji, zawróć
        currentDirection = opposite;
    }
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

void Ghost::enterFrightenedMode(float duration) {
    currentMode = FRIGHTENED;
    frightenedTimer = 0.0f;
    frightenedDuration = duration;
    blinkTimer = 0.0f;

    // Zmień kierunek na przeciwny (jeśli się porusza)
    if (currentDirection != None) {
        currentDirection = getOppositeDirection(currentDirection);
        lastValidDirection = currentDirection;
    }

    // Zmniejsz prędkość w trybie frightened
    moveSpeed = 4.0f; // Wolniejszy od normalnej prędkości (6.0f)
}

void Ghost::updateFrightenedMode(float deltaTime) {
    if (currentMode != FRIGHTENED) return;

    frightenedTimer += deltaTime;
    blinkTimer += deltaTime;

    // Sprawdź czy czas frightened się kończy
    if (frightenedTimer >= frightenedDuration) {
        currentMode = CHASE; // Wróć do trybu chase
        moveSpeed = 6.0f; // Przywróć normalną prędkość
        modeTimer = 0.0f; // Reset mode timer
    }
}

void Ghost::eatGhost() {
    currentMode = EATEN;
    moveSpeed = 12.0f; // Bardzo szybki powrót do bazy
    // W prawdziwym Pacmanie duch wraca do bazy, ale dla uproszczenia
    // możemy go po prostu zrestartować po krótkiej chwili
}