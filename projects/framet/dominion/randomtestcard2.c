/******************************
 * Program: Random Test Tribute
 * Author: Trevor Frame
 * Date: 05/16/2019
 *
 * Description: This program random tests refactored code
 * from assignment 2. The refactored code is for the 
 * tribute card.
 * ***************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

#define TESTCARD "steward"

int checkSteward(int currentPlayer, struct gameState *testG, int choice1){
	
	int handpos = 0;
	int choice2 = 0;
	int choice3 = 0;
	int bonus = 0;

	return cardEffect(steward, choice1, choice2, choice3, testG, handpos, &bonus);

}


int main(){

	int deckCount;
	int discardCount;
	int handCount;
	int player;
	int numPlayers = 2;
	int numTests = 500;	

	struct gameState G;
	struct gameState testG;

	int numPass = 0;
	int numFail = 0;

	SelectStream(2);
	PutSeed(3);

	int k[10] = {adventurer, smithy, embargo, tribute, steward, mine, cutpurse, council_room, village, sea_hag};

	printf("********** TESTING CARD: %s **********\n", TESTCARD);

	printf("Random Testing\n");

	for (int i = 0; i < numTests; i++){
		
		//int seed = floor(Random() * 1000);
		int seed = 1000;
	
		initializeGame(numPlayers, k, seed, &G);
		int choice1 = floor(Random() * 3);	
		player = floor(Random() * 2);
		G.deckCount[player] = floor(Random() * MAX_DECK);
		G.discardCount[player] = floor(Random() * MAX_HAND);
		G.handCount[player] = floor(Random() * MAX_HAND);

		memcpy(&testG, &G, sizeof(struct gameState));

		checkSteward(player, &testG, choice1);
		
		//confirm hand count increases by 2
		if(choice1 == 1){
			if(G.handCount[player] == testG.handCount[player] - 2){
				numPass++;
			}
			else{
				numFail++;
			}

		}
		//confirm coin count increases by 2
		else if(choice1 == 2){
			if(G.coins == testG.coins - 2){
				numPass++;
			}
			else{
				numFail++;
			}
		}
		//confirm handcount decreases and discard count doesn't increase
		else{
			if(G.handCount[player] - 1 == testG.handCount[player] && G.discardCount[player] == testG.discardCount[player] - 1){
				numPass++;
			}
			else{
				numFail++;
			}
		}

	}
	
	printf("Test Complete!\n");
	printf("Number of tests run: %d\n", numTests);
	printf("Number of test pass: %d\n", numPass);
	printf("Number of test failures: %d\n", numFail);

	return 0;
}





