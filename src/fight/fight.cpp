#include "fight/fight.h"
#include <iostream>

/**
 * @brief Получить номер текущего хода.
 * 
 * Метод возвращает номер текущего хода в бою.
 * 
 * @return Номер текущего хода.
 */
int Fight::getTurn()
{
    return turnNumber;
}

/**
 * @brief Переход к следующему ходу.
 * 
 * Этот метод изменяет индексы текущих игроков в каждой команде (друзья/враги)
 * и обновляет номер хода.
 */
void Fight::nextTurn()
{
    int k = 0;
    if(turnNumber % 2 == 0)
    {
        friendsInd = (friendsInd + 1) % friendsNumber;
        while(enemies[enemiesInd] == nullptr && k < enemiesNumber)
        {
            enemiesInd = (enemiesInd + 1) % enemiesNumber;
            k++;
        }
    }
    else
    {
        enemiesInd = (enemiesInd + 1) % enemiesNumber;
        while(friends[friendsInd] == nullptr && k < friendsNumber)
        {
            friendsInd = (friendsInd + 1) % friendsNumber;
            k++;
        }
    }
    turnNumber++;
}

/**
 * @brief Получить массив друзей.
 * 
 * Метод возвращает указатель на массив друзей.
 * 
 * @return Указатель на массив друзей.
 */
Character** Fight::getFriends() const
{
    return friends;
}

/**
 * @brief Получить массив врагов.
 * 
 * Метод возвращает указатель на массив врагов.
 * 
 * @return Указатель на массив врагов.
 */
Character** Fight::getEnemies() const
{
    return enemies;
}

/**
 * @brief Получить количество друзей.
 * 
 * Метод возвращает количество персонажей в команде друзей.
 * 
 * @return Количество друзей.
 */
int Fight::getFrNumber()
{
    return friendsNumber;
}

/**
 * @brief Получить количество врагов.
 * 
 * Метод возвращает количество персонажей в команде врагов.
 * 
 * @return Количество врагов.
 */
int Fight::getEnNumber()
{
    return enemiesNumber;
}

/**
 * @brief Получить текущего играющего персонажа.
 * 
 * Этот метод возвращает персонажа, который должен совершить ход.
 * В зависимости от номера хода возвращается либо персонаж из команды друзей,
 * либо из команды врагов.
 * 
 * @return Указатель на текущего играющего персонажа.
 */
Character* Fight::getPlayingCharacter()
{
    if(turnNumber % 2 == 0)
        return friends[friendsInd];
    else
        return enemies[enemiesInd];
}

/**
 * @brief Установить команды для боя.
 * 
 * Метод используется для установки команд друзей и врагов в бою.
 * 
 * @param f Массив друзей.
 * @param e Массив врагов.
 */
void Fight::setTeams(Character** f, Character** e)
{
    friends = f;
    enemies = e;
}

/**
 * @brief Проверить здоровье персонажей.
 * 
 * Этот метод проверяет здоровье всех персонажей в одной из команд и удаляет
 * тех, чье здоровье меньше или равно нулю. Возвращает массив с ID убитых персонажей.
 * 
 * @return Массив с ID убитых персонажей (первый элемент - количество убитых).
 */
int* Fight::checkHealth()
{
    Character** a;
    int n;
    int teamInd = (turnNumber + 1) % 2;
    if(teamInd == 0)
    {
        a = friends;
        n = friendsNumber;
    }
    else
    {
        a = enemies;
        n = friendsNumber;
    }
    int* dead = new int[n + 1];
    dead[0] = 0;
    for(int i = 0; i < n; i++)
    {
        dead[i + 1] = 0;
        if(a[i] != nullptr)
        {
            if(a[i]->getHealth() <= 0)
            {
                dead[i + 1] = a[i]->getID();
                delete a[i];
                a[i] = nullptr;
                dead[0]++;
            }
        }
    }
    return dead;
}

/**
 * @brief Проверить наличие выживших персонажей в обеих командах.
 * 
 * Метод проверяет, есть ли в обеих командах хотя бы один выживший персонаж.
 * 
 * @return true, если в обеих командах есть выжившие персонажи, иначе false.
 */
bool Fight::checkSurvivants()
{
    bool fr = false, en = false; 
    for(int i = 0; i < friendsNumber; i++)
    {
        if(friends[i] != nullptr)
        {
            fr = true;
        }
    }
    for(int i = 0; i < enemiesNumber; i++)
    {
        if(enemies[i] != nullptr)
        {
            en = true;
        }
    }
    return en && fr;
}

/**
 * @brief Получить координаты текущего персонажа.
 * 
 * Этот метод возвращает координаты текущего играющего персонажа.
 * 
 * @return Массив из двух элементов: координаты X и Y текущего персонажа.
 */
int* Fight::getCoords()
{
    int* coords = new int[2];
    coords[0] = getPlayingCharacter()->getX();
    coords[1] = getPlayingCharacter()->getY();
    return coords;
}

/**
 * @brief Нанести урон врагу.
 * 
 * Этот метод вычисляет урон, который текущий персонаж наносит врагам в области
 * выбранной цели. Возвращает общий урон, нанесенный всем врагам в пределах области.
 * 
 * @param X Координата X цели.
 * @param Y Координата Y цели.
 * @return Общий урон, нанесенный врагам.
 */
int Fight::dealDamage(int X, int Y)
{
    int damage = 0;
    std::vector<std::vector<int>> shot = getPlayingCharacter()->shotRegion(X, Y);
    int n;
    Character** a;
    if(turnNumber % 2 == 0)
    {
        n = enemiesNumber;
        a = enemies;    
    }
    else
    {
        n = friendsNumber;
        a = friends; 
    }
    for(int i = 0; i < n; i++)
    {
        if(a[i] != nullptr)
        {
            for(auto& it : shot)
            {
                if(it[0] == a[i]->getX() && it[1] == a[i]->getY())
                    damage += a[i]->makeDamage(it[2]);
            }
        }
    }
    return damage;
}

/**
 * @brief Переместить персонажа.
 * 
 * Этот метод проверяет, возможно ли переместить текущего персонажа в указанную
 * точку, и если да, перемещает его.
 * 
 * @param x Новая координата X.
 * @param y Новая координата Y.
 * @return true, если перемещение возможно, иначе false.
 */
bool Fight::move(int x, int y)
{
    Character* a = getPlayingCharacter();
    if(a->moveIsInRange(x, y))
    {
        a->move(x, y);
        return true;
    }
    return false;
}

/**
 * @brief Проверить и обновить эффекты.
 * 
 * Этот метод вызывает обновление эффектов для всех персонажей в команде, чей
 * ход наступил.
 */
void Fight::checkEffects()
{
    Character** a;
    int n;
    int teamInd = turnNumber % 2;
    if(teamInd == 0)
    {
        a = friends;
        n = friendsNumber;
    }
    else
    {
        a = enemies;
        n = friendsNumber;
    }
    for(int i = 0; i < n; i++)
        if(a[i] != nullptr)
            a[i]->getEffect()->nextTurn();
}

/**
 * @brief Применить эффект к персонажу.
 * 
 * Если у текущего персонажа есть эффект, который может быть применен,
 * этот эффект будет активирован.
 */
void Fight::applyEffect()
{
    if(getPlayingCharacter()->getEffect()->isPossible())
        getPlayingCharacter()->getEffect()->startEffect();
}
