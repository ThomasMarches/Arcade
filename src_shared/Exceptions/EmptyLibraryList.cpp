/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** EmptyLibraryList.cpp
*/

#include "Exceptions/EmptyLibraryList.hpp"

EmptyLibraryList::EmptyLibraryList(const std::string& strMsg) throw()
	: AException(strMsg) { }

EmptyLibraryList::~EmptyLibraryList() throw() { }