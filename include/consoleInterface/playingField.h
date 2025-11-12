#ifndef PLAYING_FIELD_H
#define PLAYING_FIELD_H

#include "fight/fight.h"
#include <vector>

/**
 * @brief Класс, отвечающий за игровое поле и отображение состояния боя.
 */
class PlayingField
{
private:
    int xSize; ///< Размер поля по оси X
    int ySize; ///< Размер поля по оси Y
    Fight& fight; ///< Ссылка на объект боя
    std::vector<std::vector<std::vector<int>>> field; 
    /**
     * @brief Поле вида field[x][y][{id, status}]
     * 
     * id = 0 : пусто  
     * id = -1 : мёртвое тело, status = время до исчезновения  
     * id ∈ {1..6} : ID персонажа, status = команда
     */
public:
    /**
     * @brief Конструктор игрового поля
     * @param f Ссылка на объект боя
     */
    PlayingField(Fight& f) : xSize(5), ySize(21), fight(f) 
    {
        xSize = 5;
        ySize = 21;
        field = std::vector<std::vector<std::vector<int>>>(xSize, std::vector<std::vector<int>>(ySize, std::vector<int>(2, 0)));
    }

    /**
     * @brief Инициализирует игровое поле с текущими позициями персонажей.
     */
    void setField();

    /**
     * @brief Обновляет состояние игрового поля.
     * Перемещает персонажей, отмечает мёртвые тела и уменьшает таймер исчезновения.
     */
    void updateField();

    /**
     * @brief Выводит поле с возможными ходами для персонажа и возвращает координаты этих ходов.
     * @param player Указатель на персонажа
     * @return Вектор координат возможных ходов {{x, y}, ...}
     */
    std::vector<std::vector<int>> get_and_print_possibleMoves(Character* player);

    /**
     * @brief Выводит текущее состояние игрового поля.
     */
    void printField();

    /**
     * @brief Возвращает координаты возможных выстрелов персонажа.
     * @param player Указатель на персонажа
     * @return Вектор координат возможных выстрелов {{x, y}, ...}
     */
    std::vector<std::vector<int>> getPossibleShots(Character* player);

    /**
     * @brief Проверяет, есть ли координаты (X, Y) в списке подсвечиваемых клеток.
     * @param X Координата X
     * @param Y Координата Y
     * @param coords Вектор координат для проверки
     * @return true если координата есть в списке, иначе false
     */
    bool isRed(int X, int Y, std::vector<std::vector<int>> coords);

    /**
     * @brief Выводит поле с подсвеченными возможными выстрелами.
     * @param coords Вектор координат возможных выстрелов
     */
    void print_possibleShots(std::vector<std::vector<int>> coords);

    /**
     * @brief Выводит информацию о здоровье всех персонажей на поле.
     * Цвет текста зависит от процента оставшегося здоровья.
     */
    void printHealth();

};

#endif
