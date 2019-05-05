/***************************************
 * Program: Unit Test 3
 * Author: Trevor Frame
 * Date: 04/29/2019
 *
 * Description: This program tests refactored code from
 * assignment 2. The refactored code tests Steward funciton.
 *
 * ************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "steward"

void assertResults(int results, int expected);

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
	printf("TEST 1: gain 2 cards \n");
	choice1 = 1;
	cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("Hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 1);
	assertResults(testG.handCount[thisPlayer], G.handCount[thisPlayer] + 1);

	printf("TEST 2: gain 2 coins \n");
	choice1 = 2;
	cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("Coins = %d, expected = %d\n", testG.coins, G.coins + 2);
	assertResults(testG.coins, G.coins + 2);

	printf("TEST 3: trash 2 cards \n");
	choice1 = 3;
	cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("Hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 2);
	printf("Deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 2);
	assertResults(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 2, testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 2);
}

void assertResults(int result, int expected){
	if(result == expected){
		printf("Test passed!\n");
	}
	else{
		printf("Test failed.\n");
	}
}
