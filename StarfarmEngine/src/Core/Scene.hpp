//
// Created by Tiphaine LAURENT on 05/08/2019.
//

#ifndef STARFARM_SCENE_HPP
#define STARFARM_SCENE_HPP

#include <map>
#include <memory>
#include <ostream>

#include <chipmunk/chipmunk_structs.h>

#include <ComponentManager.hpp>
#include <EntityManager.hpp>
#include <MediumSystemManager.hpp>

#include "../Util/Vector.hpp"

namespace star
{
        class RigidbodyComponent;

        class Scene
        {
                // ATTRIBUTES
            private:
                friend RigidbodyComponent;

                ecs::EntityManager m_entities{};
                ecs::ComponentManager m_components{};
                ecs::MediumSystemManager m_systems{};
                std::unique_ptr<cpSpace> m_world{ cpSpaceNew() };

            public:
                // METHODS
            public:   // CONSTRUCTORS
                Scene(const Vector<2> &gravity);
                Scene() = default;
                ~Scene() = default;
                Scene(const Scene &copy) = delete;
                Scene(Scene &&) = delete;

            public:   // OPERATORS
                Scene &operator=(const Scene &other) = delete;
                Scene &operator=(Scene &&) = delete;

            public:
                void update(::ecs::Interval deltaTime);
                void refresh();

                template <class E, class... ARGS>
                E &create_entity(ARGS &&... args)
                {
                        return m_entities.create<E>(*this,
                                                    std::forward<ARGS>(args)...);
                }

                template <class S, class... ARGS>
                S &create_system(ARGS &&... args)
                {
                        return m_systems.create_system<S>(
                                std::forward<ARGS>(args)...);
                }

                cpSpace &get_world();

            private:
        };

        std::ostream &operator<<(std::ostream &out, const Scene &);

}   // namespace star

#endif   // STARFARM_SCENE_HPP
