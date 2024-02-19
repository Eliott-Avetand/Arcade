/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Pacman/Enemy.cpp
*/

#include "Enemy.hpp"

/*
** Public methods
*/

arcade::entity::Enemy::Enemy(PositionVector pos, EntityState state, char entityChar) : arcade::entity::GenericEntity(pos, 1)
{
    this->setState(state);
    this->entityChar = entityChar;
    this->_isInCage = ((state == arcade::entity::ALIVE) ? false : true);
}

void arcade::entity::Enemy::move(std::vector<std::string> &map)
{
    arcade::entity::PositionVector dir = this->getDirection();
    arcade::entity::PositionVector pos = this->getPos();
    arcade::entity::PositionVector newDir, newPos;
    
    if (this->getState() != arcade::entity::ALIVE || dir == arcade::entity::PositionVector(0, 0))
        return;
    newDir = this->checkEntitySurrounding(pos, dir, map);
    newPos = pos + newDir;
    if (newPos.x < 0 || newPos.x >= (int)map[0].size())
        newPos.x = map[0].size() - 1 - pos.x;
    this->setDirection(newDir);
    this->setPos(newPos);
}

void arcade::entity::Enemy::reset(arcade::entity::PositionVector pos, arcade::entity::EntityState state)
{
    this->isInCage((state == arcade::entity::ALIVE) ? false : true);
    this->setPos(pos);
    this->setState(state);
    if (state == arcade::entity::ALIVE)
        this->setDirection(PositionVector::random(PositionVector::getAllDirs()));
}

char arcade::entity::Enemy::getEntityChar() const
{
    return this->entityChar;
}

bool arcade::entity::Enemy::isCollidingWithPlayer(const arcade::entity::PositionVector playerPos, const arcade::entity::PlayerStrongState playerState)
{
    if (this->getPos() == playerPos) {
        if (playerState == arcade::entity::STRONG) {
            this->reset(arcade::entity::PositionVector(8, 9), arcade::entity::FROZEN);
            return false;
        }
        return true;
    }
    return false;
}

/*
** Private methods
*/

arcade::entity::PositionVector arcade::entity::Enemy::checkEntitySurrounding(PositionVector pos, PositionVector dir, const std::vector<std::string> map)
{
    std::vector<PositionVector> allDirs = PositionVector::getAllDirs();
    std::vector<PositionVector> possibleDirs;

    for (PositionVector testedDir : allDirs) {
        PositionVector possibleNewPos = pos + testedDir;
        if (possibleNewPos.x < 0 || possibleNewPos.x >= (int)map[0].size())
            possibleNewPos.x = map[0].size() - 1 - pos.x;
        if (testedDir != dir.invert() && map[possibleNewPos.y][possibleNewPos.x] != '#' && map[possibleNewPos.y][possibleNewPos.x] != 'D')
            possibleDirs.push_back(testedDir);
    }
    if (possibleDirs.size() == 0)
        return PositionVector(0, 0);
    else
        return PositionVector::random(possibleDirs);
}

bool arcade::entity::Enemy::isInCage() const
{
    return this->_isInCage;
}

void arcade::entity::Enemy::isInCage(bool state)
{
    this->_isInCage = state;
}