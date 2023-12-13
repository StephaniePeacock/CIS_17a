/* 
 * File:   Player.cpp
 * Author: Stephanie Peacock
 * Created on December 10, 2023, 7:15 PM
 * Purpose: Player Class Implementation
 */
#include <iostream>

#include <array>
#include "Player.h"
using namespace std;

//template <class T>
//T Player<T>::Player() {}

Player::Player() : name(""),order(FIRST),size(0),choice(0),match(false),tScore(0),score(0){
    hand = new Card[size];
    for(int i = 0; i < size; i++){
        hand[i] = Card();
    }
}

Player::Player(string s) : name(s),order(FIRST),size(0),choice(0),match(false),tScore(0),score(0){
    hand = new Card[size];
    for(int i = 0; i < size; i++){
        hand[i] = Card();
    }
}

Player::~Player() {
    cout << "Deleting Player" << endl;
    for(int i = 0; i < size; i++){
    //    delete hand[i];
    }
    delete [] hand;
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
        //take out the trash
        delete [] hand;
        //set the new hand
        size++;
        hand = temp;
    }
}

void Player::discard(int c) {
    // make sure we have cards to discard
    if (size > 0) {
        // create a temp array 1 smaller
        Card* temp = new Card[size - 1];
        // fill the elements before the discarded card
        for (int i = 0; i < c-1; i++) {
            temp[i] = hand[i];
        }
        // fill the elements after the discarded card
        for (int i = c-1; i < size; i++) {
            temp[i] = hand[i+1];
        }
        // take out the trash
        delete[] hand;
        // set the new hand
        size--;
        hand = temp;
    }
}


//void Player::play(Stooge *s,int n) { cout << "Player played." << endl; }

