/* 
 * File:   hearts.h
 * Author: Stephanie Peacock
 * Created on October 24, 2023, 6:45 PM
 */

#ifndef HEARTS_H
#define HEARTS_H

//Constants
const int DECK = 52;    //constant number of cards

//structures
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

struct Show {
    string pshow[13];   //to correspond with the player structure    
    string show[DECK];  //face values for the entire deck
};

struct Win {
    char name[20];
    int score;
};

// Input function prototypes
//Deal to each player - deck array & all players
void deal(fstream &, fstream &, int *, Player *, const int, Show *);  
void shuffle(int *, const int, Show *); //Shuffle the deck array (nested inside deal)
int  linSrch(int *, const int);         //Find 2 of clubs  (nested inside deal) - deck array
void mSort(Player *, Show *);           //Sort each player's hand (nested inside deal)
void print(Player &, Show &);           //Print out face values of player's hand
void play(Player *, Show *);            //Play the trick           
void playCard(Player *, int);           //Determine which card to play (Stooge)
void played(Player &,Show &);           //Print out the cards played (nested inside playCard)
void set(Player &);                     //Set the player's choice to card value (nested inside playCard)
void trick(Player *);                   //Score the trick
void unset(Player &, Show &);           //Set choice back & remove played card from hand (nested inside trick)
void mSort(Win *);                      //Sort the winners

#endif /* HEARTS_H */

