//
// Created by Tiphaine LAURENT on 05/08/2019.
//

#include "Game.hpp"

namespace star
{

  bool Game::run()
  {
          if (!_running) {
                  return false;
          }

          if (!_activeScene)
                  return false;

          auto deltaTime = _clock.restart().asMicroseconds();

          for (
                  auto &[key, window] : _windows
                  ) {
                  window.processEvents();
          }

          _activeScene->update(deltaTime);
          return true;
  }
  void Game::setActiveScene(Scene *scene)
  {
        _activeScene = scene;
  }

  Scene &Game::createScene()
  {
          _scenes.emplace_back();
          return _scenes.back();
  }

  Window &Game::createWindow(
          const sf::VideoMode &mode,
          const std::string &name,
          sf::Uint32 style
  )
  {
          _windows.try_emplace(
                  name, mode, name, style
          );
          auto &window = _windows[name];

          _onKeyPressed.connect(
                  window._eventHandler.OnKeyPressed,
                  [=](const sf::Event &event) {
                          if (event.key.code == sf::Keyboard::Escape) {
                                  quit();
                          }
                  }
          );

          return window;
  }

  void Game::quit()
  {
          _running = false;
  }

}
