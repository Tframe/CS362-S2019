/***************************************
 * Program: Unit Test 1
 * Author: Trevor Frame
 * Date: 04/29/2019
 *
 * Description: This program tests refactored code from
 * assignment 2. The refactored code tests Tribute funciton.
 *
 * ************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define TESTCARD "tribute"

void assertResults(int result, int expected);

int main(){

	//setup game similar to game setup in example

	int handpos = 0;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int bonus = 0;
	
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int prevPlayer = thisPlayer + 1;		
	struct gameState G;
	struct gameState testG;
	int k[10] = {adventurer, smithy, embargo, tribute, steward, mine, cutpurse, council_room, village, sea_hag};
	
	//trackers
	int prevAction = 0;
	int action = 4;
	int deckCounter = 0;

	//initialize game
	initializeGame(numPlayers, k, seed, &G);	


	printf("\n********** TESTING CARD: %s **********\n", TESTCARD);	
	printf("Test 1: Revealed 2 Action card = +4 Action\n");
	//-------- Test 1 ... Top cards are = 1 = +2 Action --------
	deckCounter = G.deckCount[prevPlayer] - 1;
	
	prevAction = testG.numActions;
	//setup player2 deck
	G.deck[prevPlayer][deckCounter - 1] = mine;
	G.deck[prevPlayer][deckCounter] = village;
	memcpy(&testG, &G, sizeof(struct gameState));	
	

	cardEffect(tribute, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("Action count = %d, expected = %d\n", testG.numActions, G.numActions + prevAction + action);
	assertResults(testG.numActions, G.numActions + prevAction + action);


	//Test 2 ... Choice1 = 2 = +2 Coins
	printf("\nTest 2: Revealed 2 Treasure card = +4 coins\n");
	int addCoin = 4;
	action = 0;
	printf("\n");
	//setup player2 deck
	
	
	G.deck[prevPlayer][deckCounter - 2] = silver;
	G.deck[prevPlayer][deckCounter] = gold;
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(tribute, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("Coins count = %d, expected = %d\n", testG.coins, G.coins + addCoin);
	assertResults(testG.coins, G.coins + addCoin);

	//Test 3 ... Choice1 = 3 = +2 Cards
	printf("\nTest 3: Revealed 2 Victory card = +4 cards\n");
	action = 0;
	//setup player2 deck
	G.deck[prevPlayer][deckCounter - 2] = estate;
	G.deck[prevPlayer][deckCounter] = duchy;
	memcpy(&testG, &G, sizeof(struct gameState));

	int addedCards = 4;
	cardEffect(tribute, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("Hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + addedCards);
	assertResults(testG.handCount[thisPlayer], G.handCount[thisPlayer] + addedCards);
	
	return 0;
}

void assertResults(int result, int expected){

	if(result == expected){
		printf("Test passed!\n");
	}
	else{
		printf("Test failed.\n");
	}
}





