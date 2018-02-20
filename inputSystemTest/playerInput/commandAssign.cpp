//commandAssign is a file that takes inputs from inputSplit and rewrites verb and noun
//to common words

//TODO:
//test userInput::::english <-- done & removed
#include <iostream>
#include <string>
#include "../global/header.h"
#include "commandAssign.h"

//verbSearch: takes inputs from the player and makes sure that the room knows what to do with it
//syllables in the verbAssign 2d array are reassigned to the [0] string in the array
//that way if the player uses words that aren't used by startRoom, commandAssign
//makes it so that syllables are still understood.
//
//for each array, verbSearch checks the verb for all syllables (CRAWL, DRIFT, etc.)
//there is an array for each verb that the game uses

void verbSearch () {
	using std::string;

	string verbAssign [7][256] = {
	{"HELP", "FUCKTHISGAME", "FUCKYOU", "SHITDICK", "IMDONE", "STUCK", "UGH"},
	{"QUIT", "STOP", "TERMINATE", "HALT", "DISCONTINUE", "DIE"},
	{"MOVE", "GO", "WALK", "RUN", "HEAD", "ADVANCE", "CRAWL", "DRIFT", "MIGRATE", "PROCEED", "RELOCATE", "TRAVEL", "HURRY", "MARCH", "SHAMBLE"},
	{"TAKE", "STEAL", "GRAB", "PICKUP", "COLLECT", "SIEZE", "GRASP", "GRIP", "SNATCH", "FIND", "REMOVE", "PULL"},
	{"USE", "EMPLOY", "EXERCISE", "GOVERN", "APPLY", "EXPLOIT"},
	{"LOOK", "GLANCE", "PEER", "VIEW", "STARE", "ADMIRE", "GAZE", "INSPECT", "OBSERVE", "SCRUTINIZE", "SEARCH", "POKE", "TOUCH", "CARESS", "STROKE", "WIGGLE", "TAP", "PROD", "PAT", "RUB", "EXAMINE", "FEEL"},
	{"OPEN", "UNLOCK"},
	};

	for (int c = 0; c < 7; c++) {
		if (verbAssign[0][c] == userInput::verb) {
			userInput::verb="HELP";
		}
	}
	for (int c = 0; c < 6; c++) {
		if (verbAssign[1][c] == userInput::verb) {
			userInput::verb="QUIT";
		}
	}
	for (int c = 0; c < 15; c++) {
		if (verbAssign[2][c] == userInput::verb) {
			userInput::verb="MOVE";
		}
	}
	for (int c = 0; c < 12; c++) {
		if (verbAssign[3][c] == userInput::verb) {
			userInput::verb="TAKE";
		}
	}
	for (int c = 0; c < 6; c++) {
		if (verbAssign[4][c] == userInput::verb) {
			userInput::verb="USE";
		}
	}
	for (int c = 0; c < 22; c++) {
		if (verbAssign[5][c] == userInput::verb) {
			userInput::verb="LOOK";
		}
	}
	for (int c = 0; c < 2; c++) {
		if (verbAssign[6][c] == userInput::verb) {
			userInput::verb="OPEN";
		}
	}
	if (userInput::verb=="HELP" || userInput::verb=="QUIT") {
		userInput::noun="(null)";
	}
	else nounSearch ();
}

//nounSearch doesn't use the same 2d array system that verbSearch does
//because there aren't as many syllables for the nouns in the game.
//nounSearch makes sure that the inputs from the player are useable by the startRoom function

void nounSearch () {
	if (userInput::noun=="NORTH" || userInput::noun=="N") {
		userInput::noun = "NORTH";
	}
	if (userInput::noun=="EAST" || userInput::noun=="E") {
		userInput::noun = "EAST";
	}
	if (userInput::noun=="SOUTH" || userInput::noun=="S") {
		userInput::noun = "SOUTH";
	}
	if (userInput::noun=="WEST" || userInput::noun=="W") {
		userInput::noun = "WEST";
	}
	if (userInput::noun=="STONE" || userInput::noun=="BRICK" || userInput::noun=="ROCK") {
		userInput::noun = "STONE";
	}
	if (userInput::noun=="HOLE" || userInput::noun=="PANEL") {
		userInput::noun = "HOLE";
	}
	if (userInput::noun=="SKELETON" || userInput::noun=="BONES" || userInput::noun=="BONE") {
		userInput::noun = "SKELETON";
	}
	if (userInput::noun=="CLOTH" || userInput::noun=="CLOTHES" || userInput::noun=="RAGS" || userInput::noun=="RAG") {
		userInput::noun = "CLOTH";
	}
	if (userInput::noun=="BROADSWORD" || userInput::noun=="SWORD" || userInput::noun=="BLADE") {
		userInput::noun = "SWORD";
	}
	if (userInput::noun=="AROUND" || userInput::noun=="ABOUT" || userInput::noun=="EVERYWHERE")
		userInput::noun = "AROUND";
}