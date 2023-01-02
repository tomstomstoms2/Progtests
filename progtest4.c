#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define SUITE_SPADES     0x000
#define SUITE_HEARTS     0x080
#define SUITE_CLUBS      0x100
#define SUITE_DIAMONDS   0x180

#define SPADES(X)        ((X) | SUITE_SPADES) //1
#define HEARTS(X)        ((X) | SUITE_HEARTS) //2
#define CLUBS(X)         ((X) | SUITE_CLUBS) //3
#define DIAMONDS(X)      ((X) | SUITE_DIAMONDS) //4

#define RES_DRAW         0
#define RES_WIN_A        1
#define RES_WIN_B        (-1)
#define RES_INVALID      2
#endif /* __PROGTEST__ */

typedef struct card{int value; int color;}CARD;

//computes value of card
int cardValue(int value){
  if(value < 58){
    return value - 48;
  }
  if(value == 88){
    return 10;
  }
  if(value == 74){
    return 11;
  }
  if(value == 81){
    return 12;
  }
  if(value == 75){
    return 13;
  }
  if(value == 65){
    return 14;
  }
  return -1;
}

//determine what color and value card is
CARD computeCard(int card){
  CARD tmp;
  if(card > 383){
    tmp.color = 4;
    tmp.value = cardValue(card - 384);
    return tmp;
  }
  if(card > 255){
    tmp.color = 3;
    tmp.value = cardValue(card - 256);
    return tmp;
  }
  if(card > 127){
    tmp.color = 2;
    tmp.value = cardValue(card - 128);
    return tmp;
  }
  tmp.color = 1;
  tmp.value = cardValue(card);
  return tmp;
}

//reform hand to usable state
void computeHand(const int player[], CARD * save[]){
  CARD hand[5];
  CARD tmp;
  for(int i = 0; i < 5; i++){
    hand[i] = computeCard(player[i]);
  }
  int sorted = 0;
  while(!sorted){
    for(int i = 0; i < 4; i++){
      if(hand[i].value > hand[i+1].value){
        tmp.value = hand[i + 1].value;
        hand[i + 1].value = hand[i].value;
        hand[i].value = tmp.value;
      }
    }
    if(hand[0].value <= hand[1].value && hand[1].value <= hand[2].value && hand[2].value <= hand[3].value && hand[3].value <= hand[4].value){
      sorted = 1;
    }
  }
}

//checks if all cards are valid
int unknownCard(const int * hand){
  //int check = 0;
  for(int i = 0; i < 5; i++){
    //printf("%d\n", hand[i]);
    if(!(hand[i] == 50 || hand[i] == 51 || hand[i] == 52 || hand[i] == 53 || hand[i] == 54 || hand[i] == 55 || hand[i] == 56 || hand[i] == 57 || hand[i] == 88 || hand[i] == 74 || hand[i] == 81 || hand[i] == 75 || hand[i] == 65 ||hand[i] == 178 || hand[i] == 179 || hand[i] == 180 || hand[i] == 181 || hand[i] == 182 || hand[i] == 183 || hand[i] == 184 || hand[i] == 185 || hand[i] == 216 || hand[i] == 202 || hand[i] == 209 || hand[i] == 203 || hand[i] == 193 ||hand[i] == 306 || hand[i] == 307 || hand[i] == 308 || hand[i] == 309 || hand[i] == 310 || hand[i] == 311 || hand[i] == 312 || hand[i] == 313 || hand[i] == 344 || hand[i] == 330 || hand[i] == 337 || hand[i] == 331 || hand[i] == 321 ||hand[i] == 434 || hand[i] == 435 || hand[i] == 436 || hand[i] == 437 || hand[i] == 438 || hand[i] == 439 || hand[i] == 440 || hand[i] == 441 || hand[i] == 472 || hand[i] == 458 || hand[i] == 465 || hand[i] == 459 || hand[i] == 449)){
      //printf("spravny\n");
      return 1;
    }
  }
  //printf("spatny\n");
  return 0;
}

//== operator for CARD type
int cmpCards(CARD a, CARD b){
  if(a.value == b.value && a.color == b.color){
    return 1;
  }
  return 0;
}

