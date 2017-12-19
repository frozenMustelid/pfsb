#include "commonFunctions.hpp"
#include "errors.hpp"
#include "pfMon.hpp"
#include "platform.hpp"

#include <cmath>
#undef HUGE
//Something in cmath causes a conflict with Size::HUGE
#include <cstring>
#include <climits>
#include <iostream>
#include <string>

using namespace std;

/******************************************************************************\
 *                                 HEADER                                     *
\******************************************************************************/

long PfMon::crAndXp() {

	long xp;

	double crAsDouble;
	int crAsInt;

	cout << "CR (decimal 2 places if less than 1): ";
	cin >> crAsDouble;
	//TODO Add reprompt for invalid selection

	//TODO Determine formula and use that instead of using a lookup table

	crAsInt = static_cast<int>(crAsDouble);

	if (crAsDouble == .13) {
		xp = 50L;
		cr[0] = '1';
		cr[1] = '/';
		cr[2] = '8';

		this->xp = xp;
		return xp;
	}
	if (crAsDouble == .17) {
		xp = 65L;
		cr[0] = '1';
		cr[1] = '/';
		cr[2] = '6';

		this->xp = xp;
		return xp;
	}
	if (crAsDouble == .25) {
		xp = 100L;
		cr[0] = '1';
		cr[1] = '/';
		cr[2] = '4';

		this->xp = xp;
		return xp;
	}
	if (crAsDouble == .33) {
		xp = 135L;
		cr[0] = '1';
		cr[1] = '/';
		cr[2] = '3';

		this->xp = xp;
		return xp;
	}
	if (crAsDouble == .50) {
		xp = 200L;
		cr[0] = '1';
		cr[1] = '/';
		cr[2] = '2';

		this->xp = xp;
		return xp;
	}

	switch (crAsInt) {

		case 1: {
			xp = 400L;
			cr[0] = '1';

			break;
		}
		case 2: {
			xp = 600L;
			cr[0] = '2';

			break;
		}
		case 3: {
			xp = 800L;
			cr[0] = '3';

			break;
		}
		case 4: {
			xp = 1'200L;
			cr[0] = '4';

			break;
		}
		case 5: {
			xp = 1'600L;
			cr[0] = '5';

			break;
		}
		case 6: {
			xp = 2'400L;
			cr[0] = '6';

			break;
		}
		case 7: {
			xp = 3'200L;
			cr[0] = '7';

			break;
		}
		case 8: {
			xp = 4'800L;
			cr[0] = '8';

			break;
		}
		case 9: {
			xp = 6'400L;
			cr[0] = '9';

			break;
		}
		case 10: {
			xp = 9'600L;
			cr[0] = '1';
			cr[1] = '0';

			break;
		}
		case 11: {
			xp = 12'800L;
			cr[0] = '1';
			cr[1] = '1';

			break;
		}
		case 12: {
			xp = 19'200L;
			cr[0] = '1';
			cr[1] = '2';

			break;
		}
		case 13: {
			xp = 25'600L;
			cr[0] = '1';
			cr[1] = '3';

			break;
		}
		case 14: {
			xp = 38'400L;
			cr[0] = '1';
			cr[1] = '4';

			break;
		}
		case 15: {
			xp = 51'200L;
			cr[0] = '1';
			cr[1] = '5';

			break;
		}
		case 16: {
			xp = 76'800L;
			cr[0] = '1';
			cr[1] = '6';

			break;
		}
		case 17: {
			xp = 102'000L;
			cr[0] = '1';
			cr[1] = '7';

			break;
		}
		case 18: {
			xp = 153'600L;
			cr[0] = '1';
			cr[1] = '8';

			break;
		}
		case 19: {
			xp = 204'800L;
			cr[0] = '1';
			cr[1] = '9';

			break;
		}
		case 20: {
			xp = 307'200L;
			cr[0] = '2';
			cr[1] = '0';

			break;
		}
		case 21: {
			xp = 409'600L;
			cr[0] = '2';
			cr[1] = '1';

			break;
		}
		case 22: {
			xp = 614'400L;
			cr[0] = '2';
			cr[1] = '2';

			break;
		}
		case 23: {
			xp = 819'200L;
			cr[0] = '2';
			cr[1] = '3';

			break;
		}
		case 24: {
			xp = 1'228'800L;
			cr[0] = '2';
			cr[1] = '4';

			break;
		}
		case 25: {
			xp = 1'638'400L;
			cr[0] = '2';
			cr[1] = '5';

			break;
		}
		case 26: {
			xp = 2'457'600L;
			cr[0] = '2';
			cr[1] = '6';

			break;
		}
		case 27: {
			xp = 3'276'800L;
			cr[0] = '2';
			cr[1] = '7';

			break;
		}
		case 28: {
			xp = 4'915'200L;
			cr[0] = '2';
			cr[1] = '8';

			break;
		}
		case 29: {
			xp = 6'553'600L;
			cr[0] = '2';
			cr[1] = '9';

			break;
		}
		case 30: {
			xp = 9'830'400L;
			cr[0] = '3';
			cr[1] = '0';

			break;
		}
		default: {

			xp = 0;
			cr[0] = '0';
			cr[1] = '\0';
			cr[2] = '\0';

			cout << "CR not within parameters, defaulting to 0" << endl;

			break;
		}

	}
	
	formatXp(xp);
	return xp;
}

