#ifndef PFMETA_HPP
#define PFMETA_HPP

#include <string>

using namespace std;

/* I'd prefer it if all enums are referred to by specifying the enum it came
 * from. I think namespace is probably the wrong term for this, and something
 * about "scoped" seems like it could be somehow confusing. Whatever the term
 * for referring to enums as EnumName::ENUM_VALUE instead of just ENUM_VALUE is
 * what I mean to type.
 */

enum CreatureType {ABERRATION = 1, ANIMAL, CONSTRUCT, DRAGON, FEY, HUMANOID, MAGICAL_BEAST, MONSTROUS_HUMANOID, OOZE, OUTSIDER, PLANT, UNDEAD, VERMIN};
enum Size {FINE = 1, DIMINUTIVE, TINY, SMALL, MEDIUM, LARGE, HUGE, GARGANTUAN, COLOSSAL};

struct Abilities{

	int str;
	int strMod;
	string displayStr;

	int dex;
	int dexMod;
	string displayDex;

	int con;
	int conMod;
	string displayCon;

	int intelligence;
	int intMod;
	string displayInt;

	int wis;
	int wisMod;
	string displayWis;

	int cha;
	int chaMod;
	string displayCha;
};

struct AC {

	int armor = 0;
	int shield = 0;
	int dex = 0;
	int natural = 0;
	int dodge = 0;
	int deflection = 0;
	int sacred = 0;
	int profane = 0;
	int insight = 0;
	int luck = 0;
	int racial = 0;
	int size = 0;
	int trait = 0;
	int untyped = 0;

	int totalAc = 10;
	int flatFootAc;
	int touchAc;

	string breakdown;

};

struct HitDice{
	int d4 = 0;
	int d6 = 0;
	int d8 = 0;
	int d10 = 0;
	int d12 = 0;

	int totalHd;
	int racialHdCount;
	int bonus = 0; //Intended for flat bonuses, like a construct's size bonus. Bonus HP from CON or CHA (if undead) are calculated as needed.

};

struct Maneuvers{
	bool agileManuevers = false;

	int cmb;
	int cmd;

	string specialCmb;
	string specialCmd;
};

struct Saves{
	bool goodFort = false;
	bool goodReflex = false;
	bool goodWill = false;

	int fort;
	int reflex;
	int will;

};



#endif