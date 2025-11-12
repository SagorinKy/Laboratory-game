#include "consoleInterface/interface.h"
#include <thread>
#include <chrono>

struct Team;

/**
 * @brief Возвращает цвет команды для консольного вывода.
 * 
 * @param ind Индекс команды.
 * @return Строка с кодом цвета.
 */
std::string Interface::colour(int ind)
{
    if(ind % 2 == 0)
        return "\033[95m";
    else
        return "\033[92m";
}

/**
 * @brief Позволяет игрокам выбрать персонажей.
 * 
 * @param num Количество персонажей для каждой команды.
 * @return Массив выбранных персонажей.
 */
std::string* Interface::choseCharacter(int num)
{
    CharacterRegistry& registry = CharacterRegistry::getInstance();
    std::string* fighters = new std::string[num * 2]; //chosen characters
    int ind = 0;
    for(int i = 0; i < num * 2; i++)
    {
        int countCharacters = 0;
        std::string* characters = new std::string[maxNum]; //available characters
        std::cout << this->colour(i) << "Chose fighter:\033[0m" << std::endl;
        for(int j = 0; j < maxNum; j++) //makes list of available characters
        {
            bool taken = false;
            for(int k = 0; k < i; k++)
            {
                if(fighters[k] == registry.getNameByNumber(j + 1))
                {
                    taken = true;
                    break;
                }
            }
            if(!taken)
            {
                std::cout << countCharacters + 1 << ". " << registry.getNameByNumber(j + 1) << std::endl;
                characters[countCharacters] = registry.getNameByNumber(j + 1);
                countCharacters++;
            }
        }
        while(true)
        {
            std::cout << this->colour(i) << "Insert its number: \033[0m";
            ind = 0;
            std::cin >> ind; // may cause errors
            if(ind > 0 && ind <= countCharacters)
            {
                fighters[i] = characters[ind - 1];
                break;
            }
            std::cout << this->colour(i) << "Error! Wrong number!\033[0m" << std::endl;
        }
        delete[] characters;
    }
    return fighters;
}

/**
 * @brief Запрашивает у игрока выбор действия в текущем ходу.
 * 
 * @param teamNum Номер команды игрока.
 * @param effectIsPossible Флаг возможности применения эффекта.
 * @return Номер выбранного действия.
 */
int Interface::askToMakeATurn(int teamNum, bool effectIsPossible)
{
    std::cout << this->colour(teamNum) << "Choose an action: \033[0m" << std::endl;
    std::cout << "1. Attack" << std::endl;
    std::cout << "2. Make a move" << std::endl;
    if(effectIsPossible)
        std::cout << "3. Apply an effect" << std::endl;
    int ind;
    int choice = 2;
    if(effectIsPossible)
        choice = 3;
    while(true)
    {
        std::cin >> ind;
        if (ind <= choice && ind > 0)
        {
            return ind;
        }
        else
            std::cout << this->colour(teamNum) << "Error! Chose an action: \033[0m" << std::endl;
    }
}

/**
 * @brief Запрашивает координаты для перемещения персонажа.
 * 
 * @param teamNum Номер команды игрока.
 * @param emptyCases Возможные координаты для перемещения.
 * @return Массив координат [X, Y].
 */
int* Interface::askMoveCoord(int teamNum, std::vector<std::vector<int>> emptyCases)
{
    int* coord = new int[2];
    while(true)
    {
        std::cout << this->colour(teamNum) << "Insert coordinates to make a move: \033[0m" << std::endl;
        std::cin >> coord[0] >> coord[1];
        for(int i = 0; i < (int)emptyCases.size(); i++)
        {
            if(coord[0] == emptyCases[i][0] && coord[1] == emptyCases[i][1])
                return coord;
        }
        std::cout << this->colour(teamNum) << "Error! Move is out of range: \033[0m" << std::endl;
    }
    return nullptr;
}

/**
 * @brief Запрашивает координаты для выстрела.
 * 
 * @param teamNum Номер команды игрока.
 * @param possibleCases Возможные координаты для выстрела.
 * @return Массив координат [X, Y].
 */
int* Interface::askShotCoord(int teamNum, std::vector<std::vector<int>> possibleCases)
{
    int* coord = new int[2];
    while(true)
    {
        std::cout << this->colour(teamNum) << "Insert coordinates to shoot: \033[0m" << std::endl;
        std::cin >> coord[0] >> coord[1];
        for(int i = 0; i < (int)possibleCases.size(); i++)
        {
            if(coord[0] == possibleCases[i][0] && coord[1] == possibleCases[i][1])
                return coord;
        }
        std::cout << this->colour(teamNum) << "Error! Shot is out of range: \033[0m" << std::endl;
    }
    return nullptr;
}

/**
 * @brief Спрашивает подтверждение действия игрока.
 * 
 * @param teamNum Номер команды игрока.
 * @return true если игрок подтвердил, иначе false.
 */
bool Interface::askConfirmation(int teamNum)
{
    std::cout << this->colour(teamNum) << "Do you want to stay on this shot? Type 'y' or 'n' for yes/no: \033[0m";
    char c = 'w';
    while(c != 'y' && c != 'n')
    {
        try
        {
            std::cin >> c;
            if(c != 'y' && c != 'n')
                throw 0;
        }
        catch(int code)
        {
             std::cout << "You have to white down y or n";
        }
    }
    return c == 'y';
}

