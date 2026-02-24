# SFML Professional Game Architecture (MVC + State Machine)

Este repositorio proporciona una plantilla base profesional y escalable para el desarrollo de videojuegos en C++ utilizando la biblioteca SFML. La arquitectura implementa patrones de diseño avanzados para garantizar el bajo acoplamiento, la mantenibilidad y la eficiencia en el rendimiento.

## 🏗️ Arquitectura del Sistema

El proyecto está estructurado siguiendo principios de ingeniería de software modernos, dividiéndose en un núcleo de motor (Core) y una implementación de juego (Game).

### 1. Motor Base (Core)
*   **Game Engine**: Gestiona el ciclo de vida principal mediante un **Fixed Time Step** (60 FPS fijos para lógica), garantizando que la física y el comportamiento del juego sean consistentes independientemente de la potencia del hardware.
*   **State Machine**: Implementa el patrón *State* para gestionar diferentes escenas (Menú, Juego, Pausa, Game Over) de forma independiente y transicional.
*   **ResourceManager**: Un gestor genérico basado en plantillas (`templates`) para la carga y caché de recursos (`sf::Texture`, `sf::Font`, `sf::SoundBuffer`). Optimiza el uso de memoria evitando cargas duplicadas desde el disco.

### 2. Capa de Aplicación (MVC + SOLID)
El juego utiliza el patrón **Model-View-Controller (MVC)** bajo principios **SOLID**:
*   **Model**: Contiene el estado puro y la lógica de negocio. Es independiente de la representación visual.
*   **View**: Interfaz pasiva encargada exclusivamente del renderizado. Implementa la interfaz `IView` para permitir la inversión de dependencias.
*   **Controller**: Actúa como mediador, procesando la entrada y coordinando la actualización del modelo y la vista.

## 📂 Estructura del Proyecto

```text
├── include/
│   ├── Core/           # Componentes del motor (Game, ResourceManager)
│   ├── States/         # Gestión de escenas y máquina de estados
│   └── Game/           # Entidades del juego (Model, View, Controller, Interfaces)
├── src/
│   ├── Core/           # Implementación del motor
│   ├── States/         # Implementación de la lógica de estados
│   ├── Game/           # Implementación del MVC y lógica de entidades
│   └── main.cpp        # Punto de entrada y configuración inicial
├── CMakeLists.txt      # Sistema de construcción automatizado
└── assets/             # Directorio para recursos (imágenes, fuentes, sonidos)
```

## 🚀 Guía de Inicio Rápido

### Requisitos Previos
*   Compilador con soporte C++17 o superior.
*   [SFML 2.5+](https://www.sfml-dev.org/) instalado en el sistema.
*   CMake 3.25+.

### Compilación
```bash
mkdir build && cd build
cmake ..
make
./Revolution_Game
```

## 🛠️ Cómo Extender el Proyecto

### 1. Crear una nueva Escena (Estado)
Para añadir una pantalla (ej. `MenuState`), hereda de `Engine::State`:
```cpp
class MenuState : public Engine::State {
    void init() override;
    void handleInput() override;
    void update(float dt) override;
    void draw(float dt) override;
};
```

### 2. Uso del ResourceManager
Accede a los recursos de forma eficiente a través del contexto global del juego:
```cpp
// Cargar
m_data->textures.load("player_id", "assets/player.png");
// Usar
sf::Sprite sprite(m_data->textures.get("player_id"));
```

### 3. Implementar nuevas Entidades
Sigue el patrón de **Inyección de Dependencias** utilizado en el `Controller` actual:
```cpp
// El controlador no crea sus dependencias, las recibe (DIP)
Controller(Model* m, IView* v);
```

## 📜 Principios de Diseño Aplicados
*   **Single Responsibility Principle (SRP)**: Cada clase tiene una única razón para cambiar.
*   **Dependency Inversion Principle (DIP)**: El controlador depende de abstracciones (`IView`), no de implementaciones concretas de SFML.
*   **Encapsulamiento**: Los datos internos de los modelos están protegidos contra modificaciones externas no controladas.

---
Desarrollado como una base sólida para proyectos de videojuegos 2D profesionales.
