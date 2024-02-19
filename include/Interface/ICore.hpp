/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** ICore.hpp
*/
#pragma once

#include <vector>
#include <string>
#include <memory>

#include "IDisplayer.hpp"
#include "IGame.hpp"

namespace arcade
{
    namespace core
    {
        class ICore
        {
            public:
                virtual ~ICore() = default;

                virtual std::shared_ptr<arcade::displayer::IDisplayer> initDisplayer(std::string path) = 0;
                virtual std::shared_ptr<arcade::game::IGame> initGame(std::string path) = 0;

                virtual std::vector<std::string> scanDisplayers() = 0;
                virtual std::vector<std::string> scanGames() = 0;

                virtual void fillData() = 0;
                virtual void update(size_t gameIndex, size_t displayerIndex) = 0;
                virtual void start() = 0;
        };
    };
};