//
// Created by TipLa on 14/04/2019.
//

#ifndef ECS_MONOBEHAVIOURCOMPONENT_HPP
#define ECS_MONOBEHAVIOURCOMPONENT_HPP

#include <Component.hpp>
#include <ostream>

#include "Component.hpp"

namespace star
{
        class GameObject;

        class TransformComponent;

        class COMPONENT(MonoBehaviour)
        {
                // ATTRIBUTES
            protected:
                ::std::reference_wrapper<GameObject> m_gameObject;

                ::ecs::NonOwningPointer<TransformComponent> m_transform{ nullptr };

            public:
                // METHODS:
            public:    // CONSTRUCTORS
                explicit MonoBehaviour(GameObject &gameObject);
                ~MonoBehaviour() override = default;
                MonoBehaviour(const MonoBehaviour &copy) = default;
                MonoBehaviour(MonoBehaviour &&other) noexcept = default;

            public:    // OPERATORS
                MonoBehaviour &operator=(const MonoBehaviour &other) = delete;
                MonoBehaviour &operator=(MonoBehaviour &&other) = delete;

            public:
                virtual void awake();
                virtual void start(){};
                virtual void update(){};
                virtual void fixed_update(){};
                virtual void late_update(){};
        };

        std::ostream &operator<<(std::ostream &out, const MonoBehaviour &);

}    // namespace star

#endif    // ECS_MONOBEHAVIOURCOMPONENT_HPP