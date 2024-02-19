/*
** EPITECH PROJECT, 2022
** LibSFMLGame.cpp
** File description:
** sfml file for Arcade
*/

#include "LibSFML.hpp"
#include "LibSFMLErrors.hpp"
#include <iostream>

arcade::displayer::LibSfml::Game::Game(void)
{
    this->_functionsPacman = {{'P', &arcade::displayer::LibSfml::Game::createPacmanSprite},
                                {'#', &arcade::displayer::LibSfml::Game::createWalls},
                                {'o', &arcade::displayer::LibSfml::Game::createPacgumSprite},
                                {'O', &arcade::displayer::LibSfml::Game::createSuperPacgumSprite},
                                {'D', &arcade::displayer::LibSfml::Game::createDoors}};
    this->_functionsNibbler = {{'#', &arcade::displayer::LibSfml::Game::createWalls},
                               {'H', &arcade::displayer::LibSfml::Game::createNibblerHead},
                               {'Q', &arcade::displayer::LibSfml::Game::createNibblerBody},
                               {'F', &arcade::displayer::LibSfml::Game::createNibblerFruits}};
    this->_mapDatas.oldPos = {1, 1};
    this->_mapDatas.newPos = {1, 0};
}

arcade::displayer::LibSfml::Game::~Game(void)
{
    // void
}

void arcade::displayer::LibSfml::Game::createNibblerHead(void)
{
    sf::IntRect rect;

    rect.height = 42;
    rect.width = 42;
    rect.top = 0;
    rect.left = 0;
    if (!this->_mapDatas._nibblerHead.second.loadFromFile("./src/ressources/sprites/spriteNibbler.png"))
        throw arcade::displayer::libSFMLErrors("[SFML] Cannot load Texture for Nibbler Head!", "Texture can't load!");
    this->_mapDatas._nibblerHead.first.setTexture(this->_mapDatas._nibblerHead.second);
    this->_mapDatas._nibblerHead.first.setTextureRect(rect);
    this->_mapDatas._nibblerHead.first.setOrigin(21, 21);
    this->_mapDatas._nibblerHead.first.setScale(0.7, 0.7);
}

void arcade::displayer::LibSfml::Game::createNibblerBody(void)
{
    sf::IntRect rect;

    rect.height = 42;
    rect.width = 42;
    rect.top = 126 - 42;
    rect.left = 126 - 42;
    if (!this->_mapDatas._nibblerQueue.second.loadFromFile("./src/ressources/sprites/spriteNibbler.png"))
        throw arcade::displayer::libSFMLErrors("[SFML] Cannot load Texture for Nibbler Head!", "Texture can't load!");
    this->_mapDatas._nibblerQueue.first.setTexture(this->_mapDatas._nibblerQueue.second);
    this->_mapDatas._nibblerQueue.first.setTextureRect(rect);
    this->_mapDatas._nibblerQueue.first.setOrigin(21, 21);
    this->_mapDatas._nibblerQueue.first.setScale(0.7, 0.7);
}

void arcade::displayer::LibSfml::Game::createNibblerFruits(void)
{
    if (!this->_mapDatas._fruits.second.loadFromFile("./src/ressources/sprites/fruitNibbler.png"))
        throw arcade::displayer::libSFMLErrors("[SFML] Cannot load Texture for Nibbler Head!", "Texture can't load!");
    this->_mapDatas._fruits.first.setTexture(this->_mapDatas._fruits.second);
    this->_mapDatas._fruits.first.setOrigin(11 / 2, 6);
    this->_mapDatas._fruits.first.setScale(1.8, 1.8);
}

