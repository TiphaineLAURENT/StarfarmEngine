//
// Created by Tiphaine LAURENT on 05/08/2019.
//

#ifndef STARFARM_GAME_HPP
#define STARFARM_GAME_HPP

# include <ostream>
# include <list>

# include "Scene.hpp"

namespace star
{

  class Game
  {
// ATTRIBUTES
  private:
          std::list<Scene> _scenes;

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
  private:
  };

  std::ostream &operator<<(std::ostream &out, const Game &);

}

#endif //STARFARM_GAME_HPP
