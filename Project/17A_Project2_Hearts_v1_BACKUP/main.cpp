/* 
 * File:   main.cpp
 * Author: Stephanie Peacock
 * Created on November 25, 2023, 3:20 PM
 * Purpose: Play a game of Hearts vs the Three Stooges.
 */

//System Libraries
#include <fstream>   // File Library            : open(), close()
#include <cstring>   // Cstring Library         : strcpy()     
#include <iomanip>   // Formatting library      : setw()

using namespace std;

//User Libraries
#include "Stooge.h"  //Deck Library (also imports Card.h)
//Global Constants - Math/Physics/Chemistry/Conversions Only

//Class Functions - to be moved

//Execution Begins Here
int main(int argc, char** argv) {
    //Setting Random Number Seed
   
    //Declare all variables here
    Deck deck;
    //Initialize variables/input values
    //deck.display();
    deck.shuffle();
    deck.display();
    
    Player p;
    Stooge **s = new Stooge*[3];
    for(int i = 0; i < 3; i++){
        //make the new stooge
        s[i] = new Stooge();
    }
    for(int i = 0; i < 3; i++){
        p.addCard(deck.deal(i));
    }
    p.print();
    p.discard(2);
    p.print();
    
    p.play(p,s,3);
    s[1]->play(p,s,3);
    //Clean Up & Exit Program
    for(int i = 0; i < 3; i++){
        delete s[i];
    }
    delete []s;
    return 0;
}
