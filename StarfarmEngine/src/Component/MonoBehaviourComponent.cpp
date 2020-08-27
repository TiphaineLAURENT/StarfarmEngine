//
// Created by TipLa on 14/04/2019.
//

#include "MonoBehaviourComponent.hpp"
#include "../GameObject/GameObject.hpp"

namespace star
{
        MonoBehaviour::MonoBehaviour(ecs::NonOwningPointer<GameObject> gameObject)
                : Component(), _gameObject{gameObject},
                m_transform{gameObject->m_transform}
        {}
}