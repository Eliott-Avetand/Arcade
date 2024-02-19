/*
** EPITECH PROJECT, 2022
** ncurses.c
** File description:
** ncurses file for Arcade
*/

#include "LibNcurses.hpp"
#include <iostream>

arcade::displayer::ncurses::LibNcurses::NcursesGame::NcursesGame()
{

}

arcade::displayer::ncurses::LibNcurses::NcursesGame::~NcursesGame()
{


}

void arcade::displayer::ncurses::LibNcurses::NcursesGame::setAllWindowsGame(WINDOW *win)
{
    this->_game = this->ncurse.createSubWindow(win, this->ncurse.getWindowMaxY(win), this->ncurse.getWindowMaxX(win) / 2, 0, 0);
    this->_gameScore = this->ncurse.createSubWindow(win, this->ncurse.getWindowMaxY(win) / 2, this->ncurse.getWindowMaxX(win) / 2, 0, this->ncurse.getWindowMaxX(win) / 2);
    this->_gameHealth = this->ncurse.createSubWindow(win, this->ncurse.getWindowMaxY(win) / 2 + 1, this->ncurse.getWindowMaxX(win) / 2, this->ncurse.getWindowMaxY(win) / 2, this->ncurse.getWindowMaxX(win) / 2);
}

void arcade::displayer::ncurses::LibNcurses::NcursesGame::printScore(std::vector<std::string> map)
{
    this->ncurse.printInSubWindow(this->_gameScore, 1, (this->_gameScore->_maxx / 2) - 51 / 2, "  /$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$$  /$$$$$$$$");
    this->ncurse.printInSubWindow(this->_gameScore, 2, (this->_gameScore->_maxx / 2) - 51 / 2, " /$$__  $$ /$$__  $$ /$$__  $$| $$__  $$| $$_____/");
    this->ncurse.printInSubWindow(this->_gameScore, 3, (this->_gameScore->_maxx / 2) - 51 / 2, "| $$  \\__/| $$  \\__/| $$  \\ $$| $$  \\ $$| $$      ");
    this->ncurse.printInSubWindow(this->_gameScore, 4, (this->_gameScore->_maxx / 2) - 51 / 2, "|  $$$$$$ | $$      | $$  | $$| $$$$$$$/| $$$$$   ");
    this->ncurse.printInSubWindow(this->_gameScore, 5, (this->_gameScore->_maxx / 2) - 51 / 2, " \\____  $$| $$      | $$  | $$| $$__  $$| $$__/   ");
    this->ncurse.printInSubWindow(this->_gameScore, 6, (this->_gameScore->_maxx / 2) - 51 / 2, " /$$  \\ $$| $$    $$| $$  | $$| $$  \\ $$| $$      ");
    this->ncurse.printInSubWindow(this->_gameScore, 7, (this->_gameScore->_maxx / 2) - 51 / 2, "|  $$$$$$/|  $$$$$$/|  $$$$$$/| $$  | $$| $$$$$$$$");
    this->ncurse.printInSubWindow(this->_gameScore, 8, (this->_gameScore->_maxx / 2) - 51 / 2, " \\______/  \\______/  \\______/ |__/  |__/|________/");
    if (map.size() > 0)
        this->ncurse.printInSubWindow(this->_gameScore, this->_gameScore->_maxy / 2, (this->_gameScore->_maxx / 2) - (map[0].length() / 2), map[0]);
    this->ncurse.drawBox(this->_gameScore, '*', '*');
}

void arcade::displayer::ncurses::LibNcurses::NcursesGame::printHealth(std::vector<std::string> map)
{
    this->ncurse.printInSubWindow(this->_gameHealth, 1, (this->_gameHealth->_maxx / 2) - 58 / 2, " /$$   /$$ /$$$$$$$$  /$$$$$$  /$$    /$$$$$$$$ /$$   /$$");
    this->ncurse.printInSubWindow(this->_gameHealth, 2, (this->_gameHealth->_maxx / 2) - 58 / 2, "| $$  | $$| $$_____/ /$$__  $$| $$   |__  $$__/| $$  | $$");
    this->ncurse.printInSubWindow(this->_gameHealth, 3, (this->_gameHealth->_maxx / 2) - 58 / 2, "| $$  | $$| $$      | $$  \\ $$| $$      | $$   | $$  | $$");
    this->ncurse.printInSubWindow(this->_gameHealth, 4, (this->_gameHealth->_maxx / 2) - 58 / 2, "| $$$$$$$$| $$$$$   | $$$$$$$$| $$      | $$   | $$$$$$$$");
    this->ncurse.printInSubWindow(this->_gameHealth, 5, (this->_gameHealth->_maxx / 2) - 58 / 2, "| $$__  $$| $$__/   | $$__  $$| $$      | $$   | $$__  $$");
    this->ncurse.printInSubWindow(this->_gameHealth, 6, (this->_gameHealth->_maxx / 2) - 58 / 2, "| $$  | $$| $$      | $$  | $$| $$      | $$   | $$  | $$");
    this->ncurse.printInSubWindow(this->_gameHealth, 7, (this->_gameHealth->_maxx / 2) - 58 / 2, "| $$  | $$| $$$$$$$$| $$  | $$| $$$$$$$$| $$   | $$  | $$");
    this->ncurse.printInSubWindow(this->_gameHealth, 8, (this->_gameHealth->_maxx / 2) - 58 / 2, "|__/  |__/|________/|__/  |__/|________/|__/   |__/  |__/");
    if (map.size() > 1)
        this->ncurse.printInSubWindow(this->_gameHealth, this->_gameHealth->_maxy / 2, (this->_gameHealth->_maxx / 2) - (map[1].length() / 2), map[1]);
    this->ncurse.drawBox(this->_gameHealth, '*', '*');
}

void arcade::displayer::ncurses::LibNcurses::NcursesGame::printGame(std::vector<std::string> map)
{
    if (map.size() > 2) {
        for (size_t line = 2; line < map.size(); line++)
            this->ncurse.printInSubWindow(this->_game, (this->_game->_maxy / 2) + (line - 2), (this->_game->_maxx / 2) - (map[line].length() / 2), map[line]);
    }
    this->ncurse.drawBox(this->_game, '*', '*');
}

void arcade::displayer::ncurses::LibNcurses::NcursesGame::refreshAllWindows(void)
{
    this->ncurse.refreshSubWindow(this->_game);
    this->ncurse.refreshSubWindow(this->_gameHealth);
    this->ncurse.refreshSubWindow(this->_gameScore);
}

void arcade::displayer::ncurses::LibNcurses::NcursesGame::clearAllWindows(void)
{
    this->ncurse.clearSubWindow(this->_game);
    this->ncurse.clearSubWindow(this->_gameHealth);
    this->ncurse.clearSubWindow(this->_gameScore);
}
