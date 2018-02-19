#include <iostream>
#include <sstream>
#include <time.h>
#include <stdlib.h>
#include <limits>
#include <chrono>
#include <thread>
#include "header.h"

using std::string;

class enemyInfo{
public:
	string enemyName;
	int enemyHealth;
	int enemyLevel;
} enemyOne;

int combatInitPrompt(string enemyNameInput, int enemyHealthInput, int enemyLevelInput);
int combatFightModule();
void combatRunModule();
void sleepMilli(int x);
void combatUserAttackBasic();
void combatUserWait();
string combatEnemyChoice();
void combatEnemyAttack();
void combatUserSpellBasic();
void combatEnemyWait();
void givePlayerHealth();
void printOptions();
void clearScreen();

int combatInitPrompt(string enemyNameInput, int enemyHealthInput, int enemyLevelInput){ // Initial the combat with choice to fight or run, if 
	                 //fight is chosen you will be sent to the combat proper, if run you will have a chance to escape
	using std::cout;
	using std::endl;

	enemyOne.enemyName = enemyNameInput;
	enemyOne.enemyHealth = enemyHealthInput;
	enemyOne.enemyLevel = enemyLevelInput;

	clearScreen();
	string array[] = {"FIGHT", "RUN", "BUFFER"};
	cout << "A SCORNED LOVER STANDS BEFORE ME WEILDING A SPIKED CUDGEL!" << endl;
	cout << "WHAT SHOULD I DO?" << endl;
	cout << "FIGHT RUN" << endl;

	bubbleSort(array, 3);

	string userCommand = stringSearch(array, 3);
	clearScreen();
	cout << userCommand << endl;
	if(userCommand == "FIGHT"){
		return combatFightModule();
	}
	else{
		combatRunModule();
	}

}

int combatFightModule(){ // The user has chosen to fight, run all of the functions for combat
	using std::string;
	using std::cout;
	using std::endl;

	bool userTurn = true;
	string actionArray[] = {"ATTACK", "WAIT", "SPELL", "BUFFER", "BUFFER"};

	cout << "I WILL FIGHT THIS ONE!" << endl;

	sleepMilli(500);

	clearScreen();
	printOptions();
	cout << "THE SCORNED LOVER STEPS CLOSER!" << endl;
	cout << endl << "WHAT DO I DO?" << endl;

	while(enemyOne.enemyHealth > 0 && playerOne.playerHealth > 0){
		while(userTurn == true){
			bubbleSort(actionArray, 5);
			string userAction = stringSearch(actionArray, 5);

			if(userAction == "ATTACK"){
				combatUserAttackBasic();
				if(enemyOne.enemyHealth <= 0 ){
					cout << "I HAVE DASHED HIS BRAINS AGAINST THE COBBLESTONES! HOORAY!" << endl;
					return 1;
				}else{
					cout << "ENEMY HEALTH AT " << enemyOne.enemyHealth << endl;
				}
				userTurn = !userTurn;
			}else if(userAction == "SPELL"){
				combatUserSpellBasic();
				if(enemyOne.enemyHealth <= 0 ){
					cout << "I HAVE INCINERATED HIM! HOORAY!" << endl;
					return 1;
				}else{
					cout << "ENEMY HEALTH AT " << enemyOne.enemyHealth << endl;
				}
				userTurn = !userTurn;
			}else{
				combatUserWait();
				userTurn = !userTurn;
			}
		}

		while(userTurn == false){
			string enemyChoice = combatEnemyChoice();

			if(enemyChoice == "ATTACK"){
				combatEnemyAttack();
			}else if(enemyChoice == "WAIT"){
				combatEnemyWait();
			}
			if(playerOne.playerHealth <= 0){
				cout << "I HAVE BEEN STRUCK DOWN! BLEH!" << endl;
				return 0;
			}
			userTurn = !userTurn;
		}
	}
}

void combatRunModule(){ // The user has chosen to try to run away, roll for chance of run away
	using std::cout;
	using std::endl;

	clearScreen();
	cout << "I AM A COWARD AND RUN AWAY!" << endl;
}

