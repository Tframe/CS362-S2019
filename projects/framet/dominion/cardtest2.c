/***************************************
 * Program: Card Test 2
 * Author: Trevor Frame
 * Date: 04/29/2019
 *
 * Description: This program tests Smithy function
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

	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("\n********** TESTING CARD: %s **********\n", TESTCARD);
	printf("Test 1: Deck count change\n");

	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("Deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 3);
	assertResult(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 3);

	printf("Test 2: Coin change\n");	
	printf("Coin count = %d, expected = %d\n", testG.coins, G.coins);
	assertResult(testG.coins, G.coins);

	printf("Test 3: Bad function call failed\n");
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

