//
// Created by Gabriel Boruń on 23/05/2025.
//

#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QKeyEvent>

class GameOverScreen : public QWidget {
    Q_OBJECT

public:
    explicit GameOverScreen(QWidget *parent = nullptr);
    void setScore(int score);

    signals:
        void restartRequested();
    void mainMenuRequested();
    void exitRequested();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onRestartClicked();
    void onMainMenuClicked();
    void onExitClicked();

private:
    QPushButton *restartButton;
    QPushButton *mainMenuButton;
    QPushButton *exitButton;
    QLabel *gameOverLabel;
    QLabel *scoreLabel;
    QVBoxLayout *layout;

    int selectedButton; // 0 = restart, 1 = menu, 2 = exit
    int finalScore;

    void updateButtonSelection();
};

#endif //GAMEOVERSCREEN_H
