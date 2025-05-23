//
// Created by Gabriel Boruń on 25/04/2025.
// Co-authored by Konrad Gębski on 25/04/2025.
//

#include "ScoreManager.h"
#include <QFile>
#include <QDataStream>
#include <QStandardPaths>
#include <QDir>
#include <algorithm>

const QString ScoreManager::SCORES_FILE = "pacman_scores.dat";

ScoreManager::ScoreManager() {
    loadScores();
}

bool ScoreManager::saveScore(const QString &playerName, int score) {
    // Wczytaj istniejące wyniki z pliku
    loadScores();

    scores.append(ScoreEntry(playerName, score));
    sortScores();

    // Zachowaj tylko top 10 wyników
    if (scores.size() > MAX_SCORES) {
        scores.resize(MAX_SCORES);
    }

    return saveScores();
}

QVector<ScoreEntry> ScoreManager::loadTopScores() {
    // Zawsze wczytaj najnowsze dane z pliku
    loadScores();
    return scores;
}

bool ScoreManager::isHighScore(int score) {
    // Zawsze sprawdź najnowsze dane z pliku
    loadScores();

    if (scores.size() < MAX_SCORES) {
        return true;
    }
    return score > scores.last().score;
}

void ScoreManager::refreshScores() {
    loadScores();
}

bool ScoreManager::loadScores() {
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString filePath = documentsPath + "/PacmanGame/" + SCORES_FILE;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return true; // Brak pliku nie jest błędem
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_0);
    in.setByteOrder(QDataStream::LittleEndian);

    if (file.size() == 0) {
        return true;
    }

    qint32 count;
    in >> count;

    if (in.status() != QDataStream::Ok || count < 0 || count > MAX_SCORES * 2) {
        return false;
    }

    scores.clear();
    for (qint32 i = 0; i < count; ++i) {
        qint32 nameLength;
        in >> nameLength;

        if (in.status() != QDataStream::Ok || nameLength < 0 || nameLength > 1000) {
            return false;
        }

        QByteArray nameBytes(nameLength, 0);
        int bytesRead = in.readRawData(nameBytes.data(), nameLength);

        if (bytesRead != nameLength || in.status() != QDataStream::Ok) {
            return false;
        }

        QString name = QString::fromUtf8(nameBytes);

        qint32 score;
        in >> score;

        if (in.status() != QDataStream::Ok) {
            return false;
        }

        if (score < 0 || name.isEmpty() || name.length() > 50) {
            continue;
        }

        scores.append(ScoreEntry(name, score));
    }

    sortScores();
    return true;
}

bool ScoreManager::saveScores() {
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString gameDir = documentsPath + "/PacmanGame";
    QDir().mkpath(gameDir);
    QString filePath = gameDir + "/" + SCORES_FILE;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_0);
    out.setByteOrder(QDataStream::LittleEndian);

    qint32 count = static_cast<qint32>(scores.size());
    out << count;

    if (out.status() != QDataStream::Ok) {
        return false;
    }

    for (const ScoreEntry &entry : scores) {
        QByteArray nameBytes = entry.playerName.toUtf8();
        qint32 nameLength = nameBytes.size();
        qint32 score = static_cast<qint32>(entry.score);

        out << nameLength;
        out.writeRawData(nameBytes.constData(), nameLength);
        out << score;

        if (out.status() != QDataStream::Ok) {
            return false;
        }
    }

    file.flush();
    return true;
}

void ScoreManager::sortScores() {
    std::sort(scores.begin(), scores.end(),
              [](const ScoreEntry &a, const ScoreEntry &b) {
                  return a.score > b.score;
              });
}