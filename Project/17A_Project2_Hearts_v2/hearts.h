/* 
 * File:   hearts.h
 * Author: Stephanie Peacock
 * Created on November 25, 2023, 6:45 PM
 */

#ifndef HEARTS_H
#define HEARTS_H

//Constants
const int DECK = 52;    //constant number of cards

enum Order {FIRST,SECOND,THIRD,FOURTH};

// Input function prototypes
void trick();
void deal(Player, Stooge *, Deck);


#endif /* HEARTS_H */