char* PfMon::fetchAlignment() {
	
	clearBuffer();
	cout << "Alignment (two-letter): ";
	cin.getline(alignment,3,'\n');

	alignment[0] = toupper(alignment[0]);
	alignment[1] = toupper(alignment[1]);
	alignment[2] = '\0';
	
	return alignment;
}

string PfMon::fetchSize() {
	
	cout << "Size: ";
	//cin.getline(creatSizeWords,1023,'\n');
	getline(cin, creatSizeWords);
	creatSizeWords = stringToLower(creatSizeWords);
	creatSizeWords[0] = toupper(creatSizeWords[0]);
	
	switch (creatSizeWords[0]) {
		case 'F': {
			creatSize = Size::FINE;
			break;
		}
		case 'D': {
			creatSize = Size::DIMINUTIVE;
			break;
		}
		case 'T': {
			creatSize = Size::TINY;
			break;
		}
		case 'S': {
			creatSize = Size::SMALL;
			break;
				}
		case 'M': {
			creatSize = Size::MEDIUM;
		break;
		}
		case 'L': {
			creatSize = Size::LARGE;
			break;
		}
		case 'H': {
			creatSize = Size::HUGE;
			break;
		}
		case 'G': {
			creatSize = Size::GARGANTUAN;
			break;
		}
		case 'C': {
			creatSize = Size::COLOSSAL;
			break;
		}
		default: {
			cout << "Invalid creature size found, exiting program" << endl;
			exit(_ERR_INVALID_SIZE);
		}
	}
	
	return creatSizeWords;
}

string PfMon::fetchCreatureType() {
	
	cout << "Creature Type: ";
	getline(cin, creatTypeWords);

	creatTypeWords = stringToLower(creatTypeWords);
	
	determineCreatureType();
	
	return creatTypeWords;
}

string PfMon::fetchSubtypes() {
	
	string holding;
	
	cout << "Subtypes (Just hit Enter if none): ";
	getline(cin,holding);
	
	if (!(holding.empty())) {
		subtypes = '(';
		subtypes += holding;
		subtypes += ')';
	}
	
	return subtypes;
}

int PfMon::determineInitiative() {

	int initBonus = abilities.dexMod;
	char choice;

	cout << "Improved initiative feat? (yes/no)" << endl;
	cin >> choice;

	clearBuffer();

	if (choice == 'y' || choice == 'Y') {
		initBonus += 4;
		featList += "Improved Initiative, ";
	}

	initiative = initBonus;
	return initBonus;

}

string PfMon::fetchSenses() {

	int maxPerception = 3 + abilities.wisMod + hd.totalHd;

	cout << "Type what should appear next to the Senses line in the general info section. The max Perception possible, with only \
Wis mod + skill ranks + class skill bonus is " << maxPerception << "." << endl;
	getline(cin,senses);

	return senses;
}

string PfMon::fetchAura() {

	cout << "List the monster's aura/auras here: ";
	getline(cin,aura);

	return aura;
}

