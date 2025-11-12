#ifndef EFFECT_JUMP_H
#define EFFECT_JUMP_H

#include "effects/effects.h"

/**
 * @brief Эффект увеличения дальности перемещения персонажа.
 * Позволяет персонажу перемещаться на увеличенное расстояние в течение нескольких ходов.
 */
class EffectJump : public Effect
{
private:
    int jumpAdditionalLength; ///< Дополнительная длина прыжка
    bool isActive;            ///< Активен ли эффект

public:
    /**
     * @brief Конструктор эффекта прыжка.
     * Устанавливает длительность эффекта, дополнительную длину прыжка и перезарядку.
     * @param ch Указатель на персонажа, на которого накладывается эффект
     */
    EffectJump(Character* ch) : Effect::Effect(ch)
    {
        turnDur = 4;
        jumpAdditionalLength = 4;
        isActive = false;
        coolDown = 5;
    }

    /// Деструктор по умолчанию
    ~EffectJump() = default;

    /**
     * @brief Применяет эффект на персонажа.
     * Увеличивает дальность перемещения в начале действия эффекта и возвращает её в конце.
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