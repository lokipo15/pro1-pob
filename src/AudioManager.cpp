/**
 * @file AudioManager.cpp
 * @brief Implementacja klasy AudioManager odpowiedzialnej za zarządzanie dźwiękami w grze
 * @author Gabriel Boruń, Konrad Gębski
 * @date 12/06/2025
 */

#include "AudioManager.h"
#include <QDebug>

/**
 * @brief Konstruktor klasy AudioManager
 * @param parent Wskaźnik na obiekt nadrzędny
 * 
 * Inicjalizuje wszystkie efekty dźwiękowe i ustawia ich parametry domyślne.
 */
AudioManager::AudioManager(QObject *parent) 
    : QObject(parent), backgroundMusic(nullptr), powerUpSound(nullptr), 
      ghostEatingSound(nullptr), deathSound(nullptr),
      musicVolume(70), soundEffectsVolume(80), audioEnabled(true) {
    
    /// Inicjalizacja wszystkich efektów dźwiękowych
    backgroundMusic = new QSoundEffect(this);
    powerUpSound = new QSoundEffect(this);
    ghostEatingSound = new QSoundEffect(this);
    deathSound = new QSoundEffect(this);
    
    /// Ustawienie domyślnej głośności na 80%
    backgroundMusic->setVolume(0.8f);
    powerUpSound->setVolume(0.8f);
    ghostEatingSound->setVolume(0.8f);
    deathSound->setVolume(0.8f);
    
    /// Włączenie wszystkich efektów dźwiękowych
    backgroundMusic->setMuted(false);
    powerUpSound->setMuted(false);
    ghostEatingSound->setMuted(false);
    deathSound->setMuted(false);
    
    /// Ustawienie nieskończonej pętli dla muzyki tła
    backgroundMusic->setLoopCount(QSoundEffect::Infinite);
    
}

/**
 * @brief Destruktor klasy AudioManager
 * 
 * Zatrzymuje wszystkie odtwarzane dźwięki przed zniszczeniem obiektu.
 */
AudioManager::~AudioManager() {
    /// Zatrzymanie muzyki tła przed zniszczeniem
    if (backgroundMusic) {
        backgroundMusic->stop();
    }
    /// Zatrzymanie efektu dźwiękowego power-up
    if (powerUpSound) {
        powerUpSound->stop();
    }
    /// Zatrzymanie efektu dźwiękowego zjadania ducha
    if (ghostEatingSound) {
        ghostEatingSound->stop();
    }
    /// Zatrzymanie efektu dźwiękowego śmierci
    if (deathSound) {
        deathSound->stop();
    }
}

/**
 * @brief Ustawia ścieżkę do pliku muzyki tła
 * @param path Ścieżka do pliku muzyki (może być zasobem Qt lub plikiem lokalnym)
 * 
 * Obsługuje zarówno zasoby Qt (rozpoczynające się od ":/") jak i lokalne pliki.
 */
void AudioManager::setBackgroundMusicPath(const QString &path) {
    backgroundMusicPath = path;
    if (backgroundMusic && !path.isEmpty()) {
        QUrl url;
        /// Konwersja ścieżki zasobu Qt na prawidłowy URL
        if (path.startsWith(":/")) {
            url = QUrl("qrc" + path);
        } else {
            url = QUrl(path);
        }
        backgroundMusic->setSource(url);
    }
}

/**
 * @brief Ustawia ścieżkę do pliku dźwięku power-up
 * @param path Ścieżka do pliku dźwięku (może być zasobem Qt lub plikiem lokalnym)
 */
void AudioManager::setPowerUpSoundPath(const QString &path) {
    powerUpSoundPath = path;
    if (powerUpSound && !path.isEmpty()) {
        QUrl url;
        /// Konwersja ścieżki zasobu Qt na prawidłowy URL
        if (path.startsWith(":/")) {
            url = QUrl("qrc" + path);
        } else {
            url = QUrl(path);
        }
        powerUpSound->setSource(url);
    }
}

/**
 * @brief Ustawia ścieżkę do pliku dźwięku zjadania ducha
 * @param path Ścieżka do pliku dźwięku (może być zasobem Qt lub plikiem lokalnym)
 */
