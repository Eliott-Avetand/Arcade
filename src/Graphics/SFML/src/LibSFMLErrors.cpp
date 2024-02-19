/*
** EPITECH PROJECT, 2022
** LibSFMLErrors.c
** File description:
** LibSFMLErrors file for Arcade
*/

#include "LibSFMLErrors.hpp"

arcade::displayer::libSFMLErrors::libSFMLErrors(std::string const &message, std::string const &errorType)
{
    this->_message = message;
    this->_name = errorType;
}

const char *arcade::displayer::libSFMLErrors::what() const noexcept
{
    return this->_message.c_str();
}

std::string const &arcade::displayer::libSFMLErrors::getErrorType() const
{
    return this->_name;
}