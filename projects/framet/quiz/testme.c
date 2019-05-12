/*************************************
 * Author: Trevor Frame
 * Date: 05/10/2019
 * Title: Random Tester
 * **********************************/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
    //choose random number between 40 and 125 to choose ascii character
    int randNum = 0;
    char asciiChar;

    randNum = rand() % 94 + 32;
    asciiChar = randNum;
    return asciiChar;
}

char *inputString()
{
    // TODO: rewrite this function
    char stringInput[6];
    int randNum = 0;
    char possibleChars[27] = {'r', 'e', 's', 't', 0, 'a', 'b', 'c', 'd', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'u', 'v', 'w', 'x', 'y', 'z'};

    //randomly choose how many potential characters to choose from
    randNum = rand() % 21 + 5;

    stringInput[0] = possibleChars[rand() % randNum];
    stringInput[1] = possibleChars[rand() % randNum];
    stringInput[2] = possibleChars[rand() % randNum];
    stringInput[3] = possibleChars[rand() % randNum];
    stringInput[4] = possibleChars[rand() % randNum];
    stringInput[5] = possibleChars[rand() % randNum];
    return stringInput;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
