/*
** EPITECH PROJECT, 2022
** LibSFMLMenu.c
** File description:
** sfml file for Arcade
*/

#include "LibSFML.hpp"
#include "LibSFMLErrors.hpp"
#include <iostream>

arcade::displayer::LibSfml::Menu::Menu()
{
    this->_alreadyLoad = false;
    this->gameNbr = 0;
}

arcade::displayer::LibSfml::Menu::~Menu()
{

}

void arcade::displayer::LibSfml::Menu::createAllMenuAssets(std::string actualGamePath, arcade::displayer::savedDatas _datas)
{
    if (!_alreadyLoad) {
        this->createMenuJackets(this->getGameName(actualGamePath), _datas);
        this->createMenuGames(_datas.gameLibs);
        this->createMenuGraphicsLibs(_datas.graphicLibs);
        this->createMenuInfos();
        this->createArcadeTitle();
        this->createMenuBackground();
        this->_alreadyLoad = true;
    } else {
        this->createMenuJackets(this->getGameName(actualGamePath), _datas);
        this->createMenuGames(_datas.gameLibs);
        this->createMenuGraphicsLibs(_datas.graphicLibs);
    }
}

void arcade::displayer::LibSfml::Menu::createArcadeTitle(void)
{
    this->_arcadeTitle.setFont(this->_font);
    this->_arcadeTitle.setString("ARCADE");
    this->_arcadeTitle.setPosition(sf::Vector2f(300, 0));
    this->_arcadeTitle.setCharacterSize(100);
    this->_arcadeTitle.setFillColor(sf::Color::White);
    this->_arcadeTitle.setStyle(sf::Text::Bold);
}

void arcade::displayer::LibSfml::Menu::createMenuBackground()
{
    if (!this->menuBackground.second.loadFromFile(BACKGROUND_MENU))
        throw arcade::displayer::libSFMLErrors("[SFML] Background texture not found!", "Texture not load");
    this->menuBackground.first.setTexture(this->menuBackground.second);
}

void arcade::displayer::LibSfml::Menu::createMenuInfos()
{
    sf::Text textTmp;
    std::string str[8] = {"GRAPHIC LIB", "MENU INPUT", "GAME:", "RIGHT / LEFT", "GRAPHIC:", "UP / DOWN", "SELECT:" , "L"};

    textTmp.setFont(this->_font);
    textTmp.setFillColor(sf::Color::White);
    for (size_t strNbr = 0; strNbr < 8; strNbr++) {
        textTmp.setString(str[strNbr]);
        this->_menuInputText.push_back(textTmp);
    }
    this->_menuInputText[0].setPosition(sf::Vector2f(660, 200));
    this->_menuInputText[1].setPosition(sf::Vector2f(660, 580));
    this->_menuInputText[2].setPosition(sf::Vector2f(580, 650));
    this->_menuInputText[3].setPosition(sf::Vector2f(780, 650));
    this->_menuInputText[4].setPosition(sf::Vector2f(538, 700));
    this->_menuInputText[5].setPosition(sf::Vector2f(780, 700));
    this->_menuInputText[6].setPosition(sf::Vector2f(558, 750));
    this->_menuInputText[7].setPosition(sf::Vector2f(780, 750));
}

void arcade::displayer::LibSfml::Menu::createMenuGraphicsLibs(std::vector<std::string> displayerPaths)
{
    std::string libName;
    sf::Text txtTemp;

    txtTemp.setFont(this->_font);
    txtTemp.setFillColor(sf::Color::White);
    txtTemp.setCharacterSize(23);
    this->graphicsLibsText.clear();
    std::cout << displayerPaths.size() << std::endl;
    for (size_t libsNumbers = 0; libsNumbers < displayerPaths.size(); libsNumbers++) {
        libName = displayerPaths[libsNumbers].substr(displayerPaths[libsNumbers].rfind('/') + 1);
        libName = libName.substr(0, libName.find('.'));
        if (libName == "arcade_sfml") {
            txtTemp.setString(">>  " + libName);
            txtTemp.setPosition(sf::Vector2f(630, (libsNumbers * 33) + 250));
        } else {
            txtTemp.setString(libName);
            txtTemp.setPosition(sf::Vector2f(665, (libsNumbers * 33) + 250));
        }
        this->graphicsLibsText.push_back(txtTemp);
    }
}


