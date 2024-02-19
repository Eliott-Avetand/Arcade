/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Pacman/Enemy.hpp
*/

#pragma once

#include <vector>
#include <string>

#include "GenericEntity.hpp"

namespace arcade
{
    namespace entity
    {
        class Enemy : public arcade::entity::GenericEntity
        {
            private:
                char entityChar;
                bool _isInCage;

                PositionVector checkEntitySurrounding(PositionVector pos, PositionVector dir, const std::vector<std::string> map);

            public:
                Enemy(PositionVector pos, EntityState state, char entityChar);
                void move(std::vector<std::string> &map);
                void reset(PositionVector pos, EntityState state);
                char getEntityChar() const;
                bool isCollidingWithPlayer(const PositionVector playerPos, const arcade::entity::PlayerStrongState playerState);

                bool isInCage() const;
                void isInCage(bool state);
        };
    };
};