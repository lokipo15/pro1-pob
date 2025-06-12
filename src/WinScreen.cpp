//
// Created by Gabriel Boruń on 12/06/2025.
// Co-authored by Konrad Gębski on 12/06/2025.
//

#include "WinScreen.h"
#include <QPainter>
#include <QFont>
#include <QApplication>

WinScreen::WinScreen(QWidget *parent)
    : QWidget(parent), currentScore(0), scoreManager(nullptr), selectedButton(0), isHighScore(false) {

    setFixedSize(600, 650);
    setFocusPolicy(Qt::StrongFocus);
    
    setupLayout();
}

void WinScreen::setupLayout() {
    // Główny layout
    mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setSpacing(30);

    // Tytuł
    titleLabel = new QLabel("GRATULACJE! Wygrałeś!", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("QLabel { color: yellow; font-size: 48px; font-weight: bold; }");
    mainLayout->addWidget(titleLabel);

    // Wynik
    scoreLabel = new QLabel("Twój wynik: 0", this);
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setStyleSheet("QLabel { color: white; font-size: 24px; font-weight: bold; }");
    mainLayout->addWidget(scoreLabel);

    // Odstęp
    mainLayout->addSpacing(30);

    // Layout dla wprowadzenia imienia
    nameLayout = new QHBoxLayout();
    namePromptLabel = new QLabel("Twoje imię:", this);
    namePromptLabel->setStyleSheet("QLabel { color: white; font-size: 18px; }");
    nameInput = new QLineEdit(this);
    nameInput->setStyleSheet(
        "QLineEdit { "
        "background-color: #2c3e50; "
        "color: white; "
        "font-size: 16px; "
        "padding: 10px; "
        "border: 2px solid #34495e; "
        "border-radius: 5px; "
        "}"
    );
    nameInput->setMaxLength(20);
    nameLayout->addWidget(namePromptLabel);
    nameLayout->addWidget(nameInput);
    mainLayout->addLayout(nameLayout);

    // Odstęp
    mainLayout->addSpacing(20);

    // Layout dla przycisków
    buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(20);

    // Przycisk zapisania wyniku
    saveScoreButton = new QPushButton("ZAPISZ WYNIK", this);
    saveScoreButton->setStyleSheet(
        "QPushButton { "
        "background-color: #27ae60; "
        "color: white; "
        "font-size: 16px; "
        "font-weight: bold; "
        "padding: 15px 25px; "
        "border: 2px solid #2ecc71; "
        "border-radius: 10px; "
        "} "
        "QPushButton:hover { "
        "background-color: #2ecc71; "
        "}"
    );
    connect(saveScoreButton, &QPushButton::clicked, this, &WinScreen::onSaveScoreClicked);
    buttonLayout->addWidget(saveScoreButton);

    // Przycisk wyświetlenia tablicy wyników
    viewScoreboardButton = new QPushButton("TABLICA WYNIKÓW", this);
    viewScoreboardButton->setStyleSheet(
        "QPushButton { "
        "background-color: #3498db; "
        "color: white; "
        "font-size: 16px; "
        "font-weight: bold; "
        "padding: 15px 25px; "
        "border: 2px solid #2980b9; "
        "border-radius: 10px; "
        "} "
        "QPushButton:hover { "
        "background-color: #2980b9; "
        "}"
    );
    connect(viewScoreboardButton, &QPushButton::clicked, this, &WinScreen::onViewScoreboardClicked);
    buttonLayout->addWidget(viewScoreboardButton);

    mainLayout->addLayout(buttonLayout);

    // Druga linia przycisków
    QHBoxLayout *secondButtonLayout = new QHBoxLayout();
    secondButtonLayout->setSpacing(20);

    // Przycisk zagraj ponownie
    playAgainButton = new QPushButton("ZAGRAJ PONOWNIE", this);
    playAgainButton->setStyleSheet(
        "QPushButton { "
        "background-color: #f39c12; "
        "color: white; "
        "font-size: 16px; "
        "font-weight: bold; "
        "padding: 15px 25px; "
        "border: 2px solid #e67e22; "
        "border-radius: 10px; "
        "} "
        "QPushButton:hover { "
        "background-color: #e67e22; "
        "}"
    );
    connect(playAgainButton, &QPushButton::clicked, this, &WinScreen::onPlayAgainClicked);
    secondButtonLayout->addWidget(playAgainButton);

    // Przycisk wyjścia
    exitButton = new QPushButton("WYJDŹ", this);
    exitButton->setStyleSheet(
        "QPushButton { "
        "background-color: #e74c3c; "
        "color: white; "
        "font-size: 16px; "
        "font-weight: bold; "
        "padding: 15px 25px; "
        "border: 2px solid #c0392b; "
        "border-radius: 10px; "
        "} "
        "QPushButton:hover { "
        "background-color: #c0392b; "
        "}"
    );
    connect(exitButton, &QPushButton::clicked, this, &WinScreen::onExitClicked);
    secondButtonLayout->addWidget(exitButton);

    mainLayout->addLayout(secondButtonLayout);

    updateButtonSelection();
}

void WinScreen::setScore(int score) {
    currentScore = score;
    scoreLabel->setText(QString("Twój wynik: %1").arg(score));
    checkIfHighScore();
}

void WinScreen::setScoreManager(ScoreManager *manager) {
    scoreManager = manager;
    checkIfHighScore();
}

void WinScreen::checkIfHighScore() {
    if (scoreManager) {
        isHighScore = scoreManager->isHighScore(currentScore);
        if (isHighScore) {
            titleLabel->setText("NOWY REKORD!");
            titleLabel->setStyleSheet("QLabel { color: gold; font-size: 48px; font-weight: bold; }");
        } else {
            titleLabel->setText("GRATULACJE!");
            titleLabel->setStyleSheet("QLabel { color: yellow; font-size: 48px; font-weight: bold; }");
        }
    }
}

void WinScreen::updateButtonSelection() {
    // Reset all button styles
    QString normalStyle = 
        "background-color: #2c3e50; "
        "color: white; "
        "font-size: 16px; "
        "font-weight: bold; "
        "padding: 15px 25px; "
        "border: 2px solid #34495e; "
        "border-radius: 10px;";
    
    QString selectedStyle = 
        "background-color: #3498db; "
        "color: white; "
        "font-size: 16px; "
        "font-weight: bold; "
        "padding: 15px 25px; "
        "border: 2px solid yellow; "
        "border-radius: 10px;";

    saveScoreButton->setStyleSheet(QString("QPushButton { %1 }").arg(selectedButton == 0 ? selectedStyle : normalStyle));
    viewScoreboardButton->setStyleSheet(QString("QPushButton { %1 }").arg(selectedButton == 1 ? selectedStyle : normalStyle));
    playAgainButton->setStyleSheet(QString("QPushButton { %1 }").arg(selectedButton == 2 ? selectedStyle : normalStyle));
    exitButton->setStyleSheet(QString("QPushButton { %1 }").arg(selectedButton == 3 ? selectedStyle : normalStyle));
}

void WinScreen::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Up:
            selectedButton = (selectedButton - 1 + 4) % 4;
            updateButtonSelection();
            break;
        case Qt::Key_Down:
            selectedButton = (selectedButton + 1) % 4;
            updateButtonSelection();
            break;
        case Qt::Key_Left:
            if (selectedButton >= 2) selectedButton -= 2;
            else selectedButton = (selectedButton == 0) ? 2 : 3;
            updateButtonSelection();
            break;
        case Qt::Key_Right:
            if (selectedButton <= 1) selectedButton += 2;
            else selectedButton = (selectedButton == 2) ? 0 : 1;
            updateButtonSelection();
            break;
        case Qt::Key_Return:
        case Qt::Key_Enter:
            switch (selectedButton) {
                case 0: onSaveScoreClicked(); break;
                case 1: onViewScoreboardClicked(); break;
                case 2: onPlayAgainClicked(); break;
                case 3: onExitClicked(); break;
            }
            break;
        case Qt::Key_Escape:
            onExitClicked();
            break;
    }
}

void WinScreen::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    
    // Tło
    painter.fillRect(rect(), Qt::black);
    
    // Dodaj efekt świecenia dla nowego rekordu
    if (isHighScore) {
        painter.setPen(QPen(Qt::yellow, 3));
        painter.drawRect(5, 5, width() - 10, height() - 10);
    }
}

void WinScreen::onSaveScoreClicked() {
    QString playerName = nameInput->text().trimmed();
    if (playerName.isEmpty()) {
        playerName = "Anonim";
    }
    emit saveScoreRequested(playerName, currentScore);
}

void WinScreen::onViewScoreboardClicked() {
    emit viewScoreboardRequested();
}

void WinScreen::onPlayAgainClicked() {
    emit playAgainRequested();
}

void WinScreen::onExitClicked() {
    emit exitRequested();
}