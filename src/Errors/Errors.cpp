/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Errors.cpp
*/
#include "Errors.hpp"

Errors::Errors(std::string const &message, std::string const &errorType)
{
    this->_name = errorType;
    this->_message = message;
}

const char *Errors::what() const noexcept
{
    return this->_message.c_str();
}

std::string const &Errors::getErrorType() const
{
    return this->_name;
}

ProgramError::ProgramError(std::string const &message, std::string const &errorType) :
    Errors::Errors(message, errorType)
{
}

LibScannerError::LibScannerError(std::string const &message, std::string const &errorType) :
    Errors::Errors(message, errorType)
{
}