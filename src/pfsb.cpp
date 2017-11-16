#include "platform.hpp"
#include "version.hpp"

#include <iostream>
#include <new>
#include <string>
#include <fstream>

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <limits>

#define _ERR_UNRECOGNIZED_CLI_OPTION 1
#define _ERR_INVALID_SWITCH 2
#define _ERR_INVALID_SIZE 3
#define _ERR_INVALID_CREATURE_TYPE 4

/* Why is including cstdlib to call exit necessary now?
 * It's never been necessary before. I could write a program
 * that compiled on both Windows and Linux and nobody ever had
 * an issue with it.
 */

using namespace std;

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

struct BaseStats{

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

struct HitDice{
	int d4 = 0;
	int d6 = 0;
	int d8 = 0;
	int d10 = 0;
	int d12 = 0;

	int totalHd;
	int bonus = 0; //Intended for flat bonuses, like a construct's size bonus. Bonus HP from CON or CHA (if undead) are calculated as needed.

};

struct Saves{
	bool goodFort = false;
	bool goodReflex = false;
	bool goodWill = false;

	int fort;
	int reflex;
	int will;

};

struct Maneuvers{
	bool agileManuevers = false;

	int cmb;
	int cmd;

	string specialCmb;
	string specialCmd;
};

enum CreatureType {ABERRATION = 1, ANIMAL, CONSTRUCT, DRAGON, FEY, HUMANOID, MAGICAL_BEAST, MONSTROUS_HUMANOID, OOZE, OUTSIDER, PLANT, UNDEAD, VERMIN};

void printVersion();
void doProgram();
long crToXp(double cr, char* displayCr);
void insertIntoFile(fstream& monster, const char* toInsert, long beforeDollar, int keyLength, const char* baseFileName);
long findDollar(fstream& monster, long currentPos);
AC determineAC(const int dex, char size);
string determineAcBreakdown(AC ac);
CreatureType determineCreatureType(string creatureType);
BaseStats determineBaseStats(const CreatureType);
Saves determineSaves(const HitDice hd, const BaseStats abilities, const CreatureType);
HitDice determineHD(const CreatureType, char creatSize);
int determineHP(const HitDice hd, const BaseStats abilities, const CreatureType);
string determineHpBreakdown(const HitDice hd, const BaseStats abilities, const CreatureType);
int determineBab(const HitDice hd, const CreatureType);
int determineInitiative(const int dexMod);
Maneuvers determineCombatManeuvers(const BaseStats abilities, const int bab);
string determineMeleeAtk(const int bab, const BaseStats abilities);
string determineRangedAtk(const int bab, const BaseStats abilities);
string determineFeats(const HitDice hd);
string determineEnvironment();
string determineSpace(const char creatSize);
string determineReach(const char creatSize);
string determineSkills(const BaseStats abilities, const HitDice hd, const CreatureType);
string determineLanguages();
string determineDefensiveAbilities();
string determineSpecialQualities();
string determineSpecialAttacks();
string determineImmunities(const CreatureType);
string determineSenses(const BaseStats abilities,const HitDice hd);
string determineAura();
string determineOrganization();
string determineTreasure();
string determineSpeed();
string determineSpecAbilities();
void clearBuffer();
string stringToLower(string);


void findAndReplace(fstream& outfile, const char* replacement, const char* searchKey, const char* fileName);

int main(int argc, char** argv) {
	if (argc == 2 && !strcmp("--version",argv[1])) {
		printVersion();

		exit(0);
	}
	if (argc == 2 && !strcmp("--help",argv[1])) {
		cout << "Run the program with no arguments to use it. Use --version to print version info. Use --ogl to print OGL-mandated information about product identity \
and open game content. Use --help to print this text." << endl;
		cout << "Note: It is strongly advised that no user inputs contain dollar signs."<< endl << endl;

		exit(0);
	}

	if (argc == 1) {
		doProgram();

		#ifdef _DEBUG
		cout << "Exited doProgram()" << endl;
		#endif

		exit(0);
	}

	if (argc == 2 && !strcmp("--ogl",argv[1])) {
		cout << endl << "Product Identity: The following items are hereby identified as Product Identity, as defined in the Open Game License version 1.0a, Section 1(e), \
and are not Open Content: All trademarks, registered trademarks, proper names (characters, deities, etc.), dialogue, plots, storylines, locations, characters, artwork, \
and trade dress. (Elements that have previously been designated as Open Game Content or are in the public domain are not included in this declaration.)" << endl << endl;

		cout << "Open Content: Except for material designated as Product Identity (see above), the game mechanics of this game product are Open Game Content, as \
defined in the Open Gaming License version 1.0a Section 1(d). No portion of this work other than the material designated as Open Game Content may be reproduced in any form \
without written permission." << endl << endl;

		exit(0);
	}


	cout << "Unrecognized option!" << endl;

	exit(_ERR_UNRECOGNIZED_CLI_OPTION);


	return 0;
}

void doProgram() {
	ifstream pfTemplate;
	fstream monster;

	string tempStorage;

	const char* fileName;
	string monName;
	double cr;
	char displayCr[4] = "\0\0\0";
	long xp;
	string displayXp;
	char alignment[3] = "\0\0";
	string creatTypeWords;
	CreatureType creatType;
	string subtypes;
	string creatSizeWords;
	char creatSize;
	int initiative;
	AC ac;
	Saves saves;
	HitDice hd;
	int hp;
	string hpBreakdown;
	int bab;
	Maneuvers maneuvers;
	string meleeAtk;
	string rangedAtk;
	string featList;
	string envList;
     string space;
     string reach;
     string skills;
     string langList;
     string sqList;
     string specAtk;
     string defenseAbilities;
     string immunities;
     string senses;
     string aura;
     string organization;
     string treasure;
     string speed;
     string specAbilities;



	BaseStats abilities;



/*****************************************************************************\
 *                                  MONSTER                                  *
\*****************************************************************************/

	cout << "Monster Name: ";
	getline(cin, monName);

	cout << "CR (decimal 2 places if less than 1): ";
	cin >> cr;
	//TODO Add reprompt for invalid selection

	xp = crToXp(cr, displayCr);

	displayXp = to_string(xp);


	clearBuffer();
	cout << "Alignment (two-letter): ";
	cin.getline(alignment,3,'\n');

	alignment[0] = toupper(alignment[0]);
	alignment[1] = toupper(alignment[1]);


	cout << "Size: ";
	//cin.getline(creatSizeWords,1023,'\n');
	getline(cin, creatSizeWords);
	creatSizeWords = stringToLower(creatSizeWords);
	creatSizeWords[0] = toupper(creatSizeWords[0]);
	creatSize = creatSizeWords[0];

	cout << "Creature Type: ";
	getline(cin, creatTypeWords);

	creatTypeWords = stringToLower(creatTypeWords);

	creatType = determineCreatureType(creatTypeWords);


	cout << "Subtypes (Just hit Enter if none): ";
	getline(cin,subtypes);

	aura = determineAura();

	/*cout << "Aura (type \"null\" if n/a): ";
	getline(cin,subtypes); //*/


	abilities = determineBaseStats(creatType);
	ac = determineAC(abilities.dexMod,creatSize);
	hd = determineHD(creatType,creatSize);
	hp = determineHP(hd,abilities,creatType);
	hpBreakdown = determineHpBreakdown(hd,abilities,creatType);
	saves = determineSaves(hd,abilities,creatType);
	bab = determineBab(hd,creatType);
	maneuvers = determineCombatManeuvers(abilities,bab);
	initiative = determineInitiative(abilities.dexMod);
	meleeAtk = determineMeleeAtk(bab,abilities);
	rangedAtk = determineRangedAtk(bab,abilities);
	featList = determineFeats(hd);
	senses = determineSenses(abilities,hd);
     envList = determineEnvironment();
     skills = determineSkills(abilities,hd,creatType);
     space = determineSpace(creatSize);
     reach = determineReach(creatSize);
     langList = determineLanguages();
     sqList = determineSpecialQualities();
     specAtk = determineSpecialAttacks();
     defenseAbilities = determineDefensiveAbilities();
     immunities = determineImmunities(creatType);
     organization = determineOrganization();
     treasure = determineTreasure();
     speed = determineSpeed();
     specAbilities = determineSpecAbilities();


/*****************************************************************************\
 *                                WRITE FILE                                 *
\*****************************************************************************/

	clearBuffer();

	pfTemplate.open(_PFRPG_TEMPLATE, ios::in);

	fileName = strcat(strcat(strcat(getenv("PWD"),"/"),monName.c_str()),".html");

	monster.open(fileName, ios::in | ios::out | ios::trunc);
	//TODO Add file rename scheme similar to wget

	monster << pfTemplate.rdbuf();

	pfTemplate.close();

	findAndReplace(monster,monName.c_str(),u8"MONNAME",fileName);
	#ifdef _DEBUG
	cout << "Monname written" << endl;
	#endif
	tempStorage = "PFSB - ";
	tempStorage += monName;
	findAndReplace(monster,tempStorage.c_str(),u8"PF_MON",fileName);
	#ifdef _DEBUG
	cout << "Monster header written" << endl;
	#endif
	findAndReplace(monster,displayCr,u8"CR",fileName);
	#ifdef _DEBUG
	cout << "CR written" << endl;
	#endif
	findAndReplace(monster,displayXp.c_str(),u8"XP",fileName);
	#ifdef _DEBUG
	cout << "XP written" << endl;
	#endif
	findAndReplace(monster,alignment,u8"ALIGN",fileName);
	#ifdef _DEBUG
	cout << "Alignment written" << endl;
	#endif
	findAndReplace(monster,creatSizeWords.c_str(),u8"SIZE",fileName);
	#ifdef _DEBUG
	cout << "Size written: " << creatSizeWords << endl;
	#endif
	findAndReplace(monster,creatTypeWords.c_str(),u8"CREATTY",fileName);
	findAndReplace(monster,creatTypeWords.c_str(),u8"CREATTY",fileName);
	findAndReplace(monster,subtypes.c_str(),u8"SUBTYPE",fileName);

	findAndReplace(monster,abilities.displayStr.c_str(),u8"STR",fileName);
	findAndReplace(monster,abilities.displayDex.c_str(),u8"DEX",fileName);
	findAndReplace(monster,abilities.displayCon.c_str(),u8"CON",fileName);
	findAndReplace(monster,abilities.displayInt.c_str(),u8"INT",fileName);
	findAndReplace(monster,abilities.displayWis.c_str(),u8"WIS",fileName);
	findAndReplace(monster,abilities.displayCha.c_str(),u8"CHA",fileName);//*/

	/*#ifdef _DEBUG
	cout << "Before insert" << endl;
	cout << "Armor bonus (0 if n/a): " << to_string(ac.armor) << endl;
     cout << "Shield bonus: " << to_string(ac.shield) << endl;
     cout << "Natural armor: " << to_string(ac.natural) << endl;
     cout << "Deflection bonus: " << to_string(ac.deflection) << endl;
     cout << "Dodge bonus: " << to_string(ac.dodge) << endl;
     cout << "Sacred: " << to_string(ac.sacred) << endl;
     cout << "Profane: " << to_string(ac.profane) << endl;
     cout << "Insight: " << to_string(ac.insight) << endl;
     cout << "Luck: " << to_string(ac.luck) << endl;
     cout << "Racial: " << to_string(ac.racial) << endl;
     cout << "Untyped: " << to_string(ac.untyped) << endl;

     cout << "Dex bonus: " << to_string(ac.dex) << endl;
     cout << "Size bonus: " << to_string(ac.size) << endl;

     cout << "Total AC: " << to_string(ac.totalAc) << endl;
     cout << "Flat-footed AC: " << to_string(ac.flatFootAc) << endl;
     cout << "Touch AC: " << to_string(ac.touchAc) << endl;

     cout << "AC Breakdown: " << ac.breakdown << endl;
	#endif*/

	findAndReplace(monster,to_string(ac.totalAc).c_str(),u8"REGAC",fileName);
	tempStorage = "touch ";
	findAndReplace(monster,(tempStorage + to_string(ac.touchAc)).c_str(),u8"TOUCHAC",fileName);
	tempStorage = "flat-footed ";
	findAndReplace(monster,(tempStorage + to_string(ac.flatFootAc)).c_str(),u8"FLATFOO",fileName);
	findAndReplace(monster,ac.breakdown.c_str(),u8"ACBREAK",fileName);

	findAndReplace(monster,to_string(hp).c_str(),u8"HP",fileName);
	findAndReplace(monster,hpBreakdown.c_str(),u8"HPBREAK",fileName);

	findAndReplace(monster,to_string(saves.fort).c_str(),u8"FORTSAV",fileName);
	findAndReplace(monster,to_string(saves.reflex).c_str(),u8"REFSAVE",fileName);
	findAndReplace(monster,to_string(saves.will).c_str(),u8"WILLSAV",fileName);

	findAndReplace(monster,to_string(bab).c_str(),u8"BAB",fileName);
	findAndReplace(monster,to_string(initiative).c_str(),u8"INIT",fileName);

	findAndReplace(monster,to_string(maneuvers.cmb).c_str(),u8"CMB",fileName);
	findAndReplace(monster,to_string(maneuvers.cmd).c_str(),u8"CMD",fileName);
	findAndReplace(monster,maneuvers.specialCmb.c_str(),u8"SPECCMB",fileName);
	findAndReplace(monster,maneuvers.specialCmd.c_str(),u8"SPECCMD",fileName);

	findAndReplace(monster,meleeAtk.c_str(),u8"MELEE",fileName);
	findAndReplace(monster,rangedAtk.c_str(),u8"RANGED",fileName);
	findAndReplace(monster,specAtk.c_str(),u8"SPECATK",fileName);

	findAndReplace(monster,space.c_str(),u8"SPACE",fileName);
	findAndReplace(monster,reach.c_str(),u8"REACH",fileName);

	findAndReplace(monster,featList.c_str(),u8"FEATLIS",fileName);
	findAndReplace(monster,skills.c_str(),u8"SKILIST",fileName);
	findAndReplace(monster,envList.c_str(),u8"ENVLIST",fileName);
	findAndReplace(monster,organization.c_str(),u8"GRPLIST",fileName);

	findAndReplace(monster,langList.c_str(),u8"LANGLIS",fileName);
	findAndReplace(monster,sqList.c_str(),u8"SQLIST",fileName);

	findAndReplace(monster,defenseAbilities.c_str(),u8"DEFABLE",fileName);
	findAndReplace(monster,immunities.c_str(),u8"IMMUNE",fileName);

	findAndReplace(monster,senses.c_str(),u8"SENSES",fileName);
	findAndReplace(monster,aura.c_str(),u8"AURA",fileName);

	findAndReplace(monster,treasure.c_str(),u8"LOOTLST",fileName);
	findAndReplace(monster,speed.c_str(),u8"SPEED",fileName);

	findAndReplace(monster,specAbilities.c_str(),u8"SPECABL",fileName);



	monster.close();

	#ifdef _DEBUG
	cout << "Monster closed" << endl;
	#endif


	//cout << monName << endl << cr << endl << displayCr << endl << xp << endl << creatSizeWords << endl << creatSize << endl << creatType << endl << subtypes << endl;

}

string determineSpecAbilities() {

	string specAbilities;

	cout << "List special abilities here: " << endl;
	getline(cin,specAbilities);

	return specAbilities;
}

string determineTreasure() {

	string treasure;

	cout << "List treasure here: " << endl;
	getline(cin,treasure);

	return treasure;
}

string determineSpeed() {

	string speed;

	cout << "List speed here (including alt speeds, like fly or swim): " << endl;
	getline(cin,speed);

	return speed;

}

string determineMeleeAtk(const int bab, const BaseStats abilities) {

	int strAtkBonus = bab + abilities.strMod;
	int finesseAtkBonus = bab + abilities.dexMod;

	string meleeAtk;

	cout << "Type what you want to appear next to the Melee Attack line." << endl;
	cout << "The STR-based attack bonus is " << strAtkBonus << ", and the DEX-based attack bonus (if applicable) is " << finesseAtkBonus << endl;

	getline(cin,meleeAtk);

	return meleeAtk;
}

string determineRangedAtk(const int bab, const BaseStats abilities) {

	int thrownAtkBonus = bab + abilities.strMod;
	int bowAtkBonus = bab + abilities.dexMod;

	string rangedAtk;

	cout << "Type what you want to appear next to the Ranged Attack line." << endl;
	cout << "The STR-based attack bonus is " << thrownAtkBonus << ", and the DEX-based attack bonus is " << bowAtkBonus << endl;

	getline(cin,rangedAtk);

	return rangedAtk;
}

string featList(const HitDice hd) {

	int hdFeats = (1 + hd.totalHd) / 2;
	string feats;

     cout << "List the feats here. Based on HD, you should have " << hdFeats << " feats.";
	getline(cin,feats);

	return feats;
}

string determineEnvironment() {

	string environments;

	cout << "List the monster's environments here: ";
	getline(cin,environments);

	return environments;
}

string determineSkills(const BaseStats abilities, const HitDice hd, const CreatureType creatType) {

     string skills;
     int maxSkillPoints = INT_MIN;

	switch (creatType) {
		case CreatureType::ABERRATION: {
			maxSkillPoints = (4 + abilities.intMod) * hd.totalHd;
			break;
		}
		case CreatureType::ANIMAL: {
			maxSkillPoints = (2 + abilities.intMod) * hd.totalHd;
			break;
		}
		case CreatureType::CONSTRUCT: {
			maxSkillPoints = (2 + abilities.intMod) * hd.totalHd;
			break;
		}
		case CreatureType::DRAGON: {
			maxSkillPoints = (6 + abilities.intMod) * hd.totalHd;
			break;
		}
		case CreatureType::FEY: {
			maxSkillPoints = (6 + abilities.intMod) * hd.totalHd;
			break;
		}
		case CreatureType::HUMANOID: {
			maxSkillPoints = (2 + abilities.intMod) * hd.totalHd;
			break;
		}
		case CreatureType::MAGICAL_BEAST: {
			maxSkillPoints = (2 + abilities.intMod) * hd.totalHd;
			break;
		}
		case CreatureType::MONSTROUS_HUMANOID: {
			maxSkillPoints = (4 + abilities.intMod) * hd.totalHd;
			break;
		}
		case CreatureType::OOZE: {
			maxSkillPoints = (2 + abilities.intMod) * hd.totalHd;
			break;
		}
		case CreatureType::OUTSIDER: {
			maxSkillPoints = (6 + abilities.intMod) * hd.totalHd;
			break;
		}
		case CreatureType::PLANT: {
			maxSkillPoints = (2 + abilities.intMod) * hd.totalHd;
			break;
		}
		case CreatureType::UNDEAD: {
			maxSkillPoints = (4 + abilities.intMod) * hd.totalHd;
			break;
		}
		case CreatureType::VERMIN: {
			maxSkillPoints = (2 + abilities.intMod) * hd.totalHd;
			break;
		}
		default: {
			cout << "Homebrew creature types will come later. Exiting program." << endl;
			exit(_ERR_INVALID_CREATURE_TYPE);
		}

	}

     int strSkills = 3 + abilities.strMod + hd.totalHd;
     int dexSkills = 3 + abilities.dexMod + hd.totalHd;
     int conSkills = 3 + abilities.conMod + hd.totalHd;
     int intSkills = 3 + abilities.intMod + hd.totalHd;
     int wisSkills = 3 + abilities.wisMod + hd.totalHd;
     int chaSkills = 3 + abilities.chaMod + hd.totalHd;

     cout << "Enter the creature's skills. The highest possible will be listed below, assuming that the creature gains that skill as a class skill." << endl;
     cout << "\tSTR: " << strSkills << endl;
     cout << "\tDEX: " << dexSkills << endl;
     cout << "\tCON: " << conSkills << endl;
     cout << "\tINT: " << intSkills << endl;
	cout << "\tWIS: " << wisSkills << endl;
	cout << "\tCHA: " << chaSkills << endl;

	cout << "Total skill ranks available (not yet enforced by program logic): " << maxSkillPoints << endl;

	getline(cin, skills);

	return skills;
}

string determineSpace(const char creatSize) {

	string space;

	switch (creatSize) {
		case 'f':
		case 'F': {
			space = "1/2 ft.";
			break;
		}
		case 'd':
		case 'D': {
			space = "1 ft.";
			break;
		}
		case 't':
		case 'T': {
			space = "2-1/2 ft.";
			break;
		}
		case 's':
		case 'S': {
			space = "5 ft.";
			break;
				}
		case 'm':
		case 'M': {
			space = "5 ft.";
			break;
		}
		case 'l':
		case 'L': {
			space = "10 ft.";
			break;
		}
		case 'h':
		case 'H': {
			space = "15 ft.";
			break;
		}
		case 'g':
		case 'G': {
			space = "20 ft.";
			break;
		}
		case 'c':
		case 'C': {
			space = "30 ft.";
			break;
		}
		default: {
			cout << "Invalid creature size found, exiting program" << endl;
			exit(_ERR_INVALID_SIZE);
		}
	}

	return space;
}

string determineSpecialQualities() {

	string sq;

	cout << "List the monster's special qualities here: ";
	getline(cin,sq);

	return sq;

}

string determineSpecialAttacks() {

	string specAtk;

	cout << "List the monster's special attacks here: ";
	getline(cin,specAtk);

	return specAtk;
}

string determineDefensiveAbilities() {

	string defAbilities;

	cout << "List the monster's defensive abilities here: ";
	getline(cin,defAbilities);

	return defAbilities;
}

string determineImmunities(const CreatureType creatType) {

	string specAtk;
	string typeImmunities;

	switch (creatType) {
		case CreatureType::CONSTRUCT: {
			typeImmunities = "construct traits, ";
			break;
		}
		case CreatureType::PLANT: {
			typeImmunities = "plant traits, ";
			break;
		}
		case CreatureType::UNDEAD: {
			typeImmunities = "undead traits, ";
			break;
		}
		default: {
			//doNothing();
		}
	}

	cout << "List the monster's immunities here: ";
	getline(cin,specAtk);

	return specAtk;
}

string determineLanguages() {

	string languages;

	clearBuffer();
	cout << "List the monster's languages here: ";
	getline(cin,languages);

	return languages;
}

string determineSenses(const BaseStats abilities, const HitDice hd) {

	string senses;
	int maxPerception = 3 + abilities.wisMod + hd.totalHd;

	cout << "Type what should appear next to the Senses line in the general info section. The max Perception possible, with only Wis mod + skill ranks + class skill bonus is " << maxPerception << ".";
	getline(cin,senses);

	return senses;
}

string determineAura() {

	string aura;

	cout << "List the monster's aura/auras here: ";
	getline(cin,aura);

	return aura;
}

string determineOrganization() {

	string organization;

	cout << "List the monster's grouping habits here: ";
	getline(cin,organization);

	return organization;
}

string determineReach(const char creatSize) {

	string isTall;
	string reach;

	switch (creatSize) {
		case 'f':
		case 'F': {
			reach = "0 ft.";
			break;
		}
		case 'd':
		case 'D': {
			reach = "0 ft.";
			break;
		}
		case 't':
		case 'T': {
			reach = "0 ft.";
			break;
		}
		case 's':
		case 'S': {
			reach = "5 ft.";
			break;
				}
		case 'm':
		case 'M': {
			reach = "5 ft.";
			break;
		}
		case 'l':
		case 'L': {
			cout << "Is the creature tall or long? ";
			cin >> isTall;

			if (tolower(isTall[0]) == 't') {
				reach = "10 ft.";
			} else {
				reach = "5 ft.";
			}
			break;
		}
		case 'h':
		case 'H': {
			cout << "Is the creature tall or long?";
			cin >> isTall;

			if (tolower(isTall[0]) == 't') {
				reach = "15 ft.";
			} else {
				reach = "10 ft.";
			}
			break;
		}
		case 'g':
		case 'G': {
			cout << "Is the creature tall or long?";
			cin >> isTall;

			if (tolower(isTall[0]) == 't') {
				reach = "20 ft.";
			} else {
				reach = "15 ft.";
			}
			break;
		}
		case 'c':
		case 'C': {
			cout << "Is the creature tall or long?";
			cin >> isTall;

			if (tolower(isTall[0]) == 't') {
				reach = "30 ft.";
			} else {
				reach = "20 ft.";
			}
			break;
		}
		default: {
			cout << "Invalid creature size found, exiting program" << endl;
			exit(_ERR_INVALID_SIZE);
		}
	}

	return reach;
}

string determineFeats(const HitDice hd) {

	string feats;
	int featCount = (hd.totalHd + 1 ) / 2;

	cout << "By hit dice, the creature should have " << featCount << " feats. Mindless creatures, like oozes, may not have feats.";

	cout << "List the monster's feats here (nothing here is autofilled or used in any calculations): ";
	getline(cin,feats);

	return feats;
}

Maneuvers determineCombatManeuvers(const BaseStats abilities, const int bab) {

	Maneuvers maneuvers;
	char choice;

	maneuvers.cmb = bab;
	maneuvers.cmd = 10 + bab + abilities.strMod + abilities.dexMod;

	cout << "Agile Maneuvers feat? (yes/no)" << endl;
	cin >> choice;

	clearBuffer();

	cout << "Note: Feat-based calculations will be in a later build. In the feats line, you will have to re-indicate that the Agile Maneuvers feat was taken." << endl;

	if (choice == 'y' || choice == 'Y') {
		maneuvers.agileManuevers = true;
	}

	if ((!(maneuvers.agileManuevers)) || (abilities.strMod > abilities.dexMod)) {
		maneuvers.cmb += abilities.strMod;
	} else {
		maneuvers.cmb += abilities.dexMod;
	}

	cout << "Special CMB? (current normal CMB is " << maneuvers.cmb << ')' << endl;
	getline(cin,maneuvers.specialCmb);

	cout << "Special CMD? (current normal CMD is " << maneuvers.cmd << ')' << endl;
	getline(cin, maneuvers.specialCmd);

	clearBuffer();

	return maneuvers;
}

int determineInitiative(const int dexMod) {

	int initBonus = dexMod;
	char choice;

	cout << "Improved initiative feat? (yes/no)" << endl;
	cin >> choice;

	clearBuffer();

	cout << "Note: Feat-based calculations will be in a later build. In the feats line, you will have to re-indicate that the Improved Initiative feat was taken." << endl;

	if (choice == 'y' || choice == 'Y') {
		initBonus += 4;
	}

	return initBonus;

}

int determineBab(const HitDice hd, const CreatureType creatType) {
	int bab;

	switch (creatType) {
		case CreatureType::ABERRATION: {
			bab = static_cast<int>(3.0 / 4 * hd.totalHd);
			break;
		}
		case CreatureType::ANIMAL: {
			bab = static_cast<int>(3.0 / 4 * hd.totalHd);
			break;
		}
		case CreatureType::CONSTRUCT: {
			bab = hd.totalHd;
			break;
		}
		case CreatureType::DRAGON: {
			bab = hd.totalHd;
			break;
		}
		case CreatureType::FEY: {
			bab = static_cast<int>(1.0 / 4 * hd.totalHd);
			break;
		}
		case CreatureType::HUMANOID: {
			bab = static_cast<int>(3.0 / 4 * hd.totalHd);
			break;
		}
		case CreatureType::MAGICAL_BEAST: {
			bab = hd.totalHd;
			break;
		}
		case CreatureType::MONSTROUS_HUMANOID: {
			bab = hd.totalHd;
			break;
		}
		case CreatureType::OOZE: {
			bab = static_cast<int>(3.0 / 4 * hd.totalHd);
			break;
		}
		case CreatureType::OUTSIDER: {
			bab = hd.totalHd;
			break;
		}
		case CreatureType::PLANT: {
			bab = static_cast<int>(3.0 / 4 * hd.totalHd);
			break;
		}
		case CreatureType::UNDEAD: {
			bab = static_cast<int>(3.0 / 4 * hd.totalHd);
			break;
		}
		case CreatureType::VERMIN: {
			bab = static_cast<int>(3.0 / 4 * hd.totalHd);
			break;
		}
		default: {
			cout << "Homebrew creature types will come later. Exiting program." << endl;
			exit(_ERR_INVALID_CREATURE_TYPE);
		}

	}

	return bab;
}

string determineHpBreakdown(const HitDice hd, const BaseStats abilities, const CreatureType creatType) {

	int hdTypes = 0;
	string hdBreakdown;


	if (hd.d4) {
		hdTypes += 1;
	}
	if (hd.d6) {
		hdTypes += 1;
	}
	if (hd.d8) {
		hdTypes += 1;
	}
	if (hd.d10) {
		hdTypes += 1;
	}
	if (hd.d12) {
		hdTypes += 1;
	}

	if (hdTypes > 1) {
		hdBreakdown = to_string(hd.totalHd);
		hdBreakdown += "HD; ";
	}


	if (hd.d4) {
		hdBreakdown += to_string(hd.d4) + "d4 + ";
	}
	if (hd.d6) {
		hdBreakdown += to_string(hd.d6) + "d6 + ";
	}
	if (hd.d8) {
		hdBreakdown += to_string(hd.d8) + "d8 + ";
	}
	if (hd.d10) {
		hdBreakdown += to_string(hd.d10) + "d10 + ";
	}
	if (hd.d12) {
		hdBreakdown += to_string(hd.d12) + "d12 + ";
	}

	if (creatType == CreatureType::UNDEAD) {
		hdBreakdown += to_string(abilities.chaMod * hd.totalHd + hd.bonus);
	} else if (creatType == CreatureType::CONSTRUCT) {
		hdBreakdown += to_string(hd.bonus);
	} else {
		hdBreakdown += to_string(abilities.conMod * hd.totalHd + hd.bonus);
	}

	return hdBreakdown;
}

int determineHP(const HitDice hd, const BaseStats abilities, const CreatureType creatType) {

	double hdAverage = 0.0;
	int hp = 0;

	/* Note that even when monsters have multiple HD sources and two or more
	 * sources of hit dice that average to ?.5 each, each source of HD is
	 * rounded down before being added. For proof, math out the Serpentfolk
	 * Bone Prophet on MC204.
	 */

	/*#ifdef _DEBUG
	hdAverage += floor(2.5 * hd.d4);
	cout << "HD average (after d4)" << hdAverage << endl;
	hdAverage += floor(3.5 * hd.d6);
	cout << "HD average (after d6)" << hdAverage << endl;
	hdAverage += floor(4.5 * hd.d8);
	cout << "HD average (after d8)" << hdAverage << endl;
	hdAverage += floor(5.5 * hd.d10);
	cout << "HD average (after d10)" << hdAverage << endl;
	hdAverage += floor(6.5 * hd.d12);
	cout << "HD average (after d12)" << hdAverage << endl;
	#endif */


	hp = hd.bonus + static_cast<int>(hdAverage) + (abilities.conMod * hd.totalHd);

	if (creatType == CreatureType::UNDEAD) {
		hp += abilities.chaMod * hd.totalHd;
	} else if (creatType != CreatureType::CONSTRUCT) {
		hp += abilities.conMod * hd.totalHd;
	}

	/*#ifdef _DEBUG
	cout << endl << "determineHP()" << endl << endl;
	cout << "HP total: " << hp << endl;
	cout << "HD average: " << hdAverage << endl;
	cout << "HD average (casted to int): " << static_cast<int>(hdAverage) << endl;
	cout << "Con mod: " << abilities.conMod << endl;
	cout << "Con bonus HP: " << (abilities.conMod * hd.totalHd) << endl;
	cout << "Special bonus HP: " << hd.bonus << endl;
	cout << "Total HD: " << hd.totalHd << endl;
	cout << "Total d4: " << hd.d4 << endl;
	cout << "Total d6: " << hd.d6 << endl;
	cout << "Total d8: " << hd.d8 << endl;
	cout << "Total d10: " << hd.d10 << endl;
	cout << "Total d12: " << hd.d12 << endl;
	#endif*/

	return hp;
}

HitDice determineHD(const CreatureType creatType, const char creatSize) {

	HitDice hd;
	int hdCount;

	clearBuffer();

	cout << "How many racial HD does this creature have? ";
	cin >> hdCount;
	hd.totalHd = hdCount;

	cout << "Class levels for monsters will come in a later version." << endl;

	switch (creatType) {
		case CreatureType::ABERRATION: {
			hd.d8 = hdCount;
			break;
		}
		case CreatureType::ANIMAL: {
			hd.d8 = hdCount;
			break;
		}
		case CreatureType::CONSTRUCT: {
			hd.d10 = hdCount;
			switch (creatSize) {
				case 's':
				case 'S': {
					hd.bonus = 10;
					break;
				}
				case 'm':
				case 'M': {
					hd.bonus = 20;
					break;
				}
				case 'l':
				case 'L': {
					hd.bonus = 30;
					break;
				}
				case 'h':
				case 'H': {
					hd.bonus = 40;
					break;
				}
				case 'g':
				case 'G': {
					hd.bonus = 60;
					break;
				}
				case 'c':
				case 'C': {
					hd.bonus = 80;
					break;
				}
				default: {
					cout << "Invalid creature size found, exiting program" << endl;
					exit(_ERR_INVALID_SIZE);
				}
			}
			break;
		}
		case CreatureType::DRAGON: {
			hd.d12 = hdCount;
			break;
		}
		case CreatureType::FEY: {
			hd.d6 = hdCount;
			break;
		}
		case CreatureType::HUMANOID: {
			hd.d8 = hdCount;
			break;
		}
		case CreatureType::MAGICAL_BEAST: {
			hd.d10 = hdCount;
			break;
		}
		case CreatureType::MONSTROUS_HUMANOID: {
			hd.d10 = hdCount;
			break;
		}
		case CreatureType::OOZE: {
			hd.d8 = hdCount;
			break;
		}
		case CreatureType::OUTSIDER: {
			hd.d10 = hdCount;
			break;
		}
		case CreatureType::PLANT: {
			hd.d8 = hdCount;
			break;
		}
		case CreatureType::UNDEAD: {
			hd.d8 = hdCount;
			break;
		}
		case CreatureType::VERMIN: {
			hd.d8 = hdCount;
			break;
		}
		default: {
			cout << "Homebrew creature types will come later. Exiting program." << endl;
			exit(_ERR_INVALID_CREATURE_TYPE);
		}

	}

	/*#ifdef _DEBUG
	cout << "determineHD()" << endl;
	cout << "Total HD: " << hd.totalHd << endl;
	cout << "Total d4: " << hd.d4 << endl;
	cout << "Total d6: " << hd.d6 << endl;
	cout << "Total d8: " << hd.d8 << endl;
	cout << "Total d10: " << hd.d10 << endl;
	cout << "Total d12: " << hd.d12 << endl;
	#endif*/

	return hd;

}

Saves determineSaves(const HitDice hd, const BaseStats abilities, const CreatureType creatType) {

	Saves saves;
	char choice;

	switch (creatType) {
		case CreatureType::ABERRATION: {
			saves.goodWill = true;
			break;
		}
		case CreatureType::ANIMAL: {
			saves.goodFort = true;
			saves.goodReflex = true;
			break;
		}
		case CreatureType::CONSTRUCT: {
			break;
		}
		case CreatureType::DRAGON: {
			saves.goodFort = true;
			saves.goodReflex = true;
			saves.goodWill = true;
			break;
		}
		case CreatureType::FEY: {
			saves.goodFort = true;
			break;
		}
		case CreatureType::HUMANOID: {
			cout << "Humanoid creatures get 1 good save." << endl;
			cout << "\t[1] Fortitude" << endl;
			cout << "\t[2] Reflex" << endl;
			cout << "\t[3] Will" << endl;

			cin >> choice;

			switch(choice) {
				case '1': {
					saves.goodFort = true;
					break;
				}
				case '2': {
					saves.goodReflex = true;
					break;
				}
				case '3': {
					saves.goodWill = true;
					break;
				}
				default: {
					cout << "I have no idea what you just typed. Defaulting to all poor saves." << endl;
				}
			}
			break;
		}
		case CreatureType::MAGICAL_BEAST: {
			saves.goodFort = true;
			saves.goodReflex = true;
			break;
		}
		case CreatureType::MONSTROUS_HUMANOID: {
			saves.goodReflex = true;
			saves.goodWill = true;
			break;
		}
		case CreatureType::OOZE: {
			break;
		}
		case CreatureType::OUTSIDER: {
			cout << "Outsider creatures get 2 good saves." << endl;
			cout << "\t[1] Fortitude  +  Reflex" << endl;
			cout << "\t[2] Fortitude  +  Will" << endl;
			cout << "\t[3] Reflex     +  Will" << endl;

			cin >> choice;

			switch(choice) {
				case '1': {
					saves.goodFort = true;
					saves.goodReflex = true;
					break;
				}
				case '2': {
					saves.goodFort = true;
					saves.goodWill = true;
					break;
				}
				case '3': {
					saves.goodReflex = true;
					saves.goodWill = true;
					break;
				}
				default: {
					cout << "I have no idea what you just typed. Defaulting to all poor saves." << endl;
				}
			}
			break;
		}
		case CreatureType::PLANT: {
			saves.goodFort = true;
			break;
		}
		case CreatureType::UNDEAD: {
			saves.goodWill = true;
			break;
		}
		case CreatureType::VERMIN: {
			saves.goodFort = true;
			break;
		}
		default: {
			cout << "Homebrew creature types will come later. Exiting program." << endl;
			exit(_ERR_INVALID_CREATURE_TYPE);
		}

	}

	if (saves.goodFort) {
		saves.fort = static_cast<int>(0.5 * hd.totalHd) + 2;
		//cout << "Base Fort: " << saves.fort << endl;
	} else {
		saves.fort = static_cast<int>((1.0 / 3) * hd.totalHd);
		//cout << "Base Fort: " << saves.fort << endl;
	}

	if (saves.goodReflex) {
		saves.reflex = static_cast<int>(0.5 * hd.totalHd) + 2;
		//cout << "Base Ref: " << saves.reflex << endl;
	} else {
		saves.reflex = static_cast<int>((1.0 / 3) * hd.totalHd);
		//cout << "Base Ref: " << saves.reflex << endl;
	}

	if (saves.goodWill) {
		saves.will = static_cast<int>(0.5 * hd.totalHd) + 2;
		//cout << "Base Will: " << saves.will << endl;
	} else {
		saves.will = static_cast<int>((1.0 / 3) * hd.totalHd);
		//cout << "Base Will: " << saves.will << endl;
	}

	saves.fort   += abilities.conMod;
	saves.reflex += abilities.dexMod;
	saves.will   += abilities.wisMod;

	#ifdef _DEBUG
	cout << "Good fort? " << saves.goodFort << endl;
	cout << "Good reflex? " << saves.goodReflex << endl;
	cout << "Good will? " << saves.goodWill << endl;

	cout << "CON mod: " <<  abilities.conMod << endl;
	cout << "DEX mod: " <<  abilities.dexMod << endl;
	cout << "WIS mod: " <<  abilities.wisMod << endl;
	#endif

     return saves;
}

CreatureType determineCreatureType(string creatType) {

     if (creatType == "aberration" || creatType == "abberration" || creatType == "abberation") {
     	return CreatureType::ABERRATION;
     }
	if (creatType == "animal") {
		return CreatureType::ANIMAL;
	}
	if (creatType == "construct") {
		return CreatureType::CONSTRUCT;
	}
	if (creatType == "dragon") {
		return CreatureType::DRAGON;
	}
	if (creatType == "fey") {
		return CreatureType::FEY;
	}
	if (creatType == "humanoid") {
		return CreatureType::HUMANOID;
	}
	if (creatType == "magical beast") {
		return CreatureType::MAGICAL_BEAST;
	}
	if (creatType == "monstrous humanoid") {
		return CreatureType::MONSTROUS_HUMANOID;
	}
	if (creatType == "ooze") {
		return CreatureType::OOZE;
	}
	if (creatType == "outsider") {
		return CreatureType::OUTSIDER;
	}
	if (creatType == "plant") {
		return CreatureType::PLANT;
	}
	if (creatType == "vermin") {
		return CreatureType::VERMIN;
	}
	if (creatType == "undead") {
		return CreatureType::UNDEAD;
	}

	cout << "Creature type not known." << endl;
	cout << "Ability to use homebrew creature types will be in a future version of this program. Exiting program." << endl;
	exit(0);

	return static_cast<CreatureType>(NULL);
}

BaseStats determineBaseStats(const CreatureType creatType) {

	BaseStats abilities;

	cout << "Give the scores, not the modifiers." << endl;

	cout << "STR: ";
	cin >> abilities.str;
	abilities.strMod = (abilities.str - 10) / 2;
	abilities.displayStr = to_string(abilities.str);


	clearBuffer();
	cout << "DEX: ";
	cin >> abilities.dex;
	abilities.dexMod = (abilities.dex - 10) / 2;
	abilities.displayDex = to_string(abilities.dex);

	if ((creatType != CreatureType::UNDEAD) && (creatType != CreatureType::CONSTRUCT)) {
		cout << "CON: ";
		cin >> abilities.con;
		abilities.conMod = (abilities.con - 10) / 2;
		abilities.displayCon = to_string(abilities.con);
		/*cout << "determineBaseStats CON score (assign): " << abilities.con << endl;
		cout << "determineBaseStats CON mod: (assign)" << abilities.conMod << endl;*/
	} else {
		abilities.con = INT_MIN;
		abilities.displayCon = "—"; //Em-dash (U+2014) for extra width
	}


	if ((creatType != CreatureType::CONSTRUCT) && (creatType != CreatureType::OOZE)) {
		clearBuffer();
		cout << "INT: ";
		cin >> abilities.intelligence;
		abilities.intMod = (abilities.intelligence - 10) / 2;
		abilities.displayInt = to_string(abilities.intelligence);
	} else {
		abilities.intelligence = INT_MIN;
		abilities.intMod = INT_MIN;
		abilities.displayInt = "—"; //Em-dash (U+2014) for extra width
	}

	clearBuffer();
	cout << "WIS: ";
	cin >> abilities.wis;
	abilities.wisMod = (abilities.wis - 10) / 2;
	abilities.displayWis = to_string(abilities.wis);

	clearBuffer();
	cout << "CHA: ";
	cin >> abilities.cha;
	abilities.chaMod = (abilities.cha - 10) / 2;
	abilities.displayCha = to_string(abilities.cha);


	if (creatType == CreatureType::UNDEAD) {
		abilities.conMod = abilities.chaMod;
	}
	if (creatType == CreatureType::CONSTRUCT) {
		abilities.conMod = 0;
	}


	return abilities;
}

AC determineAC(const int dexMod, char size) {

	AC ac;

	ac.totalAc = 10;

	clearBuffer();
	cout << "Indicate total bonuses here. For example, if your creature has +5 Plate, give 14 as the armor bonus." << endl;

	cout << "Armor bonus (0 if n/a): ";
     cin >> ac.armor;

     clearBuffer();
     cout << "Shield bonus: ";
     cin >> ac.shield;

     clearBuffer();
     cout << "Natural armor: ";
     cin >> ac.natural;

     clearBuffer();
     cout << "Deflection bonus: ";
     cin >> ac.deflection;

     clearBuffer();
     cout << "Dodge bonus: ";
     cin >> ac.dodge;

     clearBuffer();
     cout << "Sacred: ";
     cin >> ac.sacred;

     clearBuffer();
     cout << "Profane: ";
     cin >> ac.profane;

     clearBuffer();
     cout << "Insight: ";
     cin >> ac.insight;

     clearBuffer();
     cout << "Luck: ";
     cin >> ac.luck;

     clearBuffer();
     cout << "Racial: ";
     cin >> ac.racial;

     clearBuffer();//
     cout << "Untyped: ";
     cin >> ac.untyped;

     ac.dex = dexMod;

     switch (size) {
		case 'f':
		case 'F': {
			ac.size = 8;
			break;
		}
		case 'd':
		case 'D': {
			ac.size = 4;
			break;
		}
		case 't':
		case 'T': {
			ac.size = 2;
			break;
		}
		case 's':
		case 'S': {
			ac.size = 1;
			break;
		}
		case 'm':
		case 'M': {
			ac.size = 0;
			break;
		}
		case 'l':
		case 'L': {
			ac.size = -1;
			break;
		}
		case 'h':
		case 'H': {
			ac.size = -2;
			break;
		}
		case 'g':
		case 'G': {
			ac.size = -4;
			break;
		}
		case 'c':
		case 'C': {
			ac.size = -8;
			break;
		}
		default: {
			cout << "Invalid creature size, exiting program." << endl;
			exit(_ERR_INVALID_SIZE);
		}

     }

	/*#ifdef _DEBUG
	cout << "Before calculation" << endl;
	cout << "Armor bonus (0 if n/a): " << to_string(ac.armor) << endl;
     cout << "Shield bonus: " << to_string(ac.shield) << endl;
     cout << "Natural armor: " << to_string(ac.natural) << endl;
     cout << "Deflection bonus: " << to_string(ac.deflection) << endl;
     cout << "Dodge bonus: " << to_string(ac.dodge) << endl;
     cout << "Sacred: " << to_string(ac.sacred) << endl;
     cout << "Profane: " << to_string(ac.profane) << endl;
     cout << "Insight: " << to_string(ac.insight) << endl;
     cout << "Luck: " << to_string(ac.luck) << endl;
     cout << "Racial: " << to_string(ac.racial) << endl;
     cout << "Untyped: " << to_string(ac.untyped) << endl;

     cout << "Dex bonus: " << to_string(ac.dex) << endl;
     cout << "Size bonus: " << to_string(ac.size) << endl;

     cout << "Total AC: " << to_string(ac.totalAc) << endl;
     cout << "Flat-footed AC: " << to_string(ac.flatFootAc) << endl;
     cout << "Touch AC: " << to_string(ac.touchAc) << endl;

     cout << "AC Breakdown: " << ac.breakdown << endl;
	#endif*/

     ac.totalAc += (ac.armor + ac.deflection + ac.dex + ac.dodge + ac.insight + ac.luck + ac.natural + ac.profane + ac.racial + ac.sacred + ac.shield + ac.size + ac.trait + ac.untyped);

     ac.touchAc = ac.totalAc - (ac.armor +  ac.shield + ac.natural);

     ac.flatFootAc = ac.totalAc - (ac.dex + ac.dodge);

	/*#ifdef _DEBUG
	cout << "After calculations" << endl;
	cout << "Armor bonus (0 if n/a): " << to_string(ac.armor) << endl;
     cout << "Shield bonus: " << to_string(ac.shield) << endl;
     cout << "Natural armor: " << to_string(ac.natural) << endl;
     cout << "Deflection bonus: " << to_string(ac.deflection) << endl;
     cout << "Dodge bonus: " << to_string(ac.dodge) << endl;
     cout << "Sacred: " << to_string(ac.sacred) << endl;
     cout << "Profane: " << to_string(ac.profane) << endl;
     cout << "Insight: " << to_string(ac.insight) << endl;
     cout << "Luck: " << to_string(ac.luck) << endl;
     cout << "Racial: " << to_string(ac.racial) << endl;
     cout << "Untyped: " << to_string(ac.untyped) << endl;

     cout << "Dex bonus: " << to_string(ac.dex) << endl;
     cout << "Size bonus: " << to_string(ac.size) << endl;

     cout << "Total AC: " << to_string(ac.totalAc) << endl;
     cout << "Flat-footed AC: " << to_string(ac.flatFootAc) << endl;
     cout << "Touch AC: " << to_string(ac.touchAc) << endl;

     cout << "AC Breakdown: " << ac.breakdown << endl;
	#endif*/

     ac.breakdown = determineAcBreakdown(ac);

	/*#ifdef _DEBUG
	cout << "After AC breakdown calculated" << endl;
	cout << "Armor bonus (0 if n/a): " << to_string(ac.armor) << endl;
     cout << "Shield bonus: " << to_string(ac.shield) << endl;
     cout << "Natural armor: " << to_string(ac.natural) << endl;
     cout << "Deflection bonus: " << to_string(ac.deflection) << endl;
     cout << "Dodge bonus: " << to_string(ac.dodge) << endl;
     cout << "Sacred: " << to_string(ac.sacred) << endl;
     cout << "Profane: " << to_string(ac.profane) << endl;
     cout << "Insight: " << to_string(ac.insight) << endl;
     cout << "Luck: " << to_string(ac.luck) << endl;
     cout << "Racial: " << to_string(ac.racial) << endl;
     cout << "Untyped: " << to_string(ac.untyped) << endl;

     cout << "Dex bonus: " << to_string(ac.dex) << endl;
     cout << "Size bonus: " << to_string(ac.size) << endl;

     cout << "Total AC: " << to_string(ac.totalAc) << endl;
     cout << "Flat-footed AC: " << to_string(ac.flatFootAc) << endl;
     cout << "Touch AC: " << to_string(ac.touchAc) << endl;

     cout << "AC Breakdown: " << ac.breakdown << endl;
	#endif*/

     return ac;

}

string determineAcBreakdown(AC ac) {

	string acBreakdown = "(";

	if (ac.armor != 0) {
		acBreakdown += to_string(ac.armor);
		acBreakdown += " armor, ";
	}
	if (ac.shield != 0) {
		acBreakdown += to_string(ac.shield);
		acBreakdown += " shield, ";
	}
	if (ac.natural != 0) {
		acBreakdown += to_string(ac.natural);
		acBreakdown += " natural, ";
	}
	if (ac.dex != 0) {
		acBreakdown += to_string(ac.dex);
		acBreakdown += " Dex, ";
	}
	if (ac.dodge != 0) {
		acBreakdown += to_string(ac.dodge);
		acBreakdown += " dodge, ";
	}
	if (ac.deflection != 0) {
		acBreakdown += to_string(ac.deflection);
		acBreakdown += " deflection, ";
	}
	if (ac.insight != 0) {
		acBreakdown += to_string(ac.insight);
		acBreakdown += " insight, ";
	}
	if (ac.luck != 0) {
		acBreakdown += to_string(ac.luck);
		acBreakdown += " luck, ";
	}
	if (ac.sacred != 0) {
		acBreakdown += to_string(ac.sacred);
		acBreakdown += " sacred, ";
	}
	if (ac.profane != 0) {
		acBreakdown += to_string(ac.profane);
		acBreakdown += " profane, ";
	}
	if (ac.racial != 0) {
		acBreakdown += to_string(ac.racial);
		acBreakdown += " racial, ";
	}
	if (ac.size != 0) {
		acBreakdown += to_string(ac.size);
		acBreakdown += " size";
	}

	acBreakdown += ")";
	return acBreakdown;
}


void findAndReplace(fstream& outfile, const char* replacement, const char* searchKey, const char* fileName) {

	/* I am at a total loss to explain why this code doesn't fucking work if
	 * you give it a search key longer than 8 characters (including the null
	 * terminator). If you have even the slightest fucking clue, please tell
	 * me why. I'd love to know. I could have gotten this first version of the
	 * code out nearly a month earlier if I hadn't been trying to figure out
	 * why this piece of shit doesn't work. The reason this segment of the
	 * code is such a giant fucking mess is because I couldn't figure out what
	 * the fuck is wrong with it.
	 *
	 * Seriously, if you know, please share with the class. I'd love to know.
	 * It's probably something stupid, but at least then I'd know how I
	 * managed to FUBAR this so hard. I'd honestly be impressed with myself if
	 * I wasn't so pissed off.
	 */

	fstream part1;
	fstream part2;
	long currentPos = 0;
	const int keyLength = strlen(searchKey);
	char current;
	bool located = false;

	char* potentialMatch = new char[keyLength];

	outfile.seekp(0L, ios::beg);
	outfile.seekg(0L, ios::beg);

	/*#ifdef _DEBUG
	cout << "find-replace entered" << endl;
	#endif*/

	do {
        //outfile.seekg(0L, ios::beg);
        currentPos = findDollar(outfile, currentPos);

		current = outfile.peek();

		/*#ifdef _DEBUG
		cout << "Initial character found: " << *//*static_cast<int>(current)*//* current<<endl;
		#endif //*/

          for (int x=0; x <= keyLength; x++) {
			if (searchKey[x] == (current = outfile.get())) {
				potentialMatch[x] = current;


				/*#ifdef _DEBUG
				cout << "Next character found!" << endl;

				cout << "Potential match (for loop): " << potentialMatch << endl;
				cout << "Current char (for loop): " << current << endl;
				#endif //*/


			} else {

				/*#ifdef _DEBUG
				cout << "Not found at this point, we found: " << potentialMatch << endl;
				#endif //*/
				break;
			}
          }



        if (!strcmp(potentialMatch,searchKey)) {
            located = true;
        }

       /* #ifdef _DEBUG
        cout << "Potential match (while loop): " << potentialMatch << endl;
        #endif //*/

	} while (!located && current != EOF);

	if (current == EOF) {
		cout << "Match not found, exiting program." << endl;
		exit(0);
	}
	/*#ifdef _DEBUG
	cout << "Found match" << endl;
	#endif //*/

    currentPos = currentPos - 1;

    //Item found and read cursor moved right before $


    insertIntoFile(outfile, replacement, currentPos, keyLength, fileName);


    outfile.seekp(currentPos,ios::beg);


    delete[] potentialMatch;

}


long findDollar(fstream& monster, long currentPos) {

	char ch = ' ';

	monster.seekg(currentPos, ios::beg);

	while (ch != EOF && ch != '$') {

          ch = monster.get();

          currentPos++;
	}

	monster.seekg(currentPos, ios::beg);

	/*#ifdef _DEBUG
	cout << "$ found at position: " << currentPos << endl;
	#endif*/

	return currentPos;
}


void insertIntoFile(fstream& monster, const char* toInsert, long beforeDollar, int keyLength, const char* baseFileName) {
	//cout << "entered insertIntoFile()" << endl;

	int fileNameSize = (1+strlen(baseFileName)) + 6;

	fstream part1;
	char* part1Name = new char[fileNameSize];

	fstream part2;
	char* part2Name = new char[fileNameSize];

	strcpy(part1Name,baseFileName);
	strcpy(part2Name,baseFileName);

	part1.open(strcat(part1Name,".part1"),ios::in|ios::out|ios::app);
	part2.open(strcat(part2Name,".part2"),ios::in|ios::out|ios::app);

	monster.seekg(0L, ios::beg);


	do {
		part1.put(monster.get());

	} while (monster.tellg() != beforeDollar);

	monster.seekg(beforeDollar + keyLength + 1, ios::beg);

	do {
		part2.put(monster.get());

	} while (!monster.eof());

	part2.seekg(0L, ios::beg);

	#ifdef _DEBUG
	cout << "toInsert: " << toInsert << endl;
	#endif

	part1 << toInsert;

	#ifdef _DEBUG
	cout << "inserted" << endl;
	#endif

	part1 << part2.rdbuf();

	#ifdef _DEBUG
	cout << "cat part1 and part2" << endl;
	#endif


	part2.close();

	/* To reset the file's r/w position and overwrite it. Some functions may
	 * intentionally erase large chunks of the file, so moving to the file
	 * beginning may not overwrite everything as planned.
	 */
	monster.close();
	monster.open(baseFileName, ios::in|ios::out|ios::trunc);

	part1.seekp(0L, ios::beg);
	part1.seekg(0L, ios::beg);

	monster << part1.rdbuf();

	part1.close();

	remove(part1Name);
	remove(part2Name);

	delete[] part1Name;
	delete[] part2Name;

	/*monster.seekp(0L, ios::beg);
	monster.seekg(0L, ios::beg);*/

	monster.clear();

	return;
}

long crToXp(double cr, char* displayCR) {
	//TODO Determine formula and use that instead of using a lookup table

	int xp;
	short workingCR = static_cast<short>(cr);

	if (cr == .13) {
		xp = 50;
		displayCR[0] = '1';
		displayCR[1] = '/';
		displayCR[2] = '8';

		return xp;
	}
	if (cr == .17) {
		xp = 65;
		displayCR[0] = '1';
		displayCR[1] = '/';
		displayCR[2] = '6';

		return xp;
	}
	if (cr == .25) {
		xp = 100;
		displayCR[0] = '1';
		displayCR[1] = '/';
		displayCR[2] = '4';

		return xp;
	}
	if (cr == .33) {
		xp = 135;
		displayCR[0] = '1';
		displayCR[1] = '/';
		displayCR[2] = '3';

		return xp;
	}
	if (cr == .50) {
		xp = 200;
		displayCR[0] = '1';
		displayCR[1] = '/';
		displayCR[2] = '2';

		return xp;
	}

	switch (workingCR) {

		case 1: {
			xp = 400;
			displayCR[0] = '1';

			break;
		}
		case 2: {
			xp = 600;
			displayCR[0] = '2';

			break;
		}
		case 3: {
			xp = 800;
			displayCR[0] = '3';

			break;
		}
		case 4: {
			xp = 1200;
			displayCR[0] = '4';

			break;
		}
		case 5: {
			xp = 1600;
			displayCR[0] = '5';

			break;
		}
		case 6: {
			xp = 2400;
			displayCR[0] = '6';

			break;
		}
		case 7: {
			xp = 3200;
			displayCR[0] = '7';

			break;
		}
		case 8: {
			xp = 4800;
			displayCR[0] = '8';

			break;
		}
		case 9: {
			xp = 6400;
			displayCR[0] = '9';

			break;
		}
		case 10: {
			xp = 9600;
			displayCR[0] = '1';
			displayCR[1] = '0';

			break;
		}
		case 11: {
			xp = 12'800;
			displayCR[0] = '1';
			displayCR[1] = '1';

			break;
		}
		case 12: {
			xp = 19'200;
			displayCR[0] = '1';
			displayCR[1] = '2';

			break;
		}
		case 13: {
			xp = 25'600;
			displayCR[0] = '1';
			displayCR[1] = '3';

			break;
		}
		case 14: {
			xp = 38'400;
			displayCR[0] = '1';
			displayCR[1] = '4';

			break;
		}
		case 15: {
			xp = 51'200;
			displayCR[0] = '1';
			displayCR[1] = '5';

			break;
		}
		case 16: {
			xp = 76'800;
			displayCR[0] = '1';
			displayCR[1] = '6';

			break;
		}
		case 17: {
			xp = 102'000;
			displayCR[0] = '1';
			displayCR[1] = '7';

			break;
		}
		case 18: {
			xp = 153'600;
			displayCR[0] = '1';
			displayCR[1] = '8';

			break;
		}
		case 19: {
			xp = 204'800;
			displayCR[0] = '1';
			displayCR[1] = '9';

			break;
		}
		case 20: {
			xp = 307'200;
			displayCR[0] = '2';
			displayCR[1] = '0';

			break;
		}
		case 21: {
			xp = 409'600;
			displayCR[0] = '2';
			displayCR[1] = '1';

			break;
		}
		case 22: {
			xp = 614'400;
			displayCR[0] = '2';
			displayCR[1] = '2';

			break;
		}
		case 23: {
			xp = 819'200;
			displayCR[0] = '2';
			displayCR[1] = '3';

			break;
		}
		case 24: {
			xp = 1'228'800;
			displayCR[0] = '2';
			displayCR[1] = '4';

			break;
		}
		case 25: {
			xp = 1'638'400;
			displayCR[0] = '2';
			displayCR[1] = '5';

			break;
		}
		case 26: {
			xp = 2'457'600;
			displayCR[0] = '2';
			displayCR[1] = '6';

			break;
		}
		case 27: {
			xp = 3'276'800;
			displayCR[0] = '2';
			displayCR[1] = '7';

			break;
		}
		case 28: {
			xp = 4'915'200;
			displayCR[0] = '2';
			displayCR[1] = '8';

			break;
		}
		case 29: {
			xp = 6'553'600;
			displayCR[0] = '2';
			displayCR[1] = '9';

			break;
		}
		case 30: {
			xp = 9'830'400;
			displayCR[0] = '3';
			displayCR[1] = '0';

			break;
		}
		default: {
			xp = 0;
			displayCR[0] = '0';
			displayCR[1] = '\0';
			displayCR[2] = '\0';

			cout << "CR not within parameters, defaulting to 0" << endl;

			break;
		}

	}

	return xp;
}


void printVersion() {
	cout << "PFSB, a PF RPG monster Stat Block generator" << endl << endl;
	#ifndef _DEBUG
	cout << "PFSB version " << _VERSION << endl;
	#endif
	#ifdef _DEBUG
	cout << "PFSB debug version " << _VERSION << ", by Frozen Mustelid" << endl;
	#endif
	cout << "Distributed under the Open Gaming License v1.0a. A copy of the OGL should have been included with this program, as indicated in section 10 of OGLv1.0a." << endl;
	cout << endl <<  "Copyright (C) 2017 Frozen Mustelid"<< endl;
}

void clearBuffer() {

	cin.clear();

	cin.ignore(numeric_limits<streamsize>::max(),'\n');

	cin.clear();

	return;
}

string stringToLower(string toLower) {

	int x = 0;

	while(toLower[x] != '\0') {
		toLower[x] = tolower(toLower[x]);
		x++;
	}

	return toLower;

}
/*switch (creatSize) {
	case 'f':
	case 'F': {
		break;
	}
	case 'd':
	case 'D': {
		break;
	}
	case 't':
	case 'T': {
		break;
	}
	case 's':
	case 'S': {
		break;
			}
	case 'm':
	case 'M': {
	break;
	}
	case 'l':
	case 'L': {
		break;
	}
	case 'h':
	case 'H': {
		break;
	}
	case 'g':
	case 'G': {
		break;
	}
	case 'c':
	case 'C': {
		break;
	}
	default: {
		cout << "Invalid creature size found, exiting program" << endl;
		exit(_ERR_INVALID_SIZE);
	}
} //*/


/*switch (creatType) {
		case CreatureType::ABERRATION: {
			break;
		}
		case CreatureType::ANIMAL: {
			break;
		}
		case CreatureType::CONSTRUCT: {
			break;
		}
		case CreatureType::DRAGON: {
			break;
		}
		case CreatureType::FEY: {
			break;
		}
		case CreatureType::HUMANOID: {
			break;
		}
		case CreatureType::MAGICAL_BEAST: {
			break;
		}
		case CreatureType::MONSTROUS_HUMANOID: {
			break;
		}
		case CreatureType::OOZE: {
			break;
		}
		case CreatureType::OUTSIDER: {
			break;
		}
		case CreatureType::PLANT: {
			break;
		}
		case CreatureType::UNDEAD: {
			break;
		}
		case CreatureType::VERMIN: {
			break;
		}
		default: {
			cout << "Homebrew creature types will come later. Exiting program." << endl;
			exit(_ERR_INVALID_CREATURE_TYPE);
		}

	}//*/