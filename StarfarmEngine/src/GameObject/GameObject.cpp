//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#include "GameObject.hpp"
#include "../Component/MonoBehaviourComponent.hpp"

namespace star
{

        GameObject::GameObject(Scene &scene)
                : Entity(),
                //m_transform{*create_component<TransformComponent>()},
                m_scene{scene}
        {}

        template <class Behaviour, class ...ARGS>
        void GameObject::create_behaviour(ARGS ...args)
        {
                create_component<Behaviour, MonoBehaviour>(std::forward<ARGS>(args)...);
        }

        Scene &GameObject::get_scene()
        {
                return m_scene;
        }

}
