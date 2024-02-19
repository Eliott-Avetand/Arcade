/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Nibbler/Body.cpp
*/

#include "Body.hpp"

arcade::entity::Body::Body(PositionVector pos)
{
    this->setPos(pos);
    this->setHP(1);
    this->setDirection(arcade::entity::PositionVector(0, 0));
    this->setMultiplicator(1);
    this->setState(arcade::entity::EntityState::ALIVE);
}

arcade::entity::PositionVector arcade::entity::Body::getPos() const
{
    return this->pos;
}

void arcade::entity::Body::setPos(arcade::entity::PositionVector pos)
{
    this->pos = pos;
}

arcade::entity::EntityState arcade::entity::Body::getState() const
{
    return this->state;
}

void arcade::entity::Body::setState(arcade::entity::EntityState state)
{
    this->state = state;
}

int arcade::entity::Body::getMultiplicator() const
{
    return this->multi;
}

void arcade::entity::Body::setMultiplicator(int multi)
{
    this->multi = multi;
}

int arcade::entity::Body::getHP() const
{
    return this->hp;
}

void arcade::entity::Body::setHP(int hp)
{
    this->hp = hp;
}

arcade::entity::PositionVector arcade::entity::Body::getDirection() const
{
    return this->dir;
}

void arcade::entity::Body::setDirection(arcade::entity::PositionVector dir)
{
    this->dir = dir;
}