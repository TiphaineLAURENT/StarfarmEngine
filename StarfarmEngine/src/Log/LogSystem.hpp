//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#ifndef STARFARMENGINE_LOGSYSTEM_HPP
#define STARFARMENGINE_LOGSYSTEM_HPP

#include <list>
#include <ostream>

#include <System.hpp>
#include <spdlog/spdlog.h>

namespace star
{
        class SYSTEM(LogSystem)
        {
                // ATTRIBUTES
            private:
                static inline std::list<std::string> _buffer{};

            public:
                // METHODS
            public:    // CONSTRUCTORS
                explicit LogSystem();
                ~LogSystem() override = default;
                LogSystem(const LogSystem &copy) = delete;
                LogSystem(LogSystem &&) = delete;

            public:    // OPERATORS
                LogSystem &operator=(const LogSystem &other) = delete;
                LogSystem &operator=(LogSystem &&) noexcept = delete;

            public:
                void update(ecs::Interval deltaTime) override;

                template <typename Type> static void log(const Type &value)
                {
                        LogSystem::log(std::to_string(value));
                }
                static void log(const std::string &str) { _buffer.push_back("Info: " + str); }

                static void warning(const std::string &str)
                {
                        _buffer.push_back("\033[1;33mWarning: " + str);
                }
                template <class Type> static void warning(const Type &value)
                {
                        LogSystem::warning(std::to_string(value));
                }

                static void error(const std::string &str)
                {
                        _buffer.push_back("\033[1;31mError: " + str);
                }
                template <class Type> static void error(const Type &value)
                {
                        LogSystem::error(std::to_string(value));
                }

            private:
        };

        std::ostream &operator<<(std::ostream &out, const LogSystem &);

}    // namespace star

#endif    // STARFARMENGINE_LOGSYSTEM_HPP
