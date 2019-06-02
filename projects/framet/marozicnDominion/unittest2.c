/***************************************
 * Program: Unit Test 2
 * Author: Trevor Frame
 * Date: 04/29/2019
 *
 * Description: This program tests refactored code from
 * assignment 2. The refactored code tests Adventurer funciton.
 *
 * ************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"


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

	int newCards = 2;
	int discarded = 1;
	int shuffledCards = 0;

	struct gameState G;
	struct gameState testG;
	int k[10] = {adventurer, smithy, embargo, tribute, steward, mine, cutpurse, council_room, village, sea_hag};

	initializeGame(numPlayers, k, seed, &G);

	printf("\n********** Testing Card: %s **********\n", TESTCARD);



	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("Test 1: Verify size of hand\n");
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	assertResult(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);


	printf("Test 2: Verify size of deck\n");
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.handCount[thisPlayer] - newCards + shuffledCards);
	assertResult(testG.deckCount[thisPlayer], G.handCount[thisPlayer] - newCards + shuffledCards);


}

void assertResult(int result, int expected){

	if(result == expected){
		printf("Test passed!\n");
	}
	else{
		printf("Test failed.\n");
	}
}


