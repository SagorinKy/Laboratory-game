#ifndef CHARACTER_H
#define CHARACTER_H

#include <math.h>
#include <string>
#include <vector>
#include "effects/effects.h"
#include "fight/CharacterRegistry.h"

class Effect;

class Character
{
	protected:
		std::string name;
		int ID;
		int number;
		int hitProb = 6;
		int speedInRow;
		int speedDiag;
		int healthRange;
		int health;
		int damage;

		int x, y;
		int turn = 0;
		Effect* effect;
		bool doubleShot;

	public:
		int getX() const; //+
		int getY() const; //+
		int getID() const; //+
		int getDamage(); //+
		void setCoord(int X, int Y);
		bool moveIsInRange(int X, int Y); //+
		void move(int X, int Y); //+
		virtual bool shootIsInRange(int X, int Y); //p
		virtual bool shootIsAccurate(); //p - add accuracy
		virtual std::vector<std::vector<int>> shotRegion(int X, int Y); //p
		int getHealth(); //+
		int getHealthRange(); //+
		void changeHelth(int Health); //+
		void addRange(int amount);
		void addLuck(int amount);
		int makeDamage(int d); //+
		bool canMove();
		Effect* getEffect();
		bool getDoubleShot();
		int getProbability();

		Character(int X, int Y, int num, int chID) : ID(chID), number(num), x(X), y(Y), effect(nullptr) 
		{
			name = CharacterRegistry::getInstance().getNameByNumber(chID);
		}
		virtual ~Character() = default;
};


#endif