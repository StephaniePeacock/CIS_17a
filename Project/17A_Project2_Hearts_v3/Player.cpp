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
}
void Player::play(Player &p, Stooge **s) {
    //temp variables
    int min = 53; //too big on purpose
    bool valid = false;
    int num = 0;
    //print the cards (player only)
    print();
    
    //repeat until we've found a valid choice
    do { 
        while (num < 1 || num > p.getSize()){
            cout << "Choose a card in your hand you wish to play: ";
            cin >> num; 
        }
        //player is first
        if(p.getOrder() == FIRST){
            //player has 2 clubs
            if(p.getCardVal(0) == 0){
                //2 clubs validation
                while(num != 1){
                    //player has 2 clubs and didnt play it
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
            //player first, no 2 clubs - play whatever you want
            else {
                cout << "card set" << endl
                p.setMatch(true);
                p.setChoice(num-1);
                valid = true;
            }
        }
        // Add suit validation if not first player
        // Check for Clubs
        if( !valid &&
           (s[0]->getOrder() == FIRST && s[0]->getCardSuit(s[0]->getChoice()) == 0) ||
           (s[1]->getOrder() == FIRST && s[1]->getCardSuit(s[1]->getChoice()) == 0) ||
           (s[2]->getOrder() == FIRST && s[2]->getCardSuit(s[2]->getChoice()) == 0)) {                       
            //choice is valid match
            if (p.getCardSuit(num) == 0){
                valid = true;
                p.setMatch(true);
                p.setChoice(num-1);
                p.getChoice();
            }
            if(!valid){
                //loop through all the cards to get the min
                for (int n = 0; n < p.getSize(); n++){
                    if(p.getCardSuit(n) == 0){
                        min = 12;
                    }
                }
                // else if there is a valid match that wasn't played
                if(min == 12){
                    while(p.getCardSuit(num) != 0){
                        //prompt for new choice
                        cout << "Please play \u2663: ";
                        cin >> num; 
                        //recheck if choice is valid match
                        if(num > 0 || num < p.getSize()){
                            if (p.getCardSuit(num) == 0){
                                valid = true;
                                p.setMatch(true);
                                p.setChoice(num-1);
                                p.getChoice();
                            }    
                        }
                        
                    }
                }
                else if (min != 12){
                    //no matching cards, so any card will do
                    valid = true;
                    //but we didn't match
                    p.setMatch(false);
                    p.setChoice(num-1);
                }
            }
        }
        //now check for Diamonds
        else if(!valid &&
                (s[0]->getOrder() == FIRST && s[0]->getCardSuit(s[0]->getChoice()) == 1 ) ||
                (s[1]->getOrder() == FIRST && s[1]->getCardSuit(s[1]->getChoice()) == 1 ) ||
                (s[2]->getOrder() == FIRST && s[2]->getCardSuit(s[2]->getChoice()) == 1)) {                       
            //reset min to original value
            min = 53;
            //choice is valid match
            if (p.getCardSuit(num) == 1){
                valid = true;
                p.setMatch(true);
                p.setChoice(num-1);
            }
            if(!valid){
                //loop through all the cards to get the min & max
                for (int n = 0; n < p.getSize(); n++){
                    if(p.getCardSuit(n) == 1){
                        min = 25;
                    }
                }
                // else if there is a valid match that wasn't played
                if(min == 25){
                    while(p.getCardSuit(num) != 1){
                        //prompt for new choice
                        cout << "Please play \u2662: ";
                        cin >> num; 
                        //recheck if choice is valid match
                        if(num > 0 && num < p.getSize()){
                            if (p.getCardSuit(num) == 1){
                                valid = true;
                                p.setMatch(true); 
                                p.setChoice(num-1);
                            }
                        }  
                    }
                }
                else if (min != 25){
                    //no matching cards, so any card will do
                    valid = true;
                    //but we didn't match
                    p.setMatch(false);  
                    p.setChoice(num-1);
                }
            }
        }

        //now check for Spades
        else if(!valid &&
                (s[0]->getOrder() == FIRST && s[0]->getCardSuit(s[0]->getChoice()) == 2 ) ||
                (s[1]->getOrder() == FIRST && s[1]->getCardSuit(s[1]->getChoice()) == 2 ) ||
                (s[2]->getOrder() == FIRST && s[2]->getCardSuit(s[2]->getChoice()) == 2)) {                       
            //reset min to original value
            min = 53;
            //choice is valid match
            if (p.getCardSuit(num) == 2){
                valid = true;
                p.setMatch(true);
                p.setChoice(num-1);
            }
            if(!valid){
                //loop through all the cards to get the min & max
                for (int n = 0; n < p.getSize(); n++){
                    if(p.getCardSuit(n) == 2){
                        min = 38;
                    }
                }
                // else if there is a valid match that wasn't played
                if(min == 38){
                    while(p.getCardSuit(num) != 2){
                        //prompt for new choice
                        cout << "Please play \u2660: ";
                        cin >> num; 
                        //recheck if choice is valid match
                        if(num > 0 && num < p.getSize()){
                            if (p.getCardSuit(num) == 2){
                                valid = true;
                                p.setMatch(true); 
                                p.setChoice(num-1);
                            }
                        }  
                    }
                }
                else if (min != 38){
                    //no matching cards, so any card will do
                    valid = true;
                    //but we didn't match
                    p.setMatch(false);  
                    p.setChoice(num-1);
                }
            }
        }
        //last check for Hearts
        else if(!valid &&
                (s[0]->getOrder() == FIRST && s[0]->getCardSuit(s[0]->getChoice()) == 3 ) ||
                (s[1]->getOrder() == FIRST && s[1]->getCardSuit(s[1]->getChoice()) == 3 ) ||
                (s[2]->getOrder() == FIRST && s[2]->getCardSuit(s[2]->getChoice()) == 3)) {                       
            //reset min to original value
            min = 53;
            //choice is valid match
            if (p.getCardSuit(num) == 3){
                valid = true;
                p.setMatch(true);
                p.setChoice(num-1);
            }
            if(!valid){
                //loop through all the cards to get the min & max
                for (int n = 0; n < p.getSize(); n++){
                    if(p.getCardSuit(n) == 3){
                        min = 25;
                    }
                }
                // else if there is a valid match that wasn't played
                if(min == 25){
                    while(p.getCardSuit(num) != 3){
                        //prompt for new choice
                        cout << "Please play \u2661: ";
                        cin >> num; 
                        //recheck if choice is valid match
                        if(num > 0 && num < p.getSize()){
                            if (p.getCardSuit(num) == 3){
                                valid = true;
                                p.setMatch(true); 
                                p.setChoice(num-1);
                            }
                        }  
                    }
                }
                else if (min != 25){
                    //no matching cards, so any card will do
                    valid = true;
                    //but we didn't match
                    p.setMatch(false);  
                    p.setChoice(num-1);
                }
            }
        }  
    }while(!valid); 
}

