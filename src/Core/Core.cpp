/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Core.hpp
*/

#include <iostream>
#include "Core.hpp"

#include <chrono>
#include <thread>

arcade::core::Core::Core(std::string path) {
    this->_isRunning = true;
    this->_gameIndex = 0;
    this->_displayerIndex = 0;
    this->_state = arcade::core::gameState::MENU;
    this->_displayers.push_back(this->initDisplayer(path));
    this->displayerClock = std::chrono::system_clock::now();
    this->start();
}

arcade::core::Core::~Core()
{
    for (std::shared_ptr<arcade::displayer::IDisplayer> &d : this->_displayers)
        d.reset();
    for (std::shared_ptr<arcade::game::IGame> &g : this->_games)
        g.reset();
    this->loader.destroyAllLibs();
}

std::shared_ptr<arcade::displayer::IDisplayer> arcade::core::Core::initDisplayer(std::string path)
{
    std::shared_ptr<arcade::displayer::IDisplayer> loaderSave;
    if (path.find("sfml", 0) != std::size_t(-1) ||
    path.find("ncurses", 0) != std::size_t(-1) || path.find("sdl2", 0) != std::size_t(-1)) {
        loaderSave = loader.getLibInstance<arcade::displayer::IDisplayer>(path);
    } else
        exit(84);
    if (loaderSave == nullptr)
        exit(84);
    return loaderSave;
}

std::shared_ptr<arcade::game::IGame> arcade::core::Core::initGame(std::string path)
{
    std::shared_ptr<arcade::game::IGame> loaderSave;

    if (path.find("pacman", 0) != std::size_t(-1) ||
    path.find("nibbler", 0) != std::size_t(-1)) {
        loaderSave = loader.getLibInstance<arcade::game::IGame>(path);
    } else
        exit(84);
    if (loaderSave == nullptr)
        exit(84);
    return loaderSave;
}

void arcade::core::Core::update(size_t gameIndex, size_t displayerIndex)
{
    this->_gameIndex = gameIndex;
    this->_displayerIndex = displayerIndex;
}

std::vector<std::string> arcade::core::Core::scanGames()
{
    try {
        this->_scan.updateGamesPaths();
    } catch (LibScannerError const &error) {
        std::cerr << error.what() << std::endl;
    }
    return this->_scan.getGamesPaths();
}

std::vector<std::string> arcade::core::Core::scanDisplayers()
{
    try {
        this->_scan.updateGraphicsPaths();
    } catch (LibScannerError const &error) {
        std::cerr << error.what() << std::endl;
    }
    return this->_scan.getGraphicsPaths();
}

arcade::KeyboardKeys arcade::core::Core::handleInputs()
{
    arcade::KeyboardKeys input = this->_displayers[this->_displayerIndex]->getInput();

    switch (input) {
        case arcade::ARROW_R:
            this->_scan.updateGamesPaths();
            this->_games.clear();
            for (size_t i = 0; i < this->_scan.getGamesPaths().size(); i++)
                this->_games.push_back(this->initGame(this->_scan.getGamesPaths()[i]));
            this->_gameIndex = (this->_gameIndex + 1) >= int(this->_games.size()) ? 0 : this->_gameIndex + 1;
            break;
        case arcade::ARROW_L:
            this->_scan.updateGamesPaths();
            this->_games.clear();
            for (size_t i = 0; i < this->_scan.getGamesPaths().size(); i++)
                this->_games.push_back(this->initGame(this->_scan.getGamesPaths()[i]));
            this->_gameIndex = (this->_gameIndex - 1) < 0 ? this->_games.size() - 1 : this->_gameIndex - 1;
            break;
        case arcade::ARROW_U:
            this->_scan.updateGraphicsPaths();
            this->_displayers.clear();
            for (size_t i = 0; i < this->_scan.getGraphicsPaths().size(); i++)
                this->_displayers.push_back(this->initDisplayer(this->_scan.getGraphicsPaths()[i]));
            this->_displayerIndex = (this->_displayerIndex + 1) >= int(this->_displayers.size()) ? 0 : this->_displayerIndex + 1;
            break;
        case arcade::ARROW_D:
            this->_scan.updateGraphicsPaths();
            this->_displayers.clear();
            for (size_t i = 0; i < this->_scan.getGraphicsPaths().size(); i++)
                this->_displayers.push_back(this->initDisplayer(this->_scan.getGraphicsPaths()[i]));
            this->_displayerIndex = (this->_displayerIndex - 1) < 0 ? this->_displayers.size() - 1 : this->_displayerIndex - 1;
            break;
        case arcade::KEY_L:
            this->_state = arcade::core::GAME;
            this->_displayers[_displayerIndex]->loadGameAssets(this->scanGames()[this->_gameIndex],
            this->_games[this->_gameIndex]->getDatas());
            break;
        case arcade::KEY_A:
            this->_scan.updateGamesPaths();
            this->_scan.updateGraphicsPaths();
            this->_state = arcade::core::MENU;
            this->_displayers[_displayerIndex]->loadMenuAssets(this->scanGames()[this->_gameIndex], this->scanGames(),
            this->_scan.getGraphicsPaths());
            break;
        default:
            break;
    }
    return input;
}

void arcade::core::Core::fillData()
{
    //Void
}

void arcade::core::Core::start()
{
    std::shared_ptr<arcade::displayer::IDisplayer> const &displayer = this->_displayers[this->_displayerIndex];
    std::vector<std::string> gamesPaths = this->scanGames();
    std::string actualGamePath = (gamesPaths.size() == 0) ? std::string() : gamesPaths[this->_gameIndex];
    arcade::KeyboardKeys input;

    this->_scan.updateGamesPaths();
    this->_games.clear();
    for (size_t i = 0; i < this->_scan.getGamesPaths().size(); i++)
        this->_games.push_back(this->initGame(this->_scan.getGamesPaths()[i]));

    displayer->loadMenuAssets(actualGamePath, gamesPaths, this->_scan.getGraphicsPaths());

    while (this->_displayers[this->_displayerIndex]->isRunning()) {
        arcade::core::clockTimePoint now = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsedTime = now - this->displayerClock;

        input = this->handleInputs();
        if (elapsedTime > std::chrono::milliseconds(1000 / 10)) {
            if (this->_state == arcade::core::MENU) {
                this->_displayers[this->_displayerIndex]->drawMenu(this->_scan.getGamesPaths(), this->_scan.getGraphicsPaths());
            } else
                this->computeGame(this->_displayers[this->_displayerIndex], this->_games[this->_gameIndex], input);
            this->displayerClock = now;
        }
    }
}

void arcade::core::Core::computeGame(arcade::core::sharedDisplayer const &displayer,
arcade::core::sharedGame const &game, arcade::KeyboardKeys input)
{
    game->setInput(input);
    game->update();
    displayer->drawGame(game->getDatas());
}