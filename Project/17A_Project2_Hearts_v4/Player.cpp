/* 
 * File:   Player.cpp
 * Author: Stephanie Peacock
 * Created on December 10, 2023, 7:15 PM
 * Purpose: Player Class Implementation
 */
#include <iostream>

#include <array>
#include "Player.h"
#include "Stooge.h"
using namespace std;

Player::Player() : name(""),order(SECOND),size(0),choice(0),match(false),tScore(0),score(0){
    hand = new Card[size];
    for(int i = 0; i < size; i++){
        hand[i] = Card();
    }
}
Player::Player(string s) : name(s),size(0),choice(0),match(false),tScore(0),score(0){
    hand = new Card[size];
    for(int i = 0; i < size; i++){
        hand[i] = Card();
    }
}
Player::~Player() {
    hand = nullptr;
    delete[] hand;
}
void Player::addCard(Card c){
    //if we don't have a full hand
    if(size < 13){
        //make a temp array 1 bigger
        Card *temp = new Card[size + 1];
        //fill the existing elements
        for(int i = 0; i < size; i++){
            temp[i] = hand[i];
        }
        //put the latest card at the end
        temp[size] = c;
        //increase the size
        size++;
        delete [] hand;
     //   hand = nullptr;
         hand = temp; 
    }
}
void Player::discard(int c) {
    // make sure we have cards to discard
    if (size > 0) {
        // create a temp array 1 smaller
        Card* temp = new Card[size - 1];
        if(c != 0 ){
            // fill the elements before the discarded card
            for (int i = 0; i < c; i++) {
                temp[i] = hand[i];
            }    
        }
        // fill the elements after the discarded card
        for (int i = c; i < size-1; i++) {
            temp[i] = hand[i+1];
        }
        // set the new hand
        size--;
        // take out the trash
        delete[] hand;
        hand = temp;
    }
}
void Player::mSort(){
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
void Player::print(){
cout << endl << "Play Card #:\t";
for(int i = 0; i < getSize(); i++){
   cout << i+1 << "\t";
}
cout << endl << setw(14) << "\t";
for(int i = 0; i < getSize(); i++){
   cout << hand[i].getFace() << "\t";
}
cout << endl;

//for testing
cout <<  setw(14) << "\t";
for(int i = 0; i < getSize(); i++){
   cout << hand[i].getCnum() << "\t";
}
cout << endl;

//for testing
cout <<  setw(14) << "\t";
for(int i = 0; i < getSize(); i++){
   cout << hand[i].getSuit() << "\t";
}
cout << endl;



}
void Player::play(Player &p, Stooge **s) {
    //temp variables
    bool valid = false;
    int num = 0;
    //print the cards (player only)
    print();
    
    //repeat until we've found a valid choice
    do {
        while (num < 1 || num > p.getSize()) {
            cout << "Choose a card in your hand you wish to play: ";
            cout << endl << "size is " << p.getSize() << endl;
            cin >> num;
        }
        //if player is first
        if(p.getOrder() == FIRST){
            // And they have 2 of clubs
            if(p.getCardVal(0) == 0 && num != 1){
                while(num != 1){
                    //ask again until they play it
                    cout << "Please play 2\u2663: ";
                    cin >> num;
                    //player chose 2 clubs
                    if(num == 1){
                        //num is valid - set all the things
                        p.setMatch(true);
                        p.setChoice(num-1);
                        valid = true;
                        getChoice();
                    }
                }    
            }
            //no 2 clubs, anything works
            else {
                //set all the things
                valid = true;
                p.setMatch(true);
                p.setChoice(num - 1);
            }
        }
        //player wasn't first
        else if (p.getOrder() != FIRST){
            //find who was first
            int first = -1;  // Initialize with an invalid value
            for (int i = 0; i < 3; ++i) {
                //current stooge is first
                if (s[i]->getOrder() == FIRST) {
                    //set first to the value of their suit
                    first = s[i]->getCardSuit(s[i]->getChoice());
                }
            }
            //now see if we matched that suit
            if (first != -1 && p.getCardSuit(num - 1) == first) {
                //if we did set all the things
                valid = true;
                p.setMatch(true);
                p.setChoice(num - 1);
            } 
            //if we didn't match prompt for the proper suit
            else {
                cout << "Suit must match." << endl;
                first == 0 ? cout << "Please play \u2663: " :
                first == 1 ? cout << "Please play \u2662: " :
                first == 2 ? cout << "Please play \u2660: " :
                             cout << "Please play \u2661: ";
            }
        }
        //reset num so it checks again
        num = 0;
    } while (!valid);
}

