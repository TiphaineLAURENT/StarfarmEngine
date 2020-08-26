//
// Created by Tiphaine LAURENT on 13/08/2019.
//

#include <cassert>

#include "../Core/Scene.hpp"
#include "../GameObject/GameObject.hpp"
#include "../Util/Vector.hpp"
#include "SegmentCollider.hpp"
#include "TransformComponent.hpp"

namespace star
{
        SegmentCollider::SegmentCollider(Vector<2> corner1, Vector<2> corner2, Angle radius)
                : m_corner1{ corner1 }, m_corner2{ corner2 }, m_radius{ radius }
        {}

        void SegmentCollider::setup()
        {
                auto body = get_owner()->get_component<RigidbodyComponent>();
                assert(("A entity cannot have a rigidbogy without having a "
                        "transform",
                        body != nullptr));

                auto &scene =
                        static_cast<ecs::NonOwningPointer<GameObject>>(get_owner())->get_scene();
                m_shape.reset(
                        cpSegmentShapeNew(body->m_body.get(), m_corner1, m_corner2, m_radius));
                cpSpaceAddShape(&scene.get_world(), m_shape.get());
        }

        // float SegmentCollider::distance_to(const sf::Vector2f &point) const
        //{
        //        auto distances = std::array<float, 4>{};
        //        distances[0] =
        //                distance_between(_angles[0] + _transformComponent->getPosition(), point);
        //        distances[1] = distance(_angles[1] + _transformComponent->getPosition(), point);
        //        distances[2] = distance(_angles[2] + _transformComponent->getPosition(), point);
        //        distances[3] = distance(_angles[3] + _transformComponent->getPosition(), point);

        //        auto it = std::min_element(
        //                distances.begin(), distances.end(), [](float distance1, float distance2) {
        //                        return distance1 < distance2;
        //                });
        //        return *it;
        //}

        // bool SegmentCollider::contains(const sf::Vector2f &point) const
        //{
        //        return _bounds.contains(point);
        //}

        // bool SegmentCollider::intersects(const SegmentCollider &other) const
        //{
        //        return _bounds.intersects(other._bounds);
        //}

        // const sf::FloatRect &SegmentCollider::get_bounds() const { return _bounds; }

        // std::vector<sf::Vector2f> SegmentCollider::get_vertices() const
        //{
        //        return { _angles.begin(), _angles.end() };
        //}

        // void SegmentCollider::set_offset(float x, float y)
        //{
        //        _offset = { x, y };
        //        auto position = _transformComponent->getPosition();
        //        _bounds.left = position.x + x;
        //        _bounds.top = position.y + y;
        //        update_angles();
        //}

        // void SegmentCollider::update_angles()
        //{
        //        _angles[0] = { _bounds.left, _bounds.top };
        //        _angles[1] = { _bounds.left + _bounds.width, _bounds.top };
        //        _angles[2] = { _bounds.left + _bounds.width, _bounds.top + _bounds.height };
        //        _angles[3] = { _bounds.left, _bounds.top + _bounds.height };
        //}

        // void SegmentCollider::collide(const std::vector<SegmentCollider *> &colliders)
        //{
        //        for (auto &collider : colliders)
        //        {
        //                if (collider->intersects(*this))
        //                {
        //                        // Trigger something
        //                }
        //        }
        //}

}    // namespace star
