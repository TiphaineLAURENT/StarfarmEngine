//
// Created by Tiphaine LAURENT on 05/08/2019.
//

#ifndef STARFARM_SCENE_HPP
#define STARFARM_SCENE_HPP

# include <ostream>
# include <map>

# include <EntityManager.hpp>
# include <ComponentManager.hpp>
# include <MediumSystemManager.hpp>

namespace star
{

        class RigidbodyComponent;
        class Fixture;
        class ContactManager;
        class Controller;

  class Scene
  {
// ATTRIBUTES
  private:
          friend RigidbodyComponent;
          friend Fixture;
          friend ContactManager;
          friend Controller;

          ecs::EntityManager _entities{};
          ecs::ComponentManager _components{};
          ecs::MediumSystemManager _systems{};

  public:

// METHODS
  public:// CONSTRUCTORS
          Scene() = default;
          ~Scene() = default;
          Scene(const Scene &copy) = delete;
          Scene(Scene &&) = delete;

  public: //OPERATORS
          Scene &operator=(const Scene &other) = delete;
          Scene &operator=(Scene &&) = delete;

  public:
          void update(::ecs::Interval deltaTime);
          void refresh();

          template <class E, class ...ARGS>
          E &create_entity(ARGS &&... args)
          {
                  return _entities.create<E>(*this, std::forward<ARGS>(args)...);
          }

          template <class S, class ...ARGS>
          S &create_system(ARGS &&... args)
          {
                  return _systems.create_system<S>(std::forward<ARGS>(args)...);
          }

  private:
  };

  std::ostream &operator<<(std::ostream &out, const Scene &);

}

#endif //STARFARM_SCENE_HPP
