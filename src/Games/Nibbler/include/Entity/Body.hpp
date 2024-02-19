/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Nibbler/Body.hpp
*/

#pragma once

#include <memory>
#include "IEntity.hpp"

namespace arcade
{
    namespace entity
    {
        class Body : public arcade::entity::IEntity
        {
            private:
                PositionVector pos;
                EntityState state;
                int multi;
                int hp;
                PositionVector dir;

            public:
                Body(PositionVector pos);
                
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