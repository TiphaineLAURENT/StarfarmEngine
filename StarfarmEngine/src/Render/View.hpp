//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#ifndef STARFARMENGINE_VIEW_HPP
#define STARFARMENGINE_VIEW_HPP

# include <ostream>

# include <SFML/Graphics/View.hpp>

namespace star
{

  class View : sf::View
  {
// ATTRIBUTES
  private:
  public:

// METHODS
  public:// CONSTRUCTORS
          View() = default;
          ~View() = default;
          View(const View &copy) = default;
          View(View &&) noexcept = default;

  public: //OPERATORS
          View &operator=(const View &other) = default;
          View &operator=(View &&) noexcept = default;

  public:
  private:
  };

  std::ostream &operator<<(std::ostream &out, const View &);

}

#endif //STARFARMENGINE_VIEW_HPP