void arcade::displayer::LibSfml::Game::createEnemy(std::vector<float> rectWidth, char type)
{
    std::pair<std::shared_ptr<sf::Sprite>, std::shared_ptr<sf::Texture>> Sptpair;
    sf::IntRect rect;

    Sptpair.first = std::make_shared<sf::Sprite>(sf::Sprite());
    Sptpair.second = std::make_shared<sf::Texture>(sf::Texture());
    if (!Sptpair.second->loadFromFile("./src/ressources/sprites/spritePacman.png"))
        throw arcade::displayer::libSFMLErrors("[SFML] Cannot load Texture for enemies!", "Texture can't load!");
    rect.height = rectWidth[0];
    rect.width = rectWidth[1];
    rect.top = rectWidth[2];
    rect.left = rectWidth[3];
    Sptpair.first->setTexture(*Sptpair.second);
    Sptpair.first->setTextureRect(rect);
    Sptpair.first->setOrigin(11.5, 11.5);
    this->_mapDatas._enemy.insert(std::make_pair(type, Sptpair));
}

void arcade::displayer::LibSfml::Game::createDoors(void)
{
    sf::RectangleShape rect;

    rect.setSize(sf::Vector2f(30, 15));
    rect.setFillColor(sf::Color(105, 105, 105));
    rect.setOrigin(15, 7.5);
    this->_mapDatas._doors = rect;
}

void arcade::displayer::LibSfml::Game::createWalls(void)
{
    sf::RectangleShape rect;

    rect.setSize(sf::Vector2f(30, 30));
    rect.setFillColor(sf::Color::Blue);
    rect.setOrigin(15, 15);
    this->_mapDatas._walls = rect;
}

void arcade::displayer::LibSfml::Game::createSuperPacgumSprite(void)
{
    sf::IntRect rect;

    rect.height = 15;
    rect.width = 15;
    rect.top = 23.1 * 8;
    rect.left = 0;
    this->_mapDatas.pacmanClk.restart();
    if (!this->_mapDatas._bonus.second.loadFromFile("./src/ressources/sprites/spritePacman.png"))
        throw arcade::displayer::libSFMLErrors("[SFML] Cannot load texture!", "Texture isn't load!");
    this->_mapDatas._bonus.first.setTexture(this->_mapDatas._bonus.second);
    this->_mapDatas._bonus.first.setTextureRect(rect);
    this->_mapDatas._bonus.first.setScale(1.3, 1.3);
    this->_mapDatas._bonus.first.setOrigin(this->_mapDatas._bonus.first.getGlobalBounds().width, this->_mapDatas._bonus.first.getGlobalBounds().height);
}

void arcade::displayer::LibSfml::Game::createPacgumSprite(void)
{
    sf::IntRect rect;

    rect.height = 15;
    rect.width = 15;
    rect.top = 23.1 * 8;
    rect.left = 0;
    if (!this->_mapDatas._points.second.loadFromFile("./src/ressources/sprites/spritePacman.png"))
        throw arcade::displayer::libSFMLErrors("[SFML] Cannot load texture!", "Texture isn't load!");
    this->_mapDatas._points.first.setTexture(this->_mapDatas._points.second);
    this->_mapDatas._points.first.setTextureRect(rect);
    this->_mapDatas._points.first.setOrigin(this->_mapDatas._points.first.getGlobalBounds().width, this->_mapDatas._points.first.getGlobalBounds().height);
    this->_mapDatas._points.first.scale(1, 1);
}

void arcade::displayer::LibSfml::Game::createDeadEnemy(void)
{
    sf::IntRect rect;

    rect.height = 23.1;
    rect.width = 23.1;
    rect.top = 23.1 * 7;
    rect.left = 0;
    if (!this->_mapDatas._deadEnemy.second.loadFromFile("./src/ressources/sprites/spritePacman.png"))
        throw arcade::displayer::libSFMLErrors("[SFML] Cannot load texture!", "Texture isn't load!");
    this->_mapDatas._deadEnemy.first.setTexture(this->_mapDatas._deadEnemy.second);
    this->_mapDatas._deadEnemy.first.setTextureRect(rect);
    this->_mapDatas._deadEnemy.first.setOrigin(this->_mapDatas._deadEnemy.first.getGlobalBounds().width, this->_mapDatas._deadEnemy.first.getGlobalBounds().height);
    this->_mapDatas._deadEnemy.first.scale(1, 1);
}

