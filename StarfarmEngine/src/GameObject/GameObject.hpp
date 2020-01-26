//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#ifndef STARFARMENGINE_GAMEOBJECT_HPP
#define STARFARMENGINE_GAMEOBJECT_HPP

# include <ostream>

# include <Entity.hpp>

# include "../Physics/TransformComponent.hpp"


namespace star
{

  class ENTITY(GameObject)
  {
          friend class MonoBehaviour;
// ATTRIBUTES
  private:
          ecs::NonOwningPointer<TransformComponent> _transform{nullptr};

  public:

// METHODS
  public:// CONSTRUCTORS
          GameObject();
          ~GameObject() override = default;
          GameObject(const GameObject &copy) = default;
          GameObject(GameObject &&) noexcept = default;

  public: //OPERATORS
          GameObject &operator=(const GameObject &other) = default;
          GameObject &operator=(GameObject &&) noexcept = default;

  public:
          template <class Behaviour, class ...ARGS>
          void create_behaviour(ARGS ...args);

  private:
  };

  ::std::ostream &operator<<(::std::ostream &out, const GameObject &);

}

#endif //STARFARMENGINE_GAMEOBJECT_HPP
