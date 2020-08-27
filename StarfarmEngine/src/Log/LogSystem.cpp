//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#include "LogSystem.hpp"

namespace star
{
        LogSystem::LogSystem() : System(ecs::SYSTEM_PRIORITY::LOWEST, 1)
        {
                spdlog::flush_on(spdlog::level::err);
        }

        void LogSystem::update(ecs::Interval deltaTime)
        {
                spdlog::details::registry::instance().flush_all();
        }

}    // namespace star
