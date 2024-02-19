/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** IGame.hpp
*/

#pragma once

#include <vector>
#include <memory>
#include "IEntity.hpp"
#include "Keyboards.hpp"

namespace arcade
{
    namespace game
    {
        class IGame
        {
            public:
                virtual ~IGame() = default;

                virtual void update() = 0;
                virtual std::vector<std::string> getDatas() = 0;
                virtual void setInput(arcade::KeyboardKeys input) = 0;
                virtual std::vector<std::pair<std::string, std::string>> getKeyMapping() = 0;
        };
    };
};