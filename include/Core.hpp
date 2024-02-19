/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Core.hpp
*/
#pragma once

#include "ICore.hpp"
#include "IDisplayer.hpp"
#include "IGame.hpp"
#include "Errors.hpp"
#include "DlLoader.hpp"
#include <filesystem>

namespace arcade
{
    namespace core
    {
        typedef std::shared_ptr<arcade::displayer::IDisplayer> sharedDisplayer;
        typedef std::shared_ptr<arcade::game::IGame> sharedGame;
        typedef std::chrono::time_point<std::chrono::system_clock> clockTimePoint;

        enum gameState {
            MENU,
            GAME
        };

        class Core : public arcade::core::ICore
        {
            public:
                Core(std::string displayer);
                ~Core();

                std::shared_ptr<arcade::displayer::IDisplayer> initDisplayer(std::string path);
                std::shared_ptr<arcade::game::IGame> initGame(std::string path);

                std::vector<std::string> scanDisplayers();
                std::vector<std::string> scanGames();

                arcade::KeyboardKeys handleInputs();
                void fillData();
                void update(size_t gameIndex, size_t displayerIndex);
                void start();

                class LibScanner
                {
                    private:
                        std::vector<std::string> gamesPaths;
                        std::vector<std::string> graphicsPaths;

                        std::stringstream fileBuffer;

                        void openFile(std::string filePath);
                        bool checkFilesExtension(std::string filePath);

                    public:
                        std::vector<std::string> getGamesPaths(void);
                        std::vector<std::string> getGraphicsPaths(void);

                        void updateGamesPaths(void);
                        void updateGraphicsPaths(void);
                };

            private:
                bool _isRunning;
                int _gameIndex;
                gameState _state;
                std::vector<sharedDisplayer> _displayers;
                std::vector<sharedGame> _games;
                int _displayerIndex;
                Core::LibScanner _scan;
                arcade::lib::DlLoader loader;

                clockTimePoint displayerClock;

                void computeGame(sharedDisplayer const &displayer, sharedGame const &game, arcade::KeyboardKeys input);
        };
    }
}