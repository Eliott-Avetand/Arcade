
/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** LibSDMLErrors.hpp
*/

#pragma once

#include <exception>
#include <string>

namespace arcade {

    namespace displayer {

        class libSFMLErrors : public std::exception {
            public:
                std::string _name;
                std::string _message;

                libSFMLErrors(std::string const &message, std::string const &errorType);
                const char *what() const noexcept;
                std::string const &getErrorType() const;
        };
    }
}
