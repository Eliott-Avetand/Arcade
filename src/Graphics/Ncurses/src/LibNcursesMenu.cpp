/*
** EPITECH PROJECT, 2022
** ncurses.c
** File description:
** ncurses file for Arcade
*/

#include "LibNcurses.hpp"
#include <iostream>

arcade::displayer::ncurses::LibNcurses::NcursesMenu::NcursesMenu()
{
    this->_actualGame = 0;
}

arcade::displayer::ncurses::LibNcurses::NcursesMenu::~NcursesMenu()
{
    // void
}

std::string arcade::displayer::ncurses::LibNcurses::NcursesMenu::getGameName(std::string gamePaths)
{
    std::string gameName = gamePaths.substr(gamePaths.find_last_of('/') + 1);

    gameName = gameName.substr(0, gameName.find('.'));
    return gameName;
}

void arcade::displayer::ncurses::LibNcurses::NcursesMenu::setAllWindowsMenu(WINDOW *win)
{
    this->_titleWin = this->ncurse.createSubWindow(win, 14, this->ncurse.getWindowMaxX(win), 0, 0);
    if (!this->_titleWin) {
        std::cout << "dsdsds" << std::endl;
    }
    this->_gameWin = this->ncurse.createSubWindow(win, this->ncurse.getWindowMaxY(win) - 14, this->ncurse.getWindowMaxX(win) / 2, 13, 0);
    if (!this->_gameWin) {
        std::cout << "dsdsds" << std::endl;
    }
    this->_graphicsWin = this->ncurse.createSubWindow(win, this->ncurse.getWindowMaxY(win) - 14, this->ncurse.getWindowMaxX(win) / 2 , 13, (this->ncurse.getWindowMaxX(win) / 2));
    if (!this->_graphicsWin) {
        std::cout << "dsdsds" << std::endl;
    }
}

void arcade::displayer::ncurses::LibNcurses::NcursesMenu::changeActualGame(arcade::KeyboardKeys key, std::vector<std::string> gamesPaths)
{

    if (key == arcade::KeyboardKeys::ARROW_U) {
        if (this->_actualGame < gamesPaths.size() - 1)
            this->_actualGame++;
        else
            this->_actualGame = 0;
    }
    if (key == arcade::KeyboardKeys::ARROW_D) {
        if (this->_actualGame > 0)
            this->_actualGame--;
        else
            this->_actualGame = (gamesPaths.size() - 1);
    }
}

void arcade::displayer::ncurses::LibNcurses::NcursesMenu::refreshAllWindows(void)
{
    this->ncurse.refreshSubWindow(this->_titleWin);
    this->ncurse.refreshSubWindow(this->_gameWin);
    this->ncurse.refreshSubWindow(this->_graphicsWin);
}

void arcade::displayer::ncurses::LibNcurses::NcursesMenu::clearAllWindows(void)
{
    this->ncurse.clearSubWindow(this->_titleWin);
    this->ncurse.clearSubWindow(this->_gameWin);
    this->ncurse.clearSubWindow(this->_graphicsWin);
}

void arcade::displayer::ncurses::LibNcurses::NcursesMenu::printAllGraphicsLibs(std::vector<std::string> displayersPaths)
{
    int i = 1;

    for (size_t displayNumber = 0; displayNumber < displayersPaths.size(); displayNumber++) {
        if (displayersPaths[displayNumber] == "./lib/arcade_ncurses.so")
            this->ncurse.printInSubWindow(this->_graphicsWin, (i * 2) + 10, 27, ">> " + this->getGameName(displayersPaths[displayNumber]));
        else
            this->ncurse.printInSubWindow(this->_graphicsWin, (i * 2) + 10, 30, this->getGameName(displayersPaths[displayNumber]));
        if (i <= 2)
            i++;
        else
            i = 1;
    }
}

void arcade::displayer::ncurses::LibNcurses::NcursesMenu::printAllGamesLibs(std::vector<std::string> gamesPaths)
{
    int i = 1;

    for (size_t gamesNumber = 0; gamesNumber < gamesPaths.size(); gamesNumber++) {
        if (this->_actualGame == gamesNumber)
            this->ncurse.printInSubWindow(this->_gameWin, (i * 2) + 10, 27, ">> " + this->getGameName(gamesPaths[gamesNumber]));
        else
            this->ncurse.printInSubWindow(this->_gameWin, (i * 2) + 10, 30, this->getGameName(gamesPaths[gamesNumber]));
        if (i <= 2)
            i++;
        else
            i = 1;
    }
}

