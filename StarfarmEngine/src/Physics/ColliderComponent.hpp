//
// Created by Tiphaine LAURENT on 09/08/2019.
//

#ifndef STARFARMENGINE_COLLIDERCOMPONENT_HPP
#define STARFARMENGINE_COLLIDERCOMPONENT_HPP

#include <memory>
#include <ostream>

#include <Component.hpp>
#include <IEntity.hpp>

#include "RigidbodyComponent.hpp"
#include "TransformComponent.hpp"

namespace star
{
        class COMPONENT(ColliderComponent)
        {
                // ATTRIBUTES
            private:
                // float _bounciness{0.};

                // float _density{0.};

                // float _friction{0.};

                // bool _isTrigger{false};

            protected:
                ecs::NonOwningPointer<RigidbodyComponent> m_rigidbodyComponent{ nullptr };

                ecs::NonOwningPointer<TransformComponent> m_transformComponent{ nullptr };

                std::unique_ptr<cpShape> m_shape{ nullptr };

            public:
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

                //[[nodiscard]] virtual std::vector<sf::Vector2f> get_vertices() const = 0;

                //[[nodiscard]] virtual float distance_to(const sf::Vector2f &point)
                // const = 0;
                //[[nodiscard]] virtual bool contains(const sf::Vector2f &point)
                // const = 0;

            private:
        };

        std::ostream &operator<<(std::ostream &out, const ColliderComponent &);

}    // namespace star

#endif    // STARFARMENGINE_COLLIDERCOMPONENT_HPP
