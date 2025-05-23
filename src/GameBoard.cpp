//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//


#include "GameBoard.h"

GameBoard::GameBoard() { // Konstruktor klasy GameBoard
    initializeBoard(); // Wywołanie inicjalizacji planszy
}

void GameBoard::initializeBoard() { // Inicjalizacja planszy
    // Inicjalizacja prostego labiryntu
    // 0 = nic, 1 = ściana, 2 = punkt, 3 = pozycja startowa Pacmana, 4 = pozycja startowa ducha

    // Domyślnie ustawiamy ściany na obrzeżach
    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            if (y == 0 || y == BOARD_HEIGHT - 1 || x == 0 || x == BOARD_WIDTH - 1) {
                board[y][x] = 1; // Ściany na krawędziach
            } else {
                board[y][x] = 0; // Puste miejsce wewnątrz
            }
        }
    }

    // Dodawanie wewnętrznych ścian
    for (int i = 2; i < BOARD_WIDTH - 2; i += 2) {
        for (int j = 2; j < BOARD_HEIGHT - 2; j += 2) {
            board[j][i] = 1;
        }
    }

    // Dodawanie punktów do zbierania
    for (int y = 1; y < BOARD_HEIGHT - 1; ++y) {
        for (int x = 1; x < BOARD_WIDTH - 1; ++x) {
            if (board[y][x] == 0) {
                board[y][x] = 2; // Punkt do zebrania
                collectibles.insert(QPoint(x, y)); // Użyj konstruktora QPoint
            }
        }
    }

    // Ustawienie pozycji startowej Pacmana
    board[BOARD_HEIGHT - 2][1] = 3;

    // Ustawienie pozycji startowych duchów
    board[1][BOARD_WIDTH - 2] = 4;
    board[BOARD_HEIGHT - 2][BOARD_WIDTH - 2] = 4;
    board[1][1] = 4;
    board[8][8] = 4;
}

void GameBoard::draw(QPainter &painter) { // Rysuowanie planszy
    // Rysowanie tła
    painter.fillRect(0, 0, BOARD_WIDTH * CELL_SIZE, BOARD_HEIGHT * CELL_SIZE, Qt::black);

    // Rysowanie ścian i punktów do zbierania
    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            QRect rect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);

            if (board[y][x] == 1) {
                // Ściana
                painter.fillRect(rect, Qt::blue);
            } else if (isCollectible(QPoint(x, y))) {
                // Punkt do zebrania
                painter.setPen(Qt::NoPen);
                painter.setBrush(Qt::yellow);
                painter.drawEllipse(rect.center(), CELL_SIZE / 10, CELL_SIZE / 10);
            }
        }
    }
}

bool GameBoard::isWall(const QPoint &pos) const {// Sprawdzenie czy ściana
    if (pos.x() < 0 || pos.x() >= BOARD_WIDTH || pos.y() < 0 || pos.y() >= BOARD_HEIGHT) {
        return true; // Wyjście poza planszę traktujemy jak ścianę
    }

    return board[pos.y()][pos.x()] == 1;
}

bool GameBoard::isCollectible(const QPoint &pos) const { // Sprawdzenie czy punkt
    return collectibles.find(pos) != collectibles.end();
}

void GameBoard::removeCollectible(const QPoint &pos) { // Usuwa punkt do zebrania z planszy
    collectibles.erase(pos);
}

QPoint GameBoard::getPacmanStartPosition() const { // Zwraca pozycję startową Pacmana
    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            if (board[y][x] == 3) {
                return QPoint(x, y);
            }
        }
    }

    // Awaryjnie, gdyby nie znaleziono
    return QPoint(1, BOARD_HEIGHT - 2);
}

std::vector<QPoint> GameBoard::getGhostStartPositions() const { // Zwraca liste pozycji startowych duchów
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