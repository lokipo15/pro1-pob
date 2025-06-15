///
/// Created by Gabriel Boruń on 25/04/2025.
/// Co-authored by Konrad Gębski on 25/04/2025.
///

#include "GameBoard.h"

GameBoard::GameBoard() { /// Konstruktor klasy GameBoard
    initializeBoard(); /// Wywołanie inicjalizacji planszy
}

void GameBoard::initializeBoard() { /// Inicjalizacja planszy
    /// Inicjalizacja prostego labiryntu
    /// 0 = nic, 1 = ściana, 2 = punkt, 3 = pozycja startowa Pacmana, 4 = pozycja startowa ducha, 5 = power-up

    /// Domyślnie ustawiamy ściany na obrzeżach
    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            if (y == 0 || y == BOARD_HEIGHT - 1 || x == 0 || x == BOARD_WIDTH - 1) {
                board[y][x] = 1; /// Ściany na krawędziach
            } else {
                board[y][x] = 0; /// Puste miejsce wewnątrz
            }
        }
    }

    /// Dodawanie wewnętrznych ścian
    for (int i = 2; i < BOARD_WIDTH - 2; i += 2) {
        for (int j = 2; j < BOARD_HEIGHT - 2; j += 2) {
            board[j][i] = 1;
        }
    }

    /// Ustawienie pozycji startowej Pacmana
    board[BOARD_HEIGHT - 2][1] = 3;

    /// Ustawienie pozycji startowych duchów
    board[1][BOARD_WIDTH - 2] = 4;      /// (18, 1)
    board[BOARD_HEIGHT - 2][BOARD_WIDTH - 2] = 4;  /// (18, 18)
    board[1][1] = 4;                    /// (1, 1)
    board[8][8] = 4;                    /// (8, 8) - środek

    /// Dodawanie punktów do zbierania
    for (int y = 1; y < BOARD_HEIGHT - 1; ++y) {
        for (int x = 1; x < BOARD_WIDTH - 1; ++x) {
            if (board[y][x] == 0) {
                board[y][x] = 2; /// Punkt do zebrania
                collectibles.insert(QPoint(x, y));
            }
        }
    }

    /// Dodawanie power-upów w bezpiecznych pozycjach (nie na duchach)
    QPoint powerUpPositions[] = {
        QPoint(3, 3),                    /// Lewy górny obszar
        QPoint(BOARD_WIDTH - 4, 3),      /// Prawy górny obszar
        QPoint(3, BOARD_HEIGHT - 4),     /// Lewy dolny obszar
        QPoint(BOARD_WIDTH - 4, BOARD_HEIGHT - 4)  /// Prawy dolny obszar
    };

    for (const QPoint &pos : powerUpPositions) {
        /// Sprawdź czy pozycja jest wolna (nie jest ścianą ani duchem)
        if (board[pos.y()][pos.x()] == 2) { /// Jeśli to punkt do zbierania
            collectibles.erase(pos); /// Usuń z collectibles
            board[pos.y()][pos.x()] = 5; /// Ustaw jako power-up
            powerUps.insert(pos); /// Dodaj do power-upów
        }
    }
}

void GameBoard::draw(QPainter &painter) { /// Rysuowanie planszy
    /// Rysowanie tła
    painter.fillRect(0, 0, BOARD_WIDTH * CELL_SIZE, BOARD_HEIGHT * CELL_SIZE, Qt::black);

    /// Rysowanie ścian, punktów do zbierania i power-upów
    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            QRect rect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);

            if (board[y][x] == 1) {
                /// Ściana
                painter.fillRect(rect, Qt::blue);
            } else if (isCollectible(QPoint(x, y))) {
                /// Punkt do zebrania
                painter.setPen(Qt::NoPen);
                painter.setBrush(Qt::yellow);
                painter.drawEllipse(rect.center(), CELL_SIZE / 10, CELL_SIZE / 10);
            } else if (isPowerUp(QPoint(x, y))) {
                /// Power-up
                painter.setPen(Qt::NoPen);
                painter.setBrush(Qt::white);
                int pelletSize = CELL_SIZE / 3;
                QRect powerUpRect(rect.center().x() - pelletSize/2,
                                rect.center().y() - pelletSize/2,
                                pelletSize, pelletSize);
                painter.drawEllipse(powerUpRect);
            }
        }
    }
}

bool GameBoard::isWall(const QPoint &pos) const {/// Sprawdzenie czy ściana
    if (pos.x() < 0 || pos.x() >= BOARD_WIDTH || pos.y() < 0 || pos.y() >= BOARD_HEIGHT) {
        return true; /// Wyjście poza planszę traktujemy jak ścianę
    }

    return board[pos.y()][pos.x()] == 1;
}

bool GameBoard::isCollectible(const QPoint &pos) const { /// Sprawdzenie czy punkt
    return collectibles.find(pos) != collectibles.end();
}

bool GameBoard::isPowerUp(const QPoint &pos) const { /// Sprawdzenie czy power-up
    return powerUps.find(pos) != powerUps.end();
}

void GameBoard::removeCollectible(const QPoint &pos) { /// Usuwa punkt do zebrania z planszy
    collectibles.erase(pos);
}

void GameBoard::removePowerUp(const QPoint &pos) { /// Usuwa power-up z planszy
    powerUps.erase(pos);
}

QPoint GameBoard::getPacmanStartPosition() const { /// Zwraca pozycję startową Pacmana
    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            if (board[y][x] == 3) {
                return QPoint(x, y);
            }
        }
    }

    /// Awaryjnie, gdyby nie znaleziono
    return QPoint(1, BOARD_HEIGHT - 2);
}

std::vector<QPoint> GameBoard::getGhostStartPositions() const { /// Zwraca liste pozycji startowych duchów
    std::vector<QPoint> positions;

    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            if (board[y][x] == 4) {
                positions.push_back(QPoint(x, y));
            }
        }
    }

    return positions;
}

std::vector<QPoint> GameBoard::getPowerUpPositions() const { /// Zwraca pozycje power-upów
    std::vector<QPoint> positions;
    for (const QPoint &pos : powerUps) {
        positions.push_back(pos);
    }
    return positions;
}