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

        void LogSystem::log(const std::string &str)
        {
                _buffer.push_back("Info: " + str);
        }
        void LogSystem::warning(const std::string &str)
        {
                _buffer.push_back("\033[1;33mWarning: " + str);
        }
        void LogSystem::error(const std::string &str)
        {
                _buffer.push_back("\033[1;31mError: " + str);
        }

}
