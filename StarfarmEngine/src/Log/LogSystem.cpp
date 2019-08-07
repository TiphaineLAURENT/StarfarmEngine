//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#include "LogSystem.hpp"

namespace star
{

  std::list<std::string> LogSystem::_buffer{};

  void LogSystem::update(long deltaTime)
  {
          for (auto &str : _buffer) {
                  std::clog << str;
          }
          _buffer.clear();
  }

  void LogSystem::log(const std::string &str)
  {
          _buffer.push_back("Info: " + str);
  }
  void LogSystem::warning(const std::string &str)
  {
          _buffer.push_back("Warning: " + str);
  }
  void LogSystem::error(const std::string &str)
  {
          _buffer.push_back("Error: " + str);
  }

}
