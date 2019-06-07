/***************************************
 * Program: Unit Test 4
 * Author: Trevor Frame
 * Date: 04/29/2019
 *
 * Description: This program tests refactored code from
 * assignment 2. The refactored code tests Smithy funciton.
 *
 * ************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"


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
	int k[10] = {adventurer, smithy, embargo, tribute, steward, mine, cutpurse, council_room, village, sea_hag};

	int addedCards = 2;

	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("\n********** TESTING CARD: %s **********\n", TESTCARD);
	printf("Test 1: +3 Cards\n");

	printf("Card count before played = %d, expect = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);

	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("Card count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + addedCards);
	assertResult(testG.handCount[thisPlayer], G.handCount[thisPlayer] + addedCards);
	

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

