//
// Created by Gabriel Boruń on 12/06/2025.
// Co-authored by Konrad Gębski on 12/06/2025.
//

#include "AudioManager.h"

AudioManager::AudioManager(QObject *parent) 
    : QObject(parent), backgroundMusic(nullptr), powerUpSound(nullptr), 
      ghostEatingSound(nullptr), deathSound(nullptr),
      musicVolume(70), soundEffectsVolume(80), audioEnabled(true) {
    
    // Initialize media players
    backgroundMusic = new QMediaPlayer(this);
    powerUpSound = new QMediaPlayer(this);
    ghostEatingSound = new QMediaPlayer(this);
    deathSound = new QMediaPlayer(this);
}

AudioManager::~AudioManager() {
    if (backgroundMusic) {
        backgroundMusic->stop();
    }
    if (powerUpSound) {
        powerUpSound->stop();
    }
    if (ghostEatingSound) {
        ghostEatingSound->stop();
    }
    if (deathSound) {
        deathSound->stop();
    }
}

void AudioManager::setBackgroundMusicPath(const QString &path) {
    backgroundMusicPath = path;
    if (backgroundMusic && !path.isEmpty()) {
        backgroundMusic->setSource(QUrl::fromLocalFile(path));
    }
}

void AudioManager::setPowerUpSoundPath(const QString &path) {
    powerUpSoundPath = path;
    if (powerUpSound && !path.isEmpty()) {
        powerUpSound->setSource(QUrl::fromLocalFile(path));
    }
}

void AudioManager::setGhostEatingSoundPath(const QString &path) {
    ghostEatingSoundPath = path;
    if (ghostEatingSound && !path.isEmpty()) {
        ghostEatingSound->setSource(QUrl::fromLocalFile(path));
    }
}

void AudioManager::setDeathSoundPath(const QString &path) {
    deathSoundPath = path;
    if (deathSound && !path.isEmpty()) {
        deathSound->setSource(QUrl::fromLocalFile(path));
    }
}

void AudioManager::playBackgroundMusic() {
    if (backgroundMusic && audioEnabled && !backgroundMusicPath.isEmpty()) {
        backgroundMusic->play();
    }
}

void AudioManager::stopBackgroundMusic() {
    if (backgroundMusic) {
        backgroundMusic->stop();
    }
}

void AudioManager::pauseBackgroundMusic() {
    if (backgroundMusic) {
        backgroundMusic->pause();
    }
}

void AudioManager::resumeBackgroundMusic() {
    if (backgroundMusic && audioEnabled) {
        backgroundMusic->play();
    }
}

void AudioManager::playPowerUpSound() {
    if (powerUpSound && audioEnabled && !powerUpSoundPath.isEmpty()) {
        powerUpSound->play();
    }
}

void AudioManager::playGhostEatingSound() {
    if (ghostEatingSound && audioEnabled && !ghostEatingSoundPath.isEmpty()) {
        ghostEatingSound->play();
    }
}

void AudioManager::playDeathSound() {
    if (deathSound && audioEnabled && !deathSoundPath.isEmpty()) {
        deathSound->play();
    }
}

void AudioManager::setSoundEffectsVolume(int volume) {
    soundEffectsVolume = qBound(0, volume, 100);
}

void AudioManager::setAudioEnabled(bool enabled) {
    audioEnabled = enabled;
    
    if (!enabled) {
        stopBackgroundMusic();
    }
}