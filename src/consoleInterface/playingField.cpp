#include "consoleInterface/playingField.h"
#include "characters/character.h"
#include <iostream>
#include <iomanip>
#include "fight/CharacterRegistry.h"

void PlayingField::setField()
{
    const Character* const* ch;
    ch = fight.getFriends();
    for(int k = 0; k < fight.getFrNumber(); k++)
    {
        int x = ch[k]->getX();
        int y = ch[k]->getY();
        field[x][y][0] = ch[k]->getID();
        field[x][y][1] = 0;
    }
    ch = fight.getEnemies();
    for(int k = 0; k < fight.getEnNumber(); k++)
    {
        int x = ch[k]->getX(), y = ch[k]->getY();
        field[x][y][0] = ch[k]->getID();
        field[x][y][1] = 1;
    }
}

void PlayingField::updateField()
{
    for(int i = 0; i < xSize; i++)
    {
        for(int j = 0; j < ySize; j++)
        {
            if(field[i][j][0] > 0)
            {
                if(field[i][j][1] == 0)
                {
                    const Character* const* fr = fight.getFriends();
                    for(int k = 0; k < fight.getFrNumber(); k++)
                    {
                        if(fr[k] != nullptr && fr[k]->getID() == field[i][j][0])
                        {
                            int x = fr[k]->getX(), y = fr[k]->getY();
                            if(x == -11 && y == -11)
                            {
                                field[i][j][0] = -1;
                                field[i][j][1] = 3;
                                break;
                            }
                            else if(x == i && y == j)
                                break;
                            else if(x < xSize && y < ySize && x >= 0 && y >= 0)
                            {
                                field[x][y][0] = fr[k]->getID();
                                field[x][y][1] = 0;

                                field[i][j][0] = 0;
                                field[i][j][1] = 0;
                                break;
                            }
                        }
                    }
                }
                else if(field[i][j][1] == 1)
                {
                    const Character* const* en = fight.getEnemies();
                    for(int k = 0; k < fight.getEnNumber(); k++)
                    {
                        if(en[k] != nullptr && en[k]->getID() == field[i][j][0])
                        {
                            int x = en[k]->getX(), y = en[k]->getY();
                            if(x == -11 && y == -11)
                            {
                                field[i][j][0] = -1;
                                field[i][j][1] = 3;
                                break;
                            }
                            else if(x == i && y == j)
                                break;
                            else if(x < xSize && y < ySize && x >= 0 && y >= 0)
                            {
                                field[x][y][0] = en[k]->getID();
                                field[x][y][1] = 1;

                                field[i][j][0] = 0;
                                field[i][j][1] = 0;
                                break;
                            }
                        }
                    }
                }
            }
            else if(field[i][j][0] == -1)
            {
                if(field[i][j][1] > 0)
                    field[i][j][1]--;
                else
                {
                    field[i][j][0] = 0;
                    field[i][j][1] = 0;
                }
            }
        }
    }
}

std::vector<std::vector<int>> PlayingField::get_and_print_possibleMoves(Character* player) //prints the field with possible moves and returns array of these moves
{
    std::vector<std::vector<int>> coords;

    const std::string colors[] = {
        "\033[0m",   // сброс
        "\033[95m",  // фиолетовый — team 0
        "\033[92m",  // зелёный — team 1
        "\033[38;5;240m" // серый — DB
    };

    const std::string symbols[] = {"  ", "Pi", "Ed", "Bo", "Fr", "Po", "Gr", " ✞"};

    // Верхняя нумерация
    std::cout << "      ";
    for (int j = 0; j < ySize; j++) {
        if (j < 10) std::cout << " " << j << "  ";
        else std::cout << "" << j << "  ";
    }
    std::cout << "\n";

    // Верхняя рамка
    std::cout << "     ┌";
    for (int j = 0; j < ySize - 1; j++)
        std::cout << "───┬";
    std::cout << "───┐\n";

    // Каждая строка поля (снизу вверх)
    for (int i = xSize - 1; i >= 0; i--) {
        std::cout << "  " << i << "  │"; // Номер строки слева

        for (int j = 0; j < ySize; j++) {
            int id = field[i][j][0];
            int color = field[i][j][1];

            std::string col;
            if (id == -1) 
                col = colors[3];
            else if (id >= 1 && id <= 6)
                col = (color == 0 ? colors[1] : colors[2]);
            else
                col = colors[0];

            std::string content;
            if (id == 0)
            {
                if(player->moveIsInRange(i, j))
                {
                    col = "\033[96m";
                    content = " ◌ "; //◯◉
                    coords.push_back({i, j});
                }
                else
                    content = "   ";

            }
            else if (id == -1)
                content = " ✞ ";
            else
                content = symbols[id] + " ";

            std::cout << col << content << "\033[0m";

            if (j != ySize - 1)
                std::cout << "│"; // вертикальный разделитель
        }

        std::cout << "│\n"; // правая граница

        // Разделительная линия между строками
        if (i > 0) {
            std::cout << "     ├";
            for (int j = 0; j < ySize - 1; j++)
                std::cout << "───┼";
            std::cout << "───┤\n";
        }
    }

    // Нижняя рамка
    std::cout << "     └";
    for (int j = 0; j < ySize - 1; j++)
        std::cout << "───┴";
    std::cout << "───┘\n";

    // Нижняя нумерация
    std::cout << "      ";
    for (int j = 0; j < ySize; j++) {
        if (j < 10) std::cout << " " << j << "  ";
        else std::cout << "" << j << "  ";
    }
    std::cout << "\n";

    return coords;
}

