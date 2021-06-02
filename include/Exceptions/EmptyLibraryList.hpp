/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** EmptyLibraryList.hpp header
*/

#ifndef NTS_COMPONENT_NOT_FOUND_EXCEPTION_HPP_
#define NTS_COMPONENT_NOT_FOUND_EXCEPTION_HPP_

#include "AException.hpp"

class EmptyLibraryList : public AException
{
public:
    EmptyLibraryList(const std::string &) throw();
    virtual ~EmptyLibraryList() throw();
};

#endif