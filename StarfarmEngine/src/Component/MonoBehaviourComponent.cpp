//
// Created by TipLa on 14/04/2019.
//

#include "MonoBehaviourComponent.hpp"
#include "../GameObject/GameObject.hpp"

namespace star
{
        MonoBehaviour::MonoBehaviour(GameObject &gameObject)
                : Component(), m_gameObject{ gameObject }, m_transform{ gameObject.m_transform }
        {}
}    // namespace star