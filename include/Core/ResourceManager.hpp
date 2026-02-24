#ifndef REVOLUTION_GAME_RESOURCEMANAGER_HPP
#define REVOLUTION_GAME_RESOURCEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>

template <typename Resource>
class ResourceManager {
private:
    std::unordered_map<std::string, std::unique_ptr<Resource>> m_resources;

public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    // Carga un recurso desde un archivo y lo asocia a un nombre (id)
    void load(const std::string& id, const std::string& filename) {
        if (m_resources.find(id) != m_resources.end()) {
            std::cerr << "Advertencia: El recurso '" << id << "' ya estaba cargado.
";
            return;
        }

        auto resource = std::make_unique<Resource>();
        if (!resource->loadFromFile(filename)) {
            throw std::runtime_error("ResourceManager: Error al cargar " + filename);
        }

        m_resources.insert(std::make_pair(id, std::move(resource)));
    }

    // Obtiene una referencia al recurso cargado
    Resource& get(const std::string& id) {
        auto found = m_resources.find(id);
        if (found == m_resources.end()) {
            throw std::runtime_error("ResourceManager: Recurso no encontrado -> " + id);
        }
        return *found->second;
    }
};

// Typedefs útiles para no escribir todo el template
using TextureManager = ResourceManager<sf::Texture>;
using FontManager    = ResourceManager<sf::Font>;
using SoundBufferManager = ResourceManager<sf::SoundBuffer>;

#endif //REVOLUTION_GAME_RESOURCEMANAGER_HPP