//
// Created by TipLa on 13/04/2019.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>

#include "../StarfarmEngine/src/Core/Game.hpp"
#include "../StarfarmEngine/src/Log/LogSystem.hpp"
#include "../StarfarmEngine/src/Entity/GameObject.hpp"
#include "../StarfarmEngine/src/Component/BoxCollider.hpp"


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

                                        WHEN("The game is running and the "
                                             "object move")
                                        {
                                                REQUIRE(game.run());
                                                transform->move(10 , 10);
                                                REQUIRE(game.run());

                                                REQUIRE
                                                (transform->getPosition() ==
                                                sf::Vector2f{10, 10});
                                        }
                                }
                        }

                }
        }
};

SCENARIO("Two BoxColliders intersecting", "[boxcollider][intersection]")
{
        GIVEN("A game with a scene") {
                auto game = star::Game{};
                auto &scene = game.createScene();

                GIVEN("A game object with a rigidbody") {
                        auto &ga = scene.createEntity<star::GameObject>();
                        auto *rigidbody = ga
                                .addComponent<star::RigidbodyComponent>();
                        REQUIRE(rigidbody != nullptr);

                        THEN("We add two colliders") {
                                auto *collider1 = ga
                                        .addComponent<star::BoxCollider>
                                                (sf::FloatRect{0, 0, 1, 1});
                                REQUIRE(collider1 != nullptr);
                                auto *collider2 = ga
                                        .addComponent<star::BoxCollider>
                                                (sf::FloatRect{0.5, 0.5, 1, 1});
                                REQUIRE(collider2 != nullptr);

                                THEN("We check their intersection") {
                                        REQUIRE(collider1->intersects(
                                                *collider2
                                        ));
                                        REQUIRE(collider1->contains(
                                                collider2->getVertices()[0]
                                        ));
                                }
                        }
                }
        }
};
