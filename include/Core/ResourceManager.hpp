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
class ResourceManager {
public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    // Non-copyable, movable
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = default;
    ResourceManager& operator=(ResourceManager&&) = default;

    /// Load a resource from a file and associate it with the given ID.
    /// If the ID already exists, this call is ignored.
    /// @param id       Unique identifier for the resource.
    /// @param filename Path to the resource file.
    /// @throws std::runtime_error if the file cannot be loaded.
    void load(const std::string& id, const std::filesystem::path& filename) {
        if (m_resources.contains(id)) {
            return;
        }

        auto resource = std::make_unique<Resource>();
        if (!resource->loadFromFile(filename)) {
            throw std::runtime_error(
                "ResourceManager: Failed to load '" + filename.string() + "'");
        }

        m_resources.emplace(id, std::move(resource));
    }

    /// Retrieve a loaded resource by its ID.
    /// @param id The identifier used when loading.
    /// @throws std::runtime_error if the resource is not found.
    [[nodiscard]] Resource& get(const std::string& id) {
        auto it = m_resources.find(id);
        if (it == m_resources.end()) {
            throw std::runtime_error(
                "ResourceManager: Resource not found -> " + id);
        }
        return *it->second;
    }

    /// Check whether a resource with the given ID is loaded.
    [[nodiscard]] bool has(const std::string& id) const {
        return m_resources.contains(id);
    }

    /// Remove a specific resource from the cache.
    void unload(const std::string& id) {
        m_resources.erase(id);
    }

    /// Remove all resources from the cache.
    void clear() {
        m_resources.clear();
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Resource>> m_resources;
};

// Convenient type aliases for common SFML resource types.
using TextureManager     = ResourceManager<sf::Texture>;
using FontManager        = ResourceManager<sf::Font>;
using SoundBufferManager = ResourceManager<sf::SoundBuffer>;

} // namespace Engine
