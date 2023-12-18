/* 
 * File:   Stooge.cpp
 * Author: Stephanie Peacock
 * Created on December 10, 2023, 7:16 PM
 * Purpose: Stooge Class Implementation
 */
#include <iostream>
#include "Stooge.h"
using namespace std;

void Stooge::play(Player &p, Stooge **s) { 
        bool chosen = false;
        int val = 0;
        // If npc is first to play the lowest card - chosen true
//        cout << endl << getName() << "'s Cards:" << endl;
//        print();
        if(getOrder() == FIRST) { 
            setChoice(0); chosen = true; setMatch(true);
        }    
        //not chosen - check if player was first
        if(!chosen && p.getOrder() == FIRST) {
            //player is first 
    //        cout << "player was first - checking for a match" << endl;
            // match the suit if possible - playing lowest card possible
            while(!chosen && val < getSize()) {
                if (getCardSuit(val) == p.getCardSuit(p.getChoice())) {
        //            cout << "match found for player" << endl;
                    setChoice(val); chosen = true; setMatch(true);
                }
                val++;
            }  
        }
        //not chosen & larry is first 
        val = 0;
        if(!chosen && s[0]->getOrder() == FIRST) {
    //        cout << "larry was first - checking for a match" << endl;
        // match the suit if possible - playing lowest card possible  
            while(!chosen && val < getSize()) {
                if (getCardSuit(val) == s[0]->getCardSuit(s[0]->getChoice())) {
        //            cout << "match found for larry" << endl;
                    setChoice(val); chosen = true; setMatch(true); 
                }
                val++;
            }
        }
        //curly is first 
        val = 0;
        if(!chosen && s[1]->getOrder() == FIRST) {
        //    cout << "curly was first - checking for a match" << endl
        //         << " curly played suit number: " << s[1]->getCardSuit(s[1]->getChoice()) << endl;
            // match the suit if possible - playing lowest card possible 
            while(!chosen && val < getSize()) {
                if (getCardSuit(val) == s[1]->getCardSuit(s[1]->getChoice())) {
            //        cout << "match found for curly" << endl;
            //        cout << "played suit number : " << getCardSuit(getChoice()) << endl;
                    setChoice(val); chosen = true; setMatch(true); 
                }
                val++;
            }
        }
        //moe is first & their turn to be checked - skips playing stooge
        val = 0;
        if(!chosen && s[2]->getOrder() == FIRST) {
        //    cout << "moe was first - checking for a match" << endl;
            // match the suit if possible - playing lowest card possible    
            while(!chosen && val < getSize()) {
                if (getCardSuit(val) == s[2]->getCardSuit(s[2]->getChoice())) {
            //        cout << "match found for moe" << endl;
                    setChoice(val); chosen = true; setMatch(true); 
                }
                val++;
            }
        }    
        // Play Q spades, A spades, or K spades first if can't match suit   
        if(!chosen){
    //        cout << "unable to match checking for q spades" << endl;
            for (int j = getSize(); j > 0 && !chosen; j--) {
                if (getCardVal(j) == 36) {setChoice(j); chosen = true; setMatch(false);}
                else if (getCardVal(j) == 38) {setChoice(j); chosen = true; setMatch(false);}
                else if (getCardVal(j) == 37) {setChoice(j); chosen = true; setMatch(false);}
            }
        }
        // Lastly, play the highest card available   
        if(!chosen){
    //        cout << "no match no q spades - playing highest card" << endl;
            setChoice(getSize()-1); chosen = true; setMatch(false);    
        } 
    } 


