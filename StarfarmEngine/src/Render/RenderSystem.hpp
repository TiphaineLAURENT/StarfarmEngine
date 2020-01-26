//
// Created by Tiphaine LAURENT on 21/08/2019.
//

#ifndef STARFARMENGINE_RENDERSYSTEM_HPP
#define STARFARMENGINE_RENDERSYSTEM_HPP

# include <ostream>
# include <System.hpp>

# include "../Window/Window.hpp"


namespace star
{

  class SYSTEM(RenderSystem)
  {
// ATTRIBUTES
  public:
  private:

// METHODS
  public:// CONSTRUCTORS
          explicit RenderSystem(Window &window);
          ~RenderSystem() override = default;
          RenderSystem(const RenderSystem &copy) = delete;
          RenderSystem(RenderSystem &&) noexcept = delete;

  public: //OPERATORS
          RenderSystem &operator=(const RenderSystem &other) = delete;
          RenderSystem &operator=(RenderSystem &&) noexcept = delete;

  public:
          void update(::ecs::Interval deltaTime) override;

  private:
          Window &_window;
  };

  std::ostream &operator<<(std::ostream &out, const RenderSystem &);

}

#endif //STARFARMENGINE_RENDERSYSTEM_HPP
