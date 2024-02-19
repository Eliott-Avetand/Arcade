/*
** EPITECH PROJECT, 2022
** DlLoader.cpp
** File description:
** DlLoader class definition
*/

#include "DlLoader.hpp"

arcade::lib::DlLoader::DlLoader()
{
    //Void
}

arcade::lib::DlLoader::~DlLoader()
{
    // this->destroyAllLibs();
}

void *arcade::lib::DlLoader::open(const std::string libpath)
{
    void *lib = dlopen(libpath.c_str(), RTLD_LAZY);

    if (!lib)
        throw ProgramError("[DlLoader] Error in open() : " + std::string(dlerror()));
    return lib;
}

void *arcade::lib::DlLoader::getFunction(void *handle, const char *name)
{
    return dlsym(handle, name);
}

int arcade::lib::DlLoader::close(void *handle)
{
    return dlclose(handle);
}

void arcade::lib::DlLoader::destroyAllLibs()
{
    for (void *handler : this->allLibs)
        this->close(handler);
}