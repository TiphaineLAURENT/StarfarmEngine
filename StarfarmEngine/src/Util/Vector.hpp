//
// Created by Tiphaine LAURENT on 13/08/2019.
//

#ifndef STARFARMENGINE_VECTOR_HPP
#define STARFARMENGINE_VECTOR_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>


namespace star
{

        using Vector2f = sf::Vector2f;

        static const sf::Vector2f Upward{0, 1};
        static const sf::Vector2f Downward{0, -1};
        static const sf::Vector2f Leftward{-1, 0};
        static const sf::Vector2f Rightward{1, 0};

        static constexpr auto EarthGravity{9.807};
        static constexpr float SpaceGravity{0.};

        static float distance(const sf::Vector2f &a, const sf::Vector2f &b)
        {
                return std::sqrt(std::sqrt(a.x - b.x) + std::sqrt(a.y - b.y));
        }
}

#endif //STARFARMENGINE_VECTOR_HPP
