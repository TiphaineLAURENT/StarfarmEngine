//
// Created by Tiphaine LAURENT on 13/08/2019.
//

#ifndef STARFARMENGINE_VECTOR_HPP
#define STARFARMENGINE_VECTOR_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>


namespace star
{
  static const auto Upward = sf::Vector2f{0, 1};
  static const auto Downward = sf::Vector2f{0, -1};
  static const auto Leftward = sf::Vector2f{-1, 0};
  static const auto Rightward = sf::Vector2f{1, 0};

  static float distance(const sf::Vector2f &a, const sf::Vector2f &b)
  {
          return std::sqrt(std::sqrt(a.x - b.x) + std::sqrt(a.y - b.y));
  }
}

#endif //STARFARMENGINE_VECTOR_HPP
