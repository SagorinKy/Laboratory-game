#include "characters/character.h"

bool Character::moveIsInRange(int X, int Y)
{
	int difX = std::abs(X - x);
	int difY = std::abs(Y - y);
	
	if(difX * difY == 0 && difX + difY <= speedInRow)
		return true;
	if(difX == difY && difX <= speedDiag)
		return true;
	return false;
}
int Character::getHealth()
{
	return health;
}
int Character::getHealthRange()
{
	return healthRange;
}
void Character::changeHelth(int Health)
{
	health += Health;
	if(health > healthRange)
		health = healthRange;
}
void Character::addRange(int amount)
{
	speedDiag += amount;
	speedInRow += amount;
}
void Character::addLuck(int amount)
{
	hitProb += amount;
}
int Character::getX() const
{
	return x;
}
int Character::getY() const
{
	return y;
}
void Character::setCoord(int X, int Y)
{
	x = X;
	y = Y;
}
void Character::move(int X, int Y)
{
	if(Character::moveIsInRange(X, Y))
	{
		x = X;
		y = Y;
	}
}
Effect* Character::getEffect()
{
	return effect;
}
int Character::getID() const
{
	return ID;
}
int Character::getDamage()
{
	return damage;
}
int Character::makeDamage(int d)
{
	health -= d;
	if(health <= 0)
	{
		x = -11;
		y = -11;
		return d + health;
	}
	else 
		return d;
}
bool Character::shootIsInRange(int X, int Y) {return 0;}
bool Character::shootIsAccurate() {return 0;}
std::vector<std::vector<int>> Character::shotRegion(int X, int Y) 
{
	std::vector<std::vector<int>> a = {{-1, 0, 0}};
	return a;
}
bool Character::getDoubleShot()
{
	return doubleShot;
}

int Character::getProbability()
{
	return 6 - hitProb + 1;
}