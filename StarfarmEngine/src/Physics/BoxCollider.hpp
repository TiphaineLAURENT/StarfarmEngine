//
// Created by Tiphaine LAURENT on 13/08/2019.
//

#ifndef STARFARMENGINE_BOXCOLLIDER_HPP
#define STARFARMENGINE_BOXCOLLIDER_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <ostream>

#include "ColliderComponent.hpp"

namespace star
{
        class BoxCollider : public ColliderComponent
        {
                // ATTRIBUTES
            private:
                Length m_width{ 0 };
                Length m_height{ 0 };

                Angle m_radius{ 0 };

            public:
                // METHODS
            public:    // CONSTRUCTORS
                explicit BoxCollider(Length width, Length height, Length radius);
                ~BoxCollider() override = default;
                BoxCollider(const BoxCollider &copy) = default;
                BoxCollider(BoxCollider &&) noexcept = default;

            public:    // OPERATORS
                BoxCollider &operator=(const BoxCollider &other) = default;
                BoxCollider &operator=(BoxCollider &&) noexcept = default;

            public:
                void setup() override;

        private:
        };

        std::ostream &operator<<(std::ostream &out, const BoxCollider &);

}    // namespace star

#endif    // STARFARMENGINE_BOXCOLLIDER_HPP
