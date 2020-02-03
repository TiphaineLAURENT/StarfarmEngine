//
// Created by TipLa on 13/04/2019.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <SFML/Graphics/Texture.hpp>

#include "../StarfarmEngine/src/Core/Game.hpp"
#include "../StarfarmEngine/src/Log/LogSystem.hpp"
#include "../StarfarmEngine/src/GameObject/GameObject.hpp"
#include "../StarfarmEngine/src/Render/RenderComponent.hpp"
#include "../StarfarmEngine/src/Physics/BoxCollider.hpp"
#include "../StarfarmEngine/src/Render/RenderSystem.hpp"
#include "../StarfarmEngine/src/Physics/PhysicSystem.hpp"


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
                        auto &window = game.create_window(sf::VideoMode(800, 400),
                                                         "StarfarmEngine");
                        window.setFramerateLimit(60);

                        REQUIRE(window.getSize() == sf::Vector2u{800, 400});

                        THEN("We create a new scene and set it as active scene")
                        {
                                auto &scene = game.create_scene();
                                scene.create_system<star::LogSystem>();
                                scene.create_system<star::RenderSystem>(window);

                                game.set_active_scene(&scene);
                                scene.refresh();

                                THEN("We create a new gameobject")
                                {
                                        auto &entity = scene
                                                .create_entity<star::GameObject>();
                                        auto texture = sf::Texture{};
                                        texture.loadFromFile("test.png");
                                        auto *renderer = entity
                                                .create_component<star::RenderComponent>
                                                (texture);
                                        auto *transform = entity
                                                .create_component<star::TransformComponent>();

                                        REQUIRE(transform != nullptr);
                                        REQUIRE(transform->getPosition() ==
                                                sf::Vector2f{0, 0});

                                        WHEN("The game is running and the "
                                             "object move")
                                        {
                                                REQUIRE(game.run());
                                                transform->move(10, 10);
                                                REQUIRE(game.run());

                                                REQUIRE
                                                (transform->getPosition() ==
                                                 sf::Vector2f{10, 10});

                                                while (game.run())
                                                {
                                                        window.display();
                                                        window.clear();
                                                }
                                        }
                                }
                        }

                }
        }
}


SCENARIO("Two BoxColliders intersecting", "[boxcollider][intersection]")
{
        GIVEN("A game with a scene")
        {
                auto game = star::Game{};
                auto &scene = game.create_scene();

                GIVEN("A game object with a rigidbody")
                {
                        auto &ga = scene.create_entity<star::GameObject>();
                        auto *rigidbody = ga
                                .create_component<star::RigidbodyComponent>();

                        THEN("We add two colliders")
                        {
                                auto *collider1 = ga
                                        .create_component<star::BoxCollider>
                                        (sf::FloatRect{0, 0, 1, 1});
                                REQUIRE(collider1 != nullptr);
                                auto *collider2 = ga
                                        .create_component<star::BoxCollider>
                                        (sf::FloatRect{0.5, 0.5, 1, 1});
                                REQUIRE(collider2 != nullptr);

                                THEN("We check their intersection")
                                {
                                        REQUIRE(collider1->intersects(
                                                *collider2
                                        ));
                                        REQUIRE(collider1->contains(
                                                collider2->get_vertices()[0]
                                        ));
                                }
                        }
                }
        }
}


SCENARIO("Game quitting by event keypressed", "[event][quit]")
{
        GIVEN("A game")
        {
                auto game = star::Game{};
                while (game.run())
                {
                }
        }
}
