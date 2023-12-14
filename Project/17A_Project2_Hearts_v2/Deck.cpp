/* 
 * File:   main.cpp
 * Author: Stephanie Peacock
 * Created on November 26, 2023, 9:51 PM
 * Purpose:  Deck Class Implementation
 */

#include "Deck.h"
#include "Player.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

//Deck Constructor
Deck::Deck() {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    //initialize cards
    nCards = 52;
    card = new Card*[nCards];   //creates the card array
    
    for(int i = 0; i < nCards; i++){
        card[i] = new Card(i);
        card[i]->setFace();
        card[i]->setFace();
    }
}
//Deck Destructor
Deck::~Deck(){
    for(int i = 0; i < nCards; i++){
        delete card[i];
    }
    delete []card;
}
//Deck Shuffle
void Deck::shuffle(){
    for (int i = 0; i < 52; i++) {
        int n = i + (rand()%(52 - i));
        swap(card[i], card[n]);
    } 
}
//print Deck
void Deck::display(){
    for(int i = 0; i < nCards; i++){
        cout << card[i]->getFace();
    //    cout << " Card value is " << card[i]->getCnum();
        if((i+1)%4 == 0){
            cout << endl;
        }
    }
}
Card Deck::deal(int i){
    return *card[i]; 
}
//linear search to fine 2 clubs
int Deck::linSrch(){
    int indx = 0;
    // start off with false
    bool found = false;
    // run until the val is found or we run through all the numbers
    while (indx < nCards && !found){
        // if the val is found it returns true and stops the loop, if false it adds to the count
        card[indx]->getCnum() == 0 ?  found = true : indx++;
    }
    // sends back what index 2 of clubs (1) was found at
    return indx;
}
