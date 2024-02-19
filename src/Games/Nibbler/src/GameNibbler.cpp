/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Nibbler/GameNibbler.cpp
*/

#include "GameNibbler.hpp"

/*
** Public methods
*/

arcade::game::GameNibbler::GameNibbler()
{
    std::srand(std::time(NULL));
    this->initBodies();
    this->openMap("./src/Games/Nibbler/src/Map/map1.txt");
    this->initDirectionVector();
    this->score = 0;
    this->fruitPos = arcade::entity::PositionVector(14, 6);
    this->gameState = arcade::game::INGAME;
    this->bodies.front()->setDirection(arcade::entity::PositionVector(0, -1));
}

std::vector<std::string> arcade::game::GameNibbler::getDatas()
{
    std::vector<std::string> datas = {std::to_string(this->score), std::to_string(this->bodies[0]->getHP())};
    std::vector<std::string> mapDump = this->map;

    mapDump[this->fruitPos.y][this->fruitPos.x] = 'F';

    if (this->bodies[0]->getState() == arcade::entity::ALIVE) {
        for (size_t i = 0; i < this->bodies.size(); i++) {
            arcade::entity::PositionVector bodyPos = this->bodies[i]->getPos();
            mapDump[bodyPos.y][bodyPos.x] = (i == 0) ? 'H' : 'Q';
        }
    }
    if (this->gameState == arcade::game::LOOSE)
        mapDump[11][9] = 'X';
    else if (this->gameState == arcade::game::WIN)
        mapDump[11][9] = 'W';
    datas.insert(datas.end(), mapDump.begin(), mapDump.end());
    return datas;
}

arcade::game::listOfKeyLabels arcade::game::GameNibbler::getKeyMapping()
{
    return {
        std::pair<std::string, std::string>("Q", "Tourner à gauche"),
        std::pair<std::string, std::string>("D", "Tourner à droite")
    };
}

void arcade::game::GameNibbler::setInput(arcade::KeyboardKeys input)
{
    arcade::entity::PositionVector dir = this->bodies[0]->getDirection();
    auto it = std::find(this->directionVector.begin(), this->directionVector.end(), dir);
    size_t actualDirIndex;

    if (it == this->directionVector.end())
        return;
    actualDirIndex = it - this->directionVector.begin();
    if (input == arcade::KEY_Q)
        actualDirIndex = (actualDirIndex + 1) % 4;
    else if (input == arcade::KEY_D)
        actualDirIndex = (actualDirIndex - 1) % 4;
    else
        return;
    this->bodies[0]->setDirection(this->directionVector[actualDirIndex]);
}

void arcade::game::GameNibbler::update()
{
    if (this->gameState != arcade::game::INGAME)
        return;
    this->moveAllBodies();
}

/*
** Private methods
*/

void arcade::game::GameNibbler::moveAllBodies()
{
    arcade::entity::PositionVector previousBodyLastPos;

    for (size_t i = 0; i < this->bodies.size(); i++) {
        arcade::entity::PositionVector dir = this->bodies[i]->getDirection();
        arcade::entity::PositionVector pos = this->bodies[i]->getPos();
        arcade::entity::PositionVector newPos = pos + dir;

        if (i != 0) {
            if (this->bodies[i - 1]->getPos() == previousBodyLastPos)
                return;
            this->bodies[i]->setPos(previousBodyLastPos);
            previousBodyLastPos = pos;
            if (this->bodies.front()->getPos() == previousBodyLastPos)
                return this->looseGame();
            continue;
        }
        previousBodyLastPos = pos;
        if (this->bodies[i]->getState() == arcade::entity::DEAD || dir == arcade::entity::PositionVector(0, 0))
            return;
        if (this->map[newPos.y][newPos.x] == '#')
            return this->looseGame();
        if (newPos == this->fruitPos) {
            this->score += 10;
            this->spawnNewFruit(previousBodyLastPos);
            this->addNewBody();
        }
        this->bodies[i]->setPos(newPos);
    } 
}

void arcade::game::GameNibbler::addNewBody()
{
    arcade::entity::PositionVector lastBodyPos = this->bodies.back()->getPos();
    this->bodies.push_back(std::make_shared<arcade::entity::Body>(lastBodyPos));
}

void arcade::game::GameNibbler::spawnNewFruit(arcade::entity::PositionVector headLastPos)
{
    bool isValidPos = false;
    arcade::entity::PositionVector newPos;

    while (isValidPos == false) {
        newPos = arcade::entity::PositionVector(std::rand() % this->map[0].size(), std::rand() % this->map.size());
        if (this->map[newPos.y][newPos.x] == '#' || headLastPos == newPos)
            continue;
        for (size_t i = 0; i < this->bodies.size(); i++) {
            arcade::entity::PositionVector bodyPos = this->bodies[i]->getPos();
            if (newPos == bodyPos)
                continue;
        }
        isValidPos = true;
    }
    this->fruitPos = newPos;
}

void arcade::game::GameNibbler::initBodies()
{
    for (int i = 0; i < 4; i++)
        this->bodies.push_back(std::make_shared<arcade::entity::Body>(arcade::entity::PositionVector(10, 8 + i)));
}

void arcade::game::GameNibbler::looseGame()
{
    this->bodies.front()->setDirection(arcade::entity::PositionVector(0, 0));
    this->bodies.front()->setHP(0);
    this->bodies.front()->setState(arcade::entity::DEAD);
    this->gameState = arcade::game::LOOSE;
}

void arcade::game::GameNibbler::openMap(std::string path)
{
    std::ifstream file(path);
    std::string temp;

    if (file.fail()) {
        std::cerr << "[Arcade - Nibbler] Can't open map file.\nLoading default map..." << std::endl;
        return this->loadDefaultMap();
        // throw Errors("[Arcade - Nibbler] Can't open map file.");
    }
    while (std::getline(file, temp))
        this->map.push_back(temp);
    file.close();
}

void arcade::game::GameNibbler::loadDefaultMap()
{
    this->map.push_back("######################\n");
    for (int i = 0; i < 21; i++)
        this->map.push_back("#                    #\n");
    this->map.push_back("######################\n");
}

void arcade::game::GameNibbler::initDirectionVector()
{
    this->directionVector.push_back(arcade::entity::PositionVector(0, -1));
    this->directionVector.push_back(arcade::entity::PositionVector(-1, 0));
    this->directionVector.push_back(arcade::entity::PositionVector(0, 1));
    this->directionVector.push_back(arcade::entity::PositionVector(1, 0));
}

/*
** Out-of-class methods
*/

extern "C"
{
    std::shared_ptr<arcade::game::IGame> entryPoint()
    {
        return std::make_shared<arcade::game::GameNibbler>();
    }
}