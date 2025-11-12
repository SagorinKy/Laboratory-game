#ifndef PIPER_H
#define PIPER_H

#include "effects/effectHeal.h"
#include "characters/character.h"

/**
 * @class Piper
 * @brief Класс персонажа Piper, наследник Character.
 * 
 * Персонаж Piper обладает низким здоровьем и уроном, дальностью выстрела 6 клеток,
 * применяет эффект лечения и не имеет двойного выстрела.
 */
class Piper : public Character
{
private:
    int shotRange;      ///< Дальность выстрела персонажа.
    bool regionDamage;  ///< Флаг наличия урона по региону.

public:
    /**
     * @brief Конструктор персонажа Piper.
     * 
     * Инициализирует координаты, идентификатор и характеристики персонажа,
     * такие как здоровье, урон, скорость, дальность выстрела и эффект.
     * 
     * @param X Координата X персонажа.
     * @param Y Координата Y персонажа.
     * @param num Номер персонажа.
     */
    Piper(int X, int Y, int num) : Character(X, Y, num, 1) 
    {
        name = 'P'; ///< Имя персонажа.
        hitProb = 3; ///< Вероятность попадания.
        speedInRow = 2; ///< Горизонтальная скорость.
        speedDiag = 2; ///< Диагональная скорость.
        healthRange = 100; ///< Максимальное здоровье.
        health = 100; ///< Текущее здоровье.
        damage = 75; ///< Урон персонажа.
        shotRange = 6; ///< Дальность выстрела.
        effect = new EffectHeal(this); ///< Эффект лечения.
        doubleShot = false; ///< Персонаж не имеет двойного выстрела.
    }

    /// Деструктор персонажа Piper.
    ~Piper()
    {
        effect->~Effect();
    }

    /**
     * @brief Проверяет, находится ли цель в пределах дальности выстрела.
     * 
     * Цель в пределах дальности, если сумма абсолютных разниц координат X и Y
     * не превышает shotRange.
     * 
     * @param X Координата X цели.
     * @param Y Координата Y цели.
     * @return true, если цель в диапазоне выстрела, иначе false.
     */
    bool shootIsInRange(int X, int Y) override; // +

    /**
     * @brief Проверяет точность выстрела.
     * 
     * Метод всегда возвращает true.
     * 
     * @return true, если выстрел точен.
     */
    bool shootIsAccurate() override;

    /**
     * @brief Получает регион выстрела персонажа.
     * 
     * Если цель в диапазоне, возвращает координаты цели и нанесённый урон.
     * Если цель вне диапазона, возвращает координату {-10, 0, 0}.
     * 
     * @param X Координата X цели.
     * @param Y Координата Y цели.
     * @return Вектор координат и значений урона.
     */
    std::vector<std::vector<int>> shotRegion(int X, int Y) override; // +
};

#endif