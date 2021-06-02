/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** ArcadeLib.cpp
*/

#include "ArcadeLib.hpp"

namespace arcade
{
    ArcadeLib::ArcadeLib(const std::string &strPath) : SharedLib(strPath)
    {
        m_funcGetData = nullptr;
        m_funcCreate = nullptr;
        m_funcDestroy = nullptr;
        m_pData = nullptr;
        load();
    }

    ArcadeLib::~ArcadeLib()
    {
        if (m_pData)
        {
            (*m_funcDestroy)(m_pData);
            m_pData = nullptr;
            m_funcGetData = nullptr;
            m_funcDestroy = nullptr;
            m_funcCreate = nullptr;
        }
    }

    /* PUBLIC */
    void ArcadeLib::load()
    {
        sym("library_get_data", m_funcGetData);
        sym("library_create", m_funcCreate);
        sym("library_delete", m_funcDestroy);
        m_info = (*m_funcGetData)();
    }

    void ArcadeLib::init()
    {
        if (m_pData)
            return;
        open(m_strPath);
        load();
        m_pData = (*m_funcCreate)();
        if (!m_pData) {
            throwError("ArcadeLib: Null pointer.");
        }
    }

    void ArcadeLib::unload()
    {
        if (m_pData)
        {
            (*m_funcDestroy)(m_pData);
            m_pData = nullptr;
            m_funcGetData = nullptr;
            m_funcDestroy = nullptr;
            m_funcCreate = nullptr;
        }
        close();
    }

    library_info_t ArcadeLib::getInfo()
    {
        return m_info;
    }
}