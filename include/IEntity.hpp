/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** IEntity.hpp header
*/

#ifndef IENTITY_HPP_PRIVATE
#define IENTITY_HPP_PRIVATE

#include "Common/IEntity.hpp"

template <typename T>
T *GetComponent(arcade::IEntity &e)
{
    T* oComp = nullptr;
    e.forEach([&oComp](arcade::component::IComponent& comp) {
        if (T* c = dynamic_cast<T*>(&comp))
            oComp = c;
    });
    return oComp;
}

template<typename T>
bool GetComponent(arcade::IEntity& e, T*& t)
{
    e.forEach([&](arcade::component::IComponent& comp) {
        if (T* c = dynamic_cast<T*>(&comp))
            t = c;
    });
    return t != nullptr;
}

// template <class A>
// void one_type(arcade::component::IComponent& comp, A*& oComp)
// {
//     if (A* c = dynamic_cast<A*>(&comp))
//         oComp = c;
// }

// template <typename T>
// T* read(arcade::component::IComponent& comp)
// {
//     if (T* c = dynamic_cast<T*>(&comp))
//         return c;
//     return nullptr;
// }

// template <typename... Args>
// std::tuple<Args*...> Get(arcade::component::IComponent& comp) 
// {
//     return std::make_tuple(read<Args>(comp)...);
// }

// // template <typename... Args>
// // std::tuple<Args...> Get(arcade::component::IComponent& comp) 
// // {
// //     return Get<Args...>(comp);
// // }

template<typename T1, typename T2>
bool GetComponent(arcade::IEntity& e, T1*& t1, T2*& t2)
{
    // std::tuple<Comps*...> t;
    e.forEach([&](arcade::component::IComponent& comp) {
        // t = Get<Comps...>(comp);
        if (T1* c = dynamic_cast<T1*>(&comp))
            t1 = c;
        else if (T2* c = dynamic_cast<T2*>(&comp))
            t2 = c;
    });
    return t1 != nullptr && t2 != nullptr;
}

template<typename T1, typename T2, typename T3>
bool GetComponent(arcade::IEntity& e, T1*& t1, T2*& t2, T3*& t3)
{
    e.forEach([&](arcade::component::IComponent& comp) {
        if (T1* c = dynamic_cast<T1*>(&comp))
            t1 = c;
        else if (T2* c = dynamic_cast<T2*>(&comp))
            t2 = c;
        else if (T3* c = dynamic_cast<T3*>(&comp))
            t3 = c;
    });
    return t1 != nullptr && t2 != nullptr && t3 != nullptr;
}

template<typename T>
bool HasComponent(arcade::IEntity& e)
{
    bool oComp = false;
    e.forEach([&oComp](arcade::component::IComponent& comp) {
        if (T* c = dynamic_cast<T*>(&comp))
            oComp = c != nullptr;
    });
    return oComp;
}

#endif /* !IENTITY_HPP_PRIVATE */