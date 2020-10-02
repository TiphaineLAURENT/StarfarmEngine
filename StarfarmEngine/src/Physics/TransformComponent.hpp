//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#ifndef STARFARMENGINE_TRANSFORMCOMPONENT_HPP
#define STARFARMENGINE_TRANSFORMCOMPONENT_HPP

#include <ostream>

#include <Component.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include "../Util/Vector.hpp"

namespace star
{
        class RigidbodyComponent;

        class COMPONENT(TransformComponent), public sf::Transformable
        {
                // ATTRIBUTES
            private:
                ::ecs::NonOwningPointer<RigidbodyComponent> m_rigidbodyComponent{ nullptr };

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
                void setup() override;

                void move(const Vector<2>& offsets);
                void move(Coordinate x, Coordinate y);

            private:
        };

        std::ostream &operator<<(std::ostream &out, const TransformComponent &);

}    // namespace star

#endif    // STARFARMENGINE_TRANSFORMCOMPONENT_HPP