void arcade::displayer::ncurses::LibNcurses::NcursesMenu::printMenuGraphics(std::vector<std::string> displayersPaths)
{
    this->ncurse.printInSubWindow(this->_graphicsWin, 1, (this->ncurse.getWindowMaxX(this->_graphicsWin) / 2) - 68 / 2, " $$$$$$\\  $$$$$$$\\   $$$$$$\\  $$$$$$$\\  $$\\   $$\\ $$$$$$\\  $$$$$$\\ ");
    this->ncurse.printInSubWindow(this->_graphicsWin, 2, (this->ncurse.getWindowMaxX(this->_graphicsWin) / 2) - 68 / 2, "$$  __$$\\  $$  __$$\\ $$  __$$\\ $$  __$$\\ $$ |  $$ |\\_$$  _|$$  __$$\\ ");
    this->ncurse.printInSubWindow(this->_graphicsWin, 3, (this->ncurse.getWindowMaxX(this->_graphicsWin) / 2) - 68 / 2, "$$ /  \\__|$$ |  $$ |$$ /  $$ |$$ |  $$ |$$ |  $$ |  $$ |  $$ /  \\__|");
    this->ncurse.printInSubWindow(this->_graphicsWin, 4, (this->ncurse.getWindowMaxX(this->_graphicsWin) / 2) - 68 / 2, "$$ |$$$$\\ $$$$$$$  |$$$$$$$$ |$$$$$$$  |$$$$$$$$ |  $$ |  $$ |      ");
    this->ncurse.printInSubWindow(this->_graphicsWin, 5, (this->ncurse.getWindowMaxX(this->_graphicsWin) / 2) - 68 / 2, "$$ |\\_$$ |$$  __$$< $$  __$$ |$$  ____/ $$  __$$ |  $$ |  $$ |      ");
    this->ncurse.printInSubWindow(this->_graphicsWin, 6, (this->ncurse.getWindowMaxX(this->_graphicsWin) / 2) - 68 / 2, "$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |      $$ |  $$ |  $$ |  $$ |  $$\\ ");
    this->ncurse.printInSubWindow(this->_graphicsWin, 7, (this->ncurse.getWindowMaxX(this->_graphicsWin) / 2) - 68 / 2, "\\$$$$$$  |$$ |  $$ |$$ |  $$ |$$ |      $$ |  $$ |$$$$$$\\ \\$$$$$$  |");
    this->ncurse.printInSubWindow(this->_graphicsWin, 8, (this->ncurse.getWindowMaxX(this->_graphicsWin) / 2) - 68 / 2, "  \\______/ \\__|  \\__|\\__|  \\__|\\__|      \\__|  \\__|\\______| \\______/");
    this->printAllGraphicsLibs(displayersPaths);
    this->ncurse.drawBox(this->_graphicsWin, '*', '*');
}

void arcade::displayer::ncurses::LibNcurses::NcursesMenu::printMenuGame(std::vector<std::string> gamesPaths)
{
    (void)gamesPaths;
    this->ncurse.printInSubWindow(this->_gameWin, 1, (this->ncurse.getWindowMaxX(this->_gameWin) / 2) - 54 / 2, "  /$$$$$$   /$$$$$$  /$$      /$$ /$$$$$$$$  /$$$$$$ ");
    this->ncurse.printInSubWindow(this->_gameWin, 2, (this->ncurse.getWindowMaxX(this->_gameWin) / 2) - 54 / 2, " /$$__  $$ /$$__  $$| $$$    /$$$| $$_____/ /$$__  $$");
    this->ncurse.printInSubWindow(this->_gameWin, 3, (this->ncurse.getWindowMaxX(this->_gameWin) / 2) - 54 / 2, "| $$  \\__/| $$  \\ $$| $$$$  /$$$$| $$      | $$  \\__/");
    this->ncurse.printInSubWindow(this->_gameWin, 4, (this->ncurse.getWindowMaxX(this->_gameWin) / 2) - 54 / 2, "| $$ /$$$$| $$$$$$$$| $$ $$/$$ $$| $$$$$   |  $$$$$$ ");
    this->ncurse.printInSubWindow(this->_gameWin, 5, (this->ncurse.getWindowMaxX(this->_gameWin) / 2) - 54 / 2, "| $$|_  $$| $$__  $$| $$  $$$| $$| $$__/    \\____  $$");
    this->ncurse.printInSubWindow(this->_gameWin, 6, (this->ncurse.getWindowMaxX(this->_gameWin) / 2) - 54 / 2, "| $$  \\ $$| $$  | $$| $$\\  $ | $$| $$       /$$  \\ $$");
    this->ncurse.printInSubWindow(this->_gameWin, 7, (this->ncurse.getWindowMaxX(this->_gameWin) / 2) - 54 / 2, "|  $$$$$$/| $$  | $$| $$ \\/  | $$| $$$$$$$$|  $$$$$$/");
    this->ncurse.printInSubWindow(this->_gameWin, 8, (this->ncurse.getWindowMaxX(this->_gameWin) / 2) - 54 / 2, " \\______/ |__/  |__/|__/     |__/|________/ \\______/ ");
    this->printAllGamesLibs(gamesPaths);
    this->ncurse.drawBox(this->_gameWin, '*', '*');
}

