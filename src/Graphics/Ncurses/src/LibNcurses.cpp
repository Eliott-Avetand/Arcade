/*
** EPITECH PROJECT, 2022
** ncurses.c
** File description:
** ncurses file for Arcade
*/

#include "LibNcurses.hpp"
#include <iostream>

extern "C"
{
    std::shared_ptr<arcade::displayer::IDisplayer> entryPoint(void)
    {
        return std::make_shared<arcade::displayer::ncurses::LibNcurses>();
    }
}

arcade::displayer::ncurses::LibNcurses::LibNcurses()
{
    this->ncurse.initScreen();
    this->_mainWin = this->ncurse.createWindow(this->ncurse.getWindowMaxY(stdscr), this->ncurse.getWindowMaxX(stdscr), 0, 0);
    if (!this->_mainWin)
        std::cout << "dsqdqs" << std::endl;
    this->initKeys();
    this->ncurse.setNoDelay(this->_mainWin, true);

    this->menu.setAllWindowsMenu(this->_mainWin);
    this->game.setAllWindowsGame(this->_mainWin);
    this->ncurse.init_a_color_pair(PACMAN_PAIR, COLOR_YELLOW, COLOR_YELLOW);
}

arcade::displayer::ncurses::LibNcurses::~LibNcurses()
{
    // void
}

void arcade::displayer::ncurses::LibNcurses::initKeys(void)
{
    int allKeys[40] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                      'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
                      'y', 'z', 'C', 'A', 'B', 'D','1', '2', '3', '4', '5', '6', '7', '8',
                      '9', '0'};

    for (size_t keysNumber = 0; keysNumber < 40; keysNumber++)
        this->_keysMapping.insert(std::make_pair(allKeys[keysNumber], (arcade::KeyboardKeys)(keysNumber + 1)));
}

void arcade::displayer::ncurses::LibNcurses::setKeys(int input)
{
    if (input == '\033')
        input = getch();
    for (auto it = this->_keysMapping.begin(); it != this->_keysMapping.end(); ++it) {
        if (input == it->first)
            this->_keyUse = it->second;
    }
}

void arcade::displayer::ncurses::LibNcurses::drawMenu(std::vector<std::string> gamesPaths, std::vector<std::string> displayersPaths)
{
    this->ncurse.clearSubWindow(this->_mainWin);
    this->menu.clearAllWindows();
    this->menu.printMenuGame(gamesPaths);
    this->menu.printMenuGraphics(displayersPaths);
    this->menu.printTitle();
    this->ncurse.refreshSubWindow(this->_mainWin);
    this->menu.refreshAllWindows();
    this->ncurse.refreshWindow();
    this->setKeys(this->ncurse.getWindowInput(this->_mainWin));
    this->menu.changeActualGame(this->_keyUse, gamesPaths);
}

void arcade::displayer::ncurses::LibNcurses::drawGame(std::vector<std::string> map)
{
    this->ncurse.clearSubWindow(this->_mainWin);
    this->game.clearAllWindows();
    this->game.printGame(map);
    this->game.printScore(map);
    this->game.printHealth(map);
    this->game.refreshAllWindows();
    this->ncurse.refreshSubWindow(this->_mainWin);
    this->setKeys(this->ncurse.getWindowInput(this->_mainWin));
}

void arcade::displayer::ncurses::LibNcurses::loadMenuAssets(std::string actualGamePath, std::vector<std::string> gameLibPath, std::vector<std::string> displayerlibPath)
{
    (void)actualGamePath;
    (void)gameLibPath;
    (void)displayerlibPath;
}

void arcade::displayer::ncurses::LibNcurses::loadGameAssets(std::string actualGamePath, std::vector<std::string> map)
{
    (void)actualGamePath;
    (void)map;
}

bool arcade::displayer::ncurses::LibNcurses::isRunning()
{
    return this->ncurse.windowIsOpen();
}

void arcade::displayer::ncurses::LibNcurses::destroyWindow(void)
{
    // void
}

arcade::KeyboardKeys arcade::displayer::ncurses::LibNcurses::getInput(void)
{
    return this->_keyUse;
}