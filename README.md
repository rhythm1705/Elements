# Elements Game Engine

> An awesome game engine to learn C++, Vulkan, computer graphics rendering and most importantly to have fun.

## Current Progress

- [x] Window creation and resizing using GLFW
- [x] Keyboard and Mouse Input
- [x] Logging
- [ ] GUI setup using ImGUI (In progress)
- [ ] Vulkan setup (In progress)
- [ ] Building 2d renderer

## The Architecture

The Elements Project provides the framework to develop games.

The Playground Project is where I test rendering and apply the framework.

To create a game, create a new project. Use the layers to create different components of your game that handle things like the input, scene and interaction with game objects by using the provided framework. The messaging framework allows for communication between these layers.

The messaging framework also handles communication between different systems in the framework. (Might be replaced by some other sytem such as an event queue.)

## Inspiration

- TheCherno/Hazel: Hazel Engine
https://github.com/TheCherno/Hazel

- ScrappyCocco/ScrapEngine: A very simple real-time Vulkan 3D game engine
https://github.com/ScrappyCocco/ScrapEngine

- sdslabs/Rubeus: A cross platform 2D game engine written in C++ for beginners
https://github.com/sdslabs/Rubeus

- elnormous/ouzel: C++ game engine for Windows, macOS, Linux, iOS, tvOS, Android, and web browsers
https://github.com/elnormous/ouzel
