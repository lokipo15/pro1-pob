///
/// Created by Gabriel Boruń on 25/04/2025.
/// Co-authored by Konrad Gębski on 25/04/2025.
///

#include "ScoreboardWidget.h"
#include <QPainter>
#include <QFont>

ScoreboardWidget::ScoreboardWidget(QWidget *parent)
    : QWidget(parent) {

    setFixedSize(600, 650);
    setFocusPolicy(Qt::StrongFocus);

    setupUI();
    refreshScores();
}

void ScoreboardWidget::setupUI() {
    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    layout->setSpacing(20);
    layout->setContentsMargins(50, 50, 50, 50);

    /// Tytuł
    titleLabel = new QLabel("NAJLEPSZE WYNIKI", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("QLabel { color: yellow; font-size: 28px; font-weight: bold; }");
    layout->addWidget(titleLabel);

    /// Obszar przewijania dla wyników
    scrollArea = new QScrollArea(this);
    scrollArea->setFixedHeight(400);
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setStyleSheet(
        "QScrollArea { background: transparent; border: 2px solid #34495e; border-radius: 10px; }"
        "QScrollBar:vertical { background: #2c3e50; width: 12px; border-radius: 6px; }"
        "QScrollBar::handle:vertical { background: #3498db; border-radius: 6px; }"
    );

    scoresWidget = new QWidget();
    scoresLayout = new QVBoxLayout(scoresWidget);
    scoresLayout->setAlignment(Qt::AlignTop);
    scrollArea->setWidget(scoresWidget);
    layout->addWidget(scrollArea);

    /// Przycisk powrotu
    backButton = new QPushButton("POWRÓT", this);
    backButton->setStyleSheet(
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
    connect(backButton, &QPushButton::clicked, this, &ScoreboardWidget::onBackClicked);
    layout->addWidget(backButton, 0, Qt::AlignCenter);
}

void ScoreboardWidget::refreshScores() {
    updateScoreDisplay();
}

void ScoreboardWidget::updateScoreDisplay() {
    /// Wyczyść poprzednie wyniki
    QLayoutItem *child;
    while ((child = scoresLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    QVector<ScoreEntry> topScores = scoreManager.loadTopScores();

    if (topScores.isEmpty()) {
        QLabel *noScoresLabel = new QLabel("Brak zapisanych wyników", scoresWidget);
        noScoresLabel->setAlignment(Qt::AlignCenter);
        noScoresLabel->setStyleSheet("QLabel { color: white; font-size: 16px; padding: 20px; }");
        scoresLayout->addWidget(noScoresLabel);
    } else {
        for (int i = 0; i < topScores.size(); ++i) {
            const ScoreEntry &entry = topScores[i];

            QString scoreText = QString("%1. %2 - %3")
                               .arg(i + 1, 2)
                               .arg(entry.playerName.leftJustified(15, ' ', true))
                               .arg(entry.score);

            QLabel *scoreLabel = new QLabel(scoreText, scoresWidget);
            scoreLabel->setAlignment(Qt::AlignLeft);
            scoreLabel->setStyleSheet(
                QString("QLabel { color: %1; font-size: 14px; font-family: 'Courier New'; padding: 5px; }")
                .arg(i < 3 ? "gold" : "white")  /// Top 3 w kolorze złotym
            );
            scoresLayout->addWidget(scoreLabel);
        }
    }
}

void ScoreboardWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    /// Instrukcje
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(10, height() - 20, "Naciśnij ESC lub ENTER aby wrócić");

    QWidget::paintEvent(event);
}

void ScoreboardWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Escape:
        case Qt::Key_Return:
        case Qt::Key_Enter:
            onBackClicked();
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}

void ScoreboardWidget::onBackClicked() {
    emit backRequested();
}