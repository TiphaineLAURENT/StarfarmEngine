//
// Created by Tiphaine LAURENT on 05/08/2019.
//

#ifndef STARFARM_GAME_HPP
#define STARFARM_GAME_HPP

# include <ostream>
# include <list>
# include <map>

# include <SFML/System/Clock.hpp>

# include "Scene.hpp"
# include "Window.hpp"


namespace star
{

  class Game
  {
// ATTRIBUTES
  private:
          std::list<Scene> _scenes{};
          Scene *_activeScene = nullptr;

          std::map<std::string, Window> _windows{};

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

          Scene &createScene();
          void setActiveScene(Scene *scene);

          Window &createWindow(
                  const sf::VideoMode &mode,
                  const std::string &name = "StarfarmEngine",
                  unsigned style = sf::Style::Default
          );

  private:
  };

  std::ostream &operator<<(std::ostream &out, const Game &);

}

#endif //STARFARM_GAME_HPP
