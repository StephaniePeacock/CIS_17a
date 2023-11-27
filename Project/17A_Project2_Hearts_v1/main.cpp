/* 
 * File:   main.cpp
 * Author: Stephanie Peacock
 * Created on November 25, 2023, 3:20 PM
 * Purpose: Play a game of Hearts vs the Three Stooges.
 */

//System Libraries
#include <iostream>  // Input / Output Library  : cin, cout
#include <cstdlib>   // Random Function Library : srand()
#include <ctime>     // Time Library            : time()
#include <fstream>   // File Library            : open(), close()
#include <cstring>   // Cstring Library         : strcpy()
#include <string>    // String Library         
#include <iomanip>   // Formatting library      : setw()

using namespace std;

//User Libraries
#include "Deck.h"  //Deck Library (also imports Card.h)
//Global Constants - Math/Physics/Chemistry/Conversions Only

//Class Functions - to be moved

//Execution Begins Here
int main(int argc, char** argv) {
    //Setting Random Number Seed
   
    //Declare all variables here
    Deck deck;
    //Initialize variables/input values
    deck.display();
    deck.shuffle();
    deck.display();
    //Exit Program    
    return 0;
}
