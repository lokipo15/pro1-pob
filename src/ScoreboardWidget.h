//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#ifndef SCOREBOARDWIDGET_H
#define SCOREBOARDWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QKeyEvent>
#include "ScoreManager.h"

class ScoreboardWidget : public QWidget {
    Q_OBJECT

public:
    explicit ScoreboardWidget(QWidget *parent = nullptr);
    void refreshScores();

    signals:
        void backRequested();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onBackClicked();

private:
    QVBoxLayout *layout;
    QLabel *titleLabel;
    QScrollArea *scrollArea;
    QWidget *scoresWidget;
    QVBoxLayout *scoresLayout;
    QPushButton *backButton;

    ScoreManager scoreManager;

    void setupUI();
    void updateScoreDisplay();
};

#endif //SCOREBOARDWIDGET_H