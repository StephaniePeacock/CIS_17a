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
        
        //release hand's original memory
     //   for(int i = 0; i < size; i++){
     //       delete &hand[i];
    //    }
        delete [] hand;
     //   hand = nullptr;
         hand = temp; 
        //take out the trash
      //  delete [] temp;
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
}
void Player::play(Player &p, Stooge **s) {
    //temp variables
    int min = 53; //too big on purpose
    bool valid = false;
    int num = 0;
    //print the cards (player only)
    print();
    cout << " Choose a card in your hand you wish to play: ";
    //repeat until we've found a valid choice
    do {
        
        cout << "Choice is currently " << getChoice() << endl;
        p.setChoice(12);
        cout << "now Choice is currently " << getChoice() << endl;
        
        cin >> num;
        //player is first & they have 2 clubs
        if(order == FIRST && hand[0].getCnum() == 0){
            //2 clubs validation
            while(num != 1){
                //player has 2 clubs and didnt play it
                cout << "Please play 2\u2663: ";
                cin >> num;
                //player chose 2 clubs
                if(num == 1){
                    //num is valid - set all the things
                    valid = true;
                    setMatch(true);
                    setChoice(num-1);
                }
            }    
        }
        //player first, no 2 clubs - play whatever you want
        else if(order == FIRST && hand[0].getCnum() != 0){
            valid = true;
            setMatch(true);
            setChoice(num-1);
        }
        // Add suit validation if not first player
        // Check for Clubs
        if((s[0]->getOrder() == FIRST && s[0]->getCard(s[0]->getChoice()) < 13) ||
           (s[1]->getOrder() == FIRST && s[1]->getCard(s[1]->getChoice()) < 13) ||
           (s[2]->getOrder() == FIRST && s[2]->getCard(s[2]->getChoice()) < 13)) {                       
            //choice is valid match
            if (hand[num].getCnum() < 13){
                valid = true;
                setMatch(true);
                setChoice(num-1);
            }
            //loop through all the cards to get the min
            for (int n = 0; n < 13; n++){
                if(hand[n].getCnum() < min){
                    min = hand[n].getCnum();
                }
            }
            // else if there is a valid match that wasn't played
            if(min < 13 && min != 0){
                while(hand[num].getCnum() > 13){
                    //prompt for new choice
                    cout << "Please play \u2663: ";
                            cin >> num; 
                    //recheck if choice is valid match
                    if (hand[num].getCnum() < 13){
                        valid = true;
                        setMatch(true);
                        setChoice(num-1);
                    }
                }
            }
            else if (min > 13){
                //no matching cards, so any card will do
                valid = true;
                //but we didn't match
                match = false;
                setChoice(num-1);
            }
        }
        //now check for Diamonds
        else if((s[0]->getOrder() == FIRST && (s[0]->getCard(s[0]->getChoice()) >= 14 && s[0]->getCard(s[0]->getChoice()) <= 26)) ||
                (s[1]->getOrder() == FIRST && (s[1]->getCard(s[1]->getChoice()) >= 14 && s[1]->getCard(s[1]->getChoice()) <= 26)) ||
                (s[2]->getOrder() == FIRST && (s[2]->getCard(s[2]->getChoice()) >= 14 && s[2]->getCard(s[2]->getChoice()) <= 26))) {                       
            //reset min to original value
            min = 53;
            //choice is valid match
            if (hand[num].getCnum() >= 13 && hand[num].getCnum() <= 25){
                valid = true;
                setMatch(true);
                setChoice(num-1);
            }
            //loop through all the cards to get the min & max
            for (int n = 0; n < 13; n++){
                if(hand[n].getCnum() >= 13 && hand[n].getCnum() <= 25){
                    min = hand[n].getCnum();
                }
            }
            // else if there is a valid match that wasn't played
            if(min >= 13 && min <= 25){
                while(hand[num] < 13 || hand[num] > 25){
                    //prompt for new choice
                    cout << "Please play \u2662: ";
                            cin >> num; 
                    //recheck if choice is valid match
                    if (hand[num].getCnum() >= 13 && hand[num].getCnum() <= 25){
                        valid = true;
                        setMatch(true); 
                        setChoice(num-1);
                    }
                }
            }
            else if (min > 25){
                //no matching cards, so any card will do
                valid = true;
                //but we didn't match
                match = false;  
                setChoice(num-1);
            }
        }

        //now check for Spades
        else if((s[0]->getOrder() == FIRST && (s[0]->getCard(s[0]->getChoice()) >= 27 && s[0]->getCard(s[0]->getChoice()) <= 39)) ||
                (s[1]->getOrder() == FIRST && (s[1]->getCard(s[1]->getChoice()) >= 27 && s[1]->getCard(s[1]->getChoice()) <= 39)) ||
                (s[2]->getOrder() == FIRST && (s[2]->getCard(s[2]->getChoice()) >= 27 && s[2]->getCard(s[2]->getChoice()) <= 39))) {                       
            //reset min again
            min = 53;
            //choice is valid match
            if (hand[num].getCnum() >= 26 && hand[num].getCnum() <= 38){
                valid = true;
                setMatch(true);
                setChoice(num-1);
            }
            //loop through all the cards to get the min & max
            for (int n = 0; n < 13; n++){
                if(hand[n].getCnum() >= 26 && hand[n].getCnum() <= 38){
                    min = hand[n].getCnum();
                }
            }
            // else if there is a valid match that wasn't played
            if(min <= 38){
                while(hand[num] < 26 || hand[num] > 38){
                    //prompt for new choice
                    cout << "Please play \u2660: ";
                            cin >> num; 
                    //recheck if choice is valid match
                    if (hand[num].getCnum() >= 26 && hand[num].getCnum() <= 38){
                        valid = true;
                        setMatch(true); 
                        setChoice(num-1);
                    }
                }
            }
            else if (min > 39){
                //no matching cards, so any card will do
                valid = true;
                //but we didn't match
                match = false; 
                setChoice(num-1);
            }
        }
        //last check for Hearts
        else if((s[0]->getOrder() == FIRST && s[0]->getCard(s[0]->getChoice()) >= 39) ||
                (s[1]->getOrder() == FIRST && s[1]->getCard(s[1]->getChoice()) >= 39) ||
                (s[2]->getOrder() == FIRST && s[2]->getCard(s[2]->getChoice()) >= 39)) {                       
            //reset min (it's actually max now)
            min = 1;
            //choice is valid match
            if (hand[num].getCnum() >= 39){
                valid = true;
                setMatch(true);
                setChoice(num-1);
            }
            //loop through all the cards to get the min & max
            for (int n = 0; n < 13; n++){
                if(hand[n].getCnum() >= 39){
                    min = hand[n].getCnum();
                }
            }
            // else if there is a valid match that wasn't played
            if(min >= 39){
                while(hand[num].getCnum() < 39){
                    //prompt for new choice
                    cout << "Please play \u2661: ";
                            cin >> num; 
                    //recheck if choice is valid match
                    if (hand[num].getCnum() >= 39){
                        valid = true;
                        setMatch(true); 
                        setChoice(num-1);
                    }
                }
            }
            else if (min < 39){
                //no matching cards, so any card will do
                valid = true;
                //but we didn't match
                match = false;   
                setChoice(num-1);
            }
        }  
    }while(num < 1 || num > size && !valid); 
    
    cout << "Choice is currently " << getChoice() << endl;
        p.setChoice(7);
        cout << "now Choice is currently " << getChoice() << endl;
    
}

