/***************************************
 * Program: Card Test 1
 * Author: Trevor Frame
 * Date: 04/29/2019
 *
 * Description: This program tests Adventurer function.
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

	int xtraCoins = 0;	

	struct gameState G;
	struct gameState testG;
	int k[10] = {adventurer, smithy, embargo, tribute, steward, mine, cutpurse, council_room, village, sea_hag};

	initializeGame(numPlayers, k, seed, &G);

	printf("\n********** TESTING CARD: %s **********\n", TESTCARD);

	printf("Test 1: Verify coin count changes\n");

	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assertResult(testG.coins, G.coins + xtraCoins);

	
	for(int i = 0; i < testG.handCount[thisPlayer]; i++){
		if(testG.hand[thisPlayer][i] == (copper || silver || gold)){
					xtraCoins = xtraCoins + 1;
		}
	}
	printf("Extra coins = %d, expected = 2\n", xtraCoins); 
	assertResult(xtraCoins, 2);

	printf("Test 2: Verify coins action doesn't change \n");

	printf("actions left = %d, expected = %d\n", testG.numActions, G.numActions);
	assertResult(testG.numActions, G.numActions);


	printf("Test 3: Veryify bad function call fails \n");
	assertResult(cardEffect(-adventurer, choice1, choice2, choice3, &testG, handpos, &bonus), 1);
	
	

}

void assertResult(int result, int expected){

	if(result == expected){
		printf("Test passed!\n");
	}
	else{
		printf("Test failed.\n");
	}
}


