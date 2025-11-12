#include "effects/effectHeal.h"

/**
 * @brief Применяет эффект лечения на владельца.
 * Восстанавливает здоровье на healAmount, если ход в пределах действия эффекта.
 */
void EffectHeal::affect() 
{
    if(turnNumber <= turnEnd)
        owner->changeHelth(healAmount);
}

/**
 * @brief Проверяет, возможно ли применение эффекта.
 * @return true, если эффект можно применить
 */
bool EffectHeal::isPossible() 
{
    return effectPossibility/* && (owner->getHealth() != owner->getHealthRange())*/;
}

/**
 * @brief Возвращает описание эффекта лечения.
 * @return Строка с описанием: "Effect heals you 100 points per your move"
 */
std::string EffectHeal::effectDescription()
{
    return "Effect heals you 100 points per your move";
}