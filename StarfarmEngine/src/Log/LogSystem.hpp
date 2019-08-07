//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#ifndef STARFARMENGINE_LOGSYSTEM_HPP
#define STARFARMENGINE_LOGSYSTEM_HPP

# include <ostream>
# include <list>

# include <System.hpp>

namespace star
{

  class SYSTEM(LogSystem)
  {
// ATTRIBUTES
  private:
          static std::list<std::string> _buffer;

  public:

// METHODS
  public:// CONSTRUCTORS
          LogSystem() = default;
          ~LogSystem() override = default;
          LogSystem(const LogSystem &copy) = delete;
          LogSystem(LogSystem &&) = delete;

  public: //OPERATORS
          LogSystem &operator=(const LogSystem &other) = delete;
          LogSystem &operator=(LogSystem &&) noexcept = delete;

  public:
          void update(long deltaTime) override;
          static void log(const std::string &str);
          static void warning(const std::string &str);
          static void error(const std::string &str);

  private:
  };

  std::ostream &operator<<(std::ostream &out, const LogSystem &);

}

#endif //STARFARMENGINE_LOGSYSTEM_HPP
