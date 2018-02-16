#ifndef PFSPELL_HPP
#define PFSPELL_HPP

#include <string>
#include <climits>
using namespace std;

enum class SpellSchool {NUL = 0, ABJURATION = 1, CONJURATION, CALLING, CREATION, HEALING, SUMMONING, TELEPORTATION,\
DIVINATION, SCRYING, ENCHANTMENT, CHARM, COMPULSION, EVOCATION, ILLUSION, FIGMENT, GLAMER, PATTERN, PHANTASM, SHADOW,\
NECROMANCY, TRANSMUTATION, POLYMORPH}; //Currently unused

struct SpellOutput {
	string name;
	int dc;
};


class PfSpell
{
public:
	SpellOutput determineSpell(int castingStatMod); //So everyone is a Wizard now?
	SpellOutput determineSpell(int castingStatMod, string name);

	PfSpell();
	~PfSpell();

private:
	string name;
	int dc = INT_MIN;
	int spellLevel;
	int miscDcBonuses;

	string fetchName();
	int fetchSpellLevel();
	int determineDc(int castingStatMod);
	int fetchMiscDcBonuses();
};

#endif // PFSPELL_HPP
