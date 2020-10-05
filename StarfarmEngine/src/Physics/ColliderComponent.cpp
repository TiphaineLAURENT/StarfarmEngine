//
// Created by Tiphaine LAURENT on 13/08/2019.
//

#include <stdexcept>

#include <chipmunk/chipmunk.h>

#include "ColliderComponent.hpp"

namespace star
{
        void ColliderComponent::setup()
        {
                ecs::replace_pointer(m_rigidbodyComponent,
                                     static_cast<RigidbodyComponent*>(get_owner()->get_component<TransformComponent>()));
                if (m_rigidbodyComponent == nullptr)
                        throw std::invalid_argument(
                                "A entity cannot have a collider without having a "
                                "rigidbody");
        }

        ColliderComponent &ColliderComponent::set_friction(Force friction)
        {
                cpShapeSetFriction(m_shape.get(), friction);

                return *this;
        }
        cpBB ColliderComponent::get_bb() const { return cpShapeGetBB(m_shape.get()); }

        ColliderComponent &ColliderComponent::set_elasticity(Force elasticity)
        {
                cpShapeSetElasticity(m_shape.get(), elasticity);
                return *this;
        }
}    // namespace star
