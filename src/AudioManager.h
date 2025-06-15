/**
 * @file AudioManager.h
 * @brief Zarządzanie dźwiękami w grze Pacman
 * @author Gabriel Boruń, Konrad Gębski
 * @date 12/06/2025
 */

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>
#include <QSoundEffect>
#include <QString>

/**
 * @brief Klasa zarządzająca dźwiękami w grze
 * 
 * Odpowiada za odtwarzanie muzyki tła, efektów dźwiękowych
 * i kontrolę głośności audio w grze Pacman.
 */
class AudioManager : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Konstruktor managera audio
     * @param parent Rodzic obiektu Qt
     */
    AudioManager(QObject *parent = nullptr);
    /**
     * @brief Destruktor managera audio
     */
    ~AudioManager();

    /**
     * @brief Ustawia ścieżkę do pliku muzyki tła
     * @param path Ścieżka do pliku audio
     */
    void setBackgroundMusicPath(const QString &path);
    /**
     * @brief Ustawia ścieżkę do pliku dźwięku power-up
     * @param path Ścieżka do pliku audio
     */
    void setPowerUpSoundPath(const QString &path);
    /**
     * @brief Ustawia ścieżkę do pliku dźwięku zjadania duchów
     * @param path Ścieżka do pliku audio
     */
    void setGhostEatingSoundPath(const QString &path);
    /**
     * @brief Ustawia ścieżkę do pliku dźwięku śmierci
     * @param path Ścieżka do pliku audio
     */
    void setDeathSoundPath(const QString &path);

    /**
     * @brief Rozpoczyna odtwarzanie muzyki tła
     */
    void playBackgroundMusic();
    /**
     * @brief Zatrzymuje muzykę tła
     */
    void stopBackgroundMusic();
    /**
     * @brief Pauzuje muzykę tła
     */
    void pauseBackgroundMusic();
    /**
     * @brief Wznawia odtwarzanie muzyki tła
     */
    void resumeBackgroundMusic();

    /**
     * @brief Odtwarza dźwięk power-up
     */
    void playPowerUpSound();
    /**
     * @brief Odtwarza dźwięk zjadania ducha
     */
    void playGhostEatingSound();
    /**
     * @brief Odtwarza dźwięk śmierci gracza
     */
    void playDeathSound();

    /**
     * @brief Ustawia głośność efektów dźwiękowych
     * @param volume Poziom głośności (0-100)
     */
    void setSoundEffectsVolume(int volume);

    /**
     * @brief Włącza lub wyłącza audio
     * @param enabled True aby włączyć, false aby wyłączyć
     */
    void setAudioEnabled(bool enabled);
    /**
     * @brief Sprawdza czy audio jest włączone
     * @return True jeśli audio jest włączone
     */
    bool isAudioEnabled() const { return audioEnabled; }

private:
    QSoundEffect *backgroundMusic;      ///< Obiekt odtwarzający muzykę tła
    QSoundEffect *powerUpSound;         ///< Obiekt odtwarzający dźwięk power-up
    QSoundEffect *ghostEatingSound;     ///< Obiekt odtwarzający dźwięk zjadania ducha
    QSoundEffect *deathSound;           ///< Obiekt odtwarzający dźwięk śmierci

    QString backgroundMusicPath;        ///< Ścieżka do pliku muzyki tła
    QString powerUpSoundPath;           ///< Ścieżka do pliku dźwięku power-up
    QString ghostEatingSoundPath;       ///< Ścieżka do pliku dźwięku zjadania ducha
    QString deathSoundPath;             ///< Ścieżka do pliku dźwięku śmierci

    int musicVolume;                    ///< Głośność muzyki (0-100)
    int soundEffectsVolume;             ///< Głośność efektów dźwiękowych (0-100)
    bool audioEnabled;                  ///< Flaga określająca czy audio jest włączone

};

#endif // AUDIOMANAGER_H