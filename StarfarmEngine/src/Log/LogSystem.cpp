//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#include "LogSystem.hpp"

namespace star
{
        LogSystem::LogSystem() : System(ecs::SYSTEM_PRIORITY::LOWEST, 1) {}

        void LogSystem::update(ecs::Interval deltaTime)
        {
                for (auto &str : _buffer)
                {
                        std::puts(str.data());
                }
                _buffer.clear();
        }

}    // namespace star
