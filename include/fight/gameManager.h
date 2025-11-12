#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "fight.h"
#include "consoleInterface/playingField.h"
#include "consoleInterface/interface.h"
#include "characters/piper.h"
#include "characters/edgar.h"
#include "characters/bonnie.h"
#include "characters/frank.h"
#include "characters/poco.h"
#include "characters/grom.h"
#include "CharacterRegistry.h"
#include <map>
#include <string>

/**
 * @class GameManager
 * @brief Класс, управляющий выбором персонажей и проведением боя.
 * 
 * Этот класс отвечает за выбор персонажей для игры, инициализацию игры,
 * и проведение боевых действий между персонажами.
 */
class GameManager
{
private:
    int fighterNumber; ///< Количество выбранных персонажей.
    std::string* team; ///< Массив, содержащий имена выбранных персонажей.
    Interface* interface; ///< Интерфейс для взаимодействия с пользователем.
    Fight* fight; ///< Объект, управляющий боями.
    PlayingField* playingField; ///< Игровое поле.

public:
    /**
     * @brief Выбор персонажей для игры.
     * 
     * Этот метод позволяет игроку выбрать персонажей для своих команд
     * и инициализирует их соответствующими данными.
     */
    void chooseFighter(); //+ 

    /**
     * @brief Запуск боя.
     * 
     * Этот метод запускает игровой процесс, чередуя ходы между игроками
     * и позволяя им наносить урон, двигаться и применять эффекты.
     */
    void runFight(); //+ (?)

    /**
     * @brief Конструктор класса GameManager.
     * 
     * Конструктор инициализирует объект GameManager, создавая необходимые
     * объекты для проведения игры.
     * 
     * @param playerNum Количество игроков в команде.
     */
    GameManager() = default;
    GameManager(int playerNum) : fighterNumber(3)
    {
        fight = new Fight(fighterNumber, playerNum); 
        interface = new Interface();
        playingField = new PlayingField(*fight);
    }

    /**
     * @brief Деструктор класса GameManager.
     * 
     * Освобождает ресурсы, занятые объектами GameManager.
     */
    ~GameManager() = default;
};

#endif