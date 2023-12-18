/* 
 * File:   AbsPlayer.h
 * Author: Stephanie Peacock
 * Created on December 10, 2023, 3:47 PM
 * Purpose: AbsPlayer Class Specification
 */

using namespace std;

#ifndef ABSPLAYER_H
#define ABSPLAYER_H


class Player;   //Forward Declarations
class Stooge;   

class AbsPlayer {
    protected:
        virtual void play(Player &, Stooge **) = 0;  //pick a card - setChoice nested
        virtual void mSort() = 0;   //sort the cards
        virtual void print() = 0;   //print out the hand array
        virtual void played() = 0;  //print out name & what was played
        virtual void discard(int) = 0; //was unset - now will remove the card from the hand
        virtual int   getPlayers() const = 0;
};

#endif /* ABSPLAYER_H */

