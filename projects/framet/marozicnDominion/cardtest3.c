/***************************************
 * Program: Unit Test 4
 * Author: Trevor Frame
 * Date: 04/29/2019
 *
 * Description: This program tests great_hall card
 *
 * ************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "great_hall"


void assertResult(int result, int expected);

int main(){

	int handpos = 0;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int bonus = 0;

	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;

	struct gameState G;
	struct gameState testG;
	int k[10] = {adventurer, smithy, embargo, tribute, steward, mine, cutpurse, council_room, village, great_hall};

	int addActions = 1;

	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("\n********** TESTING CARD: %s **********\n", TESTCARD);
	
	printf("Test 1: Hand count\n");
	printf("Hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	assertResult(testG.handCount[thisPlayer], G.handCount[thisPlayer]);

	printf("Test 2: Number of actions\n");
	printf("Actions = %d, expected = %d\n", testG.numActions, G.numActions + addActions);
	assertResult(testG.numActions, G.numActions + addActions);

	printf("Test 3: Coin change\n");	
	printf("Coin count = %d, expected = %d\n", testG.coins, G.coins);
	assertResult(testG.coins, G.coins);

	printf("Test 4: Bad function call failed\n");
	assertResult(cardEffect(-2, choice1, choice2, choice3, &testG, handpos, &bonus), 1);

	return 0;	

}

void assertResult(int result, int expected){

	if(result == expected){
		printf("Test passed!\n");
	}
	else{
		printf("Test failed.\n");
	}
}

