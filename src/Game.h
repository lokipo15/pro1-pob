//
// Created by Gabriel Boruń on 25/04/2025.
//

#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QTimer>
#include "GameBoard.h"
#include "Pacman.h"
#include "Ghost.h"
#include <vector>

class Game : public QWidget {
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    private slots:
        void update();

private:
    QTimer *timer;
    GameBoard *board;
    Pacman *pacman;
    std::vector<Ghost*> ghosts;
    int score;
    bool gameOver;

    void checkCollisions();
    void drawScore(QPainter &painter);
};




#endif //GAME_H