string PfMon::formatXp(long xp) {

	string xpString = to_string(xp);
	string xpReversed = "";

	for (unsigned int counter = 0; counter <= xpString.length(); counter++) {
	/* Unsigned to avoid comparing signed int to unsigned int, which is the type
	 * returned by string::length(). Unlikely to cause issues, but all code in
	 * a release build must build without errors or warnings.
	 */
		xpReversed += xpString[xpString.length() - counter];

		if ((((counter) % 3) == 0) && (counter != 0)) {
			xpReversed += ',';
		}
	}

	xpString = "";

	for (unsigned int counter = 0; counter <= xpReversed.length(); counter++) {
		xpString += xpReversed[xpReversed.length() - counter];
	}

	xpString[0] = ' ';

	if (xpString[1] == ',') { //This does produce extra spaces, but it doesnt look like browsers render these.
		xpString[1] = ' ';
	}

	this->xp = xpString;
	return xpString;
}

CreatureType PfMon::determineCreatureType() {

	if (creatTypeWords == "aberration" || creatTypeWords == "abberration" || creatTypeWords == "abberation") {
		creatType = CreatureType::ABERRATION;
		return CreatureType::ABERRATION;
	}
	if (creatTypeWords == "animal") {
		creatType = CreatureType::ANIMAL;
		return CreatureType::ANIMAL;
	}
	if (creatTypeWords == "construct") {
		creatType = CreatureType::CONSTRUCT;
		return CreatureType::CONSTRUCT;
	}
	if (creatTypeWords == "dragon") {
		creatType = CreatureType::DRAGON;
		return CreatureType::DRAGON;
	}
	if (creatTypeWords == "fey") {
		creatType = CreatureType::FEY;
		return CreatureType::FEY;
	}
	if (creatTypeWords == "humanoid") {
		creatType = CreatureType::HUMANOID;
		return CreatureType::HUMANOID;
	}
	if (creatTypeWords == "magical beast") {
		creatType = CreatureType::MAGICAL_BEAST;
		return CreatureType::MAGICAL_BEAST;
	}
	if (creatTypeWords == "monstrous humanoid") {
		creatType = CreatureType::MONSTROUS_HUMANOID;
		return CreatureType::MONSTROUS_HUMANOID;
	}
	if (creatTypeWords == "ooze") {
		creatType = CreatureType::OOZE;
		return CreatureType::OOZE;
	}
	if (creatTypeWords == "outsider") {
		creatType = CreatureType::OUTSIDER;
		return CreatureType::OUTSIDER;
	}
	if (creatTypeWords == "plant") {
		creatType = CreatureType::PLANT;
		return CreatureType::PLANT;
	}
	if (creatTypeWords == "vermin") {
		creatType = CreatureType::VERMIN;
		return CreatureType::VERMIN;
	}
	if (creatTypeWords == "undead") {
		creatType = CreatureType::UNDEAD;
		return CreatureType::UNDEAD;
	}

	cout << "Creature type not known." << endl;
	cout << "Ability to use homebrew creature types will be in a future version of this program. Exiting program." << endl;
	exit(0);

	return static_cast<CreatureType>(NULL);
}

/******************************************************************************\
 *                                 DEFENSE                                    *
\******************************************************************************/

AC PfMon::determineAC() {

	ac.totalAc = 10;

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

	ac.dex = abilities.dexMod;

	switch (creatSize) {
		case Size::FINE: {
			ac.size = 8;
			break;
		}
		case Size::DIMINUTIVE: {
			ac.size = 4;
			break;
		}
		case Size::TINY: {
			ac.size = 2;
			break;
		}
		case Size::SMALL: {
			ac.size = 1;
			break;
		}
		case Size::MEDIUM: {
			ac.size = 0;
			break;
		}
		case Size::LARGE: {
			ac.size = -1;
			break;
		}
		case Size::HUGE: {
			ac.size = -2;
			break;
		}
		case Size::GARGANTUAN: {
			ac.size = -4;
			break;
		}
		case Size::COLOSSAL: {
			ac.size = -8;
			break;
		}
		default: {
			cout << "Invalid creature size, exiting program." << endl;
			exit(_ERR_INVALID_SIZE);
		}

	}

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

	ac.breakdown = calculateAcBreakdown();

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

	clearBuffer();

	return ac;

}

