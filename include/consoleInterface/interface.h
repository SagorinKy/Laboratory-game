#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include <vector>
#include "characters/character.h"
#include "fight/CharacterRegistry.h"
#include "fight/dice.h"

/**
 * @struct Team
 * @brief Структура для хранения информации о команде.
 */
struct Team
{
    std::string character;   ///< Имя персонажа.
    int teamIdentifier;      ///< Идентификатор команды.
};

/**
 * @class Interface
 * @brief Класс для взаимодействия с пользователем в консоли.
 * 
 * Отвечает за вывод информации, выбор персонажей, ходов, координат выстрелов и передвижений,
 * а также за отображение эффектов и результатов действий.
 */
class Interface
{
private:
    int maxNum = 6; ///< Максимальное количество доступных персонажей.
    Dice dice = Dice(); ///< Игровой кубик для случайных событий.

public:
    std::string availableCharacters[6] = 
    {
        {"Piper"},
        {"Frank"},
        {"Bonnie"},
        {"Edgar"},
        {"Poco"},
        {"Grom"}
    }; ///< Список доступных персонажей.

    /**
     * @brief Позволяет игрокам выбрать персонажей.
     * 
     * @param num Количество персонажей для выбора каждой командой.
     * @return Массив строк с выбранными персонажами.
     */
    std::string* choseCharacter(int num); 

    /**
     * @brief Возвращает цвет для команды в консоли.
     * 
     * @param ind Индекс команды.
     * @return Строка с кодом цвета.
     */
    std::string colour(int ind); 

    /**
     * @brief Выводит информацию о начале хода команды.
     * 
     * @param turn Номер текущего хода.
     * @param name Имя персонажа, который делает ход.
     */
    void startTurn(int turn, std::string name);

    /**
     * @brief Спрашивает игрока, какое действие он хочет выполнить.
     * 
     * @param teamNum Номер команды игрока.
     * @param effectIsPossible Флаг доступности применения эффекта.
     * @return Выбор действия (номер действия).
     */
    int askToMakeATurn(int teamNum, bool effectIsPossible);

    /**
     * @brief Запрашивает координаты для движения персонажа.
     * 
     * @param teamNum Номер команды игрока.
     * @param emptyCases Возможные пустые клетки для перемещения.
     * @return Массив координат [X, Y] для движения.
     */
    int* askMoveCoord(int teamNum, std::vector<std::vector<int>> emptyCases);

    /**
     * @brief Запрашивает координаты для выстрела.
     * 
     * @param teamNum Номер команды игрока.
     * @param possibleCases Возможные клетки для выстрела.
     * @return Массив координат [X, Y] для выстрела.
     */
    int* askShotCoord(int teamNum, std::vector<std::vector<int>> possibleCases);

    /**
     * @brief Спрашивает игрока о подтверждении действия.
     * 
     * @param teamNum Номер команды игрока.
     * @return true, если игрок подтвердил действие.
     */
    bool askConfirmation(int teamNum);

    /**
     * @brief Выводит сообщение о успешном выстреле.
     * 
     * @param teamNum Номер команды игрока.
     * @param points Количество нанесённого урона.
     */
    void shotSuccess(int teamNum, int points);

    /**
     * @brief Выводит сообщение о промахе.
     * 
     * @param teamNum Номер команды игрока.
     */
    void shotMiss(int teamNum);

    /**
     * @brief Выводит сообщение о успешном перемещении.
     * 
     * @param teamNum Номер команды игрока.
     * @param x Координата X перемещения.
     * @param y Координата Y перемещения.
     */
    void moveSuccess(int teamNum, int x, int y);

    /**
     * @brief Выводит сообщение о неудачном перемещении.
     * 
     * @param teamNum Номер команды игрока.
     * @param x Координата X.
     * @param y Координата Y.
     */
    void moveUnsuccess(int teamNum, int x, int y);

    /**
     * @brief Выводит информацию о применении эффекта лечения.
     * 
     * @param teamNum Номер команды игрока.
     * @param healAmount Количество здоровья, восстанавливаемое за ход.
     */
    void effectHeal(int teamNum, int healAmount);

    /**
     * @brief Выводит информацию о применении эффекта увеличенного урона.
     * 
     * @param teamNum Номер команды игрока.
     */
    void effectAdditionalDamage(int teamNum);

    /**
     * @brief Выводит информацию о погибших персонажах.
     * 
     * @param teamNum Номер команды игрока.
     * @param eleminated Массив с идентификаторами погибших персонажей.
     */
    void eleminatedCharacters(int teamNum, int* eleminated);

    /**
     * @brief Ожидание нажатия Enter для продолжения.
     */
    void waitEnter();

    /**
     * @brief Эмулирует бросок кубика.
     * 
     * @param teamNum Номер команды игрока.
     * @param need Минимальное значение для успеха.
     * @return true, если бросок удовлетворил требование.
     */
    bool rollTheDice(int teamNum, int need);

    /**
     * @brief Выводит текстовое описание события или действия.
     * 
     * @param teamNum Номер команды игрока.
     * @param description Текст описания.
     */
    void giveDescription(int teamNum, std::string description);

    /// Конструктор по умолчанию.
    Interface() = default;

    /// Деструктор по умолчанию.
    ~Interface() = default;
};

#endif // INTERFACE_H