void arcade::displayer::LibSfml::Menu::createMenuJackets(std::string gameName, arcade::displayer::savedDatas _datas)
{
    sf::Sprite spriteTmp;
    sf::Texture textureTmp;

    (void)gameName;

    gamesJacketsSpt.clear();
    for (size_t gameNumbers = 0; gameNumbers < _datas.gameLibs.size(); gameNumbers++) {
        try {
            if (!textureTmp.loadFromFile("./src/ressources/" + this->getGameName(_datas.gameLibs[gameNumbers]) + "/sprites/jacket.jpg"))
                throw arcade::displayer::libSFMLErrors("[SFML] Game jacket is not found!", "Texture not found");
        } catch (const arcade::displayer::libSFMLErrors &error) {
            if (!textureTmp.loadFromFile(DEFAULT_JACKET))
                throw arcade::displayer::libSFMLErrors("[SFML] Default Game Jawcket is not found!", "Texture is not found");
        }
        this->gamesJacketsSpt.push_back(std::make_pair(spriteTmp, textureTmp));
        this->gamesJacketsSpt[gameNumbers].first.setTexture(this->gamesJacketsSpt[gameNumbers].second);
        this->gamesJacketsSpt[gameNumbers].first.setOrigin(sf::Vector2f(spriteTmp.getTextureRect().width, spriteTmp.getTextureRect().height));
        this->gamesJacketsSpt[gameNumbers].first.setPosition(sf::Vector2f(40, 300));
    }
}

void arcade::displayer::LibSfml::Menu::createMenuGames(std::vector<std::string> gamesPaths)
{
    std::string libName;
    sf::Text txtTemp;

    txtTemp.setFont(this->_font);
    txtTemp.setFillColor(sf::Color::White);
    txtTemp.setCharacterSize(40);
    this->gamesLibsText.clear();
    for (size_t libsNumbers = 0; libsNumbers < gamesPaths.size(); libsNumbers++) {
        libName = gamesPaths[libsNumbers].substr(gamesPaths[libsNumbers].rfind('/') + 1);
        libName = libName.substr(0, libName.find('.'));
        txtTemp.setString(libName);
        txtTemp.setPosition(sf::Vector2f(135, 715));
        this->gamesLibsText.push_back(txtTemp);
    }
}

arcade::KeyboardKeys arcade::displayer::LibSfml::Menu::menuKeysHandlers(std::map<sf::Keyboard::Key, arcade::KeyboardKeys> _keysMapping, sf::Event _event)
{
    for (auto it = _keysMapping.begin(); it != _keysMapping.end(); ++it) {
        if (_event.key.code == it->first) {
            return it->second;
        }
    }
    return NONE;
}

void arcade::displayer::LibSfml::Menu::drawMenuAssets(std::string actualGame, sf::RenderWindow &_win)
{
    _win.draw(this->menuBackground.first);
    _win.draw(this->_arcadeTitle);
    for (auto gameInputTxt : this->_menuInputText) {
        _win.draw(gameInputTxt);
    }
    for (auto libtxt : this->graphicsLibsText)
        _win.draw(libtxt);
    for (size_t libNbr = 0; libNbr < this->gamesLibsText.size(); libNbr++) {
        if (this->gamesLibsText[libNbr].getString() == actualGame) {
            _win.draw(this->gamesJacketsSpt[libNbr].first);
            _win.draw(this->gamesLibsText[libNbr]);
        }
    }
}

void arcade::displayer::LibSfml::Menu::setFont(sf::Font _font)
{
    this->_font = _font;
}

void arcade::displayer::LibSfml::Menu::menuEventsHandlers(arcade::KeyboardKeys key, std::vector<std::string> gamesPaths)
{
    if (key == arcade::KeyboardKeys::ARROW_L) {
        if (gameNbr < gamesPaths.size() - 1)
            this->gameNbr++;
        else
            this->gameNbr = 0;
    }
    if (key == arcade::KeyboardKeys::ARROW_R) {
        if (gameNbr > 0)
            this->gameNbr--;
        else
            this->gameNbr = (gamesPaths.size() - 1);
    }
}

void arcade::displayer::LibSfml::drawMenu(std::vector<std::string> gamesPaths, std::vector<std::string> displayersPaths)
{
    (void)displayersPaths;
    this->eventsHandler(arcade::typeDisplay::MENU);
    this->_win.clear(sf::Color::White);
    this->menu.drawMenuAssets(this->menu.getGameName(gamesPaths[this->menu.getGameNbr()]), this->_win);
    this->_win.display();
}

size_t arcade::displayer::LibSfml::Menu::getGameNbr(void)
{
    return this->gameNbr;
}