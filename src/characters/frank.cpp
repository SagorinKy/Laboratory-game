#include "characters/frank.h"

/**
 * @brief Проверяет, находится ли целевая точка в пределах диапазона выстрела.
 * 
 * Этот метод проверяет, может ли персонаж Frank выстрелить по цели, находящейся на
 * расстоянии 1 клетки по горизонтали или вертикали.
 * 
 * @param X Координата X цели.
 * @param Y Координата Y цели.
 * @return true, если цель находится в пределах диапазона выстрела, иначе false.
 */
bool Frank::shootIsInRange(int X, int Y)
{
    // Проверка, если цель на расстоянии 1 клетки по горизонтали или вертикали.
    if ((std::abs(X-x) == 1 &&  Y == y) || (std::abs(Y-y) == 1 &&  X == x))
        return true;
    return false;
}

/**
 * @brief Проверяет, точен ли выстрел.
 * 
 * Метод всегда возвращает true, так как у Frank всегда есть высокая точность выстрела.
 * 
 * @return true, если выстрел точен.
 */
bool Frank::shootIsAccurate()
{
    return true;
}

/**
 * @brief Получает регион, в котором будет произведён выстрел.
 * 
 * Если цель находится в диапазоне выстрела, метод возвращает 9 точек (включая
 * точку выстрела), которые будут поражены. Эти точки составляют 3x3 область
 * вокруг цели. Урон по каждой из точек будет одинаковым.
 * 
 * @param X Координата X цели.
 * @param Y Координата Y цели.
 * @return Вектор с координатами точек и уронов, которые будут произведены на цели.
 */
std::vector<std::vector<int>> Frank::shotRegion(int X, int Y)
{
    if(this->shootIsInRange(X, Y))
    {
        int difX = X - x;
        int difY = Y - y;
        // Создание координат всех точек в области поражения.
        std::vector<std::vector<int>> coords =
        {
            {X, Y, damage},
            {X + 2 * difX - 1, Y + 2 * difY, damage},
            {X + 2 * difX - 1, Y + 2 * difY + 1, damage},
            {X + 2 * difX, Y + 2 * difY + 1, damage},
            {X + 2 * difX + 1, Y + 2 * difY + 1, damage},
            {X + 2 * difX + 1, Y + 2 * difY, damage},
            {X + 2 * difX + 1, Y + 2 * difY - 1, damage},
            {X + 2 * difX, Y + 2 * difY - 1, damage},
            {X + 2 * difX - 1, Y + 2 * difY - 1, damage}
        };
        return coords;
    }
    else
    {
        // Если цель не в диапазоне выстрела, возвращаем пустой регион.
        std::vector<std::vector<int>> coords =
        {
            {-10, 0}
        };
        return coords;
    }
}