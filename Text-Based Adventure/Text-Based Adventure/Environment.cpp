#pragma once
	
#include "Text-Based-Adventure.h"

class Environment
{
public:
	int identifier;
	std::string description;
	int interactable[5];
	int moveableLocations[3];
	int NPCList;
	int puzzleSolution;
	int monsterList;
};

Environment TownCreator() {
	Environment Town;

	Town.identifier = 0;
	Town.description = "Welcome to the Town!";
//	Town.interactable = {	}//list of interactable places
	Town.moveableLocations;
	Town.NPCList;

	return Town;
}