//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QKeyEvent>
#include "ScoreManager.h"

class GameOverScreen : public QWidget {
    Q_OBJECT

public:
    explicit GameOverScreen(QWidget *parent = nullptr);
    void setScore(int score);

    signals:
        void restartRequested();
    void mainMenuRequested();
    void exitRequested();
    void scoreboardRequested();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onRestartClicked();
    void onMainMenuClicked();
    void onExitClicked();
    void onScoreboardClicked();
    void onSaveScoreClicked();

private:
    QPushButton *restartButton;
    QPushButton *mainMenuButton;
    QPushButton *exitButton;
    QPushButton *scoreboardButton;
    QPushButton *saveScoreButton;
    QLabel *gameOverLabel;
    QLabel *scoreLabel;
    QLabel *nameLabel;
    QLineEdit *nameInput;
    QVBoxLayout *layout;
    QHBoxLayout *nameLayout;

    int selectedButton; // 0 = restart, 1 = menu, 2 = scoreboard, 3 = exit
    int finalScore;
    bool isNewHighScore;
    bool scoreSaved;

    ScoreManager scoreManager;

    void updateButtonSelection();
    void checkHighScore();
    void setupNameInput();
    void hideNameInput();
};

#endif //GAMEOVERSCREEN_H