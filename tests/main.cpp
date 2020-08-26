//
// Created by TipLa on 13/04/2019.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>

#include <SFML/Graphics/Texture.hpp>

#include "../StarfarmEngine/src/Core/Game.hpp"
#include "../StarfarmEngine/src/GameObject/GameObject.hpp"
#include "../StarfarmEngine/src/Log/LogSystem.hpp"
#include "../StarfarmEngine/src/Physics/CircleCollider.hpp"
#include "../StarfarmEngine/src/Physics/PhysicSystem.hpp"
#include "../StarfarmEngine/src/Physics/RigidbodyComponent.hpp"
#include "../StarfarmEngine/src/Physics/SegmentCollider.hpp"
#include "../StarfarmEngine/src/Render/RenderComponent.hpp"
#include "../StarfarmEngine/src/Render/RenderSystem.hpp"
#include "../StarfarmEngine/src/Util/Vector.hpp"

SCENARIO("Game running", "[engine][gamerun]")
{
        GIVEN("A game")
        {
                star::Game game;

                THEN("The game is empty and cannot run") { REQUIRE(!game.run()); }

                THEN("We create a new window")
                {
                        auto &window =
                                game.create_window(sf::VideoMode(800, 400), "StarfarmEngine");
                        window.setFramerateLimit(60);

                        REQUIRE(window.getSize() == sf::Vector2u{ 800, 400 });

                        THEN("We create a new scene and set it as active scene")
                        {
                                auto &scene = game.create_scene(star::Vector<2>{ 0, 10 });
                                scene.create_system<star::LogSystem>();
                                scene.create_system<star::RenderSystem>(window);
                                scene.create_system<star::PhysicSystem>(scene.get_world());

                                game.set_active_scene(&scene);
                                scene.refresh();

                                THEN("We create a new gameobject")
                                {
                                        auto &ground = scene.create_entity<star::GameObject>();

                                        auto *ground_body =
                                                ground.create_component<star::RigidbodyComponent>(
                                                        cpBodyType::CP_BODY_TYPE_STATIC);

                                        auto *ground_collider =
                                                ground.create_component<star::SegmentCollider>(
                                                        star::Vector<2>{ -200, 80 },
                                                        star::Vector<2>{ 200, -80 },
                                                        0);
                                        ground_collider->set_friction(1);

                                        auto ground_texture = sf::Texture{};
                                        ground_texture.loadFromFile("rectangle.png");
                                        auto *ground_renderer =
                                                ground.create_component<star::RenderComponent>(
                                                        ground_texture);

                                        REQUIRE(ground_body != nullptr);

                                        WHEN("The game is running and the "
                                             "object move")
                                        {
                                                REQUIRE(game.run());

                                                auto &ball =
                                                        scene.create_entity<star::GameObject>();

                                                auto *ball_body = ball.create_component<
                                                        star::RigidbodyComponent>();

                                                auto *ball_collider =
                                                        ball.create_component<star::CircleCollider>(
                                                                80);
                                                ball_collider->set_friction(0.7);

                                                auto ball_texture = sf::Texture{};
                                                ball_texture.loadFromFile("circle.png");
                                                auto *ball_renderer = ball.create_component<
                                                        star::RenderComponent>(ball_texture);

                                                ground_body->set_position(window.getSize().x / 2, 300);
                                                ball_body->set_position(window.getSize().x / 2, 150);
                                                auto position = ball_body->get_position();
                                                REQUIRE(position.y == 150);

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

// SCENARIO("Two BoxColliders intersecting", "[boxcollider][intersection]")
//{
//        GIVEN("A game with a scene")
//        {
//                auto game = star::Game{};
//                auto &scene = game.create_scene();
//
//                GIVEN("A game object with a rigidbody")
//                {
//                        auto &ga = scene.create_entity<star::GameObject>();
//                        auto *rigidbody = ga
//                                .create_component<star::RigidbodyComponent>();
//
//                        THEN("We add two colliders")
//                        {
//                                auto *collider1 = ga
//                                        .create_component<star::BoxCollider>
//                                        (sf::FloatRect{0, 0, 1, 1});
//                                REQUIRE(collider1 != nullptr);
//                                auto *collider2 = ga
//                                        .create_component<star::BoxCollider>
//                                        (sf::FloatRect{0.5, 0.5, 1, 1});
//                                REQUIRE(collider2 != nullptr);
//
//                                THEN("We check their intersection")
//                                {
//                                        REQUIRE(collider1->intersects(
//                                                *collider2
//                                        ));
//                                        REQUIRE(collider1->contains(
//                                                collider2->get_vertices()[0]
//                                        ));
//                                }
//                        }
//                }
//        }
//}

SCENARIO("Game quitting by event keypressed", "[event][quit]")
{
        GIVEN("A game")
        {
                auto game = star::Game{};
                while (game.run()) {}
        }
}
