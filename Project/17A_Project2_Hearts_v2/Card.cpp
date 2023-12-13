/* 
 * File:   main.cpp
 * Author: Stephanie Peacock
 * Created on November 26, 2023, 9:51 PM
 * Purpose:  Card Class Implementation
 */

#include "Card.h"

//Card Constructor
Card::Card(int n) {
    //loop #  or start at 0
    cnum = ( n > 0 ? n : 0);
    suit = cnum%13;
    face;
}

//Face Value of the card (rank & suit combined)
void Card::setFace(){
    int n = cnum;
    n >= 0 ? n%=52 : 0;
    
    char faces[]={'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
    string suits[]={"\u2663",    // Clubs
                    "\u2662",    // Diamonds
                    "\u2660",    // Spades
                    "\u2661"};   // Hearts
    face  = faces[cnum%13];
    face += suits[cnum/13];
}