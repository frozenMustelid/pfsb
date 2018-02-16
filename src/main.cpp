#include "errors.hpp"
#include "PfMon.hpp"
#include "platform.hpp"
#include "version.hpp"

//#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

/* And for some reason, GCC no longer requires me to include cstdlib to call
 * exit. Wat.
 */

using namespace std;

void printHelp();
void printOgl();
void printVersion();

void selectGame(int argc, char** argv);
void doPf();

void insertIntoFile(fstream& monster, const char* toInsert, long beforeDollar, int keyLength, const char* baseFileName);
long findDollar(fstream& monster, long currentPos);
void findAndReplace(fstream& outfile, const char* replacement, const char* searchKey, const char* fileName);

int main(int argc, char** argv) {

		if (argc == 1) {
		doPf();

		#ifdef DEBUG_
		cout << "Exited doProgram()" << endl;
		#endif

		exit(0);
	} else if (argc == 2) {
/******************************************************************************/
#if (PLATFAM_ == __unix)
		if (!strcmp("--help",argv[1])) {
#endif
#if (PLATFAM_ == WIN32_)
		if (!strcmp("/?",argv[1])) {
#endif
/******************************************************************************/
			printHelp();
			exit(0);
	}
/******************************************************************************/
#if (PLATFAM_ == __unix)
		if (!strcmp("--ogl",argv[1])) {
#endif
#if (PLATFAM_ == WIN32_)
		if (!strcmp("/o",argv[1])) {
#endif
/******************************************************************************/
			printOgl();
			exit(0);
	}
/******************************************************************************/
//Compatibility note: No #ifs on --version because I don't know what's idiomatic for Windows
/******************************************************************************/
		if (!strcmp("--version",argv[1])) {
			printVersion();
			exit(0);
		}
		
		selectGame(argc,argv);
	} else {
		cout << "Unrecognized option!" << endl;
		exit(_ERR_UNRECOGNIZED_CLI_OPTION);
	}

	return 0;
}

void selectGame(int argc, char** argv) {

	if (!strcmp("pf",argv[1])) {
		doPf();
		exit(0);
	}

	cout << "Unrecognized option!" << endl;
	exit(_ERR_UNRECOGNIZED_CLI_OPTION);
}

void doPf() {

	string tempStorage;


	PfMon monster;


/*****************************************************************************\
 *                                  MONSTER                                  *
\*****************************************************************************/


	#ifdef DEBUG_
	cout << "Monster name: " << monster.monName << endl;
	cout << "File path: " << monster.fileName << endl;
	#endif

	monster.fetchMonNameTop();
	monster.fetchDescription();

	monster.crAndXp();
	monster.fetchAlignment();
	monster.fetchSize();
	monster.fetchCreatureType();
	monster.fetchSubtypes();
	monster.fetchAura();

	monster.fetchHd();
	monster.calculateBab();
	monster.fetchAbilities();
	monster.determineInitiative();
	monster.fetchSenses();
	monster.calculateHp();
	monster.determineAC();
	monster.determineSaves();
	monster.fetchDefensiveAbilities();
	monster.determineImmunities();
	monster.fetchResistances();
	monster.fetchWeaknesses();
	monster.fetchDr();
	monster.fetchSr();

	monster.fetchSpeed();
	monster.fetchMeleeAtk();
	monster.fetchRangedAtk();
	monster.calculateSpace();
	monster.determineReach();
	monster.fetchSpecialAttacks();
	monster.determineSlas();

	monster.determineCombatManeuvers();
	monster.fetchFeats();
	monster.fetchSkills();
	monster.fetchLanguages();
	monster.fetchSpecialQualities();

	monster.fetchEnvironment();
	monster.fetchOrganization();
	monster.fetchTreasure();

	monster.fetchSpecialAbilities(); //*/

	#ifndef DEBUG_
	monster.prepareWrite();
	#else
	cout << monster.prepareWrite();
	#endif


/*****************************************************************************\
 *                                WRITE FILE                                 *
\*****************************************************************************/

	findAndReplace(monster.file,VERSION_,u8"PROGRAM_VERSION",monster.fileName);

	tempStorage = "PFSB - ";
	tempStorage += monster.monName;
	findAndReplace(monster.file,tempStorage.c_str(),u8"PFRPG_MONNAME",monster.fileName);
	#ifdef DEBUG_
	cout << "Monster header written" << endl;
	#endif

	findAndReplace(monster.file,monster.monNameTop.c_str(),u8"MONSTER_NAME_TOP",monster.fileName);
	findAndReplace(monster.file,monster.description.c_str(),u8"MONSTER_DESCRIPTION",monster.fileName);

	findAndReplace(monster.file,monster.monName.c_str(),u8"MONSTER_NAME",monster.fileName);
	#ifdef DEBUG_
	cout << "Monname written" << endl;
	#endif

	findAndReplace(monster.file,monster.cr,u8"CR",monster.fileName);
	#ifdef DEBUG_
	cout << "CR written" << endl;
	#endif
	findAndReplace(monster.file,(monster.xp.c_str()),u8"XP",monster.fileName);
	#ifdef DEBUG_
	cout << "XP written" << endl;
	cout << endl << endl << endl << "Value (c++-string): " << monster.xp << endl << endl << endl;
	cout << endl << endl << endl << "Value (c - string): " << monster.xp.c_str() << endl << endl << endl;
	#endif
	findAndReplace(monster.file,monster.alignment.c_str(),u8"ALIGNMENT",monster.fileName);
	#ifdef DEBUG_
	cout << "Alignment written" << endl;
	#endif
	findAndReplace(monster.file,monster.creatSizeWords.c_str(),u8"SIZE",monster.fileName);
	#ifdef DEBUG_
	cout << "Size written: " << monster.creatSizeWords << endl;
	#endif

	findAndReplace(monster.file,monster.creatTypeWords.c_str(),u8"CREATURE_TYPE",monster.fileName);
	findAndReplace(monster.file,monster.creatTypeWords.c_str(),u8"CREATURE_TYPE",monster.fileName);

	findAndReplace(monster.file,monster.subtypes.c_str(),u8"SUBTYPES",monster.fileName);
	findAndReplace(monster.file,to_string(monster.initiative).c_str(),u8"INITIATIVE",monster.fileName);
	findAndReplace(monster.file,monster.senses.c_str(),u8"SENSES",monster.fileName);
	findAndReplace(monster.file,monster.aura.c_str(),u8"AURA",monster.fileName);




	findAndReplace(monster.file,to_string(monster.ac.totalAc).c_str(),u8"NORMAL_AC",monster.fileName);
	tempStorage = "touch ";
	findAndReplace(monster.file,(tempStorage + to_string(monster.ac.touchAc)).c_str(),u8"TOUCH_AC",monster.fileName);
	tempStorage = "flat-footed ";
	findAndReplace(monster.file,(tempStorage + to_string(monster.ac.flatFootAc)).c_str(),u8"FLATFOOT_AC",monster.fileName);
	findAndReplace(monster.file,monster.ac.breakdown.c_str(),u8"BREAKDOWN_AC",monster.fileName);

	findAndReplace(monster.file,to_string(monster.hp).c_str(),u8"HP",monster.fileName);
	findAndReplace(monster.file,monster.hpBreakdown.c_str(),u8"BREAKDOWN_HP",monster.fileName);

	findAndReplace(monster.file,to_string(monster.saves.fort).c_str(),u8"FORTITUDE_SAVE",monster.fileName);
	findAndReplace(monster.file,to_string(monster.saves.reflex).c_str(),u8"REFLEX_SAVE",monster.fileName);
	findAndReplace(monster.file,to_string(monster.saves.will).c_str(),u8"WILL_SAVE",monster.fileName);

	findAndReplace(monster.file,monster.defensiveAbilities.c_str(),u8"DEFENSIVE_ABILITIES",monster.fileName);
	findAndReplace(monster.file,monster.immunities.c_str(),u8"IMMUNITIES",monster.fileName);
	findAndReplace(monster.file,monster.resistances.c_str(),u8"RESISTANCES",monster.fileName);
	findAndReplace(monster.file,monster.weaknesses.c_str(),u8"WEAKNESSES",monster.fileName);

	findAndReplace(monster.file,monster.dr.c_str(),u8"DR",monster.fileName);
	findAndReplace(monster.file,monster.sr.c_str(),u8"SR",monster.fileName);




	findAndReplace(monster.file,monster.speed.c_str(),u8"SPEED",monster.fileName);

	findAndReplace(monster.file,monster.meleeAtk.c_str(),u8"MELEE_FULL_ATTACK",monster.fileName);
	findAndReplace(monster.file,monster.rangedAtk.c_str(),u8"RANGED_FULL_ATTACK",monster.fileName);

	findAndReplace(monster.file,monster.space.c_str(),u8"SPACE",monster.fileName);
	findAndReplace(monster.file,monster.reach.c_str(),u8"REACH",monster.fileName);

	findAndReplace(monster.file,monster.specAtk.c_str(),u8"SPECIAL_ATTACKS",monster.fileName);

	findAndReplace(monster.file,monster.slas.c_str(),u8"SLA",monster.fileName);




	findAndReplace(monster.file,monster.abilities.displayStr.c_str(),u8"STR",monster.fileName);
	findAndReplace(monster.file,monster.abilities.displayDex.c_str(),u8"DEX",monster.fileName);
	findAndReplace(monster.file,monster.abilities.displayCon.c_str(),u8"CON",monster.fileName);
	findAndReplace(monster.file,monster.abilities.displayInt.c_str(),u8"INT",monster.fileName);
	findAndReplace(monster.file,monster.abilities.displayWis.c_str(),u8"WIS",monster.fileName);
	findAndReplace(monster.file,monster.abilities.displayCha.c_str(),u8"CHA",monster.fileName);

	findAndReplace(monster.file,to_string(monster.bab).c_str(),u8"BAB",monster.fileName);

	findAndReplace(monster.file,to_string(monster.maneuvers.cmb).c_str(),u8"CMB",monster.fileName);
	findAndReplace(monster.file,to_string(monster.maneuvers.cmd).c_str(),u8"CMD",monster.fileName);
	findAndReplace(monster.file,monster.maneuvers.specialCmb.c_str(),u8"SPECIAL_CMB",monster.fileName);
	findAndReplace(monster.file,monster.maneuvers.specialCmd.c_str(),u8"SPECIAL_CMD",monster.fileName);

	findAndReplace(monster.file,monster.featList.c_str(),u8"FEAT_LIST",monster.fileName);
	findAndReplace(monster.file,monster.skillList.c_str(),u8"SKILL_LIST",monster.fileName);
	findAndReplace(monster.file,monster.languageList.c_str(),u8"LANGUAGE_LIST",monster.fileName);

	findAndReplace(monster.file,monster.specialQualities.c_str(),u8"SPECIAL_QUALITIES_LIST",monster.fileName);




	findAndReplace(monster.file,monster.environmentList.c_str(),u8"ENVIRONMENT_LIST",monster.fileName);
	findAndReplace(monster.file,monster.groupList.c_str(),u8"GROUPING_LIST",monster.fileName);
	findAndReplace(monster.file,monster.lootList.c_str(),u8"ITEM_LIST",monster.fileName);




	findAndReplace(monster.file,monster.specialAbilities.c_str(),u8"SPECIAL_ABILITIES",monster.fileName); //*/



	monster.file.close();

	#ifdef DEBUG_
	cout << "Monster closed" << endl;
	#endif


	//cout << monName << endl << cr << endl << displayCr << endl << xp << endl << creatSizeWords << endl << creatSize << endl << creatType << endl << subtypes << endl;

}


void findAndReplace(fstream& outfile, const char* replacement, const char* searchKey, const char* fileName) {

	fstream part1;
	fstream part2;
	long currentPos = 0;
	const int keyLength = strlen(searchKey);
	char current;
	bool located = false;

	char* potentialMatch = new char[/*1 +*/ keyLength];
	//potentialMatch[keyLength] = '\0';

	outfile.seekp(0L, ios::beg);
	outfile.seekg(0L, ios::beg);

	/*#ifdef DEBUG_
	cout << "find-replace entered" << endl;
	#endif*/

	do {
		//outfile.seekg(0L, ios::beg);
		currentPos = findDollar(outfile, currentPos);

		current = outfile.peek();

		#ifdef DEBUG_
		cout << "Initial character found: " << /*static_cast<int>(current)*/ current<<endl;
		#endif //*/

		for (int x=0; x <= keyLength; x++) {
			if (searchKey[x] == (current = outfile.get())) {
				potentialMatch[x] = current;


				#ifdef DEBUG_
				cout << "Next character found!" << endl;

				cout << "Potential match (for loop): " << potentialMatch << endl;
				cout << "Current char (for loop): " << current << endl;
				#endif //*/


			} else {

				#ifdef DEBUG_
				cout << "Not found at this point, we found: " << potentialMatch << endl;
				#endif //*/
				break;
			}
		}



		if (!strncmp(potentialMatch,searchKey,keyLength)) {
			located = true;
		}

		#ifdef DEBUG_
		cout << "Potential match (while loop): " << potentialMatch << endl;
		#endif //*/

	} while (!located && current != EOF);

	if (current == EOF) {
		cout << "Match not found, exiting program." << endl;
		exit(0);
	}
	#ifdef DEBUG_
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

	#ifdef DEBUG_
	cout << "$ found at position: " << currentPos << endl;
	#endif

	return currentPos;
}


void insertIntoFile(fstream& monster, const char* toInsert, long beforeDollar, int keyLength, const char* baseFileName) {
	#ifdef DEBUG_
	cout << "entered insertIntoFile()" << endl;
	#endif

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

	#ifdef DEBUG_
	cout << "toInsert: " << toInsert << endl;
	#endif

	part1 << toInsert;

	#ifdef DEBUG_
	cout << "inserted" << endl;
	#endif

	part1 << part2.rdbuf();

	#ifdef DEBUG_
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


void printHelp() {
	cout << "Run the program with no arguments to use it. It will output an HTML file in the" << endl;
		cout << "\tcurrent directory." << endl;
/******************************************************************************/
#if (PLATFAM_ == __unix)
	cout << "Use --version to print version info." << endl;
#endif
#if (PLATFAM_ == WIN32_)
	cout << "Use --version to print version info." << endl; //Compatibility note: Version text is same because I don't know what's idiomatic for Windows
#endif
/******************************************************************************/
#if (PLATFAM_ == __unix)
	cout << "Use --ogl to print OGL-mandated information about product identity and open game" << endl;
		cout << "\tcontent." << endl;
#endif
#if (PLATFAM_ == WIN32_)
	cout << "Use /o to print OGL-mandated information about product identity and open game" << endl;
		cout << "\tcontent." << endl;
#endif
/******************************************************************************/
#if (PLATFAM_ == __unix)
	cout << "Use --help to print this text." << endl;
#endif
#if (PLATFAM_ == WIN32_)
	cout << "Use /? to print this text." << endl;
#endif
/******************************************************************************/
	cout << "Note: It is strongly advised that no user inputs contain dollar signs."<< endl << endl;

	return;
}

void printOgl() {
	cout << endl << "Product Identity: The following items are hereby identified as Product Identity," << endl;
		cout << "as defined in the Open Game License version 1.0a, Section 1(e), and are not Open" << endl;
		cout << "Content: All trademarks, registered trademarks, proper names (characters," << endl;
		cout << "deities, etc.), dialogue, plots, storylines, locations, characters, artwork, and" << endl;
		cout << "trade dress. (Elements that have previously been designated as Open Game Content" << endl;
		cout << "or are in the public domain are not included in this declaration.)" << endl << endl;

	cout << "Open Content: Except for material designated as Product Identity (see above)," << endl;
		cout << "the game mechanics of this game product are Open Game Content, as defined in the" << endl;
		cout << "Open Gaming License version 1.0a Section 1(d). No portion of this work other" << endl;
		cout << "than the material designated as Open Game Content may be reproduced in any form" << endl;
		cout << "without written permission." << endl << endl;

	return;
}

void printVersion() {
	cout << "PFSB, a PF RPG monster Stat Block generator" << endl << endl;
	#ifndef DEBUG_
	cout << "PFSB version " << VERSION_ << endl;
	#endif
	#ifdef DEBUG_
	cout << "PFSB debug version " << VERSION_ << endl;
	#endif
	cout << "Distributed under the Open Gaming License v1.0a. A copy of the OGL should have" << endl;
		cout << "been included with this program, as indicated in section 10 of OGLv1.0a, as" << endl;
		cout << "should a copy of the CONTRIBUTORS text file." << endl;
	cout << endl <<  "Copyright (C) 2017-2018 Frozen Mustelid and contributors"<< endl;
}



/*switch (creatSize) {
	case Size::FINE: {
		break;
	}
	case Size::DIMINUTIVE: {
		break;
	}
	case Size::TINY: {
		break;
	}
	case Size::SMALL: {
		break;
			}
	case Size::MEDIUM: {
	break;
	}
	case Size::LARGE: {
		break;
	}
	case Size::HUGE: {
		break;
	}
	case Size::GARGANTUAN: {
		break;
	}
	case Size::COLOSSAL: {
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