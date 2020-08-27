//
// Created by Tiphaine LAURENT on 13/08/2019.
//

#include <stdexcept>

#include "../Core/Scene.hpp"
#include "../GameObject/GameObject.hpp"
#include "BoxCollider.hpp"
#include "RigidbodyComponent.hpp"

namespace star
{
        BoxCollider::BoxCollider(Length width, Length height, Length radius)
                : ColliderComponent(), m_width{ width }, m_height{ height }, m_radius{ radius }
        {}

        void BoxCollider::setup()
        {
                auto body = get_owner()->get_component<RigidbodyComponent>();
                if (body == nullptr)
                        throw std::invalid_argument(
                                "A entity cannot have a collider without having a "
                                "rigidbody");

                auto &scene =
                        static_cast<ecs::NonOwningPointer<GameObject>>(get_owner())->get_scene();
                m_shape.reset(cpBoxShapeNew(body->m_body.get(), m_width, m_height, m_radius));
                cpSpaceAddShape(&scene.get_world(), m_shape.get());
        }

}    // namespace star
