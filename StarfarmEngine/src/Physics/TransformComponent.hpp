//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#ifndef STARFARMENGINE_TRANSFORMCOMPONENT_HPP
#define STARFARMENGINE_TRANSFORMCOMPONENT_HPP

#include <ostream>

#include "../Util/Vector.hpp"
#include <Component.hpp>

namespace star
{
        class COMPONENT(TransformComponent)
        {
                // ATTRIBUTES
            private:
                Coordinate m_x{ 0 };
                Coordinate m_y{ 0 };

                Angle m_rotation{ 0 };

            public:
                // METHODS
            public:    // CONSTRUCTORS
                TransformComponent() = default;
                TransformComponent(const TransformComponent &copy) = default;
                TransformComponent(TransformComponent &&) noexcept = default;

            public:    // OPERATORS
                TransformComponent &operator=(const TransformComponent &other) = default;
                TransformComponent &operator=(TransformComponent &&) noexcept = default;

            public:
                virtual Vector<2> get_position() const;
                virtual void set_position(const Vector<2> & coordinates);
                virtual void set_position(Coordinate x, Coordinate y);

                virtual void move(const Vector<2> &offsets);
                virtual void move(Coordinate x, Coordinate y);

                virtual Angle get_rotation() const;
                virtual void set_rotation(Angle rotation);
                virtual void rotate(Angle rotation);

            private:
        };

        std::ostream &operator<<(std::ostream &out, const TransformComponent &);

}    // namespace star

#endif    // STARFARMENGINE_TRANSFORMCOMPONENT_HPP
