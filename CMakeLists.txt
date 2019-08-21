cmake_minimum_required(VERSION 3.14)
project(StarfarmEngine)
set(CMAKE_CXX_STANDARD 17)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(ECS)
include_directories(ECS/ECS/src/Entity)
include_directories(ECS/ECS/src/Component)
include_directories(ECS/ECS/src/System)

set(ENGINE_SOURCES
    StarfarmEngine/src/Core/Game.cpp StarfarmEngine/src/Core/Game.hpp
    StarfarmEngine/src/Core/Scene.cpp StarfarmEngine/src/Core/Scene.hpp
    StarfarmEngine/src/Log/LogSystem.cpp StarfarmEngine/src/Log/LogSystem.hpp
    StarfarmEngine/src/Render/View.cpp StarfarmEngine/src/Render/View.hpp
    StarfarmEngine/src/Entity/GameObject.cpp StarfarmEngine/src/Entity/GameObject.hpp
    StarfarmEngine/src/Component/TransformComponent.cpp StarfarmEngine/src/Component/TransformComponent.hpp
    StarfarmEngine/src/Component/RenderComponent.cpp StarfarmEngine/src/Component/RenderComponent.hpp
    StarfarmEngine/src/Component/RigidbodyComponent.cpp StarfarmEngine/src/Component/RigidbodyComponent.hpp
    StarfarmEngine/src/Component/ColliderComponent.hpp
    StarfarmEngine/src/Util/Vector.hpp
    StarfarmEngine/src/Component/BoxCollider.cpp StarfarmEngine/src/Component/BoxCollider.hpp
    StarfarmEngine/src/Component/ColliderComponent.cpp
    StarfarmEngine/src/Event/Signal.cpp StarfarmEngine/src/Event/Signal.hpp
    StarfarmEngine/src/Core/Window.cpp StarfarmEngine/src/Core/Window.hpp
    StarfarmEngine/src/Event/WindowEventHandler.cpp StarfarmEngine/src/Event/WindowEventHandler.hpp
    )

list(SORT ENGINE_SOURCES COMPARE FILE_BASENAME)
list(TRANSFORM ENGINE_SOURCES PREPEND "${CMAKE_SOURCE_DIR}/")
list(JOIN ENGINE_SOURCES "\n" ENGINE_SOURCES_STRING)
message("Found library sources: [\n" ${ENGINE_SOURCES_STRING} "\n]")

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
