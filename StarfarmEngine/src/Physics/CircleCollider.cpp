//
// Created by Tiphaine LAURENT on 13/08/2019.
//

#include "CircleCollider.hpp"
#include "../Core/Scene.hpp"
#include "../GameObject/GameObject.hpp"
#include "TransformComponent.hpp"

namespace star
{
        CircleCollider::CircleCollider(Length radius) : m_radius{ radius } {}

        void CircleCollider::setup()
        {
                ColliderComponent::setup();

                auto &scene =
                        static_cast<ecs::NonOwningPointer<GameObject>>(get_owner())->get_scene();
                m_shape.reset(cpCircleShapeNew(
                        m_rigidbodyComponent->m_body.get(), m_radius, cpvzero));
                cpSpaceAddShape(&scene.get_world(), m_shape.get());
        }

        // float CircleCollider::distance_to(const sf::Vector2f &point) const
        //{
        //        auto distances = std::array<float, 4>{};
        //        distances[0] =
        //                distance_between(_angles[0] + m_transformComponent->getPosition(), point);
        //        distances[1] = distance(_angles[1] + m_transformComponent->getPosition(), point);
        //        distances[2] = distance(_angles[2] + m_transformComponent->getPosition(), point);
        //        distances[3] = distance(_angles[3] + m_transformComponent->getPosition(), point);

        //        auto it = std::min_element(
        //                distances.begin(), distances.end(), [](float distance1, float distance2) {
        //                        return distance1 < distance2;
        //                });
        //        return *it;
        //}

        // bool CircleCollider::contains(const sf::Vector2f &point) const
        //{
        //        return _bounds.contains(point);
        //}

        // bool CircleCollider::intersects(const CircleCollider &other) const
        //{
        //        return _bounds.intersects(other._bounds);
        //}

        // const sf::FloatRect &CircleCollider::get_bounds() const { return _bounds; }

        // std::vector<sf::Vector2f> CircleCollider::get_vertices() const
        //{
        //        return { _angles.begin(), _angles.end() };
        //}

        // void CircleCollider::set_offset(float x, float y)
        //{
        //        _offset = { x, y };
        //        auto position = m_transformComponent->getPosition();
        //        _bounds.left = position.x + x;
        //        _bounds.top = position.y + y;
        //        update_angles();
        //}

        // void CircleCollider::update_angles()
        //{
        //        _angles[0] = { _bounds.left, _bounds.top };
        //        _angles[1] = { _bounds.left + _bounds.width, _bounds.top };
        //        _angles[2] = { _bounds.left + _bounds.width, _bounds.top + _bounds.height };
        //        _angles[3] = { _bounds.left, _bounds.top + _bounds.height };
        //}

        // void CircleCollider::collide(const std::vector<CircleCollider *> &colliders)
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