void AudioManager::setGhostEatingSoundPath(const QString &path) {
    ghostEatingSoundPath = path;
    if (ghostEatingSound && !path.isEmpty()) {
        QUrl url;
        /// Konwersja ścieżki zasobu Qt na prawidłowy URL
        if (path.startsWith(":/")) {
            url = QUrl("qrc" + path);
        } else {
            url = QUrl(path);
        }
        ghostEatingSound->setSource(url);
    }
}

/**
 * @brief Ustawia ścieżkę do pliku dźwięku śmierci
 * @param path Ścieżka do pliku dźwięku (może być zasobem Qt lub plikiem lokalnym)
 */
void AudioManager::setDeathSoundPath(const QString &path) {
    deathSoundPath = path;
    if (deathSound && !path.isEmpty()) {
        QUrl url;
        /// Konwersja ścieżki zasobu Qt na prawidłowy URL
        if (path.startsWith(":/")) {
            url = QUrl("qrc" + path);
        } else {
            url = QUrl(path);
        }
        deathSound->setSource(url);
    }
}

/**
 * @brief Odtwarza muzykę tła
 * 
 * Muzyka jest odtwarzana w pętli, jeśli audio jest włączone i ścieżka została ustawiona.
 */
void AudioManager::playBackgroundMusic() {
    if (backgroundMusic && audioEnabled && !backgroundMusicPath.isEmpty()) {
        backgroundMusic->play();
    }
}

/**
 * @brief Zatrzymuje muzykę tła
 */
void AudioManager::stopBackgroundMusic() {
    if (backgroundMusic) {
        backgroundMusic->stop();
    }
}

/**
 * @brief Pauzuje muzykę tła
 * 
 * W QSoundEffect nie ma metody pause(), więc używamy stop().
 */
void AudioManager::pauseBackgroundMusic() {
    if (backgroundMusic) {
        backgroundMusic->stop();
    }
}

/**
 * @brief Wznawia odtwarzanie muzyki tła
 * 
 * Muzyka jest wznawiania tylko jeśli audio jest włączone.
 */
void AudioManager::resumeBackgroundMusic() {
    if (backgroundMusic && audioEnabled) {
        backgroundMusic->play();
    }
}

/**
 * @brief Odtwarza dźwięk power-up
 * 
 * Dźwięk jest odtwarzany jednorazowo po zebraniu power-up przez gracza.
 */
void AudioManager::playPowerUpSound() {
    if (powerUpSound && audioEnabled && !powerUpSoundPath.isEmpty()) {
        powerUpSound->play();
    }
}

/**
 * @brief Odtwarza dźwięk zjadania ducha
 * 
 * Dźwięk jest odtwarzany gdy Pacman zjada ducha w trybie frightened.
 */
void AudioManager::playGhostEatingSound() {
    if (ghostEatingSound && audioEnabled && !ghostEatingSoundPath.isEmpty()) {
        ghostEatingSound->play();
    }
}

/**
 * @brief Odtwarza dźwięk śmierci
 * 
 * Dźwięk jest odtwarzany gdy Pacman zostaje złapany przez ducha.
 */
void AudioManager::playDeathSound() {
    if (deathSound && audioEnabled && !deathSoundPath.isEmpty()) {
        deathSound->play();
    }
}

/**
 * @brief Ustawia głośność efektów dźwiękowych
 * @param volume Głośność w zakresie 0-100
 * 
 * Głośność jest automatycznie ograniczona do zakresu 0-100.
 */
void AudioManager::setSoundEffectsVolume(int volume) {
    /// Ograniczenie głośności do zakresu 0-100
    soundEffectsVolume = qBound(0, volume, 100);
    /// Konwersja na format float (0.0 - 1.0)
    float volumeFloat = soundEffectsVolume / 100.0f;
    
    /// Aktualizacja głośności wszystkich efektów dźwiękowych
    if (powerUpSound) {
        powerUpSound->setVolume(volumeFloat);
    }
    if (ghostEatingSound) {
        ghostEatingSound->setVolume(volumeFloat);
    }
    if (deathSound) {
        deathSound->setVolume(volumeFloat);
    }
}

/**
 * @brief Włącza lub wyłącza audio w grze
 * @param enabled true - włącza audio, false - wyłącza audio
 * 
 * Gdy audio jest wyłączane, automatycznie zatrzymuje muzykę tła.
 */
void AudioManager::setAudioEnabled(bool enabled) {
    audioEnabled = enabled;
    
    /// Zatrzymanie muzyki tła gdy audio jest wyłączane
    if (!enabled) {
        stopBackgroundMusic();
    }
}