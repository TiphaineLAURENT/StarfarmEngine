//
// Created by Tiphaine LAURENT on 05/08/2019.
//

#ifndef STARFARM_GAME_HPP
#define STARFARM_GAME_HPP

# include <ostream>
# include <list>
# include <unordered_map>

# include <SFML/System/Clock.hpp>

# include "Scene.hpp"
# include "Window.hpp"
# include "../Event/Signal.hpp"


namespace star
{

  class Game
  {
// ATTRIBUTES
  private:
          std::list<Scene> _scenes{};
          Scene *_activeScene = nullptr;

          std::unordered_map<std::string, Window> _windows{};

          sf::Clock _clock{};

  public:

// METHODS
  public:// CONSTRUCTORS
          Game() = default;
          ~Game() = default;
          Game(const Game &copy) = delete;
          Game(Game &&) = delete;

  public: //OPERATORS
          Game &operator=(const Game &other) = delete;
          Game &operator=(Game &&) = delete;

  public:
          bool run();
          void quit();

          Scene &createScene();
          void setActiveScene(Scene *scene);

          Window &createWindow(
                  const sf::VideoMode &mode,
                  const std::string &name = "StarfarmEngine",
                  sf::Uint32 style = sf::Style::Default
          );

  private:
          bool _running = true;

          SLOT(WindowEventHandler, OnKeyPressed, _onKeyPressed);
  };

  std::ostream &operator<<(std::ostream &out, const Game &);

}

#endif //STARFARM_GAME_HPP
