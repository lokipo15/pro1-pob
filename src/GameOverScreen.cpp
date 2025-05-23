//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#include "GameOverScreen.h"
#include <QPainter>
#include <QFont>

GameOverScreen::GameOverScreen(QWidget *parent)
    : QWidget(parent), selectedButton(0), finalScore(0) {

    setFixedSize(600, 650);
    setFocusPolicy(Qt::StrongFocus);

    // Tworzenie layoutu
    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(20);

    // Napis "Game Over"
    gameOverLabel = new QLabel("KONIEC GRY", this);
    gameOverLabel->setAlignment(Qt::AlignCenter);
    gameOverLabel->setStyleSheet("QLabel { color: red; font-size: 36px; font-weight: bold; }");
    layout->addWidget(gameOverLabel);

    // Wynik
    scoreLabel = new QLabel("Wynik: 0", this);
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setStyleSheet("QLabel { color: yellow; font-size: 24px; font-weight: bold; }");
    layout->addWidget(scoreLabel);

    // Odstęp
    layout->addSpacing(30);

    // Przycisk Restart
    restartButton = new QPushButton("ZAGRAJ PONOWNIE", this);
    restartButton->setStyleSheet(
        "QPushButton { "
        "background-color: #27ae60; "
        "color: white; "
        "font-size: 16px; "
        "font-weight: bold; "
        "padding: 12px 25px; "
        "border: 2px solid #2ecc71; "
        "border-radius: 8px; "
        "}"
    );
    connect(restartButton, &QPushButton::clicked, this, &GameOverScreen::onRestartClicked);
    layout->addWidget(restartButton);

    // Przycisk Menu Główne
    mainMenuButton = new QPushButton("MENU GŁÓWNE", this);
    mainMenuButton->setStyleSheet(
        "QPushButton { "
        "background-color: #2c3e50; "
        "color: white; "
        "font-size: 16px; "
        "font-weight: bold; "
        "padding: 12px 25px; "
        "border: 2px solid #34495e; "
        "border-radius: 8px; "
        "}"
    );
    connect(mainMenuButton, &QPushButton::clicked, this, &GameOverScreen::onMainMenuClicked);
    layout->addWidget(mainMenuButton);

    // Przycisk Wyjście
    exitButton = new QPushButton("WYJŚCIE", this);
    exitButton->setStyleSheet(
        "QPushButton { "
        "background-color: #e74c3c; "
        "color: white; "
        "font-size: 16px; "
        "font-weight: bold; "
        "padding: 12px 25px; "
        "border: 2px solid #c0392b; "
        "border-radius: 8px; "
        "}"
    );
    connect(exitButton, &QPushButton::clicked, this, &GameOverScreen::onExitClicked);
    layout->addWidget(exitButton);

    updateButtonSelection();
}

void GameOverScreen::setScore(int score) {
    finalScore = score;
    scoreLabel->setText(QString("Wynik: %1").arg(score));
}

void GameOverScreen::paintEvent(QPaintEvent *event) {
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

void GameOverScreen::keyPressEvent(QKeyEvent *event) {
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
                onRestartClicked();
            } else if (selectedButton == 1) {
                onMainMenuClicked();
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

void GameOverScreen::updateButtonSelection() {
    // Reset stylów
    QString normalStyle =
        "QPushButton { "
        "background-color: %1; "
        "color: white; "
        "font-size: 16px; "
        "font-weight: bold; "
        "padding: 12px 25px; "
        "border: 2px solid %2; "
        "border-radius: 8px; "
        "}";

    restartButton->setStyleSheet(normalStyle.arg("#27ae60", "#2ecc71"));
    mainMenuButton->setStyleSheet(normalStyle.arg("#2c3e50", "#34495e"));
    exitButton->setStyleSheet(normalStyle.arg("#e74c3c", "#c0392b"));

    // Podświetl wybrany przycisk
    QString selectedStyle =
        "QPushButton { "
        "background-color: %1; "
        "color: yellow; "
        "font-size: 16px; "
        "font-weight: bold; "
        "padding: 12px 25px; "
        "border: 2px solid #f1c40f; "
        "border-radius: 8px; "
        "}";

    if (selectedButton == 0) {
        restartButton->setStyleSheet(selectedStyle.arg("#2ecc71"));
    } else if (selectedButton == 1) {
        mainMenuButton->setStyleSheet(selectedStyle.arg("#34495e"));
    } else {
        exitButton->setStyleSheet(selectedStyle.arg("#c0392b"));
    }
}

void GameOverScreen::onRestartClicked() {
    emit restartRequested();
}

void GameOverScreen::onMainMenuClicked() {
    emit mainMenuRequested();
}

void GameOverScreen::onExitClicked() {
    emit exitRequested();
}