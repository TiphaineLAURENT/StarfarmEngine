//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#include "TransformComponent.hpp"
#include "IEntity.hpp"
#include "RigidbodyComponent.hpp"

namespace star
{
        void TransformComponent::setup()
        {
                ::ecs::replace_pointer(m_rigidbodyComponent,
                                       get_owner()->get_component<RigidbodyComponent>());
        }

        void TransformComponent::move(const Vector<2> &offsets) { move(offsets.x, offsets.y); }

        void TransformComponent::move(Coordinate x, Coordinate y)
        {
                if (m_rigidbodyComponent)
                {
                        const auto position = m_rigidbodyComponent->get_position();
                        m_rigidbodyComponent->set_position({ position.x + x, position.y + y });
                }
        }
}    // namespace star
