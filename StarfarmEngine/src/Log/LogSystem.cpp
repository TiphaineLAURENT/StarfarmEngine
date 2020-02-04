//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#include "LogSystem.hpp"

namespace star
{

        void LogSystem::update(ecs::Interval deltaTime)
        {
                for (auto &str : _buffer)
                {
                        std::puts(str.data());
                }
                _buffer.clear();
        }

}
