/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Pacman/GenericEntity.cpp
*/

#include "GenericEntity.hpp"

arcade::entity::GenericEntity::GenericEntity(PositionVector pos, int hp)
{
    this->hp = hp;
    this->pos = pos;
    this->state = EntityState::ALIVE;
    this->multiplicator = 1;
    this->direction = PositionVector(0, 0);
}

arcade::entity::PositionVector arcade::entity::GenericEntity::getPos() const
{
    return this->pos;
}

void arcade::entity::GenericEntity::setPos(PositionVector pos)
{
    this->pos = pos;
}

int arcade::entity::GenericEntity::getMultiplicator() const
{
    return this->multiplicator;
}

void arcade::entity::GenericEntity::setMultiplicator(int multi)
{
    this->multiplicator = multi;
}

int arcade::entity::GenericEntity::getHP() const
{
    return this->hp;
}

void arcade::entity::GenericEntity::setHP(int hp)
{
    this->hp = hp;
}

arcade::entity::EntityState arcade::entity::GenericEntity::getState() const
{
    return this->state;
}

void arcade::entity::GenericEntity::setState(EntityState state)
{
    this->state = state;
}

arcade::entity::PositionVector arcade::entity::GenericEntity::getDirection() const
{
    return this->direction;
}

void arcade::entity::GenericEntity::setDirection(arcade::entity::PositionVector dir)
{
    this->direction = dir;
}