#include "characters/grom.h"

/**
 * @brief Проверяет, находится ли цель в пределах диапазона выстрела.
 */
bool Grom::shootIsInRange(int X, int Y)
{
    if (std::abs(X-x) <= 3 &&  std::abs(Y-y) <= 3)
        return true;
    return false;
}

/**
 * @brief Проверяет точность выстрела.
 */
bool Grom::shootIsAccurate()
{
    return true;
}

/**
 * @brief Получает регион выстрела персонажа.
 */
std::vector<std::vector<int>> Grom::shotRegion(int X, int Y)
{
    if(this->shootIsInRange(X, Y))
    {
        std::vector<std::vector<int>> coords =
        {
            {X, Y, (int)(damage * 1.5)}, ///< Центральная цель с увеличенным уроном.
            {X - 1, Y, damage},          ///< Соседние клетки вокруг цели.
            {X + 1, Y, damage},
            {X, Y - 1, damage},
            {X, Y + 1, damage}
        };
        return coords;
    }
    else
    {
        std::vector<std::vector<int>> coords =
        {
            {-10, 0} ///< Если цель вне диапазона.
        };
        return coords;
    }
}