///
/// Created by Gabriel Boruń on 25/04/2025.
/// Co-authored by Konrad Gębski on 25/04/2025.
///

#include "Pacman.h"
#include "GameBoard.h"
#include <cmath>

Pacman::Pacman(const QPointF &startPos)
    : Entity(startPos), mouthAngle(30.0f), mouthOpening(true) {
    moveSpeed = 8.0f;  /// Pacman porusza się z prędkością 8 komórek na sekundę
}

void Pacman::draw(QPainter &painter) {
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::yellow);

    /// Konwersja pozycji float na piksele
    int pixelX = static_cast<int>(position.x() * CELL_SIZE);
    int pixelY = static_cast<int>(position.y() * CELL_SIZE);

    QRect rect(pixelX, pixelY, CELL_SIZE, CELL_SIZE);

    /// Rysowanie Pacmana z otwartymi ustami
    int startAngle = 0;
    int spanAngle = 360 * 16;  /// Qt używa 1/16 stopnia

    /// Kierunek ust zależy od kierunku ruchu
    switch (currentDirection) {
        case Right:
            startAngle = mouthAngle * 16;
            spanAngle = (360 - 2 * mouthAngle) * 16;
            break;
        case Left:
            startAngle = (180 + mouthAngle) * 16;
            spanAngle = (360 - 2 * mouthAngle) * 16;
            break;
        case Up:
            startAngle = (90 + mouthAngle) * 16;
            spanAngle = (360 - 2 * mouthAngle) * 16;
            break;
        case Down:
            startAngle = (270 + mouthAngle) * 16;
            spanAngle = (360 - 2 * mouthAngle) * 16;
            break;
        default:
            painter.drawEllipse(rect);  /// Pełne koło gdy stoi
            return;
    }

    painter.drawPie(rect, startAngle, spanAngle);
}

void Pacman::move(GameBoard *board, float deltaTime) {
    /// Aktualizuj animację ust
    updateMouthAnimation(deltaTime);

    /// Jeśli Pacman stoi i gracz wybiera kierunek
    if (currentDirection == None && nextDirection != None) {
        if (canTurnAt(position, nextDirection, board)) {
            currentDirection = nextDirection;
            nextDirection = None;
        }
    }

    /// Sprawdzanie możliwości zmiany kierunku podczas ruchu
    if (nextDirection != None && nextDirection != currentDirection && currentDirection != None) {
        /// Sprawdzamy czy możemy skręcić w aktualnej pozycji lub tuż przed skrzyżowaniem
        float lookAhead = 0.4f; /// Jak daleko patrzymy w przód

        /// Oblicz pozycję do sprawdzenia (trochę przed nami)
        QPointF checkPos = position;
        switch (currentDirection) {
            case Up:
                checkPos.setY(position.y() - lookAhead);
                break;
            case Down:
                checkPos.setY(position.y() + lookAhead);
                break;
            case Left:
                checkPos.setX(position.x() - lookAhead);
                break;
            case Right:
                checkPos.setX(position.x() + lookAhead);
                break;
            default:
                checkPos = position;
                break;
        }

        /// Sprawdź czy można skręcić
        if (canTurnAt(checkPos, nextDirection, board) || canTurnAt(position, nextDirection, board)) {
            /// Wyrównaj pozycję do siatki przy skręcie
            position = getAlignedPosition(currentDirection, nextDirection);
            currentDirection = nextDirection;
            updateTargetPosition();
            nextDirection = None;
        }
        /// NIE resetuj nextDirection jeśli nie mogliśmy skręcić - zachowaj intencję gracza
    }

    /// Płynny ruch
    smoothMove(board, deltaTime);
}