HitDice PfMon::fetchHd() {

	int racialHd;

	cout << "How many racial HD does this creature have? ";
	cin >> racialHd;
	hd.totalHd = racialHd;
	hd.racialHdCount = hd.totalHd;

	cout << "Class levels for monsters will come in a later version." << endl;

	switch (creatType) {
		case CreatureType::ABERRATION: {
			hd.d8 = racialHd;
			break;
		}
		case CreatureType::ANIMAL: {
			hd.d8 = racialHd;
			break;
		}
		case CreatureType::CONSTRUCT: {
			hd.d10 = racialHd;
			switch (creatSize) {
				case Size::FINE:
				case Size::DIMINUTIVE:
				case Size::TINY: {
					break;
				}
				case Size::SMALL: {
					hd.bonus = 10;
					break;
				}
				case Size::MEDIUM: {
					hd.bonus = 20;
					break;
				}
				case Size::LARGE: {
					hd.bonus = 30;
					break;
				}
				case Size::HUGE: {
					hd.bonus = 40;
					break;
				}
				case Size::GARGANTUAN: {
					hd.bonus = 60;
					break;
				}
				case Size::COLOSSAL: {
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
			hd.d12 = racialHd;
			break;
		}
		case CreatureType::FEY: {
			hd.d6 = racialHd;
			break;
		}
		case CreatureType::HUMANOID: {
			hd.d8 = racialHd;
			break;
		}
		case CreatureType::MAGICAL_BEAST: {
			hd.d10 = racialHd;
			break;
		}
		case CreatureType::MONSTROUS_HUMANOID: {
			hd.d10 = racialHd;
			break;
		}
		case CreatureType::OOZE: {
			hd.d8 = racialHd;
			break;
		}
		case CreatureType::OUTSIDER: {
			hd.d10 = racialHd;
			break;
		}
		case CreatureType::PLANT: {
			hd.d8 = racialHd;
			break;
		}
		case CreatureType::UNDEAD: {
			hd.d8 = racialHd;
			break;
		}
		case CreatureType::VERMIN: {
			hd.d8 = racialHd;
			break;
		}
		default: {
			cout << "Homebrew creature types will come later. Exiting program." << endl;
			exit(_ERR_INVALID_CREATURE_TYPE);
		}
	}
	
	return hd;
}

int PfMon::calculateHp() {

	double hdAverage = 0.0;
	hp = 0;

	/* Note that even when monsters have multiple HD sources and two or more
	 * sources of hit dice that average to ?.5 each, each source of HD is
	 * rounded down before being added. For proof, math out the Serpentfolk
	 * Bone Prophet on MC204.
	 */

	hdAverage += (2.5 * hd.d4);
	hdAverage += (3.5 * hd.d6);
	hdAverage += (4.5 * hd.d8);
	hdAverage += (5.5 * hd.d10);
	hdAverage += (6.5 * hd.d12);

	hp = hd.bonus + static_cast<int>(hdAverage) + (abilities.conMod * hd.totalHd);


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
	
	calculateHpBreakdown();

	return hp;
}

string PfMon::fetchDefensiveAbilities() {

	cout << "List the monster's defensive abilities here: ";
	getline(cin,defensiveAbilities);

	return defensiveAbilities;
}

string PfMon::determineImmunities() {

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
	getline(cin,immunities);

	return immunities;
}

string PfMon::fetchResistances() {

	cout << "List the monster's resistances here: ";
	getline(cin,resistances);

	return resistances;
}

string PfMon::fetchWeaknesses() {

	cout << "List the monster's weaknesses here: ";
	getline(cin,weaknesses);

	return weaknesses;
}

string PfMon::fetchDr() {

	cout << "List the monster's DR here: ";
	getline(cin,dr);

	return dr;
}

string PfMon::fetchSr() {

	cout << "List the monster's SR here: ";
	getline(cin,sr);

	return sr;
}

Saves PfMon::determineSaves() {

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
			clearBuffer();

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
			clearBuffer();

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

string PfMon::calculateAcBreakdown() {

	ac.breakdown = "(";

	if (ac.armor != 0) {
		ac.breakdown += to_string(ac.armor);
		ac.breakdown += " armor, ";
	}
	if (ac.shield != 0) {
		ac.breakdown += to_string(ac.shield);
		ac.breakdown += " shield, ";
	}
	if (ac.natural != 0) {
		ac.breakdown += to_string(ac.natural);
		ac.breakdown += " natural, ";
	}
	if (ac.dex != 0) {
		ac.breakdown += to_string(ac.dex);
		ac.breakdown += " Dex, ";
	}
	if (ac.dodge != 0) {
		ac.breakdown += to_string(ac.dodge);
		ac.breakdown += " dodge, ";
	}
	if (ac.deflection != 0) {
		ac.breakdown += to_string(ac.deflection);
		ac.breakdown += " deflection, ";
	}
	if (ac.insight != 0) {
		ac.breakdown += to_string(ac.insight);
		ac.breakdown += " insight, ";
	}
	if (ac.luck != 0) {
		ac.breakdown += to_string(ac.luck);
		ac.breakdown += " luck, ";
	}
	if (ac.sacred != 0) {
		ac.breakdown += to_string(ac.sacred);
		ac.breakdown += " sacred, ";
	}
	if (ac.profane != 0) {
		ac.breakdown += to_string(ac.profane);
		ac.breakdown += " profane, ";
	}
	if (ac.racial != 0) {
		ac.breakdown += to_string(ac.racial);
		ac.breakdown += " racial, ";
	}
	if (ac.size != 0) {
		ac.breakdown += to_string(ac.size);
		ac.breakdown += " size";
	}

	ac.breakdown += ")";
	return ac.breakdown;
}

string PfMon::calculateHpBreakdown() {

	int hdTypes = 0;

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
		hpBreakdown = to_string(hd.totalHd);
		hpBreakdown += "HD; ";
	}


	if (hd.d4) {
		hpBreakdown += to_string(hd.d4) + "d4 + ";
	}
	if (hd.d6) {
		hpBreakdown += to_string(hd.d6) + "d6 + ";
	}
	if (hd.d8) {
		hpBreakdown += to_string(hd.d8) + "d8 + ";
	}
	if (hd.d10) {
		hpBreakdown += to_string(hd.d10) + "d10 + ";
	}
	if (hd.d12) {
		hpBreakdown += to_string(hd.d12) + "d12 + ";
	}

	if (creatType == CreatureType::UNDEAD) {
		hpBreakdown += to_string(abilities.chaMod * hd.totalHd + hd.bonus);
	} else if (creatType == CreatureType::CONSTRUCT) {
		hpBreakdown += to_string(hd.bonus);
	} else {
		hpBreakdown += to_string(abilities.conMod * hd.totalHd + hd.bonus);
	}

	return hpBreakdown;
}

/******************************************************************************\
 *                                OFFENSE                                     *
\******************************************************************************/

string PfMon::fetchSpeed() {

	cout << "List speed here (including alt speeds, like fly or swim): " << endl;
	getline(cin,speed);

	return speed;

}

string PfMon::fetchMeleeAtk() {

	int strAtkBonus = bab + abilities.strMod;
	int finesseAtkBonus = bab + abilities.dexMod;

	cout << "Type what you want to appear next to the Melee Attack line." << endl;
	cout << "The STR-based attack bonus is " << strAtkBonus << ", and the DEX-based attack bonus (if applicable) is " << finesseAtkBonus << endl;

	getline(cin,meleeAtk);

	return meleeAtk;
}

string PfMon::fetchRangedAtk() {

	int thrownAtkBonus = bab + abilities.strMod;
	int bowAtkBonus = bab + abilities.dexMod;

	cout << "Type what you want to appear next to the Ranged Attack line." << endl;
	cout << "The STR-based attack bonus is " << thrownAtkBonus << ", and the DEX-based attack bonus is " << bowAtkBonus << endl;

	getline(cin,rangedAtk);

	return rangedAtk;
}

string PfMon::calculateSpace() {

	switch (creatSize) {
		case Size::FINE: {
			space = "1/2 ft.";
			break;
		}
		case Size::DIMINUTIVE: {
			space = "1 ft.";
			break;
		}
		case Size::TINY: {
			space = "2-1/2 ft.";
			break;
		}
		case Size::SMALL: {
			space = "5 ft.";
			break;
				}
		case Size::MEDIUM: {
			space = "5 ft.";
			break;
		}
		case Size::LARGE: {
			space = "10 ft.";
			break;
		}
		case Size::HUGE: {
			space = "15 ft.";
			break;
		}
		case Size::GARGANTUAN: {
			space = "20 ft.";
			break;
		}
		case Size::COLOSSAL: {
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

string PfMon::determineReach() {

	string isTall;

	switch (creatSize) {
		case Size::FINE: {
			reach = "0 ft.";
			break;
		}
		case Size::DIMINUTIVE: {
			reach = "0 ft.";
			break;
		}
		case Size::TINY: {
			reach = "0 ft.";
			break;
		}
		case Size::SMALL: {
			reach = "5 ft.";
			break;
				}
		case Size::MEDIUM: {
			reach = "5 ft.";
			break;
		}
		case Size::LARGE: {
			cout << "Is the creature tall or long? ";
			cin >> isTall;

			if (tolower(isTall[0]) == 't') {
				reach = "10 ft.";
			} else {
				reach = "5 ft.";
			}
			break;
		}
		case Size::HUGE: {
			cout << "Is the creature tall or long? ";
			cin >> isTall;

			if (tolower(isTall[0]) == 't') {
				reach = "15 ft.";
			} else {
				reach = "10 ft.";
			}
			break;
		}
		case Size::GARGANTUAN: {
			cout << "Is the creature tall or long? ";
			cin >> isTall;

			if (tolower(isTall[0]) == 't') {
				reach = "20 ft.";
			} else {
				reach = "15 ft.";
			}
			break;
		}
		case Size::COLOSSAL: {
			cout << "Is the creature tall or long? ";
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

string PfMon::fetchSpecialAttacks() {

	cout << "List the monster's special attacks here: ";
	getline(cin,specAtk);

	return specAtk;
}

/******************************************************************************\
 *                               STATISTICS                                   *
\******************************************************************************/

Abilities PfMon::fetchAbilities() {

	cout << "Give the scores, not the modifiers." << endl;

	cout << "STR: ";
	cin >> abilities.str;
	abilities.strMod = static_cast<int>(floor((abilities.str - 10) / 2.0));
	abilities.displayStr = to_string(abilities.str);


	clearBuffer();
	cout << "DEX: ";
	cin >> abilities.dex;
	abilities.dexMod = static_cast<int>(floor((abilities.dex - 10) / 2.0));
	abilities.displayDex = to_string(abilities.dex);

	if ((creatType != CreatureType::UNDEAD) && (creatType != CreatureType::CONSTRUCT)) {
		cout << "CON: ";
		cin >> abilities.con;
		abilities.conMod = static_cast<int>(floor((abilities.con - 10) / 2.0));
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
		abilities.intMod = static_cast<int>(floor((abilities.intelligence - 10) / 2.0));
		abilities.displayInt = to_string(abilities.intelligence);
	} else {
		abilities.intelligence = INT_MIN;
		abilities.intMod = INT_MIN;
		abilities.displayInt = "—"; //Em-dash (U+2014) for extra width
	}

	clearBuffer();
	cout << "WIS: ";
	cin >> abilities.wis;
	abilities.wisMod = static_cast<int>(floor((abilities.wis - 10) / 2.0));
	abilities.displayWis = to_string(abilities.wis);

	clearBuffer();
	cout << "CHA: ";
	cin >> abilities.cha;
	abilities.chaMod = static_cast<int>(floor((abilities.cha - 10) / 2.0));
	abilities.displayCha = to_string(abilities.cha);


	if (creatType == CreatureType::UNDEAD) {
		abilities.conMod = abilities.chaMod;
	}
	if (creatType == CreatureType::CONSTRUCT) {
		abilities.conMod = 0;
	}

#ifdef _DEBUG
	cout << "Abilities: " << endl;

	cout << "STR   score: " << abilities.str << endl;
	cout << "STR     mod: " << abilities.strMod << endl;
	cout << "Display STR: " << abilities.displayStr << endl << endl;

	cout << "DEX   score: " << abilities.dex << endl;
	cout << "DEX     mod: " << abilities.dexMod << endl;
	cout << "Display DEX: " << abilities.displayDex << endl << endl;

	cout << "CON   score: " << abilities.con << endl;
	cout << "STR     CON: " << abilities.conMod << endl;
	cout << "Display CON: " << abilities.displayCon << endl << endl;

	cout << "INT   score: " << abilities.intelligence << endl;
	cout << "INT     mod: " << abilities.intMod << endl;
	cout << "Display INT: " << abilities.displayInt << endl << endl;

	cout << "WIS   score: " << abilities.wis << endl;
	cout << "WIS     mod: " << abilities.wisMod << endl;
	cout << "Display WIS: " << abilities.displayWis << endl << endl;

	cout << "CHA   score: " << abilities.cha << endl;
	cout << "CHA     mod: " << abilities.chaMod << endl;
	cout << "Display CHA: " << abilities.displayCha << endl << endl;
#endif

	return abilities;
}

int PfMon::calculateBab() {

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

Maneuvers PfMon::determineCombatManeuvers() {

	char choice;

	maneuvers.cmb = bab;
	maneuvers.cmd = 10 + bab + abilities.strMod + abilities.dexMod;

	cout << "Agile Maneuvers feat? (yes/no)" << endl;
	cin >> choice;

	clearBuffer();

	if (choice == 'y' || choice == 'Y') {
		maneuvers.agileManuevers = true;
		featList += "Agile Maneuvers, ";
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

	return maneuvers;
}

string PfMon::fetchFeats() {

	int hdFeats = (1 + hd.totalHd) / 2;
	string featsAddendum;

	cout << "List the feats here. Based on HD, you should have " << hdFeats << " feats." << endl;
	getline(cin,featsAddendum);

	featList += featsAddendum;

	return featList;
}

string PfMon::fetchSkills() {

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
	getline(cin, skillList);

	return skillList;
}

string PfMon::fetchLanguages() {

	cout << "List the monster's languages here: ";
	getline(cin,languageList);

	return languageList;
}

string PfMon::fetchSpecialQualities() {

	cout << "List the monster's special qualities here: ";
	getline(cin,specialQualities);

	return specialQualities;

}

/******************************************************************************\
 *                                ECOLOGY                                     *
\******************************************************************************/

string PfMon::fetchEnvironment() {

	cout << "List the monster's environments here: ";
	getline(cin,environmentList);

	return environmentList;
}

string PfMon::fetchOrganization() {

	cout << "List the monster's grouping habits here: ";
	getline(cin,groupList);

	return groupList;
}

string PfMon::fetchTreasure() {

	cout << "List treasure here: " << endl;
	getline(cin,lootList);

	return lootList;
}

/******************************************************************************\
 *                           SPECIAL ABILITIES                                *
\******************************************************************************/

string PfMon::fetchSpecialAbilities() {

	string abilityName;
	string abilityText;
	string choice;

	cout << "Does this monster have any special abilities not accounted for by the universal monster rules? ";
	getline(cin,choice);

	while (choice[0] == 'y' || choice[0] == 'Y') {

		specialAbilities += "<p><span class=\"itemheader\">";

		cout << "Ability name (Ex/Su/Sp): ";
		getline(cin,abilityName);
		specialAbilities += abilityName;

		specialAbilities += " </span>";

		cout << "Ability text: ";
		getline(cin,abilityText);
		specialAbilities += abilityText;

		specialAbilities += "</p>\n";

		cout << "Continue? ";
		getline(cin,choice);
	}

	return specialAbilities;
}

/******************************************************************************\
 *                                 SYSTEM                                     *
\******************************************************************************/

PfMon::PfMon() {

	string temp;

	cout << "Monster Name: ";
	getline(cin, monName);

	temp = monName;

	fileName = strcat(strcat(strcat(getenv("PWD"),_DIR_SEPARATOR_STRING),temp.c_str()),".html");
	//Compatibility note: I have no idea if $PWD exists on Windows

	cr [0] = '\0';
	cr [1] = '\0';
	cr [2] = '\0';
	cr [3] = '\0';

	alignment[0] = '\0';
	alignment[1] = '\0';
	alignment[2] = '\0';

	senses = "";

	specialAbilities = "";
}

PfMon::~PfMon() {
}

string PfMon::prepareWrite() {

	ifstream monTemplate;

	monTemplate.open(_PFRPG_TEMPLATE, ios::in); 
	file.open(fileName, ios::in | ios::out | ios::trunc);

	file << monTemplate.rdbuf();

	monTemplate.close();

	return "Ready for write!";
}
