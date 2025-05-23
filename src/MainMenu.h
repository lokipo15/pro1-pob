//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QKeyEvent>

class MainMenu : public QWidget {
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);

    signals:
        void startGameRequested();
    void scoreboardRequested();
    void exitRequested();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onStartGameClicked();
    void onScoreboardClicked();
    void onExitClicked();

private:
    QPushButton *startButton;
    QPushButton *scoreboardButton;
    QPushButton *exitButton;
    QLabel *titleLabel;
    QVBoxLayout *layout;

    int selectedButton; // 0 = start, 1 = scoreboard, 2 = exit
    void updateButtonSelection();
};

#endif //MAINMENU_H