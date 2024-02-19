/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Pacman/Player.cpp
*/

#include "Player.hpp"

/*
** Public methods
*/

arcade::entity::Player::Player(arcade::entity::PositionVector pos) : arcade::entity::GenericEntity(pos, 3)
{
    this->eatedSuperPacgumNumber = 0;
    this->strongState = arcade::entity::NORMAL;
}

void arcade::entity::Player::move(std::vector<std::string> &map, int &score)
{
    arcade::entity::PositionVector dir = this->getDirection();
    arcade::entity::PositionVector pos = this->getPos();
    arcade::entity::PositionVector newPos = pos + dir;

    this->goToNormalState();
    if (this->getState() == arcade::entity::DEAD || dir == arcade::entity::PositionVector(0, 0))
        return;
    if (newPos.x < 0 || newPos.x >= (int)map[0].size())
        newPos.x = map[0].size() - 1 - pos.x;
    if (map[newPos.y][newPos.x] == '#' || map[newPos.y][newPos.x] == 'D')
        return;
    if (map[newPos.y][newPos.x] == 'o') {
        score += 10;
        map[newPos.y][newPos.x] = ' ';
    }
    if (map[newPos.y][newPos.x] == 'O') {
        score += 200;
        map[newPos.y][newPos.x] = ' ';
        this->eatedSuperPacgumNumber += 1;
        this->strongState = arcade::entity::STRONG;
        this->strong_clock = std::chrono::system_clock::now();
    }
    this->setPos(newPos);
}

bool arcade::entity::Player::nextPosIsStepable(arcade::entity::PositionVector playerDirection, const std::vector<std::string> map)
{
    arcade::entity::PositionVector pos = this->getPos();
    arcade::entity::PositionVector newPos = pos + playerDirection;

    if (this->getState() == arcade::entity::DEAD)
        return false;
    if (newPos.x < 0 || newPos.x >= (int)map[0].size())
        newPos.x = map[0].size() - 1 - pos.x;
    if (map[newPos.y][newPos.x] == '#' || map[newPos.y][newPos.x] == 'D')
        return false;
    return true;
}

bool arcade::entity::Player::isCollidingWithEnemy(std::vector<std::shared_ptr<arcade::entity::Enemy>> &enemies)
{
    arcade::entity::PositionVector playerPos = this->getPos();

    for (std::shared_ptr<arcade::entity::Enemy> &enemy : enemies) {
        if (playerPos == enemy->getPos()) {
            if (this->strongState == arcade::entity::NORMAL)
                return true;
            enemy->reset(arcade::entity::PositionVector(8, 9), arcade::entity::FROZEN);
            return false;
        }
    }
    return false;
}

int arcade::entity::Player::getEatedSuperPacgum() const
{
    return this->eatedSuperPacgumNumber;
}

arcade::entity::PlayerStrongState arcade::entity::Player::getStrongState() const
{
    return this->strongState;
}

void arcade::entity::Player::goToNormalState()
{
    if (this->strongState != arcade::entity::STRONG)
        return;
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_time = now - this->strong_clock;

    if (elapsed_time >= std::chrono::seconds(10)) {
        this->strongState = arcade::entity::NORMAL;
        this->strong_clock = now;
    }
}