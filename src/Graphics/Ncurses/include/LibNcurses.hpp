/*
** EPITECH PROJECT, 2022
** libNcurses.hpp
** File description:
** libNcurses.hpp file for Arcade
*/

#pragma once

#include <memory>
#include <ncurses.h>
#include <map>
#include "IDisplayer.hpp"

#define PACMAN_PAIR 1
#define PINK_PAIR 2
#define CYAN_PAIR 3
#define YELLOW_PAIR 4
#define RED_PAIR 5
#define BLUE_PAIR 6

namespace arcade {

    namespace displayer {

        namespace ncurses {

            class Ncurses {
                private:
                    bool isOpen;

                public:
                    Ncurses();
                    ~Ncurses();
                    void initScreen(void);
                    WINDOW *createWindow(int width, int height, int starty, int end);
                    WINDOW *createSubWindow(WINDOW *_win, int height, int width, int x, int y);
                    void stopWindow(void);
                    void deleteSubWindow(WINDOW *_win);
                    void refreshWindow(void);
                    void refreshSubWindow(WINDOW *_win);
                    void clearWindow(void);
                    void clearSubWindow(WINDOW *_win);
                    int getWindowInput(void);
                    void printInSubWindow(WINDOW *_win, int y, int x, std::string str);
                    bool windowIsOpen(void);
                    int getWindowMaxX(WINDOW *win);
                    int getWindowMaxY(WINDOW *win);
                    void drawBox(WINDOW *win, char lrSide, char tdSide);
                    int getWindowInput(WINDOW *win);
                    void init_a_color_pair(short index, short foreground, short background);
                    void setNoDelay(WINDOW *win, bool active);

            };
            class LibNcurses : public arcade::displayer::IDisplayer {
                class NcursesMenu {
                    private:
                        Ncurses ncurse;
                        WINDOW *_gameWin;
                        WINDOW *_graphicsWin;
                        WINDOW *_keyWin;
                        WINDOW *_titleWin;
                        size_t _actualGame;

                        void printAllGraphicsLibs(std::vector<std::string> displayersPaths);
                        void printAllGamesLibs(std::vector<std::string> gamesPaths);
                        std::string getGameName(std::string gamePaths);
                    public:
                        NcursesMenu();
                        ~NcursesMenu();
                        void setAllWindowsMenu(WINDOW *_win);
                        void refreshAllWindows(void);
                        void clearAllWindows(void);
                        WINDOW *getGameWin(void);
                        WINDOW *getGraphicsWin(void);
                        WINDOW *getKeyWin(void);
                        WINDOW *getTitleWin(void);
                        void setGameWin(WINDOW *_win);
                        void setGraphicsWin(WINDOW *_win);
                        void setKeyWin(WINDOW *_win);
                        void setTitleWin(WINDOW *_win);
                        void printTitle(void);
                        void printMenuGame(std::vector<std::string> gamesPaths);
                        void printMenuGraphics(std::vector<std::string> displayersPaths);
                        void changeActualGame(arcade::KeyboardKeys key, std::vector<std::string> gamesPaths);
                };
                class NcursesGame {
                    private:
                        Ncurses ncurse;
                        WINDOW *_game;
                        WINDOW *_gameScore;
                        WINDOW *_gameHealth;
                    public:
                        NcursesGame();
                        ~NcursesGame();
                        void setAllWindowsGame(WINDOW *win);
                        void printGame(std::vector<std::string> map);
                        void refreshAllWindows(void);
                        void clearAllWindows(void);
                        void printScore(std::vector<std::string> map);
                        void printHealth(std::vector<std::string> map);
                };

                private:
                    Ncurses ncurse;
                    NcursesMenu menu;
                    NcursesGame game;
                    WINDOW *_mainWin;
                    std::map<int, arcade::KeyboardKeys> _keysMapping;
                    arcade::KeyboardKeys _keyUse;

                    void initKeys(void);
                    void setKeys(int input);
                public:
                    LibNcurses();
                    ~LibNcurses();
                    void drawMenu(std::vector<std::string> gamesPaths, std::vector<std::string> displayersPaths);
                    void drawGame(std::vector<std::string> map);

                    void loadMenuAssets(std::string actualGamePath, std::vector<std::string> gameLibPath, std::vector<std::string> displayerlibPath);
                    void loadGameAssets(std::string actualGamePath, std::vector<std::string> map);
                    bool isRunning();

                    void destroyWindow(void);

                    KeyboardKeys getInput();

            };
        }
    }
}