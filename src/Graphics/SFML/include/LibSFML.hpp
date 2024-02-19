/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Sfml.hpp
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <map>
#include <vector>
#include "IDisplayer.hpp"

#define DEFAULT_FONT "./src/Graphics/SFML/menu/fonts/default.ttf"
#define DEFAULT_JACKET "./src/Graphics/SFML/menu/sprites/DefaultJackets.jpg"
#define BACKGROUND_MENU "./src/Graphics/SFML/menu/sprites/BackgroundMenu.jpg"
namespace arcade
{
    enum typeDisplay {
        MENU,
        GAME
    };
    namespace displayer
    {
        struct savedDatas {
            std::vector<std::string> gameLibs;
            std::vector<std::string> graphicLibs;
            std::string actualGames;
        };

        class LibSfml : public arcade::displayer::IDisplayer
        {

            enum Direction {
                UP,
                RIGHT,
                DOWN,
                LEFT
            };
            class Menu {
                private:
                    sf::Font _font;
                    size_t gameNbr;
                    bool _alreadyLoad;

                    void createMenuGames(std::vector<std::string> gamesPaths);
                    void createMenuGraphicsLibs(std::vector<std::string> displayersPaths);
                    void createMenuJackets(std::string gameName, arcade::displayer::savedDatas _datas);
                    void createArcadeTitle(void);
                    void createMenuBackground(void);
                    void createMenuInfos(void);
                public:
                    std::vector<std::pair<sf::Sprite, sf::Texture>> gamesJacketsSpt;
                    std::vector<sf::Text> gamesLibsText;
                    std::vector<sf::Text> graphicsLibsText;
                    std::pair<sf::Sprite, sf::Texture> menuBackground;
                    sf::Text _arcadeTitle;
                    std::vector<sf::Text> _menuInputText;

                    Menu();
                    ~Menu();

                    void createAllMenuAssets(std::string actualGamePath, arcade::displayer::savedDatas _datas);

                    // Handlers for Menu
                    arcade::KeyboardKeys menuKeysHandlers(std::map<sf::Keyboard::Key, arcade::KeyboardKeys> _keysMapping, sf::Event _event);
                    void menuEventsHandlers(arcade::KeyboardKeys key, std::vector<std::string> gamesPaths);

                    // Draw Menu Assets
                    void drawMenuAssets(std::string actualGame, sf::RenderWindow &_win);

                    // Utils Functions
                    static std::string getGameName(std::string gamePaths);
                    size_t getGameNbr(void);
                    void setFont(sf::Font _font);
            };

            class Game {

                struct mapDatas {
                    sf::RectangleShape _walls;
                    sf::RectangleShape _doors;
                    std::vector<std::pair<std::shared_ptr<sf::Sprite>, std::shared_ptr<sf::Texture>>> _player;
                    sf::Clock pacmanClk;
                    std::map<char, std::pair<std::shared_ptr<sf::Sprite>, std::shared_ptr<sf::Texture>>> _enemy;
                    arcade::displayer::LibSfml::Direction _direction;


                    sf::Text infosGames;
                    sf::Text StateGame;
                    std::pair<sf::Sprite, sf::Texture> _nibblerHead;
                    std::pair<sf::Sprite, sf::Texture> _deadEnemy;
                    std::pair<sf::Sprite, sf::Texture> _nibblerQueue;
                    std::pair<float, float> newPos;
                    std::pair<float, float> oldPos;
                    std::pair<sf::Sprite, sf::Texture> _points;
                    std::pair<sf::Sprite, sf::Texture> _bonus;
                    std::pair<sf::Sprite, sf::Texture> _fruits;
                };

                private:
                    sf::Font _font;
                    std::vector<std::string> _saveMap;
                    arcade::displayer::LibSfml::Game::mapDatas _mapDatas;
                    std::map<char, void (arcade::displayer::LibSfml::Game::*)()> _functionsPacman;
                    std::map<char, void (arcade::displayer::LibSfml::Game::*)()> _functionsNibbler;

                    void createWalls();
                    void cleanAllTexture(void);

                    void drawNibblerAssets(sf::RenderWindow &_win);
                    void drawPacmanAssets(sf::RenderWindow &_win);

                    void drawEntities(int lineMap, int identifier, sf::RenderWindow &_win);
                    void moveAndDrawRect(size_t x, size_t y, sf::RenderWindow &_win, sf::RectangleShape &rect);
                    void moveAndDrawSprite(size_t x, size_t y, sf::RenderWindow &_win, sf::Sprite &spt);
                    void drawGameInfos(sf::RenderWindow &_win);
                    void drawGameState(sf::RenderWindow &_win, std::string gameState);
                public:
                    Game();
                    ~Game();

                    void createDeadEnemy(void);
                    void createAllPacman(void);
                    void createAllNibbler(void);
                    void drawGameAssets(sf::RenderWindow &_win, std::string gameName);
                    void setFont(sf::Font _font);
                    void setMap(std::vector<std::string> map);

                    void createPacgumSprite(void);
                    void createSuperPacgumSprite(void);
                    void createPacmanSprite(void);
                    void AnimatePacman(void);
                    void createDoors(void);
                    void createEnemy(std::vector<float> rectWidth, char type);

                    void createNibblerHead();
                    void createNibblerBody();
                    void createNibblerFruits();

                    void checkKeyMovement(std::pair<float, float> oldPos, std::pair<float, float> newPos);
                    void changePacmanMovement(sf::Sprite &spt, float rectTop, float rectLeft);
                    void setNewPos(int x, int y);
                    // void gameKeysHandlers(void);
            };

            private:
                sf::RenderWindow _win;
                sf::Event _event;
                sf::Font _font;
                size_t gameChoose;
                arcade::KeyboardKeys _keyUse;
                std::map<sf::Keyboard::Key, arcade::KeyboardKeys> _keysMapping;
                arcade::displayer::savedDatas _datas;
                Menu menu;
                Game game;

                void initKeys(void);
                void gameKeysHandlers(void);
                void eventsHandler(arcade::typeDisplay typeOfDisplay);

            public:
                LibSfml();
                ~LibSfml();
                void drawMenu(std::vector<std::string> gamesPaths, std::vector<std::string> displayersPaths);
                void drawGame(std::vector<std::string> map);
                // void drawLib(std::vector<std::string> gamesPaths, std::vector<std::string> displayersPaths);
                // void drawScore(size_t score);
                void loadMenuAssets(std::string actualGamePath, std::vector<std::string> gameLibPath,  std::vector<std::string> displayerlibPath);
                void loadGameAssets(std::string actualGamePath, std::vector<std::string> map);

                bool isRunning();

                void destroyWindow(void);

                // virtual void setGameLibNbr(size_t gameLibNbr);
                // virtual size_t getGameLibNbr();
                KeyboardKeys getInput();

                // void setPlayerPos(arcade::entity::Vector pos);
                // void setPlayerHp(int hp);
                // void setPlayerState(arcade::entity::EntityState state);
                // void setPlayerDirection(arcade::entity::Direction dir);

                // void setEnemiesPos(std::vector<arcade::entity::Vector> pos);
                // void setEnemiesState(std::vector<arcade::entity::EntityState> states);
                // void setEnemiesDirection(std::vector<arcade::entity::Direction> dirs);

                // void setLibs(std::vector<std::string> games, std::vector<std::string> graphs);
        };
    };
};