void arcade::displayer::LibSfml::Game::createPacmanSprite(void)
{
    std::pair<std::shared_ptr<sf::Sprite>, std::shared_ptr<sf::Texture>> Sptpair;
    sf::IntRect rect;

    rect.height = 23.1;
    rect.width = 23.1;
    rect.top = 0;
    rect.left = 0;
    Sptpair.first = std::make_shared<sf::Sprite>(sf::Sprite());
    Sptpair.second = std::make_shared<sf::Texture>(sf::Texture());
    this->_mapDatas._player.push_back(Sptpair);
    if (!this->_mapDatas._player[this->_mapDatas._player.size() - 1].second->loadFromFile("./src/ressources/sprites/spritePacman.png"))
        throw arcade::displayer::libSFMLErrors("[SFML] Cannot load texture!", "Texture isn't load!");
    this->_mapDatas._player[this->_mapDatas._player.size() - 1].first->setTexture(*this->_mapDatas._player[this->_mapDatas._player.size() - 1].second);
    this->_mapDatas._player[this->_mapDatas._player.size() - 1].first->setTextureRect(rect);
    this->_mapDatas._player[this->_mapDatas._player.size() - 1].first->setOrigin(this->_mapDatas._player[this->_mapDatas._player.size() - 1].first->getGlobalBounds().width, this->_mapDatas._player[this->_mapDatas._player.size() - 1].first->getGlobalBounds().height);
    this->_mapDatas._player[this->_mapDatas._player.size() - 1].first->scale(1.2, 1.2);
}

void arcade::displayer::LibSfml::Game::cleanAllTexture(void)
{
    this->_mapDatas._enemy.clear();
    this->_mapDatas._player.clear();
}

void arcade::displayer::LibSfml::Game::moveAndDrawRect(size_t x, size_t y,
sf::RenderWindow &_win, sf::RectangleShape &rect)
{
    rect.setPosition(x, y);
    _win.draw(rect);
}

void arcade::displayer::LibSfml::Game::moveAndDrawSprite(size_t x, size_t y,
sf::RenderWindow &_win, sf::Sprite &spt)
{
    spt.setPosition(x, y);
    _win.draw(spt);
}

void arcade::displayer::LibSfml::Game::createAllPacman()
{
    std::string infos = "P#oOD";
    std::string enemyType = "VJRB";
    std::vector<std::vector<float>> enemiesTexture = {{23.1, 23.1, 23 * 4.5, 2}, {23.1, 23.1, 23 * 6.27, 2}, {23.1, 23.1, 23 * 3.65, 2}, {23.1, 23.1, 23 * 5.33, 5}};

    this->_mapDatas.infosGames.setFont(this->_font);
    this->_mapDatas.StateGame.setFont(this->_font);
    this->cleanAllTexture();
    for (char information : infos) {
        if (this->_functionsPacman.contains(information))
            (this->*_functionsPacman[information])();
    }
    for (int i = 0; i < 4; i++)
        this->createEnemy(enemiesTexture[i], enemyType[i]);
    this->createDeadEnemy();
}

void arcade::displayer::LibSfml::Game::createAllNibbler()
{
    std::string infos = "FHQ#";

    this->_mapDatas.infosGames.setFont(this->_font);
    this->_mapDatas.StateGame.setFont(this->_font);
    this->cleanAllTexture();
    for (char information : infos) {
        if (this->_functionsNibbler.contains(information))
            (this->*_functionsNibbler[information])();
    }
}

void arcade::displayer::LibSfml::Game::drawEntities(int lineMap, int identifier, sf::RenderWindow &_win)
{
    std::string enemyType = "VJRB";

    for (size_t i = 0; i < 4; i++) {
        if (this->_saveMap[lineMap][identifier] == enemyType[i]) {
            if (this->_mapDatas._enemy.contains(enemyType[i]))
                moveAndDrawSprite((identifier * 30) + 230, (lineMap * 30) + 235, _win, *this->_mapDatas._enemy[enemyType[i]].first);
        }
    }
    if (this->_saveMap[lineMap][identifier] == 'U')
        moveAndDrawSprite((identifier * 30) + 242, (lineMap * 30) + 246, _win, this->_mapDatas._deadEnemy.first);
    if (this->_saveMap[lineMap][identifier] == 'P') {
        if (this->_saveMap.size() > 0) {
            this->_mapDatas.oldPos = this->_mapDatas.newPos;
            this->_mapDatas.newPos = std::make_pair(lineMap, identifier);
            moveAndDrawSprite((identifier * 30) + 242, (lineMap * 30) + 246, _win, *this->_mapDatas._player[0].first);
        }
    }
}

