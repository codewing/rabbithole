//
// Created by codewing on 14.11.18.
//

#pragma once

enum class EComponentType {
    UPDATE = 0,
    RENDERABLE = 1,
    PHYSICS = 2,
    INPUT = 4,
};

inline EComponentType operator|(EComponentType a, EComponentType b)
{return static_cast<EComponentType>(static_cast<int>(a) | static_cast<int>(b));}

inline EComponentType operator&(EComponentType a, EComponentType b)
{return static_cast<EComponentType>(static_cast<int>(a) & static_cast<int>(b));}