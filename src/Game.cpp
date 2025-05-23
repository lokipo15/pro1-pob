//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#include "Game.h"
#include <QPainter>
#include <QKeyEvent>
#include <QApplication>

// Inicjalizacja planszy i obiektów
Game::Game(QWidget *parent) : QWidget(parent), lastUpdateTime(0), score(0), gameOver(false),
    blinky(nullptr), pinky(nullptr), inky(nullptr), clyde(nullptr) {
    // Ustawienie focus policy, aby otrzymywać zdarzenia klawiatury
    setFocusPolicy(Qt::StrongFocus);

    // Tworzenie planszy gry
    board = new GameBoard();

    // Tworzenie Pacmana
    QPoint gridPos = board->getPacmanStartPosition();
    pacman = new Pacman(QPointF(gridPos.x(), gridPos.y()));

    // Tworzenie konkretnych typów duchów
    std::vector<QPoint> ghostPositions = board->getGhostStartPositions();

    if (ghostPositions.size() >= 4) {
        // Blinky - czerwony duch (pierwsza pozycja)
        blinky = new Blinky(QPointF(ghostPositions[0].x(), ghostPositions[0].y()));
        ghosts.push_back(blinky);

        // Pinky - różowy duch (druga pozycja)
        pinky = new Pinky(QPointF(ghostPositions[1].x(), ghostPositions[1].y()));
        ghosts.push_back(pinky);

        // Inky - niebieski duch (trzecia pozycja) - potrzebuje referencji do Blinky
        inky = new Inky(QPointF(ghostPositions[2].x(), ghostPositions[2].y()), blinky);
        ghosts.push_back(inky);

        // Clyde - pomarańczowy duch (czwarta pozycja)
        clyde = new Clyde(QPointF(ghostPositions[3].x(), ghostPositions[3].y()));
        ghosts.push_back(clyde);
    } else {
        // Fallback - stwórz przynajmniej jeden duch jeśli nie ma 4 pozycji
        for (const QPoint &pos : ghostPositions) {
            Ghost *ghost = new Ghost(QPointF(pos.x(), pos.y()));
            ghosts.push_back(ghost);
        }
    }

    // Uruchomienie timera czasu
    elapsedTimer.start();

    // Tworzenie i uruchamianie timera do aktualizacji gry
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Game::update);
    // Timer ustawiony na 16ms dla 60 FPS
    timer->start(16);
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

    // Rysowanie "Game Over" jeśli gra się skończyła
    if (gameOver) {
        painter.setPen(Qt::red);
        painter.setFont(QFont("Arial", 24, QFont::Bold));
        painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");
    }
}

// Movement/ruch gracza
void Game::keyPressEvent(QKeyEvent *event) {
    if (gameOver) {
        if (event->key() == Qt::Key_Escape) {
            QApplication::quit();
        }
        return;
    }

    switch (event->key()) {
        case Qt::Key_Up:
            pacman->setDirection(Entity::Up);
            break;
        case Qt::Key_Down:
            pacman->setDirection(Entity::Down);
            break;
        case Qt::Key_Left:
            pacman->setDirection(Entity::Left);
            break;
        case Qt::Key_Right:
            pacman->setDirection(Entity::Right);
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

    // Obliczanie delta time
    qint64 currentTime = elapsedTimer.elapsed();
    float deltaTime = 0.0f;

    if (lastUpdateTime > 0) {
        deltaTime = (currentTime - lastUpdateTime) / 1000.0f; // Konwersja ms na sekundy

        // Ograniczenie delta time do maksymalnie 0.1s (na wypadek lag spike'ów)
        if (deltaTime > 0.1f) {
            deltaTime = 0.1f;
        }
    }

    lastUpdateTime = currentTime;

    // Poruszanie Pacmana z delta time
    pacman->move(board, deltaTime);

    // Aktualizacja trybów duchów
    updateGhostModes(deltaTime);

    // POPRAWKA: Użyj nowej metody move z parametrem Pacman
    for (Ghost *ghost : ghosts) {
        ghost->move(board, deltaTime, pacman);
    }

    // Sprawdzanie kolizji
    checkCollisions();

    // Odświeżanie widoku
    repaint();
}

void Game::updateGhostModes(float deltaTime) {
    // Aktualizuj timery trybów dla wszystkich duchów
    for (Ghost *ghost : ghosts) {
        if (ghost->getMode() != Ghost::FRIGHTENED && ghost->getMode() != Ghost::EATEN) {
            ghost->updateModeTimer(deltaTime);
        }
    }
}

// System kolizji
void Game::checkCollisions() {
    // Sprawdzanie kolizji z punktami do zbierania
    QPoint pacmanGridPos = pacman->getGridPosition();
    if (board->isCollectible(pacmanGridPos)) {
        board->removeCollectible(pacmanGridPos);
        score += 10;
    }

    // Sprawdzanie kolizji z duchami
    for (Ghost *ghost : ghosts) {
        // Sprawdzenie kolizji na podstawie odległości w pikselach
        QPointF pacmanPos = pacman->getPosition();
        QPointF ghostPos = ghost->getPosition();

        float dx = pacmanPos.x() - ghostPos.x();
        float dy = pacmanPos.y() - ghostPos.y();
        float distance = std::sqrt(dx * dx + dy * dy);

        // Kolizja gdy odległość jest mniejsza niż 0.5 komórki
        if (distance < 0.5f) {
            gameOver = true;
            // Nie zamykamy aplikacji automatycznie, pozwalamy graczowi zobaczyć "Game Over"
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