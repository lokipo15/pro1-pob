///
/// Created by Gabriel Boruń on 25/04/2025.
/// Co-authored by Konrad Gębski on 25/04/2025.
///

#include "GameOverScreen.h"
#include <QPainter>
#include <QFont>

GameOverScreen::GameOverScreen(QWidget *parent)
    : QWidget(parent), selectedButton(0), finalScore(0), isNewHighScore(false), scoreSaved(false) {

    setFixedSize(600, 650);
    setFocusPolicy(Qt::StrongFocus);

    /// Tworzenie layoutu
    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(20);

    /// Napis "Game Over"
    gameOverLabel = new QLabel("KONIEC GRY", this);
    gameOverLabel->setAlignment(Qt::AlignCenter);
    gameOverLabel->setStyleSheet("QLabel { color: red; font-size: 36px; font-weight: bold; }");
    layout->addWidget(gameOverLabel);

    /// Wynik
    scoreLabel = new QLabel("Wynik: 0", this);
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setStyleSheet("QLabel { color: yellow; font-size: 24px; font-weight: bold; }");
    layout->addWidget(scoreLabel);

    /// Layout dla wprowadzania imienia (domyślnie ukryty)
    nameLayout = new QHBoxLayout();
    nameLabel = new QLabel("Wprowadź imię:", this);
    nameLabel->setStyleSheet("QLabel { color: white; font-size: 16px; }");
    nameInput = new QLineEdit(this);
    nameInput->setMaxLength(15);
    nameInput->setPlaceholderText("Twoje imię...");
    nameInput->setStyleSheet(
        "QLineEdit { "
        "background-color: white; "
        "color: black; "
        "font-size: 14px; "
        "padding: 5px; "
        "border: 2px solid #3498db; "
        "border-radius: 5px; "
        "}"
    );

    saveScoreButton = new QPushButton("ZAPISZ", this);
    saveScoreButton->setStyleSheet(
        "QPushButton { "
        "background-color: #27ae60; "
        "color: white; "
        "font-size: 14px; "
        "font-weight: bold; "
        "padding: 8px 15px; "
        "border: 2px solid #2ecc71; "
        "border-radius: 5px; "
        "}"
    );
    connect(saveScoreButton, &QPushButton::clicked, this, &GameOverScreen::onSaveScoreClicked);

    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameInput);
    nameLayout->addWidget(saveScoreButton);
    layout->addLayout(nameLayout);

    hideNameInput(); /// Domyślnie ukryj

    /// Odstęp
    layout->addSpacing(30);

    /// Przycisk Restart
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

    /// Przycisk Menu Główne
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

    /// Przycisk Tablica Wyników
    scoreboardButton = new QPushButton("NAJLEPSZE WYNIKI", this);
    scoreboardButton->setStyleSheet(
        "QPushButton { "
        "background-color: #9b59b6; "
        "color: white; "
        "font-size: 16px; "
        "font-weight: bold; "
        "padding: 12px 25px; "
        "border: 2px solid #8e44ad; "
        "border-radius: 8px; "
        "}"
    );
    connect(scoreboardButton, &QPushButton::clicked, this, &GameOverScreen::onScoreboardClicked);
    layout->addWidget(scoreboardButton);

    /// Przycisk Wyjście
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
    scoreSaved = false;
    checkHighScore();
}

void GameOverScreen::checkHighScore() {
    isNewHighScore = scoreManager.isHighScore(finalScore);

    if (isNewHighScore) {
        scoreLabel->setStyleSheet("QLabel { color: gold; font-size: 24px; font-weight: bold; }");
        scoreLabel->setText(QString("NOWY REKORD: %1!").arg(finalScore));
        setupNameInput();
    } else {
        scoreLabel->setStyleSheet("QLabel { color: yellow; font-size: 24px; font-weight: bold; }");
        hideNameInput();
    }
}

void GameOverScreen::setupNameInput() {
    nameLabel->show();
    nameInput->show();
    saveScoreButton->show();
    nameInput->setFocus();
    nameInput->clear();
}

void GameOverScreen::hideNameInput() {
    nameLabel->hide();
    nameInput->hide();
    saveScoreButton->hide();
}

void GameOverScreen::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    /// Tło
    painter.fillRect(rect(), Qt::black);

    /// Instrukcje nawigacji
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(10, height() - 80, "Użyj strzałek ↑↓ do nawigacji");
    painter.drawText(10, height() - 60, "Naciśnij ENTER aby wybrać");
    painter.drawText(10, height() - 40, "Naciśnij ESC aby wyjść");

    if (isNewHighScore && !scoreSaved) {
        painter.setPen(Qt::yellow);
        painter.drawText(10, height() - 20, "Gratulacje! Osiągnąłeś wysoki wynik!");
    }

    QWidget::paintEvent(event);
}

void GameOverScreen::keyPressEvent(QKeyEvent *event) {
    /// Jeśli pole imienia jest aktywne, obsłuż wprowadzanie tekstu
    if (isNewHighScore && !scoreSaved && nameInput->hasFocus()) {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            onSaveScoreClicked();
            return;
        } else if (event->key() == Qt::Key_Escape) {
            nameInput->clearFocus();
            return;
        }
        /// Pozwól na normalne wprowadzanie tekstu
        QWidget::keyPressEvent(event);
        return;
    }

    switch (event->key()) {
        case Qt::Key_Up:
            selectedButton = (selectedButton - 1 + 4) % 4;
            updateButtonSelection();
            break;
        case Qt::Key_Down:
            selectedButton = (selectedButton + 1) % 4;
            updateButtonSelection();
            break;
        case Qt::Key_Return:
        case Qt::Key_Enter:
            if (selectedButton == 0) {
                onRestartClicked();
            } else if (selectedButton == 1) {
                onMainMenuClicked();
            } else if (selectedButton == 2) {
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

void GameOverScreen::updateButtonSelection() {
    /// Reset stylów
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
    scoreboardButton->setStyleSheet(normalStyle.arg("#9b59b6", "#8e44ad"));
    exitButton->setStyleSheet(normalStyle.arg("#e74c3c", "#c0392b"));

    /// Podświetl wybrany przycisk
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
    } else if (selectedButton == 2) {
        scoreboardButton->setStyleSheet(selectedStyle.arg("#8e44ad"));
    } else {
        exitButton->setStyleSheet(selectedStyle.arg("#c0392b"));
    }
}

void GameOverScreen::onSaveScoreClicked() {
    QString playerName = nameInput->text().trimmed();

    if (playerName.isEmpty()) {
        playerName = "ANONIM";
    }

    if (scoreManager.saveScore(playerName, finalScore)) {
        scoreSaved = true;
        hideNameInput();
        scoreLabel->setText(QString("Wynik %1 zapisany!").arg(finalScore));
    } else {
        scoreLabel->setText("Błąd zapisu wyniku!");
    }
}

void GameOverScreen::onRestartClicked() {
    emit restartRequested();
}

void GameOverScreen::onMainMenuClicked() {
    emit mainMenuRequested();
}

void GameOverScreen::onScoreboardClicked() {
    emit scoreboardRequested();
}

void GameOverScreen::onExitClicked() {
    emit exitRequested();
}