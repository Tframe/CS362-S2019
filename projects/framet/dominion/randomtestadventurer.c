/******************************
 * Program: Random Test Adventurer
 * Author: Trevor Frame
 * Date: 05/16/2019
 *
 * Description: This program random tests refactored code
 * from assignment 2. The refactored code is for the 
 * adventurer card.
 * ***************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "adventurer"


int checkAdventurer(int currentPlayer, struct gameState *testState){
	int drawntreasure = 0;
	int cardDrawn;
	int temphand[MAX_HAND];
	int z = 0;

	int testing;

	testing = playAdventurer(currentPlayer, testState, temphand, drawntreasure, z);

}

int main(){

	srand(time(0));
	int deckCount;
	int discardCount;
	int handCount;
	int player;

	struct gameState G;

	//int k[10] = {adventurer, smithy, embargo, tribute, steward, mine, cutpurse, council_room, village, sea_hag};
	int k[16] = {estate, duchy, province, copper, silver, gold, adventurer, smithy, embargo, tribute, steward, mine, cutpurse, council_room, village, sea_hag};
	

	printf("********** TESTING CARD: %s **********\n", TESTCARD);

	printf("Random Teseting");

	for (int i = 0; i < 2000; i++){
	
		for(int j = 0; j < sizeof(struct gameState); j++){
			((char*)&G)[j] = rand() * 256;
		}
	
		player = rand() % 2;
		G.deckCount[player] = rand() % MAX_DECK;
		G.discardCount[player] = rand() % MAX_DECK;
		G.handCount[player] = rand() % MAX_HAND + 1;
	
		//setup deck
		for(int j = 0; j < G.deckCount[player]; j++){
			G.deck[player][j] = k[rand() % 16];
		}
	
		//setup hand
		for(int j = 0; j < G.handCount[player]; j++){
			G.hand[player][j] = k[rand() % 16];
		}

		checkAdventurer(player, &G);
	
	}
	

	return 0;
}
