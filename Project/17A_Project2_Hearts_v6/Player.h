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

class Stooge;   //Forward Declare Stooge

class Player : public AbsPlayer {
protected:
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
    void setTrick(int t)    { tScore += t;}
    void resetTrick()       { tScore = 0; }
    void setScore(int sc)   { score += sc; }
    static int players;  //tracks total number of players
    //Accessors
    string getName()  const       { return name;   }
    Order  getOrder() const       { return order;  }
    int    getChoice()const       { return choice; }
    bool   getMatch() const       { return match;  }
    int    getTrick() const       { return tScore; }
    int    getScore() const       { return score;  }
    int    getSize()  const       { return size;   }
    int    getCardSuit(int i)const   { return hand[i].getSuit();}
    int    getCardVal(int i) const   { return hand[i].getCnum();}
    int    getPlayers() const     { return players;}
    //Other Functions
    virtual void play(Player &, Stooge **);
    void mSort();
    void print();
    void played(){ cout << getName() << " played " << hand[getChoice()].getFace() << endl;}
    
};


#endif /* PLAYER_H */