void arcade::displayer::LibSfml::Game::AnimatePacman(void)
{
    sf::Time time = this->_mapDatas.pacmanClk.getElapsedTime();

    if (time.asSeconds() > 0.05) {
        if (this->_mapDatas._player[0].first->getTextureRect().left == 0)
            this->changePacmanMovement(*this->_mapDatas._player[0].first, this->_mapDatas._player[0].first->getTextureRect().top, 23.1);
        else
            this->changePacmanMovement(*this->_mapDatas._player[0].first, this->_mapDatas._player[0].first->getTextureRect().top, 0);
        this->checkKeyMovement(this->_mapDatas.oldPos, this->_mapDatas.newPos);
        this->_mapDatas.pacmanClk.restart();
    }
}

void arcade::displayer::LibSfml::Game::drawGameState(sf::RenderWindow &_win, std::string gameState)
{
    this->_mapDatas.StateGame.setString(gameState);
    this->_mapDatas.StateGame.setCharacterSize(100);
    this->_mapDatas.StateGame.setPosition(500, 500);
    this->_mapDatas.StateGame.setOrigin(this->_mapDatas.StateGame.getGlobalBounds().width / 2, this->_mapDatas.StateGame.getGlobalBounds().height / 2);
    _win.draw(this->_mapDatas.StateGame);
}

void arcade::displayer::LibSfml::Game::drawGameInfos(sf::RenderWindow &_win)
{
    this->_mapDatas.infosGames.setString("SCORE");
    this->_mapDatas.infosGames.setCharacterSize(50);
    this->_mapDatas.infosGames.setPosition(100, 10);
    _win.draw(this->_mapDatas.infosGames);
    if (this->_saveMap.size() > 0) {
        this->_mapDatas.infosGames.setPosition(100, 100);
        this->_mapDatas.infosGames.setCharacterSize(20);
        this->_mapDatas.infosGames.setString(this->_saveMap[0]);
        _win.draw(this->_mapDatas.infosGames);
    }
    this->_mapDatas.infosGames.setString("HEALTH");
    this->_mapDatas.infosGames.setPosition(730, 10);
    this->_mapDatas.infosGames.setCharacterSize(50);
    _win.draw(this->_mapDatas.infosGames);
    if (this->_saveMap.size() > 1) {
        this->_mapDatas.infosGames.setPosition(900, 100);
        this->_mapDatas.infosGames.setCharacterSize(20);
        this->_mapDatas.infosGames.setString(this->_saveMap[1]);
        _win.draw(this->_mapDatas.infosGames);
    }
}

void arcade::displayer::LibSfml::Game::drawPacmanAssets(sf::RenderWindow &_win)
{
    std::string infos = "P#oOD";

    for (size_t lineMap = 2; lineMap < this->_saveMap.size(); lineMap++) {
        for (size_t identifier = 0; identifier < this->_saveMap[lineMap].size(); identifier++) {
            if (this->_saveMap[lineMap][identifier] == 'o')
                moveAndDrawSprite((identifier * 30) + 235, (lineMap * 30) + 246, _win, this->_mapDatas._points.first);
            if (this->_saveMap[lineMap][identifier] == 'O')
                moveAndDrawSprite((identifier * 30) + 242, (lineMap * 30) + 255, _win, this->_mapDatas._bonus.first);
            if (this->_saveMap[lineMap][identifier] == '#')
                moveAndDrawRect((identifier * 30) + 230, (lineMap * 30) + 236, _win, this->_mapDatas._walls);
            if (this->_saveMap[lineMap][identifier] == 'D')
                moveAndDrawRect((identifier * 30) + 230, (lineMap * 30) + 235, _win, this->_mapDatas._doors);
            this->drawEntities(lineMap, identifier, _win);
            if (this->_saveMap[lineMap][identifier] == 'W')
                this->drawGameState(_win, "YOU WIN !!");
            else if (this->_saveMap[lineMap][identifier] == 'X')
                this->drawGameState(_win, "YOU LOOSE !!");
        }
    }
    this->drawGameInfos(_win);
    this->AnimatePacman();
}

