//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#include "GameObject.hpp"

namespace star
{

  star::GameObject::GameObject()
  {
        _transform = addComponent<TransformComponent>();
  }

}
