/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Pacman/Pacman.cpp
*/

#include "GamePacman.hpp"

/*
** Public methods
*/

arcade::game::GamePacman::GamePacman()
{
    std::srand(std::time(NULL));
    this->player = std::make_shared<arcade::entity::Player>(arcade::entity::PositionVector(9, 11));
    this->score = 0;
    this->openMap("./src/Games/Pacman/src/Map/map1.txt");
    this->initDirectionMapping();
    this->initEnemies("BJV");
    this->gameState = arcade::game::INGAME;

    this->door = arcade::game::ElementDoor(false, std::chrono::system_clock::now(), std::chrono::system_clock::now());
}

std::vector<std::string> arcade::game::GamePacman::getDatas()
{
    std::vector<std::string> datas = {std::to_string(this->score), std::to_string(this->player->getHP())};
    std::vector<std::string> mapDump = map;
    arcade::entity::PositionVector playerPos = this->player->getPos();

    if (this->player->getState() != arcade::entity::DEAD)
        mapDump[playerPos.y][playerPos.x] = 'P';
    for (std::shared_ptr<arcade::entity::Enemy> e : this->enemies) {
        arcade::entity::PositionVector enemyPos = e->getPos();
        mapDump[enemyPos.y][enemyPos.x] = (this->player->getStrongState() == arcade::entity::NORMAL) ? e->getEntityChar() : 'U';
    }
    if (this->gameState == arcade::game::LOOSE)
        mapDump[11][9] = 'X';
    else if (this->gameState == arcade::game::WIN)
        mapDump[11][9] = 'W';
    
    datas.insert(datas.end(), mapDump.begin(), mapDump.end());
    return datas;
}

arcade::game::listOfKeyLabels arcade::game::GamePacman::getKeyMapping()
{
    return {
        std::pair<std::string, std::string>("Z", "Avancer"),
        std::pair<std::string, std::string>("Q", "Tourner à gauche"),
        std::pair<std::string, std::string>("S", "Reculer"),
        std::pair<std::string, std::string>("D", "Tourner à droite")
    };
}

void arcade::game::GamePacman::setInput(arcade::KeyboardKeys input)
{
    if (!this->directionMapping.contains(input))
        return;
    arcade::entity::PositionVector playerDirection = this->directionMapping.find(input)->second;
    if (this->player->nextPosIsStepable(playerDirection, this->map))
        this->player->setDirection(playerDirection);
}

void arcade::game::GamePacman::update()
{
    if (this->gameState != arcade::game::INGAME)
        return;
    this->door.checkForOpen();
    this->teleportEnemiesOutOfCage();
    this->player->move(this->map, this->score);
    if (this->player->isCollidingWithEnemy(this->enemies))
        return this->resetGame();
    if (this->player->getEatedSuperPacgum() == 4) {
        this->gameState = arcade::game::WIN;
        return;
    }
    for (int i = 0; i < 4; i++) {
        this->enemies[i]->move(this->map);
        if (this->enemies[i]->isCollidingWithPlayer(this->player->getPos(), this->player->getStrongState()))
            return this->resetGame();
    }
}

/*
** Private methods
*/

void arcade::game::GamePacman::resetGame()
{
    this->player->setState(arcade::entity::DEAD);
    this->player->setDirection(arcade::entity::PositionVector(0, 0));
    this->player->setHP(this->player->getHP() - 1);
    if (this->player->getHP() <= 0) {
        this->gameState = arcade::game::LOOSE;
        return;
    }
    this->player->setPos(arcade::entity::PositionVector(9, 11));
    this->enemies[0]->reset(arcade::entity::PositionVector(9, 7), arcade::entity::ALIVE);
    for (int i = 1; i < 4; i++)
        this->enemies[i]->reset(arcade::entity::PositionVector(8 + (i - 1), 9), arcade::entity::FROZEN);
    this->player->setState(arcade::entity::ALIVE);
}

void arcade::game::GamePacman::winGame()
{
    this->player->setState(arcade::entity::DEAD);
    this->player->setDirection(arcade::entity::PositionVector(0, 0));
    for (int i = 0; i < 4; i++)
        this->enemies[i]->setState(arcade::entity::DEAD);
    this->gameState = arcade::game::WIN;
}

void arcade::game::GamePacman::teleportEnemiesOutOfCage()
{
    if (this->door.isOpen == false)
        return;
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_time = now - this->door.tp_enemy_clock;

    if (elapsed_time >= std::chrono::seconds(10)) {
        this->door.tp_enemy_clock = now;
        for (std::shared_ptr<arcade::entity::Enemy> e : this->enemies) {
            if (e->isInCage() == true) {
                e->setState(arcade::entity::ALIVE);
                e->setPos(arcade::entity::PositionVector(9, 7));
                e->setDirection(arcade::entity::PositionVector(-1, 0));
                e->isInCage(false);
                break;
            }
        }
    }
}

void arcade::game::GamePacman::openMap(std::string path)
{
    std::ifstream file(path);
    std::string temp;

    if (file.fail())
        throw Errors("[Arcade - Pacman] Can't open map file.");
    while (std::getline(file, temp))
        this->map.push_back(temp);
    file.close();
}

void arcade::game::GamePacman::initDirectionMapping()
{
    this->directionMapping.insert(std::make_pair(arcade::KEY_Z, arcade::entity::PositionVector(0, -1)));
    this->directionMapping.insert(std::make_pair(arcade::KEY_S, arcade::entity::PositionVector(0, 1)));
    this->directionMapping.insert(std::make_pair(arcade::KEY_Q, arcade::entity::PositionVector(-1, 0)));
    this->directionMapping.insert(std::make_pair(arcade::KEY_D, arcade::entity::PositionVector(1, 0)));
}

void arcade::game::GamePacman::initEnemies(std::string enemiesChar)
{
    this->enemies.push_back(std::make_shared<arcade::entity::Enemy>(arcade::entity::PositionVector(9, 7), arcade::entity::ALIVE, 'R'));
    for (int i = 8; i < 11; i++)
        this->enemies.push_back(std::make_shared<arcade::entity::Enemy>(arcade::entity::PositionVector(i, 9), arcade::entity::FROZEN, enemiesChar[i - 8]));
    this->enemies[0]->setDirection(arcade::entity::PositionVector(-1, 0));
}

/*
** Out-of-class methods
*/

extern "C"
{
    std::shared_ptr<arcade::game::IGame> entryPoint()
    {
        return std::make_shared<arcade::game::GamePacman>();
    }
}