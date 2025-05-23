//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#include "MainMenu.h"
#include <QPainter>
#include <QFont>
#include <QApplication>

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent), selectedButton(0) {

    setFixedSize(600, 650);
    setFocusPolicy(Qt::StrongFocus);

    // Tworzenie layoutu
    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(30);

    // Tytuł gry
    titleLabel = new QLabel("PACMAN", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("QLabel { color: yellow; font-size: 48px; font-weight: bold; }");
    layout->addWidget(titleLabel);

    // Odstęp
    layout->addSpacing(50);

    // Przycisk Start
    startButton = new QPushButton("ROZPOCZNIJ GRĘ", this);
    startButton->setStyleSheet(
        "QPushButton { "
        "background-color: #2c3e50; "
        "color: white; "
        "font-size: 18px; "
        "font-weight: bold; "
        "padding: 15px 30px; "
        "border: 2px solid #34495e; "
        "border-radius: 10px; "
        "} "
        "QPushButton:hover { "
        "background-color: #34495e; "
        "border-color: #3498db; "
        "}"
    );
    connect(startButton, &QPushButton::clicked, this, &MainMenu::onStartGameClicked);
    layout->addWidget(startButton);

    // Przycisk Najlepsze Wyniki
    scoreboardButton = new QPushButton("NAJLEPSZE WYNIKI", this);
    scoreboardButton->setStyleSheet(
        "QPushButton { "
        "background-color: #2c3e50; "
        "color: white; "
        "font-size: 18px; "
        "font-weight: bold; "
        "padding: 15px 30px; "
        "border: 2px solid #34495e; "
        "border-radius: 10px; "
        "} "
        "QPushButton:hover { "
        "background-color: #34495e; "
        "border-color: #3498db; "
        "}"
    );
    connect(scoreboardButton, &QPushButton::clicked, this, &MainMenu::onScoreboardClicked);
    layout->addWidget(scoreboardButton);

    // Przycisk Exit
    exitButton = new QPushButton("WYJŚCIE", this);
    exitButton->setStyleSheet(
        "QPushButton { "
        "background-color: #2c3e50; "
        "color: white; "
        "font-size: 18px; "
        "font-weight: bold; "
        "padding: 15px 30px; "
        "border: 2px solid #34495e; "
        "border-radius: 10px; "
        "} "
        "QPushButton:hover { "
        "background-color: #34495e; "
        "border-color: #3498db; "
        "}"
    );
    connect(exitButton, &QPushButton::clicked, this, &MainMenu::onExitClicked);
    layout->addWidget(exitButton);

    updateButtonSelection();
}

void MainMenu::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // Tło
    painter.fillRect(rect(), Qt::black);

    // Instrukcje nawigacji
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(10, height() - 60, "Użyj strzałek ↑↓ do nawigacji");
    painter.drawText(10, height() - 40, "Naciśnij ENTER aby wybrać");
    painter.drawText(10, height() - 20, "Naciśnij ESC aby wyjść");

    QWidget::paintEvent(event);
}

void MainMenu::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Up:
            selectedButton = (selectedButton - 1 + 3) % 3;
            updateButtonSelection();
            break;
        case Qt::Key_Down:
            selectedButton = (selectedButton + 1) % 3;
            updateButtonSelection();
            break;
        case Qt::Key_Return:
        case Qt::Key_Enter:
            if (selectedButton == 0) {
                onStartGameClicked();
            } else if (selectedButton == 1) {
                onScoreboardClicked();
            } else {
                onExitClicked();
            }
            break;
        case Qt::Key_Escape:
            onExitClicked();
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}

void MainMenu::updateButtonSelection() {
    // Reset stylów
    startButton->setStyleSheet(
        "QPushButton { "
        "background-color: #2c3e50; "
        "color: white; "
        "font-size: 18px; "
        "font-weight: bold; "
        "padding: 15px 30px; "
        "border: 2px solid #34495e; "
        "border-radius: 10px; "
        "}"
    );

    scoreboardButton->setStyleSheet(
        "QPushButton { "
        "background-color: #2c3e50; "
        "color: white; "
        "font-size: 18px; "
        "font-weight: bold; "
        "padding: 15px 30px; "
        "border: 2px solid #34495e; "
        "border-radius: 10px; "
        "}"
    );

    exitButton->setStyleSheet(
        "QPushButton { "
        "background-color: #2c3e50; "
        "color: white; "
        "font-size: 18px; "
        "font-weight: bold; "
        "padding: 15px 30px; "
        "border: 2px solid #34495e; "
        "border-radius: 10px; "
        "}"
    );

    // Podświetl wybrany przycisk
    QString selectedStyle =
        "QPushButton { "
        "background-color: #34495e; "
        "color: yellow; "
        "font-size: 18px; "
        "font-weight: bold; "
        "padding: 15px 30px; "
        "border: 2px solid #f1c40f; "
        "border-radius: 10px; "
        "}";

    if (selectedButton == 0) {
        startButton->setStyleSheet(selectedStyle);
    } else if (selectedButton == 1) {
        scoreboardButton->setStyleSheet(selectedStyle);
    } else {
        exitButton->setStyleSheet(selectedStyle);
    }
}

void MainMenu::onStartGameClicked() {
    emit startGameRequested();
}

void MainMenu::onScoreboardClicked() {
    emit scoreboardRequested();
}

void MainMenu::onExitClicked() {
    emit exitRequested();
}