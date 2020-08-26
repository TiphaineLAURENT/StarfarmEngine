//
// Created by Tiphaine LAURENT on 13/08/2019.
//

#ifndef STARFARMENGINE_CircleCollider_HPP
#define STARFARMENGINE_CircleCollider_HPP

#include <memory>
#include <ostream>

#include <chipmunk/chipmunk.h>

#include "../Util/Vector.hpp"
#include "ColliderComponent.hpp"

namespace star
{
        class CircleCollider : public ColliderComponent
        {
                // ATTRIBUTES
            private:
                Angle m_radius;

            public:
                // METHODS
            public:    // CONSTRUCTORS
                explicit CircleCollider(Length radius);
                ~CircleCollider() override = default;
                CircleCollider(const CircleCollider &copy) = default;
                CircleCollider(CircleCollider &&) noexcept = default;

            public:    // OPERATORS
                CircleCollider &operator=(const CircleCollider &other) = default;
                CircleCollider &operator=(CircleCollider &&) noexcept = default;

            public:
                void setup() override;

                //    void set_offset(float x, float y);

                //    [[nodiscard]] const sf::FloatRect &get_bounds() const;
                //    [[nodiscard]] std::vector<sf::Vector2f> get_vertices() const override;

                //    [[nodiscard]] float distance_to(const sf::Vector2f &point) const override;
                //    [[nodiscard]] bool contains(const sf::Vector2f &point) const override;
                //    [[nodiscard]] bool intersects(const CircleCollider &other) const;

                //    void collide(const std::vector<CircleCollider *> &);

                // private:
                //    void update_angles();
        };

        std::ostream &operator<<(std::ostream &out, const CircleCollider &);

}    // namespace star

#endif    // STARFARMENGINE_CircleCollider_HPP
