//
// Created by Tiphaine LAURENT on 13/08/2019.
//

#include <chipmunk/chipmunk.h>

#include "ColliderComponent.hpp"

namespace star
{
        void ColliderComponent::setup()
        {
                ecs::replace_pointer(m_rigidbodyComponent,
                                     get_owner()->get_component<RigidbodyComponent>());
                ecs::replace_pointer(m_transformComponent,
                                     get_owner()->get_component<TransformComponent>());
        }

        ColliderComponent &ColliderComponent::set_friction(Force friction)
        {
                cpShapeSetFriction(m_shape.get(), friction);

                return *this;
        }
        cpBB ColliderComponent::get_bb() const { return cpShapeGetBB(m_shape.get()); }
}    // namespace star
