#ifndef EFFECT_H
#define EFFECT_H

#include "characters/character.h"
#include <string>

class Character;

/**
 * @brief Базовый класс для эффектов, применяемых к персонажу.
 * Содержит основную функциональность:
 * длительность эффекта, перезарядку, возможность применения и владельца эффекта.
 */
class Effect
{
protected:
    int turnNumber;           ///< Текущий номер хода
    bool effectPossibility;   ///< Возможность применения эффекта
    int turnEnd;              ///< Номер хода, на котором эффект завершится
    int turnDur;              ///< Длительность эффекта в ходах
    int coolDown;             ///< Время перезарядки эффекта
    Character* owner;         ///< Указатель на персонажа-владельца эффекта

public:
    /**
     * @brief Конструктор эффекта.
     * Инициализирует владельца, номер хода, возможность применения и перезарядку.
     * @param ch Указатель на персонажа-владельца эффекта
     */
    Effect(Character* ch) : turnNumber(0), effectPossibility(true), turnEnd(-1000), coolDown(3), owner(ch) {}

    /**
     * @brief Переход к следующему ходу.
     * Вызывает метод affect(), увеличивает turnNumber
     * и восстанавливает возможность применения эффекта после перезарядки.
     */
    void nextTurn();

    /**
     * @brief Применяет эффект на персонажа.
     * Должен быть переопределён в наследниках.
     */
    virtual void affect();

    //virtual bool isActive();

    /**
     * @brief Проверяет, возможно ли применение эффекта.
     * @return true, если эффект можно применить, иначе false
     */
    virtual bool isPossible();

    /**
     * @brief Запускает эффект.
     * Устанавливает turnEnd и блокирует повторное применение до окончания перезарядки.
     */
    void startEffect();

    /// Виртуальный деструктор по умолчанию
    virtual ~Effect() = default;

    /**
     * @brief Возвращает описание эффекта.
     * Должен быть переопределён в наследниках.
     * @return Строка с описанием эффекта
     */
    virtual std::string effectDescription();
};

#endif
