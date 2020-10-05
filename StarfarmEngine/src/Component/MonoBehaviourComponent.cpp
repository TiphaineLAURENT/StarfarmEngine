//
// Created by TipLa on 14/04/2019.
//

#include "MonoBehaviourComponent.hpp"
#include "../GameObject/GameObject.hpp"

namespace star
{
        MonoBehaviour::MonoBehaviour(GameObject &gameObject)
                : Component(), m_gameObject{ gameObject }
        {}

        void MonoBehaviour::awake()
        {
                ::ecs::replace_pointer(m_transform,
                                       m_gameObject.get().get_component<TransformComponent>());
        }
}    // namespace star