void arcade::displayer::ncurses::LibNcurses::NcursesMenu::printTitle(void)
{
    this->ncurse.printInSubWindow(this->_titleWin, 14 / 2 - 4, (this->ncurse.getWindowMaxX(this->_titleWin) / 2) - 22, " /$$      /$$ /$$$$$$$$ /$$   /$$ /$$   /$$");
    this->ncurse.printInSubWindow(this->_titleWin, 14 / 2 - 3, (this->ncurse.getWindowMaxX(this->_titleWin) / 2) - 22, "| $$$    /$$$| $$_____/| $$$ | $$| $$  | $$");
    this->ncurse.printInSubWindow(this->_titleWin, 14 / 2 - 2, (this->ncurse.getWindowMaxX(this->_titleWin) / 2) - 22, "| $$$$  /$$$$| $$      | $$$$| $$| $$  | $$");
    this->ncurse.printInSubWindow(this->_titleWin, 14 / 2 - 1, (this->ncurse.getWindowMaxX(this->_titleWin) / 2) - 22, "| $$ $$/$$ $$| $$$$$   | $$ $$ $$| $$  | $$");
    this->ncurse.printInSubWindow(this->_titleWin, 14 / 2 + 0, (this->ncurse.getWindowMaxX(this->_titleWin) / 2) - 22, "| $$  $$$| $$| $$__/   | $$  $$$$| $$  | $$");
    this->ncurse.printInSubWindow(this->_titleWin, 14 / 2 + 1, (this->ncurse.getWindowMaxX(this->_titleWin) / 2) - 22, "| $$\\  $ | $$| $$      | $$\\  $$$| $$  | $$");
    this->ncurse.printInSubWindow(this->_titleWin, 14 / 2 + 2, (this->ncurse.getWindowMaxX(this->_titleWin) / 2) - 22, "| $$ \\/  | $$| $$$$$$$$| $$ \\  $$|  $$$$$$/");
    this->ncurse.printInSubWindow(this->_titleWin, 14 / 2 + 3, (this->ncurse.getWindowMaxX(this->_titleWin) / 2) - 22, "|__/     |__/|________/|__/  \\__/ \\______/ ");
    this->ncurse.drawBox(this->_titleWin, '*', '*');
}

WINDOW *arcade::displayer::ncurses::LibNcurses::NcursesMenu::getGameWin(void)
{
    return this->_gameWin;
}

WINDOW *arcade::displayer::ncurses::LibNcurses::NcursesMenu::getGraphicsWin(void)
{
    return this->_graphicsWin;
}

WINDOW *arcade::displayer::ncurses::LibNcurses::NcursesMenu::getKeyWin(void)
{
    return this->_keyWin;
}

WINDOW *arcade::displayer::ncurses::LibNcurses::NcursesMenu::getTitleWin(void)
{
    return this->_titleWin;
}

void arcade::displayer::ncurses::LibNcurses::NcursesMenu::setKeyWin(WINDOW *_win)
{
    this->_keyWin = _win;
}

void arcade::displayer::ncurses::LibNcurses::NcursesMenu::setGameWin(WINDOW *_win)
{
    this->_gameWin = _win;
}

void arcade::displayer::ncurses::LibNcurses::NcursesMenu::setGraphicsWin(WINDOW *_win)
{
    this->_graphicsWin = _win;
}

void arcade::displayer::ncurses::LibNcurses::NcursesMenu::setTitleWin(WINDOW *_win)
{
    this->_titleWin = _win;
}