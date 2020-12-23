// Text-Based Adventure.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Text-Based-Adventure.h"


void initialSetup()
{
	isPlaying = true;
	isExploring = true;
	hasWon = false;
	userCommand = "list";

	playerIsBlocking = false;
	monsterIsBlocking = false;

	srand(time(0));
	
	//All exploring commands
	exploringCommandList[0] = "list";
	exploringCommandList[1] = "look";
	exploringCommandList[2] = "inspect";
	exploringCommandList[3] = "talk";
	exploringCommandList[4] = "move";
	exploringCommandList[5] = "inventory";
	exploringCommandList[6] = "use";
	exploringCommandList[7] = "equip";
	exploringCommandList[9] = "quest";
	exploringCommandList[8] = "endgame";
	

	//All fighting commands
	fightingCommandList[0] = "list";
	fightingCommandList[1] = "attack";
	fightingCommandList[2] = "block";
	fightingCommandList[3] = "item";
	fightingCommandList[4] = "run";
	fightingCommandList[5] = "endgame";

	//Create All Environments
	environmentArray[0] = TownCreator();
	environmentArray[1] = ForestCreator();
	environmentArray[2] = CastleCreator();
//	currentEnvironment = 0;
	currentEnvironment = environmentArray->identifier;

	//Create All Monsters
	monsterList[0] = monsterCreateGoblin();
	monsterList[1] = monsterCreateLizardman();
	monsterList[2] = monsterCreateGrowler();
	monsterList[3] = monsterCreateGhost();
	monsterList[4] = monsterCreateSpecter();
	monsterList[5] = monsterCreateDragon();

	//Create Inventory setup
	StartInv();
}

void startCombat(characterObject monster)
{
	isExploring = false;
	currentMonster = monster;
}

void enemyAI()
{
	
}

void endCombat()
{

}

void exploringCommands()
{
	//I realize now that I cannot use a switch statement for strings... I am sad...
	if (userCommand == "list")
	{
		std::cout << "Here are all the available commands: " << std::endl;
		for (int i = 0; i < 9; i++)
		{
			std::cout << exploringCommandList[i] << std::endl;
		}
	}
	else if (userCommand == "look") //Describes Area
	{
		std::cout << environmentArray[currentEnvironment].description << std::endl;
	}
	else if (userCommand == "inspect") //Inspects and picks up objects of interest
	{
		std::cout << "You look around and find a ";

		if (environmentArray[currentEnvironment].pickedUp == false)
		{
			AddItem(environmentArray[currentEnvironment].pickUpItem);
			environmentArray[currentEnvironment].pickedUp = true;

			std::cout << environmentArray[currentEnvironment].pickUpItem.name << std::endl;
		}
		else
		{
			std::cout << "plain old leaf; nothing of value" << std::endl;
		}
	}
	else if (userCommand == "talk") //Talks to NPC
	{
		cout << "Who would you like to talk to?" << endl;
		for (int i = 0; i < (sizeof(environmentArray[currentEnvironment].NPCList)/sizeof(environmentArray[currentEnvironment].NPCList[0])); i++)
		{
			cout << environmentArray[currentEnvironment].NPCList[i] << endl;
		}

		cin >> userCommand;

		for (int i = 0; i < (3); i++)
		{
			
		}
	}
	else if (userCommand == "move") //moves player to area
	{
		std::cout << "Where would you like to go?" << std::endl;
		for (int i = 0; i < (sizeof(environmentArray[currentEnvironment].moveableLocations)/sizeof(environmentArray[currentEnvironment].moveableLocations[0])); i++)
		{
			std::cout << environmentArray[i].moveableLocations[i] << std::endl;
		}

		std::cin >> userCommand;

		for (int i = 0; i < 3; i++)
		{
			if (userCommand == environmentArray[i].moveableLocations[i])
			{
				currentEnvironment = i;
			}
		}
//		std::cout << currentEnvironment;
		std::cout << "You go to the " << environmentArray[currentEnvironment].moveableLocations[currentEnvironment] << std::endl;
	}
	else if (userCommand == "inventory")	//opens inventory list
	{
		Inventory();
	}
	else if (userCommand == "use")
	{

	}
	else if (userCommand == "equip")
	{

	}
	else if (userCommand == "quest")
	{

	}
	else if (userCommand == "endgame")
	{
		isPlaying = false;
	}
	else
	{
		std::cout << "Not a recognized command.  Input 'list' to list all commands.  Remember, all commands must be in all lowercase." << std::endl;
	}
}

void fightingCommands()
{
	playerIsBlocking = false;

	if (userCommand == "list")
	{
		std::cout << "Here are all the available commands: " << std::endl;
		for (int i = 0; i < 5; i++)
		{
			std::cout << fightingCommandList[i] << std::endl;
		}
		return;  //Don't want the enemy attacking just because the player asked on what to do.
	}
	else if (userCommand == "fight")
	{
		int damage = -Player.dealDamage();
		if (monsterIsBlocking)
		{
			damage = damage / 2;
		}
		currentMonster.heal(damage);

		if (currentMonster.stats.health <= 0)
		{

		}

		cout << "You dealt " + to_string(damage) + " points of damage!  The monster is at " + to_string(currentMonster.stats.health) + "health points." << endl;

	}
	else if (userCommand == "block")
	{
		cout << "You ready yourself for a blow.  Damage is halved." << endl;
		playerIsBlocking = true;
	}
	else if (userCommand == "run")
	{
		
	}
	else if (userCommand == "endgame")
	{
		isPlaying = false;
		return;	//No sense in making them wait
	}
	else
	{
		cout << "Not a recognized command.  Input 'list' to list all commands.  Remember, all commands must be in all lowercase." << endl;
		return;	//Don't want the enemy attacking for a mistype
	}

	enemyAI();
}

int main()
{
	//Sets up the locations and characters, etc.
	initialSetup();
	//Put opening blurb here.
	std::cout << "Welcome to 'The Castle of Mystery' text-based adventure.  In this game, you must solve puzzles, and battle monsters to try and find out what happened to the mysterious castle on the hill.\n" << std::endl;

	exploringCommands();

	do
	{
		std::cin >> userCommand;
		if (isExploring)
		{
			exploringCommands();
		}
		else
		{
			fightingCommands();
		}
	} while (isPlaying);

}
