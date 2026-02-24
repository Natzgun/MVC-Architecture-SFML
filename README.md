# SFML Engine Architecture - Professional Game Template

Este repositorio proporciona una infraestructura técnica avanzada para el desarrollo de videojuegos 2D utilizando C++17 y la biblioteca SFML. La arquitectura ha sido diseñada bajo estándares de ingeniería de software profesionales, integrando patrones de diseño que aseguran un alto rendimiento, mantenibilidad y desacoplamiento.

## 1. Arquitectura del Sistema

El motor se divide en dos capas principales: el Núcleo (Core) y la Capa de Aplicación (Game).

### 1.1 Motor Base (Core)

#### 1.1.1 Ciclo de Vida (Game Loop)
Se implementa un bucle de tiempo fijo (Fixed Time Step). Esta técnica es estándar en la industria para garantizar que la lógica del juego y la física se ejecuten a una velocidad constante, evitando inconsistencias causadas por variaciones en la tasa de refresco (FPS).

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
        // Renderizado
        m_data->window->clear();
        m_data->machine->getActiveState()->draw(accumulator / dt);
        m_data->window->display();
    }
}
```

#### 1.1.2 Gestión de Estados (State Machine)
La navegación entre escenas (Menú, Nivel, Pausa) se administra mediante una máquina de estados basada en una pila (Stack). Esto permite la superposición de contextos y una transición fluida entre pantallas sin pérdida de estado.

#### 1.1.3 Gestión de Recursos (ResourceManager)
Utiliza un sistema de caché basado en plantillas para centralizar la carga de activos (texturas, fuentes y audio), reduciendo el consumo de memoria y optimizando el acceso a los datos.

### 1.2 Implementación MVC y SOLID

Dentro de cada estado, las entidades siguen el patrón Model-View-Controller, reforzado por el principio de Inversión de Dependencias (DIP).

*   **Model**: Gestiona los datos y la lógica interna de la entidad.
*   **View**: Implementa la interfaz `IView` para renderizar el estado del modelo.
*   **Controller**: Recibe dependencias inyectadas para coordinar el flujo entre modelo y vista.

```cpp
// Ejemplo de Inyección de Dependencias en el Controlador
Controller::Controller(Model* m, Game::IView* v) : modelo(m), vista(v) {}
```

## 2. Estructura del Proyecto

La organización de directorios sigue el estándar de la industria para separar las declaraciones de las implementaciones:

```text
├── include/            # Cabeceras (.h / .hpp)
│   ├── Core/           # Componentes base del motor
│   ├── States/         # Máquina de estados y estados globales
│   └── Game/           # Lógica de entidades (MVC e Interfaces)
├── src/                # Implementaciones (.cpp)
│   ├── Core/           # Lógica del motor y Game Loop
│   ├── States/         # Lógica de transiciones de escenas
│   ├── Game/           # Lógica de controladores, modelos y vistas
│   └── main.cpp        # Punto de entrada de la aplicación
├── assets/             # Recursos multimedia (imágenes, audio, fuentes)
├── CMakeLists.txt      # Configuración del sistema de construcción
└── LICENSE             # Apache License 2.0
```

## 3. Flujo de Ejecución Detallado

1.  **Inicialización**: `main.cpp` instancia el objeto `Engine::Game` y registra el estado inicial a través de la máquina de estados.
2.  **Procesamiento de Estados**: En cada iteración, el motor verifica si existen cambios de escena (push/pop/change).
3.  **Entrada (Input)**: El estado activo captura los eventos de sistema y periféricos a través de `handleInput()`.
4.  **Actualización (Update)**: Se ejecuta la lógica del controlador y el modelo utilizando un paso de tiempo fijo (`dt`).
5.  **Renderizado (Draw)**: La vista dibuja los componentes en la ventana compartida del contexto global.

## 4. Guía de Inicio y Construcción

### 4.1 Requisitos
*   Compilador compatible con C++17 (GCC 7+, Clang 5+, MSVC 2017+).
*   CMake 3.28+.
*   Este proyecto utiliza la estructura recomendada por [SFML/cmake-sfml-project](https://github.com/SFML/cmake-sfml-project/) para la gestión automática de dependencias.

### 4.2 Compilación
Siga estos comandos para construir el binario desde la terminal:

```bash
# 1. Crear directorio de compilación
mkdir build && cd build

# 2. Generar archivos de construcción
cmake ..

# 3. Compilar el proyecto
make

# 4. Ejecutar el videojuego
./Revolution_Game
```

## 5. Licencia

Este software se distribuye bajo la **Apache License 2.0**. Esta licencia permite el uso comercial, la modificación y la distribución, garantizando al mismo tiempo la protección de patentes por parte de los contribuidores. Para más detalles, consulte el archivo `LICENSE`.