//checks for wrong input
int inputCheck(const int *playerA, const int *playerB){
  if(unknownCard(playerB) || unknownCard(playerA)){
    return 1;
  }
  int tmp;
  int count = 0;
  for(int i = 0; i < 5; i++){
    tmp = playerA[i];
    for(int j = 0; j < 5; j++){
      if(tmp == playerA[j]){
        count++;
      }
    }
    for(int j = 0; j < 5; j++){
      if(tmp == playerB[j]){
        count++;
      }
    }
  }
  if(count != 5){
    return 1;
  }
  count = 0;
  for(int i = 0; i < 5; i++){
    tmp = playerB[i];
    for(int j = 0; j < 5; j++){
      if(tmp == playerA[j]){
        count++;
      }
    }
    for(int j = 0; j < 5; j++){
      if(tmp == playerB[j]){
        count++;
      }
    }
  }
  if(count != 5){
    return 1;
  }
return 0;
}
/*
int inputCheck(CARD * hand1, CARD * hand2){
  //duplicate cards check
  CARD tmp;
  int count = 0;
  for(int i = 0; i < 5; i++){
    tmp = hand1[i];
    for(int j = 0; j < 5; j++){
      if(cmpCards(tmp, hand1[j])){
        count++;
      }
    }
    for(int j = 0; j < 5; j++){
      if(cmpCards(tmp, hand2[j])){
        count++;
      }
    }
  }
  printf("count = %d\n", count);
  if(count != 5){
    printf("duplicate1\n");
    return 1;
  }
  count = 0;
  for(int i = 0; i < 5; i++){
    tmp = hand2[i];
    for(int j = 0; j < 5; j++){
      if(cmpCards(tmp, hand1[j])){
        count++;
      }
    }
    for(int j = 0; j < 5; j++){
      if(cmpCards(tmp, hand2[j])){
        count++;
      }
    }
  }
  if(count != 5){
    printf("duplicate2\n");
    return 1;
  }

  if(unknownCard(hand1) || unknownCard(hand2)){
    printf("unknown\n");
    return 1;
  }
  return 0;
}
*/

//checks for draw
int gameDraw(CARD * hand1, CARD * hand2){
  for(int i = 0; i < 5; i++){
    if(!cmpCards(hand1[i], hand2[i])){
      return 0;
    }
  }
  return 1;
}

//checks for combinations of cards, the better combination, the bigger returned number
int combinations(CARD * hand){
  int count[5] = {0};
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
      if(hand[i].value == hand[j].value){
        count[i]++;
      }
    }
  }
  //sort the counts
  int sorted = 0, tmp;
  while(!sorted){
    for(int i = 0; i < 4; i++){
      if(count[i] > count[i+1]){
        tmp = count[i+1];
        count[i+1] = count[i];
        count[i] = tmp;
      }
    }
    if(count[0] <= count[1] && count[1] <= count[2] && count[2] <= count[3] && count[3] <= count[4]){
      sorted = 1;
    }
  }


  if(count[4] == 1 && hand[0].color == hand[1].color && hand[0].color == hand[2].color && hand[0].color == hand[3].color && hand[0].color == hand[4].color &&
                  hand[0].value + 1 == hand[1].value && hand[1].value + 1 == hand[2].value && hand[2].value + 1 == hand[3].value && hand[3].value + 1 == hand[4].value){
    return 9;
  }
  if(count[4] == 4){
    return 8;
  }
  if(count[4] == 3 && count[1] == 2){
    return 7;
  }
  if(hand[0].color == hand[1].color && hand[0].color == hand[2].color && hand[0].color == hand[3].color && hand[0].color == hand[4].color){
    return 6;
  }
  if(count[4] == 1 && hand[0].value + 1 == hand[1].value && hand[1].value + 1 == hand[2].value && hand[2].value + 1 == hand[3].value && hand[3].value + 1 == hand[4].value){
    return 5;
  }
  if(count[4] == 3){
    return 4;
  }
  if(count[4] == 2 && count[2] == 2){
    return 3;
  }
  if(count[4] == 2){
    return 2;
  }
  return 1;
}


