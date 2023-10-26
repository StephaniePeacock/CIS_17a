/* 
 * File:   hearts.h
 * Author: Stephanie Peacock
 * Created on June 4, 2023, 4:45 PM
 */

#ifndef HEARTS_H
#define HEARTS_H

struct Cards {
    int cards[13];      //Card values to determine trick winner            
};

enum Order {FIRST,SECOND,THIRD,FOURTH};

struct Player {
    char *name;         //C-String to hold player name
    Order order;        //To determine order for the trick    
    Cards hand;         //Holds the player's cards
    int choice;         //Int value for the player's card
    bool match;         //Enforce suit
    int tScore;         //Trick score
    int score;          //Game score
};



// Input function prototypes
int  shuffle(fstream &);        //Shuffle entire deck then return the array
void deal(int *, Player *);     //Deal to each player - deck array & all players
int  linSrch(int *);            //Find 2 of clubs  (nested inside deal) - deck array
void mSort(Player *);           //Sort each player's hand (nested inside deal)
void print(Player &,string*);   //Print out face values of player's hand
void playCard(Player *);        //Determine which card to play
void played(Player &,string*);  //Print out the cards played (nested inside playCard)
void set(Player &);             //Set the player's choice to card value (nested inside playCard)
void trick( Player *);          //Score the trick
void unset(Player &);           //Set choice back & remove played card from hand (nested inside trick)
void count();                   //Counts how many tricks have been played

#endif /* HEARTS_H */

