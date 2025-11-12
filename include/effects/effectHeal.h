#ifndef EFFECT_HEAL_H
#define EFFECT_HEAL_H

#include "effects/effects.h"

/**
 * @brief Эффект лечения персонажа.
 * Восстанавливает здоровье персонажа на фиксированное количество очков.
 */
class EffectHeal : public Effect
{
private:
    int healAmount;  ///< Количество восстанавливаемого здоровья
    bool isActive;   ///< Активен ли эффект
public:
    /**
     * @brief Конструктор эффекта лечения.
     * Устанавливает длительность действия и начальное количество здоровья.
     * @param ch Указатель на персонажа, на которого накладывается эффект
     */
    EffectHeal(Character* ch) : Effect::Effect(ch)
    {
        turnDur = 4;
        healAmount = 100;
        isActive = false;
    }

    /// Деструктор по умолчанию
    ~EffectHeal() = default;

    /**
     * @brief Применяет эффект на персонажа.
     * Восстанавливает здоровье, если текущий ход находится в пределах действия эффекта.
     */
    void affect() override;

    /**
     * @brief Проверяет, возможно ли применение эффекта.
     * @return true, если эффект можно применить, иначе false
     */
    bool isPossible() override;

    /**
     * @brief Возвращает описание эффекта.
     * @return Строковое описание эффекта
     */
    std::string effectDescription() override;
};

#endif