/**
 * @brief Выводит сообщение о успешном выстреле и нанесённом уроне.
 * 
 * @param teamNum Номер команды игрока.
 * @param points Количество нанесённых очков урона.
 */
void Interface::shotSuccess(int teamNum, int points)
{
    std::cout << this->colour(teamNum) << "You successfully hit enemy! \033[0m" << std::endl;
    std::cout << this->colour(teamNum) << "You deal \033[95m" << points << this->colour(teamNum) << " points of damage! \033[0m" << std::endl;
}

/**
 * @brief Выводит сообщение о промахе игрока.
 * 
 * @param teamNum Номер команды игрока.
 */
void Interface::shotMiss(int teamNum)
{
    std::cout << this->colour(teamNum) << "You missed :( \033[0m" << std::endl;
}

/**
 * @brief Выводит сообщение об успешном перемещении персонажа.
 * 
 * @param teamNum Номер команды игрока.
 * @param x Координата X.
 * @param y Координата Y.
 */
void Interface::moveSuccess(int teamNum, int x, int y)
{
    std::cout << this->colour(teamNum) << "You successfully moved (" << x << ", " << y << ")! \033[0m" << std::endl;
}

/**
 * @brief Выводит сообщение о неудачном перемещении персонажа.
 * 
 * @param teamNum Номер команды игрока.
 * @param x Координата X.
 * @param y Координата Y.
 */
void Interface::moveUnsuccess(int teamNum, int x, int y)
{
    std::cout << this->colour(teamNum) << "You can't move (" << x << ", " << y << ")! Try again!\033[0m" << std::endl;
}

/**
 * @brief Выводит сообщение о применении эффекта лечения.
 * 
 * @param teamNum Номер команды игрока.
 * @param healAmount Количество здоровья, восстанавливаемого за ход.
 */
void Interface::effectHeal(int teamNum, int healAmount)
{
    std::cout << this->colour(teamNum) << "You used effect! This character will gain \033[96m" << healAmount << this->colour(teamNum) << " points per turn for 4 turns!\033[0m" << std::endl;
}

/**
 * @brief Выводит сообщение о применении эффекта увеличенного урона.
 * 
 * @param teamNum Номер команды игрока.
 */
void Interface::effectAdditionalDamage(int teamNum)
{
    std::cout << this->colour(teamNum) << "You used effect! This character will deal 75% more damage next move!\033[0m" << std::endl;
}

/**
 * @brief Выводит информацию о погибших персонажах.
 * 
 * @param teamNum Номер команды игрока.
 * @param eleminated Массив идентификаторов погибших персонажей.
 */
void Interface::eleminatedCharacters(int teamNum, int* eleminated)
{
    std::cout << this->colour(teamNum);
    int i = 1;
    while(eleminated[0] != 0)
    {
        if(eleminated[i] != 0)
        {
            std::cout << "Character " << CharacterRegistry::getInstance().getNameByNumber(eleminated[i]) << " is dead" << std::endl;
            eleminated[0]--;
        }
        i++;
    }
    std::cout << "\033[0m\n";
}

/**
 * @brief Выводит информацию о начале хода команды.
 * 
 * @param t Номер хода.
 * @param name Имя персонажа, который делает ход.
 */
void Interface::startTurn(int t, std::string name)
{
    std::cout << "\n\nTurn #" << t << "!" << std::endl;
    std::cout << this->colour(t) << "Team " << t%2 << std::endl << name << " is" << "\033[0m to play!" << std::endl;
}

/**
 * @brief Ожидание нажатия Enter для продолжения.
 */
void Interface::waitEnter()
{
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

/**
 * @brief Выполняет бросок кубика и проверяет результат на успех.
 * 
 * @param teamNum Номер команды игрока.
 * @param need Минимальное значение для успешного броска.
 * @return true если бросок успешен, иначе false.
 */
bool Interface::rollTheDice(int teamNum, int need)
{
    std::cout << this->colour(teamNum) << "Press Enter to roll the dice...\n";
    std::cout << this->colour(teamNum) << "You need at least " << need << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    std::cout << "\033[031m";
    int got = dice.roll();
    switch (got)
    {
        case 1: std::cout << "⚀"; break;
        case 2: std::cout << "⚁"; break;
        case 3: std::cout << "⚂"; break;
        case 4: std::cout << "⚃"; break;
        case 5: std::cout << "⚄"; break;
        case 6: std::cout << "⚅"; break;
    }
    std::cout << "\033[0m\n";
    std::cout << "You got " << got << "!\n";
    if(got >= need)
    {
        std::cout << this->colour(teamNum) << "Shot will hit its target\n";
        return true;
    }
    std::cout << this->colour(teamNum) << "Shot won't hit its target\n";
    return false;    
}

/**
 * @brief Выводит текстовое описание действия или события.
 * 
 * @param teamNum Номер команды игрока.
 * @param description Текстовое описание.
 */
void Interface::giveDescription(int teamNum, std::string description)
{
    std::cout << this->colour(teamNum) << description << "\033[0m\n";
}
