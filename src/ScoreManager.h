//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <QString>
#include <QVector>
#include <QDataStream>

struct ScoreEntry {
    QString playerName;
    int score;

    ScoreEntry() : score(0) {}
    ScoreEntry(const QString &name, int s) : playerName(name), score(s) {}
};

class ScoreManager {
public:
    ScoreManager();

    bool saveScore(const QString &playerName, int score);
    QVector<ScoreEntry> loadTopScores();
    bool isHighScore(int score);
    void refreshScores();

private:
    static const QString SCORES_FILE;
    static const int MAX_SCORES = 10;

    QVector<ScoreEntry> scores;

    bool loadScores();
    bool saveScores();
    void sortScores();
};

#endif //SCOREMANAGER_H