void arcade::displayer::LibSfml::Game::drawNibblerAssets(sf::RenderWindow &_win)
{
    for (size_t lineMap = 2; lineMap < this->_saveMap.size(); lineMap++) {
        for (size_t identifier = 0; identifier < this->_saveMap[lineMap].size(); identifier++) {
            if (this->_saveMap[lineMap][identifier] == 'F')
                moveAndDrawSprite((identifier * 30) + 230, (lineMap * 30) + 235, _win, this->_mapDatas._fruits.first);
            if (this->_saveMap[lineMap][identifier] == '#')
                moveAndDrawRect((identifier * 30) + 230, (lineMap * 30) + 236, _win, this->_mapDatas._walls);
            if (this->_saveMap[lineMap][identifier] == 'H')
                moveAndDrawSprite((identifier * 30) + 230, (lineMap * 30) + 235, _win, this->_mapDatas._nibblerHead.first);
            if (this->_saveMap[lineMap][identifier] == 'Q')
                moveAndDrawSprite((identifier * 30) + 230, (lineMap * 30) + 235, _win, this->_mapDatas._nibblerQueue.first);
            if (this->_saveMap[lineMap][identifier] == 'X')
                this->drawGameState(_win, "YOU LOOSE !!");
        }
    }
    this->drawGameInfos(_win);
}

void arcade::displayer::LibSfml::Game::drawGameAssets(sf::RenderWindow &_win, std::string gameName)
{
    if (gameName == "arcade_pacman")
        this->drawPacmanAssets(_win);
    else
        this->drawNibblerAssets(_win);
}

void arcade::displayer::LibSfml::drawGame(std::vector<std::string> map)
{
    this->game.setMap(map);
    this->eventsHandler(arcade::typeDisplay::GAME);
    this->_win.clear(sf::Color::Black);
    this->game.drawGameAssets(this->_win, arcade::displayer::LibSfml::Menu::getGameName(this->_datas.actualGames));
    this->_win.display();
}

void arcade::displayer::LibSfml::Game::changePacmanMovement(sf::Sprite &spt, float rectTop, float rectLeft)
{
    sf::IntRect newRect = spt.getTextureRect();

    newRect.top = rectTop;
    newRect.left = rectLeft;

    spt.setTextureRect(newRect);
}

void arcade::displayer::LibSfml::Game::checkKeyMovement(std::pair<float, float> oldPos, std::pair<float, float> newPos)
{
    std::map<std::pair<float, float>, float> movement = {{{0, 1}, 23.1 * 0.9}, {{1, 0}, 23.1 * 2.6}, {{0, -1}, 0}, {{-1, 0}, 23.1 * 1.8}};
    std::pair<float, float> sub = {newPos.first - oldPos.first, newPos.second - oldPos.second};

    if (movement.contains(sub))
        this->changePacmanMovement(*this->_mapDatas._player[0].first, movement.find(sub)->second, this->_mapDatas._player[0].first->getTextureRect().left);
}

void arcade::displayer::LibSfml::gameKeysHandlers(void)
{
    for (auto it = this->_keysMapping.begin(); it != this->_keysMapping.end(); ++it) {
        if (this->_event.key.code == it->first) {
            this->_keyUse = it->second;
        }
    }
}

void arcade::displayer::LibSfml::Game::setMap(std::vector<std::string> map)
{
    this->_saveMap = map;
}

void arcade::displayer::LibSfml::Game::setNewPos(int x, int y)
{
    this->_mapDatas.newPos = {x, y};
}

void arcade::displayer::LibSfml::destroyWindow(void)
{
    this->_win.close();
}

void arcade::displayer::LibSfml::Game::setFont(sf::Font font)
{
    this->_font = font;
}