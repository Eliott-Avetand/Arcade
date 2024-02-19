/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Pacman/GenericEntity.hpp
*/

#pragma once

#include <vector>
#include "IEntity.hpp"

namespace arcade
{
    namespace entity
    {
        class GenericEntity : public IEntity {
            private:
                int hp;
                PositionVector pos;
                EntityState state;
                int multiplicator;
                PositionVector direction;

            public:
                GenericEntity(PositionVector pos, int hp);

                PositionVector getPos() const;
                void setPos(PositionVector pos);

                EntityState getState() const;
                void setState(EntityState state);

                int getMultiplicator() const;
                void setMultiplicator(int multi);

                int getHP() const;
                void setHP(int hp);

                PositionVector getDirection() const;
                void setDirection(PositionVector dir);
        };
    };
};