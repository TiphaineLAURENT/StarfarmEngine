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

        class Scene;

  class ENTITY(GameObject)
  {
          friend class MonoBehaviour;
// ATTRIBUTES
  private:
          ecs::NonOwningPointer<TransformComponent> _transform{nullptr};
          Scene &_scene;

  public:

// METHODS
  public:// CONSTRUCTORS
          GameObject(Scene &scene);
          ~GameObject() override = default;
          GameObject(const GameObject &copy) = default;
          GameObject(GameObject &&) noexcept = default;

  public: //OPERATORS
          GameObject &operator=(const GameObject &other) = default;
          GameObject &operator=(GameObject &&) noexcept = default;

  public:
          template <class Behaviour, class ...ARGS>
          void create_behaviour(ARGS ...args);

          template <class C, class Container = C, class ...ARGS>
          ecs::NonOwningPointer<C> create_component(ARGS &&... args)
          {
                  return ecs::ComponentManager::create_component<C, Container>(
                          this, _scene,
                          std::forward<ARGS>(args)...
                          );
          }

  private:
  };

  ::std::ostream &operator<<(::std::ostream &out, const GameObject &);

}

#endif //STARFARMENGINE_GAMEOBJECT_HPP
