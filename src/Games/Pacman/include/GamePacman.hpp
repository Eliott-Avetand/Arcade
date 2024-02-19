/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Pacman/Pacman.hpp
*/

#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <chrono>

#include "IGame.hpp"
#include "Errors.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "ElementDoor.hpp"

namespace arcade
{
    namespace game
    {
        typedef std::vector<std::pair<std::string, std::string>> listOfKeyLabels;

        enum GameState {
            INGAME,
            WIN,
            LOOSE
        };

        class GamePacman : public IGame
        {
            private:
                std::map<arcade::KeyboardKeys, arcade::entity::PositionVector> directionMapping;
                std::shared_ptr<arcade::entity::Player> player;
                std::vector<std::shared_ptr<arcade::entity::Enemy>> enemies;
                std::vector<std::string> map;
                int score;
                GameState gameState;

                ElementDoor door;

                void openMap(std::string path);
                void initDirectionMapping();
                void initEnemies(std::string enemiesChar);
                void resetGame();
                void winGame();
                void teleportEnemiesOutOfCage();

            public:
                GamePacman();

                void update();
                std::vector<std::string> getDatas();
                void setInput(arcade::KeyboardKeys input);
                listOfKeyLabels getKeyMapping();
        };
    };
};
