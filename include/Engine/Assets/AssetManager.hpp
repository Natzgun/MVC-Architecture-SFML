#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>
#include <filesystem>

namespace Engine {

/// Generic resource cache that loads, stores, and retrieves SFML resources.
///
/// Works with any SFML resource type that supports `loadFromFile()`
/// (sf::Texture, sf::Font, sf::SoundBuffer, etc.).
///
/// Resources are stored as unique_ptr and accessed by a string identifier.
/// Loading the same ID twice is a no-op (returns silently).
///
/// @tparam Resource An SFML resource type with a `loadFromFile` method.
template <typename Resource>
class AssetManager {
public:
    AssetManager() = default;
    ~AssetManager() = default;

    // Non-copyable, movable
    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;
    AssetManager(AssetManager&&) = default;
    AssetManager& operator=(AssetManager&&) = default;

    /// Load a resource from a file and associate it with the given ID.
    /// If the ID already exists, this call is ignored.
    /// @param id       Unique identifier for the resource.
    /// @param filename Path to the resource file.
    /// @throws std::runtime_error if the file cannot be loaded.
    void load(const std::string& id, const std::filesystem::path& filename) {
        if (m_assets.contains(id)) {
            return;
        }

        auto asset = std::make_unique<Resource>();
        if (!asset->loadFromFile(filename)) {
            throw std::runtime_error(
                "AssetManager: Failed to load '" + filename.string() + "'");
        }

        m_assets.emplace(id, std::move(asset));
    }

    /// Retrieve a loaded resource by its ID.
    /// @param id The identifier used when loading.
    /// @throws std::runtime_error if the resource is not found.
    [[nodiscard]] Resource& get(const std::string& id) {
        auto it = m_assets.find(id);
        if (it == m_assets.end()) {
            throw std::runtime_error(
                "AssetManager: Asset not found -> " + id);
        }
        return *it->second;
    }

    /// Retrieve a loaded resource by its ID (const version).
    [[nodiscard]] const Resource& get(const std::string& id) const {
        auto it = m_assets.find(id);
        if (it == m_assets.end()) {
            throw std::runtime_error(
                "AssetManager: Asset not found -> " + id);
        }
        return *it->second;
    }

    /// Check whether a resource with the given ID is loaded.
    [[nodiscard]] bool has(const std::string& id) const {
        return m_assets.contains(id);
    }

    /// Remove a specific resource from the cache.
    void unload(const std::string& id) {
        m_assets.erase(id);
    }

    /// Remove all resources from the cache.
    void clear() {
        m_assets.clear();
    }

    /// Get the number of loaded resources.
    [[nodiscard]] std::size_t size() const {
        return m_assets.size();
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Resource>> m_assets;
};

// Convenient type aliases for common SFML resource types.
using TextureManager     = AssetManager<sf::Texture>;
using FontManager        = AssetManager<sf::Font>;
using SoundBufferManager = AssetManager<sf::SoundBuffer>;

} // namespace Engine
