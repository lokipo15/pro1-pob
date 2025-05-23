//
// Created by Gabriel Boruń on 23/05/2025.
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
    void exitRequested();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onStartGameClicked();
    void onExitClicked();

private:
    QPushButton *startButton;
    QPushButton *exitButton;
    QLabel *titleLabel;
    QVBoxLayout *layout;

    int selectedButton; // 0 = start, 1 = exit
    void updateButtonSelection();
};


#endif //MAINMENU_H
