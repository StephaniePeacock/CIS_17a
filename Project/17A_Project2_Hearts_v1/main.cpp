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
void order(Player &, Stooge **);

//Execution Begins Here
int main(int argc, char** argv) {
    //Placeholder inputs for feeding things into the objects
    string input;   //for player name input
    int num;        //for player card choice
    char again;     //for choosing to go again
    
    //Create the Deck & players
    Deck deck;
    Player p;
    Stooge **s = new Stooge*[3];
    for(int i = 0; i < 3; i++){
        //make the new stooge
        s[i] = new Stooge();
    }
    //Name our Stooges
    s[0]->setName("Larry");
    s[1]->setName("Curly");
    s[2]->setName("Moe");
    //Begin game intro
    cout << "Hey buddy, we need a fourth player!" << endl
         << "Let's play some Hearts!" << endl
         << "My name is Larry, this is my good friend Curly," << endl
         << "and that's his brother, Moe." << endl << endl
         << "So what's your name?" << endl;
    //get Player's name
    getline(cin,input);
    //assign name to Player
    p.setName(input);
    //finish intro
    cout << "Alright " << p.getName() << ", let's play Hearts! I'll deal." << endl;
    
    // deck.display();
    
    /************************
     *                      *
     *    BEGIN GAME LOOP   *
     *                      *
     ************************/
  //  do{
        //shuffle the cards
        deck.shuffle();
        //find the index for 2 clubs to set who's first
        num = deck.linSrch();
        //deal the cards
        for(int i = 0; i < deck.getNCards(); i++){
            //give card to larry
            if(i%4 == 0){
                s[0]->addCard(deck.deal(i));
                //set as first if 2 clubs belongs to larry
                if(num == i){
                    s[0]->setOrder(FIRST);
                }
            } 
            //give card to curly
            else if(i%4 == 1){
                s[1]->addCard(deck.deal(i));
                //set as first if 2 clubs belongs to curly
                if(num == i){
                    s[1]->setOrder(FIRST);
                }
            } 
            //give card to moe
            else if(i%4 == 2){
                s[2]->addCard(deck.deal(i));
                //set as first if 2 clubs belongs to moe
                if(num == i){
                    s[2]->setOrder(FIRST);
                }
            } 
            //give card to player
            else if(i%4 == 3){
                p.addCard(deck.deal(i));
                //set as first if 2 clubs belongs to player
                if(num == i){
                    p.setOrder(FIRST);
                }
             }
        }
        //sort all the hands
        p.mSort();
        for(int i = 0; i < 3; i++){
            s[i]->mSort();
        }
        //set the order & initial match status & tScores to 0
        order(p,s);
        
        
        //begin hand loop - go 13 times
        for(int i = 0; i < 13; i++){
            
        }
        //print out player's cards
   // }while(p.getScore() < 50 && 
    //        s[0]->getScore() < 50 && 
    //        s[1]->getScore() < 50 &&
    //        s[2]->getScore() < 50);

    
    
 
    

    
    cout << "2 clubs found at element " << deck.linSrch() << endl;
    cout << p.getName() << endl;
    p.print();
    
    cout << endl << s[0]->getName() << endl;
    s[0]->print();
    cout << endl << s[1]->getName() << endl;
    s[1]->print();
    cout << endl << s[2]->getName() << endl;
    s[2]->print();
    
    cout << "Player Order is " << p.getOrder() << " : Larry Order is " << s[0]->getOrder()
         << " : Curly Order is " << s[1]->getOrder() << " : Moe Order is " << s[2]->getOrder() << endl;
    
  //  p.discard(2);
  //  p.print();
    
  //  p.play(p,s,3);
  //  s[1]->play(p,s,3);
    
    
    
    //Clean Up & Exit Program
    for(int i = 0; i < 3; i++){
        delete s[i];
    }
    delete []s;
    return 0;
}

void order(Player &p, Stooge **s){
    //set the order - player is first
        if(p.getOrder() == FIRST){
            //player match is true, tScore is 0
            p.setMatch(true); p.setTrick(0);
            //rest are false, all tScores 0
            s[0]->setOrder(SECOND);  s[0]->setMatch(false);  s[0]->setTrick(0);
            s[1]->setOrder(THIRD);   s[1]->setMatch(false);  s[1]->setTrick(0);
            s[2]->setOrder(FOURTH);  s[2]->setMatch(false);  s[2]->setTrick(0);
        }
        //set the order - larry is first
        else if(s[0]->getOrder() == FIRST){
            //larry match is true tScore is 0
            s[0]->setMatch(true);   s[0]->setTrick(0);
            //rest don't match tScores are 0
            s[1]->setOrder(SECOND); s[1]->setMatch(false);  s[1]->setTrick(0);
            s[2]->setOrder(THIRD);  s[2]->setMatch(false);  s[2]->setTrick(0);
            p.setOrder(FOURTH);     p.setMatch(false);      p.setTrick(0);
        }
        //set the order - curly is first
        else if(s[1]->getOrder() == FIRST){
            //curly's match is true tScore is 0
            s[1]->setMatch(true);   s[1]->setTrick(0);
            //rest dont match tScores are 0
            s[2]->setOrder(SECOND); s[2]->setMatch(false);  s[2]->setTrick(0);
            p.setOrder(THIRD);      p.setMatch(false);      p.setTrick(0);
            s[0]->setOrder(FOURTH); s[0]->setMatch(false);  s[0]->setTrick(0); 
        }
        //set the order - moe is first
        else if(s[2]->getOrder() == FIRST){
            s[2]->setMatch(true);   s[2]->setTrick(0);
            p.setOrder(SECOND);     p.setMatch(false);      p.setTrick(0);
            s[0]->setOrder(THIRD);  s[0]->setMatch(false);  s[0]->setTrick(0);
            s[1]->setOrder(FOURTH); s[1]->setMatch(false);  s[1]->setTrick(0);
        }
}