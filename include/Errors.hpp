/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** Errors.hpp
*/
#pragma once

#include <exception>
#include <string>

class Errors : public std::exception {
    protected:
        std::string _message;
        std::string _name;

    public:
        Errors(std::string const &message, std::string const &errorType = "Unknown");

        virtual const char *what() const noexcept;
        std::string const &getErrorType() const;
};

class ProgramError : public Errors {
    public:
        ProgramError(std::string const &message, std::string const &errorType = "Unknown");
};

class LibScannerError : public Errors {
    public:
        LibScannerError(std::string const &message, std::string const &errorType = "Unknown");
};