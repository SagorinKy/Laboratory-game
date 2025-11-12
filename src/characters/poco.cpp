#include "characters/poco.h"

/**
 * @brief Проверяет, находится ли цель в пределах дальности выстрела.
 */
bool Poco::shootIsInRange(int X, int Y)
{
    if ((std::abs(X-x) == 1 &&  Y == y) || (std::abs(Y-y) == 1 &&  X == x))
        return true;
    return false;
}

/**
 * @brief Проверяет точность выстрела.
 */
bool Poco::shootIsAccurate()
{
    return true;
}

/**
 * @brief Получает регион выстрела персонажа.
 */
std::vector<std::vector<int>> Poco::shotRegion(int X, int Y)
{
    if(this->shootIsInRange(X, Y))
    {
        int difX = X - x;
        int difY = Y - y;
        std::vector<std::vector<int>> coords =
        {
            {X + difX, Y + difY, damage},
            {X + 2 * difX, Y + 2 * difY, damage},
            {X + 3 * difX, Y + 3 * difY, damage},
            {X + 4 * difX, Y + 4 * difY, damage},
            {X + 2 * difX - difY, Y + 2 * difY - difX, damage},
            {X + 3 * difX - difY, Y + 3 * difY - difX, damage},
            {X + 4 * difX - difY, Y + 4 * difY - difX, damage},
            {X + 2 * difX + difY, Y + 2 * difY + difX, damage},
            {X + 3 * difX + difY, Y + 3 * difY + difX, damage},
            {X + 4 * difX + difY, Y + 4 * difY + difX, damage},
            {X + 3 * difX - 2 * difY, Y + 3 * difY - 2 * difX, damage},
            {X + 4 * difX - 2 * difY, Y + 4 * difY - 2 * difX, damage},
            {X + 3 * difX + 2 * difY, Y + 3 * difY + 2 * difX, damage},
            {X + 4 * difX + 2 * difY, Y + 4 * difY + 2 * difX, damage}
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