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
void trick(Player &, Stooge **);

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
    
  //   deck.display();
    
    p.setChoice(3);
    
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
                    cout << "Larry is first " << endl;
                }
            } 
            //give card to curly
            else if(i%4 == 1){
                s[1]->addCard(deck.deal(i));
                //set as first if 2 clubs belongs to curly
                if(num == i){
                    s[1]->setOrder(FIRST);
                    cout << "Curly is first " << endl;
                }
            } 
            //give card to moe
            else if(i%4 == 2){
                s[2]->addCard(deck.deal(i));
                //set as first if 2 clubs belongs to moe
                if(num == i){
                    s[2]->setOrder(FIRST);
                    cout << "Moe is first " << endl;
                }
            } 
            //give card to player
            else if(i%4 == 3){
                p.addCard(deck.deal(i));
                //set as first if 2 clubs belongs to player
                if(num == i){
                    p.setOrder(FIRST);
                    cout << "Player is first " << endl;
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
            //each player plays
            for(int n = 0; n < 4; n++){
                //player checks 3 - dont go out of bounds
                if(n != 3){
                    if(s[n]->getOrder() == n){
                        s[n]->play(p,s);
                        s[n]->played();
                    }     
                }
                //stooges check 0 1 2
                else {
                    //pick a card
                    p.play(p,s);
                    
                    cout << "Choice is currently " << p.getChoice() << endl;
                    p.setChoice(13);
                    cout << "now Choice is currently " << p.getChoice() << endl;
                    //output played card
                    p.played();
                    ;
                }
            }
            //score the trick
            trick(p,s);
            //discard the cards that were played
            p.discard(p.getChoice());
            s[0]->discard(s[0]->getChoice());
            s[1]->discard(s[1]->getChoice());
            s[2]->discard(s[2]->getChoice());
            
      //  cout << "2 Clubs card value is "   << deck.card[0]->getCnum() << endl; 
        }
        //check for shooting the moon
        //add tScores to score
        //output current game scores
        
        //print out player's cards
   // }while(p.getScore() < 50 && 
    //        s[0]->getScore() < 50 && 
    //        s[1]->getScore() < 50 &&
    //        s[2]->getScore() < 50);

        
        //someone hit 50 points, let's find the winner
    
 
    
    
    
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
            cout << "Player first Player order is " << p.getOrder() << endl;
        }
        //set the order - larry is first
        else if(s[0]->getOrder() == FIRST){
            //larry match is true tScore is 0
            s[0]->setMatch(true);   s[0]->setTrick(0);
            //rest don't match tScores are 0
            s[1]->setOrder(SECOND); s[1]->setMatch(false);  s[1]->setTrick(0);
            s[2]->setOrder(THIRD);  s[2]->setMatch(false);  s[2]->setTrick(0);
            p.setOrder(FOURTH);     p.setMatch(false);      p.setTrick(0);
            cout << "Larry first Player order is " << p.getOrder() << endl;
        }
        //set the order - curly is first
        else if(s[1]->getOrder() == FIRST){
            //curly's match is true tScore is 0
            s[1]->setMatch(true);   s[1]->setTrick(0);
            //rest dont match tScores are 0
            s[2]->setOrder(SECOND); s[2]->setMatch(false);  s[2]->setTrick(0);
            p.setOrder(THIRD);      p.setMatch(false);      p.setTrick(0);
            s[0]->setOrder(FOURTH); s[0]->setMatch(false);  s[0]->setTrick(0); 
            cout << "Curly first Player order is " << p.getOrder() << endl;
        }
        //set the order - moe is first
        else if(s[2]->getOrder() == FIRST){
            s[2]->setMatch(true);   s[2]->setTrick(0);
            p.setOrder(SECOND);     p.setMatch(false);      p.setTrick(0);
            s[0]->setOrder(THIRD);  s[0]->setMatch(false);  s[0]->setTrick(0);
            s[1]->setOrder(FOURTH); s[1]->setMatch(false);  s[1]->setTrick(0);
            cout << "Moe first Player order is " << p.getOrder() << endl;
        }
}
//score the trick
void trick(Player &p, Stooge **s){
    //local counters
    int tempscore = 0,  //holds the trick points
        max = 0,    //hold the highest card value
        winner;     //holds the winner's location
    //loop through all four players
    for(int i = 0; i < 3; i++){
        //dont go out of bounds
        if(s[i]->getMatch() == true && s[i]->getCard(s[i]->getChoice()) > max){
            //set their choice to the max
            max = s[i]->getCard(s[i]->getChoice());
            //set them as winner
            winner = i;
        }
        //now see if there was a heart played
        if(s[i]->getCard(s[i]->getChoice()) > 38){
            //add 1 to the trick value
            tempscore += 1;
        }
        //last check if the Q Spades was played
        if(s[i]->getCard(s[i]->getChoice()) == 36){
            tempscore += 13;
        }
    }

    //now check the player
   if(p.getMatch() == true && p.getCard(p.getChoice()) > max){
    //set their choice to the max
    max = p.getCard(p.getChoice());
    //set them as winner
    winner = 3;
    }
    //now see if there was a heart played
    if(p.getCard(p.getChoice()) > 38){
        //add 1 to the trick value
        tempscore += 1;
    }
    //last check if the Q Spades was played
    if(p.getCard(p.getChoice()) == 36){
        tempscore += 13;
    }

    
    
    //output the trick value
    cout << endl << "Trick is worth " << tempscore << " points. ";
    //output the winner & add the points
    if(winner = 3){
        cout << p.getName() << " takes the trick." << endl << endl;
        p.setTrick(tempscore);
    }else{
        cout << s[winner]->getName() << " takes the trick." << endl << endl;
        s[winner]->setTrick(tempscore);
    }
    
    //set the new order - player was winner?
    winner == 3 ? p.setOrder(FIRST),s[0]->setOrder(SECOND),s[1]->setOrder(THIRD),s[2]->setOrder(FOURTH) :
    //larry was winner?
    winner == 0 ? s[0]->setOrder(FIRST),s[1]->setOrder(SECOND),s[2]->setOrder(THIRD),p.setOrder(FOURTH) :
    //curly was winner?
    winner == 1 ? s[1]->setOrder(FIRST),s[2]->setOrder(SECOND),p.setOrder(THIRD),s[0]->setOrder(FOURTH) :
    //else moe was the winner
                  s[2]->setOrder(FIRST),p.setOrder(SECOND),s[0]->setOrder(THIRD),s[1]->setOrder(FOURTH);
    //check all 4 players
    for(int i = 0; i < 4; i++){
        if(i == 3){
            p.setMatch(false);
            cout << p.getName() <<"'s hand is " << p.getTrick() << "\t";
        }else{
            //reset match for all
            s[i]->setMatch(false);
            //for testing - output all hand values
            cout << s[i]->getName() <<"'s hand is " << s[i]->getTrick() << "\t";    
        }   
    }
    cout << endl;
}