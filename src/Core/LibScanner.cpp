/*
** EPITECH PROJECT, 2022
** LibParser.cpp
** File description:
** LibParser class definition
*/

#include <fstream>
#include "Core.hpp"

void arcade::core::Core::LibScanner::openFile(std::string fileName)
{
    std::ifstream file(fileName);

    if (file.fail())
        throw LibScannerError(std::string("[Scanner] Can't open file: ").append(fileName));
    this->fileBuffer.clear();
    this->fileBuffer << file.rdbuf();
    file.close();
}

bool arcade::core::Core::LibScanner::checkFilesExtension(std::string filePath)
{
    if (filePath.substr(filePath.find('.') - 1) == ".so")
        return true;
    return false;
}

void arcade::core::Core::LibScanner::updateGamesPaths(void)
{
    std::string line;
    std::vector<std::string> gamesTemp;

    this->openFile("./lib/games.txt");
    while (getline(this->fileBuffer, line, '\n')) {
        if (this->checkFilesExtension(line))
            continue;
        gamesTemp.push_back(line);
    }
    this->gamesPaths.clear();
    for (auto file : std::filesystem::directory_iterator("./lib/")) {
        for (std::string gameLib : gamesTemp) {
            if (file.path() == "./lib/" + gameLib)
                this->gamesPaths.push_back(file.path());
        }
    }
}

void arcade::core::Core::LibScanner::updateGraphicsPaths(void)
{
    std::string line;
    std::vector<std::string> graphicsTemp;

    this->openFile("./lib/graphics.txt");
    while (getline(this->fileBuffer, line, '\n')) {
        if (this->checkFilesExtension(line))
            continue;
        graphicsTemp.push_back(line);
    }
    this->graphicsPaths.clear();
    for (auto file : std::filesystem::directory_iterator("./lib/")) {
        for (std::string graphicsLib : graphicsTemp) {
            if (file.path() == "./lib/" + graphicsLib)
                this->graphicsPaths.push_back(file.path());
        }
    }
}

std::vector<std::string> arcade::core::Core::LibScanner::getGamesPaths(void)
{
    return this->gamesPaths;
}

std::vector<std::string> arcade::core::Core::LibScanner::getGraphicsPaths(void)
{
    return this->graphicsPaths;
}