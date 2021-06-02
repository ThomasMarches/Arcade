/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** ArcadeLib.hpp header
*/

#ifndef ARCADE_ARCADE_SHARED_LIB_HPP
#define ARCADE_ARCADE_SHARED_LIB_HPP

#include <memory>
#include "SharedLib.hpp"
#include "Exceptions/CastException.hpp"

namespace arcade
{
    class ArcadeLib : public SharedLib
    {
    public:
        using UPtr = std::unique_ptr<ArcadeLib>;
        using SPtr = std::shared_ptr<ArcadeLib>;
        ArcadeLib(const std::string &strPath);
        ~ArcadeLib();

        void load();
        void init();
        void unload();

        /**
        * @brief Get library info
        * @return library_info_t of lib
        */
        library_info_t getInfo();

        // /**
        // * @brief Create library
        // * @return ILibrary as void*
        // */
        // void *libCreate();

        // /**
        // * @brief Destroy library
        // * @param lib Pointer of ILibrary as void*
        // */
        // void libDestroy(void *lib);

        template <typename T>
        T* get()
        {
            T* data = static_cast<T*>(m_pData);
            if (!data)
                throw CastException("ArcadeLib: Invalid Cast to " + std::string(typeid(T).name()));
            return data;
        }
    protected:

        library_info_t m_info;
        void* m_pData;

        library_info_t (*m_funcGetData)();
        void *(*m_funcCreate)();
        void (*m_funcDestroy)(void *);
    };
} // namespace arcade

#endif //! ARCADE_SHARED_LIB_HPP