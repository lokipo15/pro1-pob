//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#include "Game.h"

#include <QPainter>
#include <QKeyEvent>
#include <QApplication>

// Inicjalizacja planszy i obiektów
Game::Game(QWidget *parent) : QWidget(parent), score(0), gameOver(false) {
    // Ustawienie focus policy, aby otrzymywać zdarzenia klawiatury
    setFocusPolicy(Qt::StrongFocus);

    // Tworzenie planszy gry
    board = new GameBoard();

    // Tworzenie Pacmana
    pacman = new Pacman(board->getPacmanStartPosition());

    // Tworzenie duchów
    for (const QPoint &pos : board->getGhostStartPositions()) {
        Ghost *ghost = new Ghost(pos);
        ghosts.push_back(ghost);
    }

    // Tworzenie i uruchamianie timera/zegara do aktualizacji gry
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Game::update);
    // Zegar bezpośrednio wpływa na prędkość rozgrywki, ustawienie 100 jest optymalnym rozwiązaniem
    // Duchy i gracz nie są zbyt szybkie, czas reakcji przeciętnej osoby pozwala na wygodne sterowanie
    timer->start(100);
}
// Destruktor
Game::~Game() {
    delete board;

    delete pacman;

    for (Ghost *ghost : ghosts) {
        delete ghost;
    }
}

void Game::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // Rysowanie planszy
    board->draw(painter);

    // Rysowanie Pacmana
    pacman->draw(painter);

    // Rysowanie duchów
    for (Ghost *ghost : ghosts) {
        ghost->draw(painter);
    }

    // Rysowanie wyniku
    drawScore(painter);
}

// Movement/ruch gracza
void Game::keyPressEvent(QKeyEvent *event) {
    if (gameOver) {
        return;
    }
    switch (event->key()) {
        case Qt::Key_Up:
            pacman->setDirection(Pacman::Up);
            break;
        case Qt::Key_Down:
            pacman->setDirection(Pacman::Down);
            break;
        case Qt::Key_Left:
            pacman->setDirection(Pacman::Left);
            break;
        case Qt::Key_Right:
            pacman->setDirection(Pacman::Right);
            break;
        case Qt::Key_Escape:
            QApplication::quit();
            break;
    }
}
// Skrypt odświeżający
void Game::update() {
    if (gameOver) {
        return;
    }

    // Poruszanie Pacmana

    pacman->move(board);

    // Ruch duchów
    for (Ghost *ghost : ghosts) {
        ghost->move(board);
    }

    // Sprawdzanie kolizji
    checkCollisions();

    // Odświeżanie widoku
    repaint();
}
// System kolizji
void Game::checkCollisions() {
    // Sprawdzanie kolizji z punktami do zbierania
    QPoint pacmanPos = pacman->getPosition();
    if (board->isCollectible(pacmanPos)) {
        board->removeCollectible(pacmanPos);
        score += 10;
    }

    // Sprawdzanie kolizji z duchami
    for (Ghost *ghost : ghosts) {
        if (pacman->getPosition() == ghost->getPosition()) {
            gameOver = true;
            QTimer::singleShot(1000, qApp, &QApplication::quit);
            break;
        }
    }
}
// Wyświetlanie wyniku w lewym górnym rogu
void Game::drawScore(QPainter &painter) {
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(10, 20, QString("Wynik: %1").arg(score));
}