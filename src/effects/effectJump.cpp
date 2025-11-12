#include "effects/effectJump.h"

/**
 * @brief Применяет эффект увеличения дальности перемещения.
 * Добавляет дополнительную длину прыжка в начале действия эффекта
 * и возвращает дальность в исходное состояние по окончании действия.
 */
void EffectJump::affect() 
{
    if(turnNumber == turnEnd - turnDur)
        owner->addRange(jumpAdditionalLength);
    if(turnNumber == turnEnd)
        owner->addRange(-jumpAdditionalLength);
}

/**
 * @brief Проверяет, возможно ли применение эффекта.
 * @return true, если эффект можно применить
 */
bool EffectJump::isPossible() 
{
    return effectPossibility;
}

/**
 * @brief Возвращает описание эффекта увеличения дальности перемещения.
 * @return Строка с описанием: "Effect permets you move in a expanded range"
 */
std::string EffectJump::effectDescription()
{
    return "Effect permets you move in a expanded range";
}