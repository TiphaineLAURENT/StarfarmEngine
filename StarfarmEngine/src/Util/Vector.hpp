//
// Created by Tiphaine LAURENT on 13/08/2019.
//

#ifndef STARFARMENGINE_VECTOR_HPP
# define STARFARMENGINE_VECTOR_HPP

# include <cmath>
# include <box2d/b2_math.h>

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

        /*template <Dimension dimension>
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
        };*/

        template <Dimension dimension>
        struct Vector
        {
                Vector<dimension> &operator+=(const Vector<dimension> &other);
                Vector<dimension> &operator-=(const Vector<dimension> &other);
                Vector<dimension> &operator*=(const Coordinate &other);

                Vector<dimension> operator+(const Vector<dimension> &other)
                {
                        Vector<dimension> vec{this};
                        vec += other;
                        return vec;
                }

                Vector<dimension> operator-(const Vector<dimension> &other)
                {
                        Vector<dimension> vec{this};
                        vec -= other;
                        return vec;
                }
        };

        template <>
        struct Vector<2> : private b2Vec2
        {
                using b2Vec2::x;
                using b2Vec2::y;

                Vector(const Point<2> &tail)
                        : b2Vec2(tail.x, tail.y)
                {}

                Vector(const Coordinate &x, const Coordinate &y)
                        : b2Vec2(x, y)
                {}

                Vector<2> &operator+=(const Vector<2> &other)
                {
                        b2Vec2::operator+=(other);
                        return *this;
                }

                Vector<2> &operator-=(const Vector<2> &other)
                {
                        b2Vec2::operator-=(other);
                        return *this;
                }

                Vector<2> &operator*=(const Coordinate &other)
                {
                        b2Vec2::operator*=(other);
                        return *this;
                }

                star::Length calculate_magnitude() const
                {
                        return std::sqrt(LengthSquared());
                }

                star::Length normalize()
                {
                        return Normalize();
                }
        };

        template <>
        struct Vector<3> : private b2Vec3
        {
                using b2Vec3::x;
                using b2Vec3::y;
                using b2Vec3::z;

                Vector(const Point<3> &tail)
                        : b2Vec3(tail.x, tail.y, tail.z)
                {}

                Vector(const Coordinate &x, const Coordinate &y, const Coordinate &z)
                        : b2Vec3(x, y, z)
                {}

                Vector<3> &operator+=(const Vector<3> &other)
                {
                        b2Vec3::operator+=(other);
                        return *this;
                }

                Vector<3> &operator-=(const Vector<3> &other)
                {
                        b2Vec3::operator-=(other);
                        return *this;
                }

                Vector<3> &operator*=(const Coordinate &other)
                {
                        b2Vec3::operator*=(other);
                        return *this;
                }

        };


        static constexpr auto EarthGravity{9.807};
        static constexpr auto SpaceGravity{0.};

}

#endif //STARFARMENGINE_VECTOR_HPP
