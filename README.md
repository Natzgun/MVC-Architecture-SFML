# SFML Engine Architecture - Professional Template

Este proyecto constituye una arquitectura base robusta para el desarrollo de videojuegos 2D utilizando la biblioteca SFML y C++17. Se fundamenta en patrones de diseño de alto nivel para garantizar la escalabilidad, el rendimiento y el desacoplamiento de componentes.

## 1. Arquitectura del Motor (Core)

El motor se articula en torno a tres componentes fundamentales que gestionan el ciclo de vida, los recursos y el flujo de la aplicación.

### 1.1 Game Loop (Fixed Time Step)

A diferencia de un bucle de juego simple, esta arquitectura implementa un **Fixed Time Step**. Esto asegura que la lógica del juego (física, colisiones) se ejecute a una frecuencia constante (60 Hz por defecto), independientemente de la tasa de refresco (FPS) del monitor.

```cpp
void Game::run() {
    float currentTime = m_clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    while (m_data->window->isOpen()) {
        float newTime = m_clock.getElapsedTime().asSeconds();
        float frameTime = newTime - currentTime;
        if (frameTime > 0.25f) frameTime = 0.25f;
        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= dt) {
            m_data->machine->getActiveState()->update(dt);
            accumulator -= dt;
        }
        // Renderizado con interpolación
        m_data->window->clear();
        m_data->machine->getActiveState()->draw(accumulator / dt);
        m_data->window->display();
    }
}
```

### 1.2 State Machine (Gestión de Escenas)

La gestión de pantallas (Menú, Juego, Pausa) se realiza mediante una pila de estados. Esto permite superponer estados (como un menú de pausa sobre el juego activo) sin perder el contexto.

*   `pushState`: Añade un estado sobre el actual.
*   `changeState`: Reemplaza el estado activo.
*   `popState`: Elimina el estado actual y resume el anterior.

### 1.3 ResourceManager (Gestión de Memoria)

Implementa una caché de recursos basada en plantillas para optimizar el uso de memoria. Los recursos (texturas, fuentes, sonidos) se cargan una única vez y se comparten mediante referencias.

```cpp
template <typename Resource>
class ResourceManager {
    std::unordered_map<std::string, std::unique_ptr<Resource>> m_resources;
public:
    void load(const std::string& id, const std::string& filename);
    Resource& get(const std::string& id);
};
```

## 2. Flujo de Ejecución

El flujo de la aplicación sigue una jerarquía clara desde la inicialización hasta el cierre:

1.  **Entry Point (`main.cpp`)**: Instancia la clase `Game` y define el estado inicial (`GameState`).
2.  **Motor (`Game`)**: Configura la ventana y los sistemas de Core. Inicia el bucle principal.
3.  **Gestión de Estados**: El `StateMachine` procesa los cambios pendientes antes de cada iteración del bucle.
4.  **Ciclo de Estado**:
    *   `handleInput()`: Captura eventos de SFML y entradas de teclado.
    *   `update(dt)`: Actualiza la lógica de las entidades (MVC interno).
    *   `draw(dt)`: Ejecuta el renderizado a través de la Vista.

## 3. Implementación de Entidades (MVC & SOLID)

Dentro de cada estado, las entidades se organizan siguiendo el patrón Model-View-Controller, aplicando Inversión de Dependencias (DIP) mediante interfaces.

### 3.1 Desacoplamiento de la Vista (IView)

El controlador no interactúa directamente con clases concretas de SFML, sino con una interfaz abstracta. Esto permite cambiar el backend de renderizado sin modificar la lógica de control.

```cpp
class IView {
public:
    virtual ~IView() = default;
    virtual void drawEsfera(int radio, int x, int y) = 0;
};
```

### 3.2 Inyección de Dependencias

El ensamblaje de componentes se realiza en el método `init()` de cada estado, garantizando que el `Controller` reciba sus dependencias de forma externa:

```cpp
void GameState::init() {
    m_model = std::make_unique<Model>();
    m_view = std::make_unique<View>(m_data);
    m_controller = std::make_unique<Controller>(m_model.get(), m_view.get());
}
```

## 4. Instalación y Construcción

El proyecto utiliza CMake como sistema de construcción, lo que facilita la gestión de dependencias y la compilación multiplataforma.

```bash
# Crear directorio de construcción
mkdir build && cd build

# Configurar y compilar
cmake ..
make

# Ejecutar el binario
./Revolution_Game
```

## 5. Licencia

Este proyecto se distribuye bajo la **Apache License 2.0**. Consulte el archivo `LICENSE` para obtener más detalles sobre los términos de uso, reproducción y distribución.
