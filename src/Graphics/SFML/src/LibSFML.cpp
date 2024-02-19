/*
** EPITECH PROJECT, 2022
** sfml.c
** File description:
** sfml file for Arcade
*/

#include "LibSFML.hpp"
#include "LibSFMLErrors.hpp"
#include <iostream>

extern "C"
{
    std::shared_ptr<arcade::displayer::IDisplayer> entryPoint(void)
    {
        return std::make_shared<arcade::displayer::LibSfml>();
    }
}

arcade::displayer::LibSfml::LibSfml()
{
    this->_win.create(sf::VideoMode(1000, 1000), "Arcade", sf::Style::Close);
    this->_win.setFramerateLimit(30);
    this->_win.setVerticalSyncEnabled(true);
    this->initKeys();
    this->gameChoose = 0;

    if (!this->_font.loadFromFile(DEFAULT_FONT))
        throw libSFMLErrors("[SFML] can't open font!", "Files Error");
    this->menu.setFont(this->_font);
    this->game.setFont(this->_font);
}

arcade::displayer::LibSfml::~LibSfml()
{

}

std::string arcade::displayer::LibSfml::Menu::getGameName(std::string gamePaths)
{
    if (gamePaths.empty())
        return gamePaths;
    std::string gameName = gamePaths.substr(gamePaths.find_last_of('/') + 1);

    gameName = gameName.substr(0, gameName.find('.'));
    return gameName;
}
void arcade::displayer::LibSfml::loadGameAssets(std::string actualGamePath, std::vector<std::string> map)
{
    this->game.setMap(map);
    this->_datas.actualGames = actualGamePath;
    if (arcade::displayer::LibSfml::Menu::getGameName(actualGamePath) == "arcade_pacman")
        this->game.createAllPacman();
    else if (arcade::displayer::LibSfml::Menu::getGameName(actualGamePath) == "arcade_nibbler")
        this->game.createAllNibbler();
}

void arcade::displayer::LibSfml::loadMenuAssets(std::string actualGamePath, std::vector<std::string> gameLibPath,  std::vector<std::string> displayerlibPath)
{
    this->_datas.gameLibs = gameLibPath;
    this->_datas.graphicLibs = displayerlibPath;
    this->_datas.actualGames = actualGamePath;
    this->menu.createAllMenuAssets(actualGamePath, this->_datas);
}

void arcade::displayer::LibSfml::initKeys(void)
{
    sf::Keyboard::Key allKeys[40] = {sf::Keyboard::Key::A, sf::Keyboard::Key::B, sf::Keyboard::Key::C, sf::Keyboard::Key::D, sf::Keyboard::Key::E,
                                     sf::Keyboard::Key::F, sf::Keyboard::Key::G, sf::Keyboard::Key::H, sf::Keyboard::Key::I, sf::Keyboard::Key::J,
                                     sf::Keyboard::Key::K, sf::Keyboard::Key::L, sf::Keyboard::Key::M, sf::Keyboard::Key::N, sf::Keyboard::Key::O,
                                     sf::Keyboard::Key::P, sf::Keyboard::Key::Q, sf::Keyboard::Key::R, sf::Keyboard::Key::S, sf::Keyboard::Key::T, sf::Keyboard::Key::U,
                                     sf::Keyboard::Key::V, sf::Keyboard::Key::W, sf::Keyboard::Key::X, sf::Keyboard::Key::Y, sf::Keyboard::Key::Z,
                                     sf::Keyboard::Key::Right, sf::Keyboard::Key::Up, sf::Keyboard::Key::Down, sf::Keyboard::Key::Left,
                                     sf::Keyboard::Key::Num1, sf::Keyboard::Key::Num2, sf::Keyboard::Key::Num3, sf::Keyboard::Key::Num4, sf::Keyboard::Key::Num5,
                                     sf::Keyboard::Key::Num6, sf::Keyboard::Key::Num7, sf::Keyboard::Key::Num8, sf::Keyboard::Key::Num9, sf::Keyboard::Key::Num0};

    for (size_t keysNumber = 0; keysNumber < 40; keysNumber++)
        this->_keysMapping.insert(std::make_pair(allKeys[keysNumber], (arcade::KeyboardKeys)(keysNumber + 1)));
}

void arcade::displayer::LibSfml::eventsHandler(arcade::typeDisplay typeOfDisplay)
{
    while (this->_win.pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed)
            this->_win.close();
        if (this->_event.type == sf::Event::KeyPressed && typeOfDisplay == arcade::typeDisplay::GAME)
            this->gameKeysHandlers();
        else if (this->_event.type == sf::Event::KeyPressed && typeOfDisplay == arcade::typeDisplay::MENU) {
            this->_keyUse = this->menu.menuKeysHandlers(this->_keysMapping, this->_event);
            this->menu.menuEventsHandlers(this->_keyUse, this->_datas.gameLibs);
        }
        if (this->_event.type == sf::Event::KeyReleased)
            this->_keyUse = arcade::KeyboardKeys::NONE;
    }
}

bool arcade::displayer::LibSfml::isRunning()
{
    return this->_win.isOpen();
}

arcade::KeyboardKeys arcade::displayer::LibSfml::getInput()
{
    return this->_keyUse;
}