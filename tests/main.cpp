//
// Created by TipLa on 13/04/2019.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>

#include "../StarfarmEngine/src/Core/Game.hpp"
#include "../StarfarmEngine/src/Log/LogSystem.hpp"
#include "../StarfarmEngine/src/Entity/GameObject.hpp"

SCENARIO("Game running", "[engine][gamerun]")
{
        GIVEN("A game")
        {
                star::Game game;

                THEN("The game is empty and cannot run")
                {
                        REQUIRE(!game.run());
                }

                THEN("We create a new window")
                {
                        auto &window = game.createWindow(sf::VideoMode(800, 400),
                                                         "StarfarmEngine");

                        REQUIRE(window.getSize() == sf::Vector2u{800, 400});

                        THEN("We create a new scene and set it as active scene")
                        {
                                auto &scene = game.createScene();
                                scene.createSystem<star::LogSystem>();

                                game.setActiveScene(&scene);
                                scene.refresh();

                                THEN("We create a new gameobject")
                                {
                                        auto &entity = scene
                                                .createEntity<star::GameObject>();
                                        auto *transform = entity
                                                .getComponent<star::TransformComponent>();

                                        REQUIRE(transform != nullptr);
                                        REQUIRE(transform->getPosition() ==
                                        sf::Vector2f{0, 0});

                                        WHEN("The game is running")
                                        {
                                                REQUIRE(game.run());

                                                window.clear();
                                                window.display();
                                        }
                                }
                        }

                }
        }
};

