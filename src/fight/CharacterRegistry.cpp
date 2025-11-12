#include "fight/CharacterRegistry.h"

/**
 * @brief Конструктор класса CharacterRegistry.
 * 
 * Инициализирует количество персонажей и их соответствующие имена и номера.
 */
CharacterRegistry::CharacterRegistry() : num(6), characters{
    {"Piper", 1},
    {"Edgar", 2},
    {"Bonnie", 3},
    {"Frank", 4},
    {"Poco", 5},
    {"Grom", 6}
} {}

/**
 * @brief Получить единственный экземпляр класса CharacterRegistry.
 * 
 * Реализует паттерн Singleton, возвращая единственный экземпляр для использования
 * в других частях программы.
 * 
 * @return Ссылка на единственный экземпляр класса.
 */
CharacterRegistry& CharacterRegistry::getInstance() {
    static CharacterRegistry instance; ///< Единственный экземпляр класса.
    return instance;
}

/**
 * @brief Получить номер персонажа по его имени.
 * 
 * Ищет персонажа по имени и возвращает его номер, если персонаж найден.
 * Если персонаж с таким именем не найден, возвращается -1.
 * 
 * @param name Имя персонажа.
 * @return Номер персонажа или -1, если персонаж не найден.
 */
int CharacterRegistry::getNumberByName(std::string& name) 
{
    auto it = characters.find(name); ///< Ищем персонажа по имени.
    if (it != characters.end()) 
        return it->second; ///< Возвращаем номер, если персонаж найден.
    else 
        return -1; ///< Возвращаем -1, если персонаж не найден.
}

/**
 * @brief Получить имя персонажа по его номеру.
 * 
 * Ищет персонажа по номеру и возвращает его имя. Если такого персонажа нет,
 * возвращается строка "err".
 * 
 * @param number Номер персонажа.
 * @return Имя персонажа или строка "err", если персонажа с таким номером нет.
 */
std::string CharacterRegistry::getNameByNumber(int number) 
{
    for (const auto& [name, num] : characters) {
        if (num == number) return name; ///< Возвращаем имя персонажа по номеру.
    }
    return "err"; ///< Возвращаем "err", если персонаж с таким номером не найден.
}

/**
 * @brief Получить количество персонажей.
 * 
 * Этот метод возвращает общее количество персонажей в реестре.
 * 
 * @return Число персонажей.
 */
int CharacterRegistry::getNum() 
{
    return num; ///< Возвращаем количество персонажей.
}