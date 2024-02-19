/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Utils/PositionVector.hpp
*/

#pragma once

#include <vector>

namespace arcade
{
    namespace entity
    {
        struct PositionVector {
            int x;
            int y;

            PositionVector invert() {
                return PositionVector(this->x * -1, this->y * -1);
            }

            static std::vector<PositionVector> getAllDirs() {
                return {PositionVector(-1, 0), PositionVector(1, 0), PositionVector(0, -1), PositionVector(0, 1)};
            }

            static PositionVector random(std::vector<PositionVector> possibleDirs) {
                return possibleDirs[std::rand() % possibleDirs.size()];
            }

            PositionVector operator+(const PositionVector &otherPos) const
            {
                return PositionVector(this->x + otherPos.x, this->y + otherPos.y);
            }

            PositionVector operator*(const int &multiplicator) const
            {
                return PositionVector(this->x * multiplicator, this->y * multiplicator);
            }

            bool operator==(const PositionVector &otherPos) const
            {
                return (this->x == otherPos.x && this->y == otherPos.y);
            }

            bool operator!=(const PositionVector &otherPos) const
            {
                return (this->x != otherPos.x || this->y != otherPos.y);
            }
        };
    };
};