void sleepMilli(int x){ // Sleeps for X milliseconds
	std::this_thread::sleep_for(std::chrono::milliseconds(x));
}

void combatUserAttackBasic(){ // Rolls damage for the user basic attack and applies damage to the enemy
	using std::cout;
	using std::endl;

	srand(time(NULL));

	int damageRoll = (rand() % 10);

	if(playerOne.classNum == 1){
		clearScreen();
		printOptions();

		if(damageRoll < 1){
			damageRoll = 0;
		}else{
			damageRoll -= 1;
		}
		cout << endl << "I HAVE SMASHED HIS HEAD FOR " << damageRoll << " DAMAGE!" << endl;

		enemyOne.enemyHealth = enemyOne.enemyHealth - damageRoll;
	}else if(playerOne.classNum == 2){
                clearScreen();
                printOptions();
		
		damageRoll += playerOne.playerLevel;

		cout << endl << "I HAVE SMASHED HIS HEAD FOR " << damageRoll << " DAMAGE!" << endl;

		enemyOne.enemyHealth = enemyOne.enemyHealth - damageRoll;

        }else if(playerOne.classNum == 3){
                clearScreen();
                printOptions();

		if(playerOne.playerCrit == true){
			int critRoll = (rand() % 10) + 5;

			cout << endl << "I HAVE STAB THE ENEMY WITH MY ... ROCK!" << endl;

			enemyOne.enemyHealth = enemyOne.enemyHealth - critRoll;

			cout << "THEY TAKE " <<  critRoll << " DAMAGE" << endl;

			playerOne.playerCrit = false;

		}else{
			damageRoll += 1;

			cout << endl << "I HAVE SMASHED HIS HEAD FOR " << damageRoll << " DAMAGE!" << endl;

			enemyOne.enemyHealth = enemyOne.enemyHealth - damageRoll;
		}
		
        }else if(playerOne.classNum == 4){
                clearScreen();
		printOptions();

		if(damageRoll < 4){
			damageRoll = 0;
		}else{
			damageRoll -= 4;
		}
		cout << endl << "I HAVE SMASHED HIS HEAD FOR " << damageRoll << " DAMAGE!" << endl;
		enemyOne.enemyHealth = enemyOne.enemyHealth - damageRoll;
        }
}

void combatUserSpellBasic(){ // Spell damage rolls
	using std::cout;
	using std::endl;

	srand(time(NULL));

	int damageRoll;

	if(playerOne.classNum == 1){
		clearScreen();
		printOptions();

		damageRoll = (rand() % 10);
		if(damageRoll == 0){
			cout << "I CAST A FIRE BALL AT THE ENEMY! IT GOES PAST THEM AND HITS ME IN THE BACK OF THE HEAD!" << endl;
			cout << "I LOSE 3 HEALTH!" << endl;
			playerOne.playerHealth = playerOne.playerHealth - 3;
		}else if(damageRoll < 10){
			cout << "I SEND A FIRE BALL AT THE ENEMY! ";
			cout << "IT CONNECTS WITH HIS LEFT NOSTRIL!" << endl;
			enemyOne.enemyHealth = enemyOne.enemyHealth - 4;
			cout << "HE TAKES 4 DAMAGE, AND HIS NOSE HAIR IS SINGED!" << endl;
		}else if(damageRoll == 10){
			cout << "I SEND A LIGHTNING BOLT AT THE ENEMY! ";
			cout << "IT STRIKES HIM IN THE RIGHT BIG TOE!" << endl;
			enemyOne.enemyHealth = enemyOne.enemyHealth - 7;
			cout << "THE PAIN OF A HUNDRED STUBBED TOES BRINGS HIM 7 DAMAGES!" << endl;
		}
	}else if(playerOne.classNum == 2){
                clearScreen();
		printOptions();

		cout << "I TRY VERY HARD TO CAST A SPELL. INSTEAD I HAVE DROOLED ON MY CHEST!" << endl;
        }else if(playerOne.classNum == 3){
                clearScreen();
		printOptions();

		cout << "I TRY VERY HARD TO CAST A SPELL. INSTEAD I HAVE DROOLED ON MY CHEST!" << endl;
        }else if(playerOne.classNum == 4){
                clearScreen();
		printOptions();

		damageRoll = (rand() % 10);
		if(damageRoll == 0){
			cout << "I CAST A FIRE BALL AT THE ENEMY! IT GOES PAST THEM AND HITS ME IN THE BACK OF THE HEAD!" << endl;
			cout << "I LOSE 3 HEALTH!" << endl;
			playerOne.playerHealth = playerOne.playerHealth - 3;
		}else if(damageRoll < 10){
			cout << "I SEND A FIRE BALL AT THE ENEMY!" << endl << endl;
			cout << "IT CONNECTS WITH HIS LEFT NOSTRIL!" << endl << endl;
			enemyOne.enemyHealth = enemyOne.enemyHealth - 5;
			cout << "HE TAKES 5 DAMAGE, AND HIS NOSE HAIR IS SINGED!" << endl;
		}else if(damageRoll == 10){
			cout << "I SEND A LIGHTNING BOLT AT THE ENEMY!" << endl;
			cout << "IT STRIKES HIM IN THE RIGHT BIG TOE!" << endl;
			enemyOne.enemyHealth = enemyOne.enemyHealth - 8;
			cout << "THE PAIN OF A HUNDRED STUBBED TOES BRINGS HIM 8 DAMAGE!" << endl;
		}
        }
}

