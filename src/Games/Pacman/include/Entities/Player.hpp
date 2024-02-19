/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Pacman/Player.hpp
*/

#pragma once

#include <vector>
#include <string>
#include <memory>
#include <chrono>

#include "GenericEntity.hpp"
#include "Enemy.hpp"

namespace arcade
{
    namespace entity
    {
        class Player : public arcade::entity::GenericEntity
        {
            private:
                int eatedSuperPacgumNumber;
                arcade::entity::PlayerStrongState strongState;
                std::chrono::time_point<std::chrono::system_clock> strong_clock;

                void goToNormalState();

            public:
                Player(PositionVector pos);
                void move(std::vector<std::string> &map, int &score);
                bool isCollidingWithEnemy(std::vector<std::shared_ptr<arcade::entity::Enemy>> &enemies);
                bool nextPosIsStepable(arcade::entity::PositionVector playerDirection, const std::vector<std::string> map);

                int getEatedSuperPacgum() const;
                PlayerStrongState getStrongState() const;
        };
    };
};