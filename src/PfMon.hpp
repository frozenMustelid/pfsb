#ifndef PFMON_HPP
#define PFMON_HPP

#include "commonFunctions.hpp"
#include "PfMeta.hpp"

#include <fstream>
using namespace std;

class PfMon
{
public:

/* Note: I have to declare most of the data members as public, or else the find-
 * replace function won't work. I'd end up being forced to write trivial getters
 * for nearly every data member. So just make sure that only this class itself
 * (and even then only the functions that should change that specific member's
 * values) ever modifies any data members. Or else we're gonna have big trouble
 * when/if I update this program to support non-PF games.
 * 
 * Also note that these functions always return a value. Assigning this value to
 * the appropriate data member is redundant. The value is returned for
 * a) Debugging purposes, b) In case it becomes necessary in the future to
 * use this value for something else, and c) Style reasons. I believe that void
 * functions should be used sparingly, as they can obfuscate the purpose of a
 * function. Add in the obfuscation caused by method calls that don't take
 * arguments like a function does, and things can get confusing quickly.
 * 
 * On the function naming scheme: "fetch" functions focus almost exclusively on
 * user input. "calculate" functions  do not contain any user input elements at
 * all. "determine" functions feature both, but does enough to not warrant a
 * fetch label.
 */
/******************************************************************************\
 *                                 HEADER                                     *
\******************************************************************************/

	string monNameTop;
	string description;

	string monName;
	char cr[4];
	string xp;
	string alignment;
	Size creatSize;
	string creatSizeWords;
	CreatureType creatType;
	string creatTypeWords;
	string subtypes;
	int initiative;
	string senses;
	string aura;

	string fetchMonNameTop();
	string fetchDescription();
	long crAndXp(); //Returns the XP value
	string fetchAlignment();
	string fetchSize();
	string fetchCreatureType();
	string fetchSubtypes();
	int determineInitiative();
	string fetchSenses();
	string fetchAura();


/******************************************************************************\
 *                                 DEFENSE                                    *
\******************************************************************************/

	AC ac;
	HitDice hd;
	int hp;
	string hpBreakdown;
	Saves saves;
	string defensiveAbilities;
	string immunities;
	string resistances;
	string weaknesses;
	string dr;
	string sr;

	AC determineAC();
	HitDice fetchHd();
	int calculateHp();
	Saves determineSaves();
	string fetchDefensiveAbilities();
	string determineImmunities();
	string fetchResistances();
	string fetchWeaknesses();
	string fetchDr();
	string fetchSr();


/******************************************************************************\
 *                                OFFENSE                                     *
\******************************************************************************/

	string speed;
	string meleeAtk;
	string rangedAtk;
	string space;
	string reach;
	string specAtk;
	string slas;

	string fetchSpeed();
	string fetchMeleeAtk();
	string fetchRangedAtk();
	string calculateSpace();
	string determineReach();
	string fetchSpecialAttacks();
	string determineSlas();


/******************************************************************************\
 *                               STATISTICS                                   *
\******************************************************************************/

	Abilities abilities;
	int bab;
	Maneuvers maneuvers;
	string featList;
	string skillList;
	string languageList;
	string specialQualities;

	Abilities fetchAbilities();
	int calculateBab();
	Maneuvers determineCombatManeuvers();
	string fetchFeats();
	string fetchSkills();
	string fetchLanguages();
	string fetchSpecialQualities();

/******************************************************************************\
 *                                ECOLOGY                                     *
\******************************************************************************/

	string environmentList;
	string groupList;
	string lootList;

	string fetchEnvironment();
	string fetchOrganization();
	string fetchTreasure();

/******************************************************************************\
 *                           SPECIAL ABILITIES                                *
\******************************************************************************/

	string specialAbilities;

	string fetchSpecialAbilities();

/******************************************************************************\
 *                                 SYSTEM                                     *
\******************************************************************************/

	const char* fileName;
	fstream file;

	PfMon();
	~PfMon();
	string prepareWrite();


private:
	
/******************************************************************************\
 *                                 HEADER                                     *
\******************************************************************************/

	string formatXp(long xp);
	CreatureType determineCreatureType();

/******************************************************************************\
 *                                 DEFENSE                                    *
\******************************************************************************/

	string calculateAcBreakdown();
	string calculateHpBreakdown();

/******************************************************************************\
 *                                OFFENSE                                     *
\******************************************************************************/

	string addSlaListItem();

/******************************************************************************\
 *                                 SYSTEM                                     *
\******************************************************************************/

	const string noneString = "<p class=\"none\">None</p>";

	inline void setEmptyStringToNone(string& toAlter) {

		if (toAlter.empty()) {
			toAlter = noneString;
		}
		return;
	}

	/* Like compilers actually care if you inline the function. You'd think that
	 * all pretense that compilers care what the programmers think would make
	 * the code more performant would have been lost after they deprecated the
	 * register keyword, but I guess we can't admit that yet.
	 */
};

#endif // PFMON_HPP