void Pacman::smoothMove(GameBoard *board, float deltaTime) {
    if (currentDirection == None) return;

    /// Oblicz następną pozycję
    QPointF nextPos = calculateNextPosition(currentDirection, deltaTime);

    /// Sprawdź kolizję
    bool canMove = true;

    /// Pacman zajmuje przestrzeń od position do position+1
    /// Sprawdzamy tylko gdy faktycznie przekraczamy granicę komórki
    switch (currentDirection) {
        case Up: {
            /// Górna krawędź Pacmana to position.y()
            if (nextPos.y() < position.y()) { /// Ruch w górę
                int newGridY = static_cast<int>(std::floor(nextPos.y()));
                int currentGridY = static_cast<int>(std::floor(position.y()));
                if (newGridY < currentGridY) { /// Przekraczamy granicę komórki
                    int checkX = static_cast<int>(std::floor(position.x() + 0.5f));
                    canMove = !board->isWall(QPoint(checkX, newGridY));
                }
            }
            break;
        }
        case Down: {
            /// Dolna krawędź Pacmana to position.y() + 1
            if (nextPos.y() > position.y()) { /// Ruch w dół
                int newGridY = static_cast<int>(std::floor(nextPos.y() + 0.899f));
                int currentGridY = static_cast<int>(std::floor(position.y() + 0.899f));
                if (newGridY > currentGridY) { /// Przekraczamy granicę komórki
                    int checkX = static_cast<int>(std::floor(position.x() + 0.5f));
                    canMove = !board->isWall(QPoint(checkX, newGridY));
                }
            }
            break;
        }
        case Left: {
            /// Lewa krawędź Pacmana to position.x()
            if (nextPos.x() < position.x()) { /// Ruch w lewo
                int newGridX = static_cast<int>(std::floor(nextPos.x()));
                int currentGridX = static_cast<int>(std::floor(position.x()));
                if (newGridX < currentGridX) { /// Przekraczamy granicę komórki
                    int checkY = static_cast<int>(std::floor(position.y() + 0.5f));
                    canMove = !board->isWall(QPoint(newGridX, checkY));
                }
            }
            break;
        }
        case Right: {
            /// Prawa krawędź Pacmana to position.x() + 1
            if (nextPos.x() > position.x()) { /// Ruch w prawo
                int newGridX = static_cast<int>(std::floor(nextPos.x() + 0.899f));
                int currentGridX = static_cast<int>(std::floor(position.x() + 0.899f));
                if (newGridX > currentGridX) { /// Przekraczamy granicę komórki
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
    } else {
        /// Zatrzymaj dokładnie na granicy komórki
        switch (currentDirection) {
            case Up: {
                int blockedY = static_cast<int>(std::floor(position.y()));
                position.setY(static_cast<float>(blockedY));
                break;
            }
            case Down: {
                int blockedY = static_cast<int>(std::floor(position.y()));
                position.setY(static_cast<float>(blockedY));
                break;
            }
            case Left: {
                int blockedX = static_cast<int>(std::floor(position.x()));
                position.setX(static_cast<float>(blockedX));
                break;
            }
            case Right: {
                int blockedX = static_cast<int>(std::floor(position.x()));
                position.setX(static_cast<float>(blockedX));
                break;
            }
            default:
                break;
        }
        currentDirection = None;
    }
}

void Pacman::setDirection(Direction dir) {
    if (dir != None) {
        nextDirection = dir;
    }
}

bool Pacman::canTurnAt(const QPointF &pos, Direction dir, GameBoard *board) const {
    /// Sprawdź czy można skręcić w danej pozycji
    QPoint gridPos(
        static_cast<int>(std::round(pos.x())),
        static_cast<int>(std::round(pos.y()))
    );

    /// Upewnij się, że pozycja startowa jest w granicach planszy
    if (gridPos.x() < 0 || gridPos.x() >= 20 || gridPos.y() < 0 || gridPos.y() >= 20) {
        return false;
    }

    QPoint targetPos = gridPos;
    switch (dir) {
        case Up:
            targetPos.setY(gridPos.y() - 1);
            break;
        case Down:
            targetPos.setY(gridPos.y() + 1);
            break;
        case Left:
            targetPos.setX(gridPos.x() - 1);
            break;
        case Right:
            targetPos.setX(gridPos.x() + 1);
            break;
        default:
            return false;
    }

    return canMoveTo(targetPos, board);
}

QPointF Pacman::getAlignedPosition(Direction fromDir, Direction toDir) const {
    /// Wyrównaj pozycję do siatki przy skręcaniu
    QPointF aligned = position;
    QPoint grid = getGridPosition();

    /// Przy skręcie 90 stopni, wyrównaj do centrum komórki
    if ((fromDir == Up || fromDir == Down) && (toDir == Left || toDir == Right)) {
        aligned.setY(grid.y());
    } else if ((fromDir == Left || fromDir == Right) && (toDir == Up || toDir == Down)) {
        aligned.setX(grid.x());
    }

    return aligned;
}

void Pacman::updateMouthAnimation(float deltaTime) {
    /// Animacja tylko gdy Pacman się porusza
    if (currentDirection != None) {
        if (mouthOpening) {
            mouthAngle += 90.0f * deltaTime;  /// 90 stopni na sekundę
            if (mouthAngle >= 45.0f) {
                mouthAngle = 45.0f;
                mouthOpening = false;
            }
        } else {
            mouthAngle -= 90.0f * deltaTime;
            if (mouthAngle <= 10.0f) {
                mouthAngle = 10.0f;
                mouthOpening = true;
            }
        }
    }
}