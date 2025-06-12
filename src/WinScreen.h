//
// Created by Gabriel Boruń on 12/06/2025.
// Co-authored by Konrad Gębski on 12/06/2025.
//

#ifndef WINSCREEN_H
#define WINSCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QKeyEvent>
#include "ScoreManager.h"

class WinScreen : public QWidget {
    Q_OBJECT

public:
    explicit WinScreen(QWidget *parent = nullptr);
    
    void setScore(int score);
    void setScoreManager(ScoreManager *manager);

signals:
    void saveScoreRequested(const QString &playerName, int score);
    void viewScoreboardRequested();
    void playAgainRequested();
    void exitRequested();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onSaveScoreClicked();
    void onViewScoreboardClicked();
    void onPlayAgainClicked();
    void onExitClicked();

private:
    QLabel *titleLabel;
    QLabel *scoreLabel;
    QLabel *namePromptLabel;
    QLineEdit *nameInput;
    QPushButton *saveScoreButton;
    QPushButton *viewScoreboardButton;
    QPushButton *playAgainButton;
    QPushButton *exitButton;
    
    QVBoxLayout *mainLayout;
    QHBoxLayout *nameLayout;
    QHBoxLayout *buttonLayout;

    int currentScore;
    ScoreManager *scoreManager;
    int selectedButton; // 0 = save, 1 = scoreboard, 2 = play again, 3 = exit
    bool isHighScore;
    
    void updateButtonSelection();
    void checkIfHighScore();
    void setupLayout();
};

#endif // WINSCREEN_H