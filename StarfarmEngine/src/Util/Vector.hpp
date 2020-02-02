//
// Created by Tiphaine LAURENT on 13/08/2019.
//

#ifndef STARFARMENGINE_VECTOR_HPP
# define STARFARMENGINE_VECTOR_HPP

# include <cmath>

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
                Length magnitude{calculate_magnitude()};
                Angle direction{calculate_direction()};

                Vector(const Point<dimension> &tail_, const Point<dimension> &head)
                        : tail{tail_}, magnitude{distance_between(head, tail)}
                {}

                explicit Vector(const Point<dimension> &tail_)
                        : tail{tail_}
                {}

                Point<dimension> calculate_head() const
                {
                        return tail + magnitude;
                }

                Length calculate_magnitude() const;

                Angle calculate_direction() const;

                template <typename Trivial>
                Vector<dimension> operator*(const Trivial &trivial) const
                {
                        return {tail * trivial};
                }
        };

        static constexpr auto EarthGravity{9.807};
        static constexpr auto SpaceGravity{0.};

}

#endif //STARFARMENGINE_VECTOR_HPP
