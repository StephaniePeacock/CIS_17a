/* 
 * File:   Player.h
 * Author: Stephanie Peacock
 * Created on December 10, 2023, 7:15 PM
 * Purpose: Player Class Specification
 */

#include "AbsPlayer.h"
#include "Deck.h"
#include <iomanip>
using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

enum Order {FIRST,SECOND,THIRD,FOURTH};

//class Stooge;   //Forward Declare Stooge

class Player : public AbsPlayer {
private:
    string name;         //C-String to hold player name
    Order  order;        //To determine order for the trick    
    Card  *hand;         //Holds the player's cards
    int    size;         //current number of cards in the player's hand
    int    choice;       //Int value for the player's card
    bool   match;        //Enforce suit
    int    tScore;       //Trick score
    int    score;        //Game score
public:
    Player();
    Player(string);
    virtual ~Player();
    //Mutators
    void addCard(Card c);  //push back a card to the hand (modifies hand & size)
    void discard(int);   //pop off selected card from the hand (modifies hand & size)
    void setName(string s)  { name = s;   }
    void setOrder(Order ord){ order = ord;}
    void setChoice(int c)   { choice = c; }
    void setMatch(bool m)   { match = m;  }
    void setTrick(int t)    { tScore = t; }
    void setScore(int sc)   { score = sc; }
    //Accessors
    string getName()  { return name;  }
    Order  getOrder() { return order; }
    int    getChoice(){ return choice;}
    bool   getMatch() { return match; }
    int    getTrick() { return tScore;}
    int    getScore() { return score; }
    int    getSize()  { return size;  }
    //Other Functions
    void play(Player &, Stooge **, int) { cout << "Player played." << endl; }
    void mSort(){
        for(int j = 0; j < 13; j++){
            for(int i = j + 1; i < 13; i++){
                if(hand[j] > hand[i]){
                    //sort the player int values
                    Card temp = hand[j];
                    hand[j] = hand[i];
                    hand[i] = temp;
                }
            }
        }
    }
    void print(){
        cout << endl << "Play Card #:\t";
        for(int i = 0; i < getSize(); i++){
           cout << i+1 << "\t";
        }
        cout << endl << setw(14) << "\t";
        for(int i = 0; i < getSize(); i++){
           cout << hand[i].getFace() << "\t";
        }
        cout << endl;
    }
    void played(){}
    
};

#endif /* PLAYER_H */

