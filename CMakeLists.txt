cmake_minimum_required(VERSION 3.14)
project(StarfarmEngine)
set(CMAKE_CXX_STANDARD 20)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(ECS)
include_directories(ECS/ECS/src/Entity)
include_directories(ECS/ECS/src/Component)
include_directories(ECS/ECS/src/System)
include_directories(ECS/ECS/src/util)

add_subdirectory(box2d/src)
include_directories(box2d/include)

set(ENGINE_SOURCES
    StarfarmEngine/src/Core/Game.cpp StarfarmEngine/src/Core/Game.hpp
    StarfarmEngine/src/Core/Scene.cpp StarfarmEngine/src/Core/Scene.hpp
    StarfarmEngine/src/Log/LogSystem.cpp StarfarmEngine/src/Log/LogSystem.hpp
    StarfarmEngine/src/Render/View.cpp StarfarmEngine/src/Render/View.hpp
    StarfarmEngine/src/GameObject/GameObject.cpp StarfarmEngine/src/GameObject/GameObject.hpp
    StarfarmEngine/src/Physics/TransformComponent.cpp StarfarmEngine/src/Physics/TransformComponent.hpp
    StarfarmEngine/src/Render/RenderComponent.cpp StarfarmEngine/src/Render/RenderComponent.hpp
    StarfarmEngine/src/Physics/RigidbodyComponent.cpp StarfarmEngine/src/Physics/RigidbodyComponent.hpp
    StarfarmEngine/src/Physics/ColliderComponent.hpp
    StarfarmEngine/src/Util/Vector.cpp StarfarmEngine/src/Util/Vector.hpp
    StarfarmEngine/src/Util/Point.hpp
    StarfarmEngine/src/Physics/BoxCollider.cpp StarfarmEngine/src/Physics/BoxCollider.hpp
    StarfarmEngine/src/Physics/ColliderComponent.cpp
    StarfarmEngine/src/Event/Signal.cpp StarfarmEngine/src/Event/Signal.hpp
    StarfarmEngine/src/Window/Window.cpp StarfarmEngine/src/Window/Window.hpp
    StarfarmEngine/src/Window/WindowEventHandler.cpp StarfarmEngine/src/Window/WindowEventHandler.hpp
    StarfarmEngine/src/Render/RenderSystem.cpp StarfarmEngine/src/Render/RenderSystem.hpp
    StarfarmEngine/src/Component/MonoBehaviourComponent.cpp StarfarmEngine/src/Component/MonoBehaviourComponent.hpp
    StarfarmEngine/src/Physics/PhysicSystem.cpp StarfarmEngine/src/Physics/PhysicSystem.hpp
    )

list(SORT ENGINE_SOURCES COMPARE FILE_BASENAME)
list(TRANSFORM ENGINE_SOURCES PREPEND "${CMAKE_SOURCE_DIR}/")
list(JOIN ENGINE_SOURCES "\n" ENGINE_SOURCES_STRING)
message("Found starfarmengine sources: [\n" ${ENGINE_SOURCES_STRING} "\n]")

if (WIN32)
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        message("Windows 64bits")
        set(SFML_DIR "SFML-2.5.1-visual64/lib/cmake/SFML")
        set(SFML_DLLS "${CMAKE_SOURCE_DIR}/SFML-2.5.1-visual64/bin")
        include_directories(SFML-2.5.1-visual64/include)
    endif ()
endif ()
find_package(SFML 2.5 COMPONENTS graphics audio window network system REQUIRED)

add_library(starfarm STATIC ${ENGINE_SOURCES})


#add_library(coverage_config INTERFACE)
option(CODE_COVERAGE "Enable coverage reporting" OFF)
if (CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(coverage_config INTERFACE
                           -O0
                           -g
                           --coverage
                           )
    if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
        target_link_options(coverage_config INTERFACE --coverage)
    else ()
        target_link_libraries(coverage_config INTERFACE --coverage)
    endif ()
endif ()

option(BUILD_TESTING "Build testing tree" ON)
if (BUILD_TESTING AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    enable_testing()
    add_subdirectory(tests)
endif ()
