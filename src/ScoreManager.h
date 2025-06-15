/**
 * @file ScoreManager.h
 * @brief Zarządzanie wynikami i tablicą najlepszych wyników
 * @author Gabriel Boruń, Konrad Gębski
 * @date 25/04/2025
 */

#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <QString>
#include <QVector>
#include <QDataStream>

/**
 * @brief Struktura reprezentująca wpis wyniku
 * 
 * Zawiera imię gracza i osiągnięty wynik.
 */
struct ScoreEntry {
    QString playerName; ///< Imię gracza
    int score;          ///< Osiągnięty wynik

    /**
     * @brief Konstruktor domyślny
     */
    ScoreEntry() : score(0) {}
    
    /**
     * @brief Konstruktor z parametrami
     * @param name Imię gracza
     * @param s Wynik gracza
     */
    ScoreEntry(const QString &name, int s) : playerName(name), score(s) {}
};

/**
 * @brief Klasa zarządzająca wynikami gry
 * 
 * Odpowiada za zapisywanie, wczytywanie i sortowanie
 * najlepszych wyników graczy.
 */
class ScoreManager {
public:
    /**
     * @brief Konstruktor managera wyników
     */
    ScoreManager();

    /**
     * @brief Zapisuje wynik gracza
     * @param playerName Imię gracza
     * @param score Wynik gracza
     * @return True jeśli zapisano pomyślnie
     */
    bool saveScore(const QString &playerName, int score);
    /**
     * @brief Wczytuje najlepsze wyniki
     * @return Wektor najlepszych wyników
     */
    QVector<ScoreEntry> loadTopScores();
    /**
     * @brief Sprawdza czy wynik kwalifikuje się do top 10
     * @param score Wynik do sprawdzenia
     * @return True jeśli wynik jest wystarczająco wysoki
     */
    bool isHighScore(int score);
    /**
     * @brief Odświeża listę wyników z pliku
     */
    void refreshScores();

private:
    static const QString SCORES_FILE;   ///< Nazwa pliku z wynikami
    static const int MAX_SCORES = 10;   ///< Maksymalna liczba zapisanych wyników

    QVector<ScoreEntry> scores;         ///< Wektor przechowujący wyniki

    /**
     * @brief Wczytuje wyniki z pliku
     * @return True jeśli wczytano pomyślnie
     */
    bool loadScores();
    /**
     * @brief Zapisuje wyniki do pliku
     * @return True jeśli zapisano pomyślnie
     */
    bool saveScores();
    /**
     * @brief Sortuje wyniki malejąco
     */
    void sortScores();
};

#endif ///SCOREMANAGER_H