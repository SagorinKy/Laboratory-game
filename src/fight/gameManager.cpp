#include "fight/gameManager.h"

/**
 * @brief Метод для выбора персонажей игроками.
 * 
 * Этот метод позволяет игрокам выбрать персонажей для своих команд, создавая их
 * на основе выбранных имен и размещая их на игровом поле.
 */
void GameManager::chooseFighter()
{
    int teamZero = 0, teamOne = 0;
    team = interface->choseCharacter(fighterNumber);
    
    Character** friends = new Character*[fighterNumber];
    Character** enemies = new Character*[fighterNumber];

    // Размещение персонажей на поле 5x21 на позициях 0, 2, 4 для каждой команды
    for (int i = 0; i < fighterNumber * 2; i++) 
    {
        int num = CharacterRegistry::getInstance().getNumberByName(team[i]);
    
        Character* character = nullptr;
    
        switch (num) {
            case 1: character = new Piper(i - (i % 2), 5 + 10 * (i % 2), i / 2); break;
            case 2: character = new Edgar(i - (i % 2), 5 + 10 * (i % 2), i / 2); break;
            case 3: character = new Bonnie(i - (i % 2), 5 + 10 * (i % 2), i / 2); break;
            case 4: character = new Frank(i - (i % 2), 5 + 2 * (i % 2), i / 2); break;
            case 5: character = new Poco(i - (i % 2), 5 + 10 * (i % 2), i / 2); break;
            case 6: character = new Grom(i - (i % 2), 5 + 10 * (i % 2), i / 2); break;
            default: break;
        }
    
        if (i % 2 == 0) 
        {
            friends[teamZero] = character;
            teamZero++;
        } 
        else 
        {
            enemies[teamOne] = character;
            teamOne++;
        }
    }
    fight->setTeams(friends, enemies);
    playingField->setField();
}

/**
 * @brief Метод для проведения боя.
 * 
 * Этот метод управляет ходами игроков, проверяет условия победы, наносит урон,
 * перемещает персонажей, и применяет эффекты во время боя.
 */
void GameManager::runFight()
{
    int turn = 0;
    while(fight->checkSurvivants())
    {
        fight->checkEffects();

        Character* pl= fight->getPlayingCharacter();
        CharacterRegistry& registry = CharacterRegistry::getInstance();
        interface->startTurn(turn, registry.getNameByNumber(pl->getID()));
        playingField->updateField();
        playingField->printField();
        playingField->printHealth();

        int action = interface->askToMakeATurn(turn % 2, pl->getEffect()->isPossible());
        if(action == 1)
        {
            if(interface->rollTheDice(turn % 2, pl->getProbability()))
            {
                std::vector<std::vector<int>> possibleCases = playingField->getPossibleShots(pl);
                int* coords;
                bool confirmation = false;
                while(!confirmation)
                {
                    playingField->print_possibleShots(possibleCases);
                    coords = interface->askShotCoord(turn % 2, possibleCases);
                    playingField->print_possibleShots(pl->shotRegion(coords[0], coords[1]));
                    confirmation = interface->askConfirmation(turn % 2);
                }
                int damage = fight->dealDamage(coords[0], coords[1]);
                if(damage == 0)
                    interface->shotMiss(turn % 2);
                else
                    interface->shotSuccess(turn % 2, damage);
            }

            if(pl->getDoubleShot())
            {
                if(interface->rollTheDice(turn % 2, pl->getProbability()))
                {
                    std::vector<std::vector<int>> possibleCases = playingField->getPossibleShots(pl);
                    int* coords;
                    bool confirmation = false;
                    while(!confirmation)
                    {
                        playingField->print_possibleShots(possibleCases);
                        coords = interface->askShotCoord(turn % 2, possibleCases);
                        playingField->print_possibleShots(pl->shotRegion(coords[0], coords[1]));
                        confirmation = interface->askConfirmation(turn % 2);
                    }
                    int damage = fight->dealDamage(coords[0], coords[1]);
                    if(damage == 0)
                        interface->shotMiss(turn % 2);
                    else
                        interface->shotSuccess(turn % 2, damage);
                }
            }
            playingField->updateField();
        }
        else if(action == 3)
        {
            fight->applyEffect();
            interface->giveDescription(turn % 2, pl->getEffect()->effectDescription());
        }
        else if(action == 2)
        {
            std::vector<std::vector<int>> emptyCases = playingField->get_and_print_possibleMoves(pl);
            int* coords = interface->askMoveCoord(turn % 2, emptyCases);
            bool hasMoved;
            hasMoved = fight->move(coords[0], coords[1]);
            while(!hasMoved)
            {
                interface->moveUnsuccess(turn % 2, coords[0], coords[1]);
                coords = interface->askMoveCoord(turn % 2, emptyCases);
                hasMoved = fight->move(coords[0], coords[1]);
            }
            interface->moveSuccess(turn % 2, coords[0], coords[1]);
        }

        int* eleminated = fight->checkHealth();
        interface->eleminatedCharacters(turn % 2, eleminated);

        interface->waitEnter();

        fight->nextTurn();
        turn++;
    }
}