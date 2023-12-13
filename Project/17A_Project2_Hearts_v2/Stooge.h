/* 
 * File:   Stooge.h
 * Author: Stephanie Peacock
 * Created on December 10, 2023, 7:16 PM
 * Purpose: Stooge Class Specification
 */

#include "Player.h"
using namespace std;

#ifndef STOOGE_H
#define STOOGE_H

//template <class T>

class Stooge : public Player{
private:

public:
    Stooge() : Player() {cout << "Stooge Created" << endl;}
    Stooge(string s) : Player(s) {}
    virtual ~Stooge() {cout << "Deleting Stooge" << endl;}

    //Mutators

    //Accessors

    //Other Functions
    virtual void play(Player &p, Stooge **s) { 
        bool chosen = false;
        // If npc is first to play in the trick - check for 2 clubs first
        if(getOrder() == FIRST) { 
            cout << "Stooge.h line 33" << endl;
            if ( getCard(0) == 0) {
                cout << "Stooge.h line 35" << endl;
                setChoice(0); setMatch(true); chosen = true;}
            // If no 2 clubs, play lowest card
            else {
                cout << "Stooge.h line 39" << endl;
                for(int i = 0; i < getSize() && !chosen; i++){
                    cout << "Stooge.h line 41" << endl;
                    setChoice(i); chosen = true; setMatch(true);
                }
            }
        }    
        else {
            //Check against all 4 players
            for(int z = 0; z < 4; z++){
                //make sure we don't go out of range - checks 3
                if(z == 3){
                    cout << "Stooge.h line 51" << endl;
                    if(p.getOrder() == FIRST) {
                        cout << "Stooge.h line 53" << endl;
                        int min = p.getChoice() < 13 ? 0 : p.getChoice() < 26 ? 13 : p.getChoice() < 39 ? 26 : 39;
                        int max = min + 13;
                    // match the suit if possible - playing lowest card possible    
                        for (int i = 0; i < getSize() && !chosen; i++) {
                            if (getCard(i) >= min && getCard(i) <= max) {
                                cout << "Stooge.h line 59" << endl;
                                setChoice(i); chosen = true; setMatch(true);
                            }
                        }
                    // Play Q spades, A spades, or K spades first if can't match suit   
                        if(!chosen){
                            for (int j = getSize(); j > 0 && !chosen; j--) {
                                cout << "Stooge.h line 66" << endl;
                                if (getCard(j) == 36) {setChoice(j); chosen = true; setMatch(false);}
                                if (getCard(j) == 38) {setChoice(j); chosen = true; setMatch(false);}
                                if (getCard(j) == 37) {setChoice(j); chosen = true; setMatch(false);}
                            }
                        }
                    // Lastly, play the highest card available   
                        if(!chosen){
                            for (int j = getSize(); j > 0 && !chosen; j--) {
                                cout << "Stooge.h line 75" << endl;
                                setChoice(j); chosen = true; setMatch(false);
                            }
                        } 
                    }
                }
                else {
                    //a stooge is first - checks 0 1 2
                    if(s[z]->getOrder() == FIRST) {
                        cout << "Stooge.h line 84" << endl;
                        int min = s[z]->getChoice() < 13 ? 0 : s[z]->getChoice() < 26 ? 13 : s[z]->getChoice() < 39 ? 26 : 39;
                        int max = min + 13;
                    // match the suit if possible - playing lowest card possible    
                        for (int i = 0; i < getSize() && !chosen; i++) {
                            if (getCard(i) >= min && getCard(i) <= max) {
                                setChoice(i); chosen = true; setMatch(true); 
                            }
                        }
                    // Play Q spades, A spades, or K spades first if can't match suit   
                        if(!chosen){
                            for (int j = getSize(); j > 0 && !chosen; j--) {
                                if (getCard(j) == 36) {setChoice(j); chosen = true; setMatch(false);}
                                if (getCard(j) == 38) {setChoice(j); chosen = true; setMatch(false);}
                                if (getCard(j) == 37) {setChoice(j); chosen = true; setMatch(false);}
                            }
                        }
                    // Lastly, play the highest card available   
                        if(!chosen){
                            cout << "Stooge.h line 97" << endl;
                            for (int j = getSize(); j > 0 && !chosen; j--) {
                                setChoice(j); chosen = true; setMatch(false);
                            }
                        } 
                    }
                }
            }
        }
    }
};

#endif /* STOOGE_H */

