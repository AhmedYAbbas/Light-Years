# Light Years

A space-shooter action game/game engine built with C++ and SFML.​

[![Watch the video](https://img.youtube.com/vi/yFh2rjWwgo4/hqdefault.jpg)](https://www.youtube.com/embed/yFh2rjWwgo4)

***
## Features
- Custom C++ game engine (`LightYearsCore`) with an actor/world framework, timers, delegates, and a widget-based UI system.
- Box2D-powered physics and collisions.
- A full gameplay loop: main menu, multiple enemy types (Vanguard, TwinBlade, Hexagon, UFO), a Chaos Stage, and a Boss Stage.
- HUD with health, life count, and score tracking, plus a Game Over screen.
- Parallax scrolling backgrounds and particle-based VFX (explosions, etc.).

## Tech Stack
- C++20
- [SFML 2.6.1](https://github.com/SFML/SFML) — rendering, windowing, audio
- [Box2D 2.4.1](https://github.com/erincatto/box2d) — physics
- CMake 3.29+ (SFML and Box2D are fetched automatically via `FetchContent`)

***
## Building the Project
1. Clone the repository to your local machine.
2. Navigate to the root directory of the project.
3. Create a new directory named `build`.
4. Open Command Prompt (CMD) and change the directory to the newly created `build` folder.
5. In CMD, type the following command to configure the project: `cmake -S .. -B .`
   - This step requires an internet connection, as CMake will download SFML and Box2D automatically.
6. Once configuration succeeds, open `LightYears.sln` in the `build` directory with Visual Studio and build the `LightYearsGame` project.
***

## Controls
- WASD keys for movement.
- 'Space' key for firing.
