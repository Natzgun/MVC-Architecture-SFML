#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <list>
#include <memory>
#include <filesystem>
#include <stdexcept>

namespace Engine {

/// Abstraction layer for audio playback (sound effects and music).
///
/// Sound effects are short samples loaded as sf::SoundBuffer (via AssetManager)
/// and played through pooled sf::Sound instances. Music streams from disk
/// via sf::Music for large audio files.
///
/// Usage:
/// @code
///   // Load a sound buffer through the AssetManager first
///   assets.sounds.load("jump", "assets/audio/jump.wav");
///
///   // Then play it through AudioManager
///   audioManager.playSound(assets.sounds.get("jump"));
///
///   // Music
///   audioManager.playMusic("assets/audio/theme.ogg");
///   audioManager.setMusicVolume(50.f);
/// @endcode
class AudioManager {
public:
    AudioManager() = default;
    ~AudioManager() = default;

    // Non-copyable, movable
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;
    AudioManager(AudioManager&&) = default;
    AudioManager& operator=(AudioManager&&) = default;

    // ---- Sound Effects ----

    /// Play a sound effect from a loaded SoundBuffer.
    /// Automatically manages sf::Sound instances (pooling).
    /// @param buffer The SoundBuffer to play.
    void playSound(const sf::SoundBuffer& buffer);

    /// Set the global volume for sound effects [0, 100].
    void setSoundVolume(float volume);

    /// Get the current sound effect volume.
    [[nodiscard]] float getSoundVolume() const;

    // ---- Music (streaming) ----

    /// Open and play a music file from disk (streams, doesn't load fully).
    /// @param filename Path to the music file.
    /// @param loop     Whether to loop the music.
    /// @throws std::runtime_error if the file cannot be opened.
    void playMusic(const std::filesystem::path& filename, bool loop = true);

    /// Pause the currently playing music.
    void pauseMusic();

    /// Resume paused music.
    void resumeMusic();

    /// Stop the currently playing music.
    void stopMusic();

    /// Set the music volume [0, 100].
    void setMusicVolume(float volume);

    /// Get the current music volume.
    [[nodiscard]] float getMusicVolume() const;

    /// Check if music is currently playing.
    [[nodiscard]] bool isMusicPlaying() const;

    // ---- Global ----

    /// Stop all sounds and music.
    void stopAll();

    /// Remove finished sound instances to free resources.
    /// Called automatically by playSound, but can be called manually.
    void cleanup();

private:
    /// Pool of active sound instances.
    std::list<sf::Sound> m_sounds;

    /// Current music stream.
    std::unique_ptr<sf::Music> m_music;

    float m_soundVolume = 100.f;
    float m_musicVolume = 100.f;
};

} // namespace Engine
