///
/// Created by Gabriel Boruń on 25/04/2025.
/// Co-authored by Konrad Gębski on 25/04/2025.
///

#include "GameWindow.h"
#include <QApplication>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Pacman"); /// Ustawia tytuł okna na "Pacman"
    setFixedSize(600, 650); /// Ustawia stały rozmiar okna na 600x650 pikseli

    setupUI();
}

/// Destruktor
GameWindow::~GameWindow() {
    /// Wszystkie obiekty będą automatycznie usunięte, ponieważ są widgetami potomnymi
}

void GameWindow::setupUI() {
    /// Tworzenie QStackedWidget jako centralnego widget'u
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    /// Tworzenie menu głównego
    mainMenu = new MainMenu(this);
    connect(mainMenu, &MainMenu::startGameRequested, this, &GameWindow::onStartGameRequested);
    connect(mainMenu, &MainMenu::scoreboardRequested, this, &GameWindow::onScoreboardRequested);
    connect(mainMenu, &MainMenu::exitRequested, this, &GameWindow::onExitRequested);
    stackedWidget->addWidget(mainMenu);

    /// Tworzenie gry
    game = new Game(this);
    connect(game, &Game::gameStateChanged, this, &GameWindow::onGameStateChanged);
    stackedWidget->addWidget(game);

    /// Tworzenie ekranu końca gry
    gameOverScreen = new GameOverScreen(this);
    connect(gameOverScreen, &GameOverScreen::restartRequested, this, &GameWindow::onRestartRequested);
    connect(gameOverScreen, &GameOverScreen::mainMenuRequested, this, &GameWindow::onMainMenuRequested);
    connect(gameOverScreen, &GameOverScreen::scoreboardRequested, this, &GameWindow::onScoreboardRequested);
    connect(gameOverScreen, &GameOverScreen::exitRequested, this, &GameWindow::onExitRequested);
    stackedWidget->addWidget(gameOverScreen);

    /// Tworzenie ekranu wygranej
    winScreen = new WinScreen(this);
    connect(winScreen, &WinScreen::saveScoreRequested, this, &GameWindow::onWinSaveScoreRequested);
    connect(winScreen, &WinScreen::viewScoreboardRequested, this, &GameWindow::onWinViewScoreboardRequested);
    connect(winScreen, &WinScreen::playAgainRequested, this, &GameWindow::onWinPlayAgainRequested);
    connect(winScreen, &WinScreen::exitRequested, this, &GameWindow::onWinExitRequested);
    stackedWidget->addWidget(winScreen);

    /// Tworzenie tablicy wyników
    scoreboardWidget = new ScoreboardWidget(this);
    connect(scoreboardWidget, &ScoreboardWidget::backRequested, this, &GameWindow::onScoreboardBackRequested);
    stackedWidget->addWidget(scoreboardWidget);

    /// Ustaw menu główne jako domyślny widok
    showMainMenu();
}

void GameWindow::showMainMenu() {
    stackedWidget->setCurrentWidget(mainMenu);
    mainMenu->setFocus();
}

void GameWindow::showGame() {
    stackedWidget->setCurrentWidget(game);
    game->setFocus();
}

void GameWindow::showGameOver() {
    gameOverScreen->setScore(game->getScore());
    stackedWidget->setCurrentWidget(gameOverScreen);
    gameOverScreen->setFocus();
}

void GameWindow::showWin() {
    winScreen->setScore(game->getScore());
    winScreen->setScoreManager(gameOverScreen->getScoreManager());
    stackedWidget->setCurrentWidget(winScreen);
    winScreen->setFocus();
}

void GameWindow::showScoreboard() {
    scoreboardWidget->refreshScores();
    stackedWidget->setCurrentWidget(scoreboardWidget);
    scoreboardWidget->setFocus();
}

void GameWindow::onStartGameRequested() {
    game->startGame();
    showGame();
}

void GameWindow::onRestartRequested() {
    game->resetGame();
    game->startGame();
    showGame();
}

void GameWindow::onMainMenuRequested() {
    showMainMenu();
}

void GameWindow::onScoreboardRequested() {
    showScoreboard();
}

void GameWindow::onScoreboardBackRequested() {
    showMainMenu();
}

void GameWindow::onExitRequested() {
    QApplication::quit();
}


void GameWindow::onGameStateChanged(GameState newState) {
    switch (newState) {
        case MENU:
            showMainMenu();
            break;
        case PLAYING:
            showGame();
            break;
        case GAME_OVER:
            showGameOver();
            break;
        case WIN:
            showWin();
            break;
        case PAUSED:
            /// Gra pozostaje widoczna, ale wyświetla informację o pauzie
            break;
    }
}

void GameWindow::onWinSaveScoreRequested(const QString &playerName, int score) {
    gameOverScreen->getScoreManager()->saveScore(playerName, score);
    showScoreboard();
}

void GameWindow::onWinViewScoreboardRequested() {
    showScoreboard();
}

void GameWindow::onWinPlayAgainRequested() {
    game->resetGame();
    game->startGame();
    showGame();
}

void GameWindow::onWinExitRequested() {
    QApplication::quit();
}