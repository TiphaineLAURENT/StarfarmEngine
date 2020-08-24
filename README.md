# StarfarmEngine

A C++ game engine

## Builds

![C/C++ CI](https://github.com/TiphaineLAURENT/StarfarmEngine/workflows/C/C++%20CI/badge.svg?branch=chipmunk)

## Goal

The goal of this project is to create a powerful engine easy in the same veine as Unity.
Ultimately I want it to let programmers create full game in a pythonic way using just a few line of codes:

```cpp
auto game = star::Game{};

auto &window = game.createWindow();
auto &scene = game.createScene<star::DIMENSION::2D::PLATFORM>();
auto &player = scene.createObject<Player>();
scene.add_player(player);
scene.loadConfiguration("main_scene.cfg");

return game.run();
```

This code should be able to run a 2D side view platform style game using default input (keyboard: ZQSD / WASD), at default viewport (fullscreen).