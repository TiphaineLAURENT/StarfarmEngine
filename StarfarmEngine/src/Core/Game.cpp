//
// Created by Tiphaine LAURENT on 05/08/2019.
//

#include "Game.hpp"


bool star::Game::run()
{
        auto deltaTime = _clock.restart().asMicroseconds();

        if (!_activeScene)
                return false;

        _activeScene->update(deltaTime);
        return true;
}
