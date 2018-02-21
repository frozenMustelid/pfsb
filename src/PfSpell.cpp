#include "commonFunctions.hpp"
#include "PfSpell.hpp"

#include <iostream>
using namespace std;

SpellOutput PfSpell::determineSpell(int castingStatMod) {

	SpellOutput spell;

	fetchName();
	fetchSpellLevel();
	fetchMiscDcBonuses();
	determineDc(castingStatMod);

	spell.name = name;
	spell.dc = dc;

	return spell;
}

SpellOutput PfSpell::determineSpell(int castingStatMod, string name) {

	SpellOutput spell;

	fetchSpellLevel();
	fetchMiscDcBonuses();
	determineDc(castingStatMod);

	spell.name = name;
	spell.dc = dc;

	return spell;
}

string PfSpell::fetchName() {

	cout << "Enter spell name: ";
	getline(cin,name);

	return name;
}

int PfSpell::fetchSpellLevel() {

	bool valid = false;

	do {
		cout << "Enter spell level: ";
		cin >> spellLevel;
		clearBuffer();

		if (_betweeninc(spellLevel,0,9)) {
			valid = true;
		} else {
			cout << "Spell level must be between 0 and 9." << endl;
		}
	} while (!(valid));

	return spellLevel;
}

int PfSpell::determineDc(int castingStatMod) {

	dc = 10 + spellLevel + castingStatMod + miscDcBonuses;

	return dc;
}

int PfSpell::fetchMiscDcBonuses() {

	cout << "Amount of misc. DC bonuses (not casting stat/spell level/10 base): ";
	cin >> miscDcBonuses;

	clearBuffer();

	return miscDcBonuses;
}

PfSpell::PfSpell()
{
}

PfSpell::~PfSpell()
{
}

