//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#include "GameObject.hpp"
#include "../Component/MonoBehaviourComponent.hpp"

namespace star
{

        GameObject::GameObject()
                : Entity(),
                _transform{create_component<TransformComponent>()}
        {}

        template <class Behaviour, class ...ARGS>
        void GameObject::create_behaviour(ARGS ...args)
        {
                create_component<Behaviour, MonoBehaviour>(std::forward<ARGS>(args)...);
        }

}
