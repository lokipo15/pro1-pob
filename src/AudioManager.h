//
// Created by Gabriel Boruń on 12/06/2025.
// Co-authored by Konrad Gębski on 12/06/2025.
//

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QString>

class AudioManager : public QObject {
    Q_OBJECT

public:
    AudioManager(QObject *parent = nullptr);
    ~AudioManager();

    // Configuration methods for audio file paths
    void setBackgroundMusicPath(const QString &path);
    void setPowerUpSoundPath(const QString &path);
    void setGhostEatingSoundPath(const QString &path);
    void setDeathSoundPath(const QString &path);

    // Sound control methods
    void playBackgroundMusic();
    void stopBackgroundMusic();
    void pauseBackgroundMusic();
    void resumeBackgroundMusic();

    void playPowerUpSound();
    void playGhostEatingSound();
    void playDeathSound();

    // Volume control
    void setSoundEffectsVolume(int volume); // 0-100

    // Enable/disable audio
    void setAudioEnabled(bool enabled);
    bool isAudioEnabled() const { return audioEnabled; }

private:
    QMediaPlayer *backgroundMusic;
    QMediaPlayer *powerUpSound;
    QMediaPlayer *ghostEatingSound;
    QMediaPlayer *deathSound;

    QString backgroundMusicPath;
    QString powerUpSoundPath;
    QString ghostEatingSoundPath;
    QString deathSoundPath;

    int musicVolume;
    int soundEffectsVolume;
    bool audioEnabled;

};

#endif // AUDIOMANAGER_H