//
// Created by Tiphaine LAURENT on 13/08/2019.
//

#ifndef STARFARMENGINE_SegmentCollider_HPP
#define STARFARMENGINE_SegmentCollider_HPP

#include <memory>
#include <ostream>

#include <chipmunk/chipmunk.h>

#include "../Util/Vector.hpp"
#include "ColliderComponent.hpp"

namespace star
{
        class SegmentCollider : public ColliderComponent
        {
                // ATTRIBUTES
            private:
                Vector<2> m_endpoint_1;
                Vector<2> m_endpoint_2;
                Angle m_radius;

            public:
                // METHODS
            public:    // CONSTRUCTORS
                explicit SegmentCollider(Vector<2> corner1, Vector<2> corner2, Angle radius);
                ~SegmentCollider() override = default;
                SegmentCollider(const SegmentCollider &copy) = default;
                SegmentCollider(SegmentCollider &&) noexcept = default;

            public:    // OPERATORS
                SegmentCollider &operator=(const SegmentCollider &other) = default;
                SegmentCollider &operator=(SegmentCollider &&) noexcept = default;

            public:
                void setup() override;

                //    void set_offset(float x, float y);

                //    [[nodiscard]] const sf::FloatRect &get_bounds() const;
                //    [[nodiscard]] std::vector<sf::Vector2f> get_vertices() const override;

                //    [[nodiscard]] float distance_to(const sf::Vector2f &point) const override;
                //    [[nodiscard]] bool contains(const sf::Vector2f &point) const override;
                //    [[nodiscard]] bool intersects(const SegmentCollider &other) const;

                //    void collide(const std::vector<SegmentCollider *> &);

                // private:
                //    void update_angles();
        };

        std::ostream &operator<<(std::ostream &out, const SegmentCollider &);

}    // namespace star

#endif    // STARFARMENGINE_SegmentCollider_HPP
