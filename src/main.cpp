/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** main.cpp
*/

#include <iostream>
#include "ArcadeConfig.hpp.in"
#include "Core.hpp"

int printHelp()
{
    std::cout << "Arcade project - Version " << Arcade_VERSION_MAJOR << "." << Arcade_VERSION_MINOR << std::endl << std::endl;
    std::cout << "USAGE:" << std::endl;
    std::cout << "\t" << "./arcade graphicLib" << std::endl << std::endl;
    std::cout << "DESCRIPTION:" << std::endl;
    std::cout << "\t" << "graphicLib" << "\tThe graphic library to start with (SFML, SDL, Ncurses, ...)" << std::endl;
    return 84;
}

int main(int ac, char const **av)
{
    if (ac != 2)
        return printHelp();
    try {
        arcade::core::Core core(av[1]);
    } catch (std::exception const &error) {
        return 84;
    }
    return 0;
}