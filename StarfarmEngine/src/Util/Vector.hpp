//
// Created by Tiphaine LAURENT on 13/08/2019.
//

#ifndef STARFARMENGINE_VECTOR_HPP
# define STARFARMENGINE_VECTOR_HPP

# include <cmath>
# include <SFML/System/Vector2.hpp>

# include "Point.hpp"

namespace star
{

        using Length = float;
        using Angle = float;
        using Force = float;
        using Weight = float;
        using Speed = float;

        template <Dimension dimension>
        Length distance_between(const Point<dimension> &a, const Point<dimension> &b)
        {
                return std::sqrt(std::sqrt(a.x - b.x) + std::sqrt(a.y - b.y));
        }

        template <Dimension dimension>
        Angle angle_between(const Point<dimension> &a, const Point<dimension> &b)
        {
                return std::atan2(b.x - a.x, b.y - a.y);
        }

        template <Dimension dimension>
        struct Vector
        {
                Point<dimension> tail{};
                Length magnitude{};
                Angle direction{};

                Vector(const Point<dimension> &tail_, const Point<dimension> &head,
                       Angle direction_ = 0.)
                        : tail{tail_}, magnitude{distance_between(head, tail)},
                        direction(direction_)
                {}

                Point<dimension> calculate_head()
                {
                        return tail + magnitude;
                }
        };

        static constexpr auto EarthGravity{9.807};
        static constexpr float SpaceGravity{0.};

}

#endif //STARFARMENGINE_VECTOR_HPP
