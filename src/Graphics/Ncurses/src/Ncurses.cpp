/*
** EPITECH PROJECT, 2022
** ncurses.cpp
** File description:
** ncurses file for Arcade
*/

#include "LibNcurses.hpp"

extern "C" {
    arcade::displayer::ncurses::Ncurses::Ncurses()
    {
        this->isOpen = true;
    }
    arcade::displayer::ncurses::Ncurses::~Ncurses()
    {
        // void
    }
    void arcade::displayer::ncurses::Ncurses::initScreen()
    {
        initscr();
        noecho();
        cbreak();
    }

    void arcade::displayer::ncurses::Ncurses::setNoDelay(WINDOW *win, bool active)
    {
        nodelay(win, active);
    }

    void arcade::displayer::ncurses::Ncurses::init_a_color_pair(short index, short foreground, short background)
    {
        init_pair(index, foreground, background);
    }

    WINDOW *arcade::displayer::ncurses::Ncurses::createWindow(int height, int width, int starty, int end)
    {
        WINDOW *win = newwin(height, width, starty, end);

        refresh();
        return win;
    }

    WINDOW *arcade::displayer::ncurses::Ncurses::createSubWindow(WINDOW *_win, int height, int width, int x, int y)
    {
        WINDOW *win = subwin(_win, height, width, x, y);

        refresh();
        return win;
    }

    void arcade::displayer::ncurses::Ncurses::stopWindow(void)
    {
        endwin();
        this->isOpen = false;
    }

    void arcade::displayer::ncurses::Ncurses::deleteSubWindow(WINDOW *_win)
    {
        delwin(_win);
    }

    void arcade::displayer::ncurses::Ncurses::refreshWindow(void)
    {
        refresh();
    }

    void arcade::displayer::ncurses::Ncurses::refreshSubWindow(WINDOW *_win)
    {
        wrefresh(_win);
    }
    void arcade::displayer::ncurses::Ncurses::clearWindow()
    {
        clear();
    }

    void arcade::displayer::ncurses::Ncurses::clearSubWindow(WINDOW *_win)
    {
        wclear(_win);
    }

    int arcade::displayer::ncurses::Ncurses::getWindowInput(void)
    {
        return getch();
    }

    void arcade::displayer::ncurses::Ncurses::printInSubWindow(WINDOW *_win, int x, int y, std::string str)
    {
        mvwprintw(_win, x, y, str.c_str());
    }

    bool arcade::displayer::ncurses::Ncurses::windowIsOpen(void)
    {
        return this->isOpen;
    }

    int arcade::displayer::ncurses::Ncurses::getWindowMaxX(WINDOW *win)
    {
        return getmaxx(win);
    }

    int arcade::displayer::ncurses::Ncurses::getWindowMaxY(WINDOW *win)
    {
        return getmaxy(win);
    }

    void arcade::displayer::ncurses::Ncurses::drawBox(WINDOW *win, char lrSide, char tdSide)
    {
        box(win, lrSide, tdSide);
    }

    int arcade::displayer::ncurses::Ncurses::getWindowInput(WINDOW *win)
    {
        return wgetch(win);
    }
}