std::vector<std::vector<int>> PlayingField::getPossibleShots(Character* player)
{
    std::vector<std::vector<int>> coords;
    for(int i = xSize - 1; i >= 0; i--)
        for(int j = 0; j < ySize; j++)
            if(player->shootIsInRange(i, j))
                coords.push_back({i, j});
    return coords;
}
bool PlayingField::isRed(int X, int Y, std::vector<std::vector<int>> coords)
{
    for(int i = 0; i < (int)coords.size(); i++)
        if(coords[i][0] == X && coords[i][1] == Y)
            return true;
    return false;
}
void PlayingField::print_possibleShots(std::vector<std::vector<int>> coords) 
{

    const std::string colors[] = {
        "\033[0m",   // сброс
        "\033[95m",  // фиолетовый — team 0
        "\033[92m",  // зелёный — team 1
        "\033[38;5;240m" // серый — DB
    };
    const std::string symbols[] = {"  ", "Pi", "Ed", "Bo", "Fr", "Po", "Gr", " ✞"};

    // Верхняя нумерация
    std::cout << "      ";
    for (int j = 0; j < ySize; j++) {
        if (j < 10) std::cout << " " << j << "  ";
        else std::cout << "" << j << "  ";
    }
    std::cout << "\n";

    // Верхняя рамка
    std::cout << "     ┌";
    for (int j = 0; j < ySize; j++)
    {
        if(this->isRed(xSize - 1, j, coords))
            std::cout << "\033[31m" << "───" << "\033[0m";
        else
            std::cout << "───";
        if(j != ySize - 1)
            std::cout << "┬";
    }
    std::cout << "┐\n";

    // Каждая строка поля (снизу вверх)
    for (int i = xSize - 1; i >= 0; i--) {

        if(this->isRed(i, 0, coords))
            std::cout << "  " << i << "\033[31m" << "  │" << "\033[0m";
        else
            std::cout << "  " << i << "  │"; // Номер строки слева

        for (int j = 0; j < ySize; j++) {
            int id = field[i][j][0];
            int color = field[i][j][1];

            std::string col;
            if (id == -1) 
                col = colors[3];
            else if (id >= 1 && id <= 6)
                col = (color == 0 ? colors[1] : colors[2]);
            else
                col = colors[0];

            std::string content;
            if (id == 0)
            {
                content = "   ";

            }
            else if (id == -1)
                content = " ✞ ";
            else
                content = symbols[id] + " ";

            std::cout << col << content << "\033[0m";



            
            if(this->isRed(i, j, coords))
                std::cout << "\033[31m" << "│" << "\033[0m";
            else if(j != ySize - 1 && this->isRed(i, j + 1, coords))
                std::cout << "\033[31m" << "│" << "\033[0m";
            else
                std::cout << "│"; // вертикальный разделитель
        }

        std::cout << "\n"; // правая граница

        // Разделительная линия между строками
        if (i > 0) {
            std::cout << "     ├";
            for (int j = 0; j < ySize; j++)
            {

                if(this->isRed(i, j, coords))
                    std::cout << "\033[31m" << "───" << "\033[0m";
                else if(i != 0 && this->isRed(i - 1, j, coords))
                    std::cout << "\033[31m" << "───" << "\033[0m";
                else
                    std::cout << "───";

                if(j != ySize - 1)
                    std::cout << "┼";
            }
            std::cout << "┤\n";
        }
    }

    // Нижняя рамка
    std::cout << "     └";
    for (int j = 0; j < ySize; j++)
    {
        if(this->isRed(0, j, coords))
            std::cout << "\033[31m" << "───" << "\033[0m";
        else
            std::cout << "───";
        if(j != ySize - 1)
            std::cout << "┴";
    }
    std::cout << "┘\n";

    // Нижняя нумерация
    std::cout << "      ";
    for (int j = 0; j < ySize; j++) {
        if (j < 10) std::cout << " " << j << "  ";
        else std::cout << "" << j << "  ";
    }
    std::cout << "\n";

}

