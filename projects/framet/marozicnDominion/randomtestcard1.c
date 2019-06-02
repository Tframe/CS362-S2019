/******************************
 * Program: Random Test Smithy
 * Author: Trevor Frame
 * Date: 05/16/2019
 *
 * Description: This program random tests refactored code
 * from assignment 2. The refactored code is for the 
 * smithy card.
 * ***************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

#define TESTCARD "smithy"


int checkSmithy(int currentPlayer, struct gameState *testG){
	
	int handpos = 0;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int bonus = 0;

	return cardEffect(smithy, choice1, choice2, choice3, testG, handpos, &bonus);

}


int main(){

	int deckCount;
	int discardCount;
	int handCount;
	int player;
	int numPlayers = 4;
	struct gameState G;
	struct gameState testG;
	int extraTreasures;
	int numTests = 2000;
	int numPass = 0;
	int numFail = 0;	

	SelectStream(2);
	PutSeed(3);

	int k[10] = {adventurer, smithy, embargo, tribute, steward, mine, cutpurse, council_room, village, sea_hag};
	int t[3] = {copper, silver, gold};

	int expectedCount = 0;
	int actualCount = 0;

	printf("********** TESTING CARD: %s **********\n", TESTCARD);

	printf("Random Teseting\n");

	for (int i = 0; i < numTests; i++){
		expectedCount = 0;
		actualCount = 0;
		//int seed = floor(Random() * 1000);	
		int seed = 1000;
		initializeGame(numPlayers, k, seed, &G);
	
		extraTreasures = floor(Random() * 5);
		
		//add random number of treasure cards
		for(int j = 0; j < extraTreasures; j++){
			gainCard(t[(int)floor(Random() * 3)], &G, 1, player);
		}
		player = floor(Random() * 4);

		G.deckCount[player] = floor(Random() * MAX_DECK);
		G.discardCount[player] = floor(Random() * MAX_DECK);
		G.handCount[player] = floor(Random() * MAX_HAND);

		memcpy(&testG, &G, sizeof(struct gameState));

		checkSmithy(player, &testG);
		
		if(G.handCount[player]  == testG.handCount[player] || G.deckCount[player]  == testG.deckCount[player] || G.discardCount[player] == testG.deckCount[player]){
			numPass++;
		}
		else{
			numFail++;
		}

	}
	
	printf("Test Complete!\n");
	printf("Number of tests run: %d\n", numTests);
	printf("Number of test pass: %d\n", numPass);
	printf("Number of test failures: %d\n", numFail);

	return 0;
}
