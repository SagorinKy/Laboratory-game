#include "characters/piper.h"

/**
 * @brief Проверяет, находится ли цель в пределах дальности выстрела.
 */
bool Piper::shootIsInRange(int X, int Y)
{
    if (std::abs(X-x) + std::abs(Y-y) <= shotRange)
        return true;
    return false;
}

/**
 * @brief Проверяет точность выстрела.
 */
bool Piper::shootIsAccurate()
{
    return true;
}

/**
 * @brief Получает регион выстрела персонажа.
 */
std::vector<std::vector<int>> Piper::shotRegion(int X, int Y)
{
    if(this->shootIsInRange(X, Y))
    {
        int d = damage * (std::abs(X-x) + std::abs(Y-y));
        std::vector<std::vector<int>> coords =
        {
            {X, Y, d} ///< Координата цели и нанесённый урон.
        };
        return coords;
    }
    else
    {
        std::vector<std::vector<int>> coords =
        {
            {-10, 0, 0} ///< Если цель вне диапазона.
        };
        return coords;
    }
}