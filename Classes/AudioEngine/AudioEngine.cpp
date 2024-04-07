#include "AudioEngine.h"

Audio* Audio::instance = nullptr;

Audio::Audio() {
    int backgroundMusicId = play2d("Sounds/bg_music.mp3", true);
}

Audio::~Audio() {
    stop(backgroundMusicId);
}

Audio* Audio::getInstance() {
    if (!instance) {
        instance = new Audio();
    }
    return instance;
}

int Audio::play2d(const std::string& filePath, bool loop, float volume, const AudioProfile* profile) {
    return AudioEngine::play2d(filePath, loop, volume, profile);
}

void Audio::setVolume(int audioId, float volume) {
    AudioEngine::setVolume(audioId, volume);
}

void Audio::pause(int audioId) {
    AudioEngine::pause(audioId);
}

void Audio::resume(int audioId) {
    AudioEngine::resume(audioId);
}

void Audio::stop(int audioId) {
    AudioEngine::stop(audioId);
}
