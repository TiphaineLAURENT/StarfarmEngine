//
// Created by tiphaine on 06/04/19.
//

#ifndef ECS_SYSTEM_HPP
# define ECS_SYSTEM_HPP

# include <ostream>
# include "ISystem.hpp"

namespace ecs
{
# define SYSTEM(system) system : public ecs::System<system>

  template <class S>
  class System : public ISystem
  {
// ATTRIBUTES
  private:
  public:
          static const SystemTypeID _systemTypeID;

// METHODS:
  public: // CONSTRUCTORS
          explicit System(
                  SYSTEM_PRIORITY priority = SYSTEM_PRIORITY::NORMAL,
                  long updateInterval = 10
          )
                  : ISystem(priority, updateInterval)
          {
          }
          ~System() override = default;
          System(const System &copy) = delete;
          System(System &&other) noexcept = delete;

  public: // OPERATORS
          System &operator=(const System &other) = delete;
          System &operator=(System &&other) = delete;

  public:
          [[nodiscard]] SystemTypeID getSystemTypeID() const override
          {
                  return _systemTypeID;
          }
          [[nodiscard]] const char *getSystemTypeName() const override
          {
                  static const char *systemTypeName{typeid(S).name()};

                  return systemTypeName;
          }

          [[deprecated]] void preUpdate(float deltaTime) override
          {
          }
          void update(long deltaTime) override
          {
          }
          [[deprecated]] void postUpdate(float deltaTime) override
          {
          }

          /*
          template <class ...Dependencies>
          void addDependencies(Dependencies &&... dependencies)
          {
                  SystemManager::addSystemDependency(
                          this,
                          std::forward<Dependencies>(dependencies)...
                  );
          }
          */
  };

  template <class S>
  std::ostream &operator<<(std::ostream &out, const System<S> &);

  template <class S>
  const SystemTypeID System<S>::_systemTypeID =
          util::FamilyTypeID<ISystem>::getTypeID<S>();

}

#endif //ECS_SYSTEM_HPP