void PlayingField::printField()
{
    const std::string colors[] = {
        "\033[0m",   // сброс
        "\033[95m",  // фиолетовый — team 0
        "\033[92m",  // зелёный — team 1
        "\033[38;5;240m" // серый — DB
    };

    const std::string symbols[] = {"  ", "Pi", "Ed", "Bo", "Fr", "Po", "Gr", " ✞"};

    // Верхняя нумерация
    std::cout << "      ";
    for (int j = 0; j < ySize; j++) {
        if (j < 10) std::cout << " " << j << "  ";
        else std::cout << "" << j << "  ";
    }
    std::cout << "\n";

    // Верхняя рамка
    std::cout << "     ┌";
    for (int j = 0; j < ySize - 1; j++)
        std::cout << "───┬";
    std::cout << "───┐\n";

    // Каждая строка поля (снизу вверх)
    for (int i = xSize - 1; i >= 0; i--) {
        std::cout << "  " << i << "  │"; // Номер строки слева

        for (int j = 0; j < ySize; j++) {
            int id = field[i][j][0];
            int color = field[i][j][1];

            std::string col;
            if (id == -1) col = colors[3];
            else if (id >= 1 && id <= 6)
                col = (color == 0 ? colors[1] : colors[2]);
            else
                col = colors[0];

            std::string content;
            if (id == 0)
                content = "   ";
            else if (id == -1)
                content = " ✞ ";
            else
                content = symbols[id] + " ";

            std::cout << col << content << "\033[0m";

            if (j != ySize - 1)
                std::cout << "│"; // вертикальный разделитель
        }

        std::cout << "│\n"; // правая граница

        // Разделительная линия между строками
        if (i > 0) {
            std::cout << "     ├";
            for (int j = 0; j < ySize - 1; j++)
                std::cout << "───┼";
            std::cout << "───┤\n";
        }
    }

    // Нижняя рамка
    std::cout << "     └";
    for (int j = 0; j < ySize - 1; j++)
        std::cout << "───┴";
    std::cout << "───┘\n";

    // Нижняя нумерация
    std::cout << "      ";
    for (int j = 0; j < ySize; j++) {
        if (j < 10) std::cout << " " << j << "  ";
        else std::cout << "" << j << "  ";
    }
    std::cout << "\n";
}

void PlayingField::printHealth()
{
    std::string blue = "\033[34m";
    std::string green = "\033[32m";
    std::string yellow = "\033[33m";
    std::string red = "\033[31m";
    std::string pink = "\033[36m";
    std::string frColour = "\033[95m";
    std::string enColour = "\033[92m";

    std::cout << pink << std::setw(19) << "" << std::setw(19) << "🞣🞥🞧 Health info 🞧🞥🞣\n"; //w = 19

    std::cout << pink << "┌";
    for(int i = 0; i + 1 < 57; i++)
        std::cout << pink << "─";
    std::cout << pink << "┐";
    std::cout << "\033[0m\n";

    std::cout << frColour << " " << std::setw(11) << "Team 0" << std::setw(11) << "HP" << std::setw(6) << "" << enColour << std::setw(11) << "Team 1" << std::setw(11) << "HP" << "\n";
    
    std::cout << pink << "├";
    for(int i = 0; i + 1 < 57; i++)
        std::cout << pink << "─";
    std::cout << pink << "┤";
    std::cout << "\033[0m\n";

    Character** fr = fight.getFriends();
    std::vector<std::string> frNames = {};
    std::vector<std::string> frHealth = {};

    Character** en = fight.getEnemies();
    std::vector<std::string> enNames = {};
    std::vector<std::string> enHealth = {};

    for(int i = 0; i < fight.getFrNumber(); i++)
    {
        if(fr[i] != nullptr)
        {
            frNames.push_back(CharacterRegistry::getInstance().getNameByNumber(fr[i]->getID()));
            int health = fr[i]->getHealth();
            int healthRange = fr[i]->getHealthRange();
            double percent = static_cast<double>(health) / healthRange;
            if(health == healthRange)
                frHealth.push_back(blue + std::to_string(health));
            else if(percent >= 0.7)
                frHealth.push_back(green + std::to_string(health));
            else if(percent >= 0.3)
                frHealth.push_back(yellow + std::to_string(health));
            else
                frHealth.push_back(red + std::to_string(health));

        }
    }
    for(int i = 0; i < fight.getEnNumber(); i++)
    {
        if(en[i] != nullptr)
        {
            enNames.push_back(CharacterRegistry::getInstance().getNameByNumber(en[i]->getID()));
            int health = en[i]->getHealth();
            int healthRange = en[i]->getHealthRange();
            double percent = static_cast<double>(health) / healthRange;
            if(health == healthRange)
                enHealth.push_back(blue + std::to_string(health));
            else if(percent >= 0.7)
                enHealth.push_back(green + std::to_string(health));
            else if(percent >= 0.3)
                enHealth.push_back(yellow + std::to_string(health));
            else
                enHealth.push_back(red + std::to_string(health));

        }
    }
    for(int i = 0; i < (int)std::max(size(frNames), size(enNames)); i++)
    {
        std::cout << frColour << " " << std::setw(11);
        if(i < (int)size(frNames))
            std::cout << frNames[i] << std::setw(17) << frHealth[i];
        else
            std::cout << "" << std::setw(12) << "";
        
        if(i < (int)size(enNames))
            std::cout << std::setw(5) << "" << enColour << std::setw(11) << enNames[i] << std::setw(17) << enHealth[i];
        std::cout << "\n";
    }

    std::cout << pink << "└";
    for(int i = 0; i + 1 < 57; i++)
        std::cout << pink << "─";
    std::cout << pink << "┘";
    std::cout << "\033[0m\n";
}