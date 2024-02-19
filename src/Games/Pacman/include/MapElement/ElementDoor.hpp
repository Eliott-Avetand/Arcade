/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Pacman/ElementDoor.hpp
*/

#pragma once

#include <chrono>

namespace arcade
{
    namespace game
    {
        struct ElementDoor {
            bool isOpen;
            std::chrono::time_point<std::chrono::system_clock> open_clock;
            std::chrono::time_point<std::chrono::system_clock> tp_enemy_clock;

            void checkForOpen()
            {
                if (this->isOpen == true)
                    return;
                std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_time = now - this->open_clock;

                if (elapsed_time >= std::chrono::seconds(10))
                    this->isOpen = true;
            }
        };
    };
};