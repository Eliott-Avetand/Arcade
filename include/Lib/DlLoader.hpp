/*
** EPITECH PROJECT, 2022
** DlLoader.hpp
** File description:
** DlLoader class definition
*/
#pragma once

#include <string>
#include <dlfcn.h>
#include <memory>
#include <iostream>
#include "Errors.hpp"
#include "IDisplayer.hpp"
#include "IGame.hpp"

namespace arcade {
    namespace lib {
        class DlLoader {
            private:
                std::vector<void *> allLibs;

                void *getFunction(void *handle, const char *name);
                void *open(const std::string libpath);
                int close(void *handle);

                template <typename Type>
                std::shared_ptr<Type> getEntryPoint(void *handle, const std::string funcname)
                {
                        std::shared_ptr<Type> (*fctPtr)(void) = (std::shared_ptr<Type>(*)(void))this->getFunction(handle, funcname.c_str());

                        if (!fctPtr)
                            throw ProgramError("[DlLoader] Error in getEntryPoint() : " + std::string(dlerror()));
                        return fctPtr();
                };

            public:
                DlLoader();
                ~DlLoader();

                void destroyAllLibs();

                template <typename Type>
                std::shared_ptr<Type> getLibInstance(const std::string libpath)
                {
                    try {
                        void *handle = this->open(libpath);
                        this->allLibs.push_back(handle);
                        std::shared_ptr<Type> lib = this->getEntryPoint<Type>(handle, "entryPoint");
                        return lib;
                    } catch (const ProgramError &error) {
                        std::cout << error.what() << std::endl;
                        return nullptr;
                    }
                };
        };
    };
};