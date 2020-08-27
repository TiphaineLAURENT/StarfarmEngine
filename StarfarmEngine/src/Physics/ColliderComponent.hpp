//
// Created by Tiphaine LAURENT on 09/08/2019.
//

#ifndef STARFARMENGINE_COLLIDERCOMPONENT_HPP
#define STARFARMENGINE_COLLIDERCOMPONENT_HPP

#include <memory>
#include <ostream>

#include <Component.hpp>
#include <IEntity.hpp>

#include "../Event/Signal.hpp"
#include "RigidbodyComponent.hpp"
#include "TransformComponent.hpp"

namespace star
{
        class COMPONENT(ColliderComponent)
        {
                // ATTRIBUTES
            private:
            protected:
                ecs::NonOwningPointer<RigidbodyComponent> m_rigidbodyComponent{ nullptr };

                ecs::NonOwningPointer<TransformComponent> m_transformComponent{ nullptr };

            public:
                std::unique_ptr<cpShape> m_shape{ nullptr };
                // METHODS
            public:    // CONSTRUCTORS
                explicit ColliderComponent() = default;
                ~ColliderComponent() override = default;
                ColliderComponent(const ColliderComponent &copy) = default;
                ColliderComponent(ColliderComponent &&) noexcept = default;

            public:    // OPERATORS
                ColliderComponent &operator=(const ColliderComponent &other) = default;
                ColliderComponent &operator=(ColliderComponent &&) noexcept = default;

            public:
                void setup() override;

                ColliderComponent &set_friction(Force friction);
                cpBB get_bb() const;

                SIGNAL(OnPostCollision, cpSpace*, void*, void*);

            private:
        };

        std::ostream &operator<<(std::ostream &out, const ColliderComponent &);

}    // namespace star

#endif    // STARFARMENGINE_COLLIDERCOMPONENT_HPP
