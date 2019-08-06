//
// Created by Tiphaine LAURENT on 05/08/2019.
//

#ifndef STARFARM_SCENE_HPP
#define STARFARM_SCENE_HPP

# include <ostream>
# include <EntityManager.hpp>
# include <ComponentManager.hpp>
# include <MediumSystemManager.hpp>


namespace star
{

  class Scene
  {
// ATTRIBUTES
  private:
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
  private:
  };

  std::ostream &operator<<(std::ostream &out, const Scene &);

}

#endif //STARFARM_SCENE_HPP