int comparePokerHands ( const int playerA[], const int playerB[] ){
  if(inputCheck(playerA, playerB)){
    return RES_INVALID;
  }

  CARD hand1[5];
  CARD hand2[5];
  //computeHand(playerA, *hand1[]);
  //computeHand(playerB, *hand2[]);
  CARD tmp;
  for(int i = 0; i < 5; i++){
    hand1[i] = computeCard(playerA[i]);
  }
  int sorted = 0;
  while(!sorted){
    for(int i = 0; i < 4; i++){
      if(hand1[i].value > hand1[i+1].value){
        tmp.value = hand1[i + 1].value;
        hand1[i + 1].value = hand1[i].value;
        hand1[i].value = tmp.value;
      }
    }
    if(hand1[0].value <= hand1[1].value && hand1[1].value <= hand1[2].value && hand1[2].value <= hand1[3].value && hand1[3].value <= hand1[4].value){
      sorted = 1;
    }
  }
  for(int i = 0; i < 5; i++){
    hand2[i] = computeCard(playerB[i]);
  }
  sorted = 0;
  while(!sorted){
    for(int i = 0; i < 4; i++){
      if(hand2[i].value > hand2[i+1].value){
        tmp.value = hand2[i + 1].value;
        hand2[i + 1].value = hand2[i].value;
        hand2[i].value = tmp.value;
      }
    }
    if(hand2[0].value <= hand2[1].value && hand2[1].value <= hand2[2].value && hand2[2].value <= hand2[3].value && hand2[3].value <= hand2[4].value){
      sorted = 1;
    }
  }


  if(gameDraw(hand1, hand2)){
    return RES_DRAW;
  }
  int p1, p2;
  p1 = combinations(hand1);
  p2 = combinations(hand2);
  if(p1 > p2){
    return RES_WIN_A;
  }
  if(p1 < p2){
    return RES_WIN_B;
  }
  if(p1 == p2){
    if(hand1[4].value == hand2[4].value){
      if(hand1[3].value == hand2[3].value){
        if(hand1[2].value == hand2[2].value){
          if(hand1[1].value == hand2[1].value){
            if(hand1[0].value == hand2[0].value){
              return RES_DRAW;
            }else if(hand1[0].value > hand2[0].value){
              return RES_WIN_A;
            }else{return RES_WIN_B;}
          }else if(hand1[1].value > hand2[1].value){
            return RES_WIN_A;
          }else{return RES_WIN_B;}
        }else if(hand1[2].value > hand2[2].value){
          return RES_WIN_A;
        }else{return RES_WIN_B;}
      }else if(hand1[3].value > hand2[3].value){
        return RES_WIN_A;
      }else{return RES_WIN_B;}
    }else if(hand1[4].value > hand2[4].value){
      return RES_WIN_A;
    }else{return RES_WIN_B;}
  }
  return -1;
}


