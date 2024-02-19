/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Nibbler/GameNibbler.hpp
*/

#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <chrono>

#include "IGame.hpp"
#include "Errors.hpp"
#include "Body.hpp"
#include "PositionVector.hpp"

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

        class GameNibbler : public IGame
        {
            private:
                std::vector<std::shared_ptr<arcade::entity::Body>> bodies;
                std::vector<std::string> map;
                arcade::entity::PositionVector fruitPos;
                std::vector<arcade::entity::PositionVector> directionVector;
                int score;
                GameState gameState;

                void openMap(std::string path);
                void loadDefaultMap();
                void initDirectionVector();
                void looseGame();
                void initBodies();
                void moveAllBodies();
                void spawnNewFruit(arcade::entity::PositionVector headLastPos);
                void addNewBody();

            public:
                GameNibbler();

                void update();
                std::vector<std::string> getDatas();
                void setInput(arcade::KeyboardKeys input);
                listOfKeyLabels getKeyMapping();
        };
    };
};
