#include "Engine/Audio/AudioManager.hpp"

namespace Engine {

void AudioManager::playSound(const sf::SoundBuffer& buffer) {
    // Clean up finished sounds first
    cleanup();

    m_sounds.emplace_back(buffer);
    m_sounds.back().setVolume(m_soundVolume);
    m_sounds.back().play();
}

void AudioManager::setSoundVolume(float volume) {
    m_soundVolume = volume;
}

float AudioManager::getSoundVolume() const {
    return m_soundVolume;
}

void AudioManager::playMusic(const std::filesystem::path& filename, bool loop) {
    m_music = std::make_unique<sf::Music>();
    if (!m_music->openFromFile(filename)) {
        m_music.reset();
        throw std::runtime_error(
            "AudioManager: Failed to open music '" + filename.string() + "'");
    }
    m_music->setLooping(loop);
    m_music->setVolume(m_musicVolume);
    m_music->play();
}

void AudioManager::pauseMusic() {
    if (m_music) {
        m_music->pause();
    }
}

void AudioManager::resumeMusic() {
    if (m_music && m_music->getStatus() == sf::SoundSource::Status::Paused) {
        m_music->play();
    }
}

void AudioManager::stopMusic() {
    if (m_music) {
        m_music->stop();
    }
}

void AudioManager::setMusicVolume(float volume) {
    m_musicVolume = volume;
    if (m_music) {
        m_music->setVolume(volume);
    }
}

float AudioManager::getMusicVolume() const {
    return m_musicVolume;
}

bool AudioManager::isMusicPlaying() const {
    return m_music && m_music->getStatus() == sf::SoundSource::Status::Playing;
}

void AudioManager::stopAll() {
    for (auto& sound : m_sounds) {
        sound.stop();
    }
    m_sounds.clear();
    stopMusic();
}

void AudioManager::cleanup() {
    m_sounds.remove_if([](const sf::Sound& sound) {
        return sound.getStatus() == sf::SoundSource::Status::Stopped;
    });
}

} // namespace Engine
