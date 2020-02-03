//
// Created by Tiphaine LAURENT on 21/08/2019.
//

#ifndef STARFARMENGINE_PHYSICSYSTEM_HPP
#define STARFARMENGINE_PHYSICSYSTEM_HPP

# include <ostream>
# include <System.hpp>

# include <box2d/b2_world.h>


namespace star
{

        class SYSTEM(PhysicSystem)
        {
                // ATTRIBUTES
        public:
                b2World &_world;
                static constexpr auto TIME_STEP = 1. / 60.;
                static constexpr auto VELOCITY_ITERATIONS = 8;
                static constexpr auto POSITION_ITERATIONS = 3;

        private:

                // METHODS
        public:// CONSTRUCTORS
                explicit PhysicSystem(b2World &world);
                ~PhysicSystem() override = default;
                PhysicSystem(const PhysicSystem &copy) = delete;
                PhysicSystem(PhysicSystem &&) noexcept = delete;

        public: //OPERATORS
                PhysicSystem &operator=(const PhysicSystem & other) = delete;
                PhysicSystem &operator=(PhysicSystem &&) noexcept = delete;

        public:
                void update(::ecs::Interval deltaTime) override;
        };

        std::ostream &operator<<(std::ostream &out, const PhysicSystem &);

}

#endif //STARFARMENGINE_PHYSICSYSTEM_HPP