void combatUserWait(){ 
	using std::cout;
	using std::endl;

	clearScreen();
	printOptions();

	if(playerOne.classNum == 3){
		cout << endl << "I PREPARE MY WEAPON, GIVING THE ENEMY A MEAN GLARE!" << endl;
		playerOne.playerCrit = true;
	}else{
		cout << endl << "I HAVE COMPLETED MY LIFE LONG GOAL OF WASTING MY TURN!" << endl;
	}
}

string combatEnemyChoice(){ // Determin the choice of the enemy
	srand(time(NULL));
	int enemyChoice = (rand() % 5);

	if(enemyChoice > 3){
		return "WAIT";
	}else{
		return "ATTACK";
	}
}

void combatEnemyAttack(){ // Roll enemy damage and apply damage
	using std::cout;
	using std::endl;
	using std::cin;

	srand(time(NULL));

	int damageRoll;

	cout << endl << "THE BRUTE STAGGERS FORWARD AND SWINGS AT ME WITH HIS SPIKED CUDGEL!" << endl;

	if(enemyOne.enemyLevel <= 5){
		damageRoll = (rand() % 10);
		if(damageRoll == 0){
			
			cout << endl << "THE BASTARD HAS MISSED! NOW IS MY CHANCE!" << endl;
			cout << endl;
		}else{
			
			playerOne.playerHealth = playerOne.playerHealth - damageRoll;
			cout << endl << "OOFF, I'VE TAKEN " << damageRoll << " DAMAGE!" << endl;
			if(playerOne.playerHealth <= 0){
				string userDeathCommand;
				bool userDed;

				cout << endl << "I MUST NOW CHOOSE TO HOLD ON OR DIE." << endl;
				getline(cin, userDeathCommand);

				while(!userDed){
					if(userDeathCommand == "DIE"){
						userDed = true;
					}else{
						cout << "I REALLY AM TIRED..." << endl << endl;
						getline(cin, userDeathCommand);
					}

				}
			}else{
				cout << "I ONLY HAVE " << playerOne.playerHealth 
				<< " LEFT! I MUST BE CAREFUL" << endl;

				cout << endl;
			}
			
		}
	}
}

void combatEnemyWait(){ // The enemy waits a turn
	using std::cout;
	using std::endl;

	cout << endl << "THE DRUNKEN LOVER BELCHES AND STARES AT ME MENACINGLY!" << endl << endl;
}

void printOptions(){
	using std::cout;
	using std::endl;

	cout << "OPTIONS -- ATTACK (HIT THE ENEMY WITH A LARGE ROCK) -- SPELL (CAST A POWERFULL SPELL AT THE ENEMY... PROBABLY) -- WAIT (STAND WITH A BLANK EXPRESION)" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
}

void clearScreen(){ // Clear the screen and move curser to the upper left
	using std::cout;

	cout << "\033[2J\033[1;1H";
}