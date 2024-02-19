/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** IDisplayer.hpp
*/
#pragma once

#include <string>
#include <vector>
#include "IEntity.hpp"
#include "Keyboards.hpp"


namespace arcade
{
    namespace displayer
    {
        class IDisplayer
        {
            public:
                virtual ~IDisplayer() = default;

                virtual void drawMenu(std::vector<std::string> gamesPaths, std::vector<std::string> displayersPaths) = 0;
                virtual void drawGame(std::vector<std::string> map) = 0;
                // virtual void drawGame(std::vector<std::string> map, std::vector<std::pair<std::string, std::string>> keyMapping) = 0;
                // virtual void drawLib(std::vector<std::string> gamesPaths, std::vector<std::string> displayersPaths) = 0;
                // virtual void drawScore(size_t score) = 0;
                virtual void loadMenuAssets(std::string actualGamePath, std::vector<std::string> gameLibPath, std::vector<std::string> displayerlibPath) = 0;
                virtual void loadGameAssets(std::string actualGamePath, std::vector<std::string> map) = 0;
                virtual bool isRunning() = 0;

                virtual void destroyWindow(void) = 0;
                // virtual void setGameLibNbr(size_t gameLibNbr) = 0;
                // virtual size_t getGameLibNbr() = 0;
                virtual KeyboardKeys getInput() = 0;

                // virtual void setPlayerPos(arcade::entity::Vector pos) = 0;
                // virtual void setPlayerHp(int hp) = 0;
                // virtual void setPlayerState(arcade::entity::EntityState state) = 0;
                // virtual void setPlayerDirection(arcade::entity::Direction dir) = 0;

                // virtual void setEnemiesPos(std::vector<arcade::entity::Vector> pos) = 0;
                // virtual void setEnemiesState(std::vector<arcade::entity::EntityState> states) = 0;
                // virtual void setEnemiesDirection(std::vector<arcade::entity::Direction> dirs) = 0;

                // virtual void setLibs(std::vector<std::string> games, std::vector<std::string> graphs) = 0;
        };
    };
};