#ifndef __PROGTEST__
int main (int argc, char * argv [])
{

  int x0[] = { SPADES('5'), HEARTS('5'), CLUBS('5'), DIAMONDS('5'), HEARTS('X') };
  int y0[] = { SPADES('6'), SPADES('9'), SPADES('8'), SPADES('X'), SPADES('7') };
  //printf("%d\n", comparePokerHands ( x0, y0 ));
  assert ( comparePokerHands ( x0, y0 ) == RES_WIN_B );

  //printf("\n\n\nNEXT\n");

  int x1[] = { SPADES('2'), HEARTS('2'), CLUBS('2'), SPADES('A'), DIAMONDS('2') };
  int y1[] = { CLUBS('A'), HEARTS('K'), HEARTS('A'), SPADES('K'), DIAMONDS('A') };
  //printf("%d\n", comparePokerHands ( x1, y1 ));
  assert ( comparePokerHands ( x1, y1 ) == RES_WIN_A );

  //printf("\n\n\nNEXT\n");

  int x2[] = { CLUBS('3'), HEARTS('2'), HEARTS('3'), SPADES('2'), DIAMONDS('3') };
  int y2[] = { CLUBS('A'), CLUBS('9'), CLUBS('Q'), CLUBS('4'), CLUBS('J') };
  //printf("%d\n", comparePokerHands ( x2, y2 ));
  //printf("\nSAME\n\n");
  assert ( comparePokerHands ( x2, y2 ) == RES_WIN_A );

  //printf("\n\n\nNEXT\n");

  int x3[] = { DIAMONDS('3'), HEARTS('7'), SPADES('5'), DIAMONDS('6'), SPADES('4') };
  int y3[] = { CLUBS('2'), CLUBS('4'), CLUBS('6'), CLUBS('3'), CLUBS('X') };
  assert ( comparePokerHands ( x3, y3 ) == RES_WIN_B );

  int x4[] = { DIAMONDS('3'), HEARTS('7'), SPADES('5'), DIAMONDS('6'), SPADES('4') };
  int y4[] = { CLUBS('2'), DIAMONDS('2'), CLUBS('6'), CLUBS('3'), HEARTS('2') };
  assert ( comparePokerHands ( x4, y4 ) == RES_WIN_A );

  int x5[] = { DIAMONDS('3'), HEARTS('7'), SPADES('3'), DIAMONDS('6'), SPADES('7') };
  int y5[] = { CLUBS('2'), DIAMONDS('2'), CLUBS('6'), CLUBS('3'), HEARTS('2') };
  assert ( comparePokerHands ( x5, y5 ) == RES_WIN_B );

  int x6[] = { DIAMONDS('3'), HEARTS('7'), SPADES('3'), DIAMONDS('6'), SPADES('7') };
  int y6[] = { CLUBS('2'), DIAMONDS('9'), CLUBS('K'), CLUBS('A'), HEARTS('2') };
  assert ( comparePokerHands ( x6, y6 ) == RES_WIN_A );

  int x7[] = { DIAMONDS('A'), HEARTS('J'), SPADES('Q'), DIAMONDS('X'), SPADES('2') };
  int y7[] = { CLUBS('2'), DIAMONDS('9'), CLUBS('K'), CLUBS('A'), HEARTS('2') };
  assert ( comparePokerHands ( x7, y7 ) == RES_WIN_B );

  int x8[] = { DIAMONDS('A'), HEARTS('J'), SPADES('Q'), DIAMONDS('X'), SPADES('2') };
  int y8[] = { CLUBS('Q'), DIAMONDS('K'), CLUBS('2'), CLUBS('A'), HEARTS('3') };
  assert ( comparePokerHands ( x8, y8 ) == RES_WIN_B );

  int x9[] = { DIAMONDS('A'), HEARTS('5'), SPADES('4'), DIAMONDS('5'), CLUBS('4') };
  int y9[] = { DIAMONDS('4'), DIAMONDS('K'), CLUBS('5'), SPADES('5'), HEARTS('4') };
  assert ( comparePokerHands ( x9, y9 ) == RES_WIN_A );

  int x10[] = { CLUBS('A'), CLUBS('2'), CLUBS('3'), CLUBS('4'), CLUBS('5') };
  int y10[] = { HEARTS('J'), CLUBS('J'), SPADES('J'), HEARTS('2'), SPADES('2') };
  assert ( comparePokerHands ( x10, y10 ) == RES_WIN_B );

  int x11[] = { CLUBS('A'), CLUBS('K'), CLUBS('Q'), CLUBS('J'), CLUBS('X') };
  int y11[] = { HEARTS('3'), CLUBS('3'), SPADES('3'), HEARTS('2'), SPADES('2') };
  assert ( comparePokerHands ( x11, y11 ) == RES_WIN_A );

  int x12[] = { DIAMONDS('A'), HEARTS('5'), SPADES('4'), DIAMONDS('5'), CLUBS('4') };
  int y12[] = { DIAMONDS('4'), DIAMONDS('K'), CLUBS('5'), HEARTS('5'), HEARTS('4') };
  assert ( comparePokerHands ( x12, y12 ) == RES_INVALID );

  int x13[] = { DIAMONDS('A'), HEARTS('Z'), SPADES('4'), DIAMONDS('5'), CLUBS('4') };
  int y13[] = { DIAMONDS('4'), DIAMONDS('K'), CLUBS('5'), SPADES('5'), HEARTS('4') };
  assert ( comparePokerHands ( x13, y13 ) == RES_INVALID );

  int x14[] = { HEARTS('3'), SPADES('3'), CLUBS('3'), DIAMONDS('3'), SPADES('K') };
  int y14[] = { DIAMONDS('7'), HEARTS('7'), CLUBS('7'), SPADES('7'), SPADES('Q') };
  assert ( comparePokerHands ( x14, y14 ) == RES_WIN_B );

  return 0;
}
#endif /* __PROGTEST__ */
