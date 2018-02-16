#ifndef PFMETA_HPP
#define PFMETA_HPP

#include "PfSpell.hpp"

#include <string>
using namespace std;

enum class Alignment {NUL = 0, LAWFUL_GOOD = '1', NEUTRAL_GOOD, CHAOTIC_GOOD, LAWFUL_NEUTRAL, TRUE_NEUTRAL,\
CHAOTIC_NEUTRAL, LAWFUL_EVIL, NEUTRAL_EVIL, CHAOTIC_EVIL};

enum class CreatureType {NUL = 0, ABERRATION = '1', ANIMAL, CONSTRUCT, DRAGON, FEY, HUMANOID, MAGICAL_BEAST,\
MONSTROUS_HUMANOID, OOZE, OUTSIDER, PLANT, UNDEAD, VERMIN};

enum class Size {NUL = 0, FINE = 1, DIMINUTIVE, TINY, SMALL, MEDIUM, LARGE, HUGE, GARGANTUAN, COLOSSAL};

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

struct Sla{
	int frequency;
	string timePeriod;

	SpellOutput spell;
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