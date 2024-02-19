/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** IEntity.hpp
*/

#pragma once

#include <vector>
#include <string>
#include "PositionVector.hpp"

namespace arcade
{
    namespace entity
    {
        enum EntityState
        {
            ALIVE,
            FROZEN,
            DEAD
        };

        enum PlayerStrongState {
            NORMAL,
            STRONG
        };

        class IEntity {
            public:
                ~IEntity() = default;

                virtual PositionVector getPos() const = 0;
                virtual void setPos(PositionVector pos) = 0;

                virtual EntityState getState() const = 0;
                virtual void setState(EntityState state) = 0;

                virtual int getMultiplicator() const = 0;
                virtual void setMultiplicator(int multi) = 0;

                virtual int getHP() const = 0;
                virtual void setHP(int hp) = 0;

                virtual PositionVector getDirection() const = 0;
                virtual void setDirection(PositionVector dir) = 0;
        };
    };
};