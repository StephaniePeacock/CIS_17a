/* 
 * File:   main.cpp
 * Author: Stephanie Peacock
 * Created on October  24, 2023, 6:45 PM
 * Purpose: Play a game of Hearts vs the Three Stooges.
 */

//System Libraries
#include <iostream>  // Input / Output Library
#include <cstdlib>   // Random Function Library
#include <ctime>     // Time Library
#include <fstream>   // File Library
#include <string>
#include <cstring>
#include <iomanip>


using namespace std;

//User Libraries
#include "hearts.h"  // Hearts specific library
//Global Constants - Math/Physics/Chemistry/Conversions Only
//Function Prototypes - included in hearts.h


//Execution Begins Here
int main(int argc, char** argv) {
    //Setting Random Number Seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare all variables here
    
    //Initialize variables/input values
    char saved;             //check if player wants to resume or save game
    fstream save,           //saved.bin - stream for save file
            cards,          //cards.bin - initial card values file
            fv;             //cards.dat - for storing face values
    int *deck;              //pointer to store the card values
    Player *p;              //4 player structures, for each player
    Show pfv[4];            //4 string structures, for each player
    
    //Create the structures
    p = new Player[4];
    //Make the NPC name arrays and fill them
    p[1].name = new char[6];p[2].name = new char[6];p[3].name = new char[4];
    strcpy(p[1].name,"Larry"); strcpy(p[2].name,"Curly"); strcpy(p[3].name,"Moe");
    //set all game scores to 0
    p[0].score = p[1].score = p[2].score = p[3].score = 0;  
    //GET THE FACE VALUES OF THE DECK
    fv.open("cards.dat", ios::in);
    //just the player 1 values will be used
    for(int i = 0; i < DECK; i++){
       getline(fv,pfv[0].show[i]);
    }
    cout << endl;  
    //close the file
    fv.close();
    
    //INTRO
    cout << "Hey buddy, we need a fourth player!" << endl
         << "Let's play some Hearts!" << endl
         << "Would you like to resume a saved game?" << endl
         << "Enter y to load saved game or n to start a new game." << endl;
//    cin >> saved;
//    if(saved == 'y' || saved == 'Y'){
    
//    }else{
    cout << "My name is Larry, this is my good friend Curly," << endl
         << "and that's his brother, Moe." << endl << endl
         << "So what's your name?" << endl;
    string input;
    getline(cin,input);
    p[0].name = new char[input.length()+1];
    strcpy(p[0].name,input.c_str());
    cout << "Alright " << p[0].name << ", let's play Hearts! I'll deal." << endl;
 //   }
    //make sure we ignore the newline char
    //cin.ignore();
    
    
    //start the game loop 
    do{
        //Deal the cards
        deal(cards,fv,deck,p,DECK,pfv);

        //Hand loop
        for(int i = 0; i < 13; i++){
            //Play 13 tricks
            play(p,pfv);
            //Score the trick
            trick(p);
            //Unset the cards so they can't be replayed
            for(int n = 0; n < 4; n++){
                unset(p[n],pfv[n]);
            }
            cout << "**************************************************" << endl;
        }
        // Check for Shooting the Moon
        p[0].tScore == 26 ? p[0].tScore = 0, p[1].tScore = 26, p[2].tScore = 26, p[4].tScore = 26,cout << "Hey, Wiseguy! You shot the moon! The Stooges takes all points." << endl << endl :
        p[1].tScore == 26 ? p[1].tScore = 0, p[0].tScore = 26, p[2].tScore = 26, p[4].tScore = 26, cout << "Larry shot the moon! The rest of you schmucks can take the points."  << endl << endl :
        p[2].tScore == 26 ? p[2].tScore = 0, p[0].tScore = 26, p[1].tScore = 26, p[4].tScore = 26, cout << "Curly shot the moon! The rest of you schmucks can take the points."  << endl << endl :
        p[4].tScore == 26 ? p[4].tScore = 0, p[0].tScore = 26, p[2].tScore = 26, p[1].tScore = 26, cout << "Moe shot the moon! The rest of you schmucks can take the points."  << endl << endl :    
        cout << endl << "What a fun hand!" << endl << endl;
        //add tscores to score
        for(int n = 0; n < 4; n++){
            p[n].score += p[n].tScore;    
        }
        cout << "The current game score is:" << endl<< p[0].name << " : " << p[0].score << endl;
        cout << "Larry : " << p[1].score << endl;
        cout << "Curly : " << p[2].score << endl;
        cout << "Moe   : " << p[3].score << endl;
    }while(p[0].score < 50 && p[1].score < 50 && p[2].score < 50 && p[3].score < 50);
    cout << endl;
    if (p[0].score < p[1].score && p[0].score < p[2].score && p[0].score < p[3].score) { cout << "You won the game!" << endl; }
    else { cout << "You lost the game. Better luck next time!" << endl; }
    
    
    
    
    
    //save.open("saved.bin", ios::out | ios::in | ios::binary);   //read in saved file
    //make sure we start at the beginning
    //save.seekg(0);
    //save.read(reinterpret_cast<char*>(Player), 4 * sizeof(Player));
    //make sure we start at the beginning
    //save.seekp(0);
    //save.write(reinterpret_cast<char*>(Player), 4 * sizeof(Player));
    
    
    delete []p[0].name;
    delete []p[1].name;
    delete []p[2].name;
    delete []p[3].name;
    delete []p;
    //Exit Program    
    return 0;
}
//Deal to each player - deck array & all players
void deal(fstream &cards, fstream &fv, int *deck, Player *p, const int DECK, Show *pfv){
    //read in fresh cards
    cards.open("cards.bin", ios::in | ios::binary);
    deck = new int[DECK];
    cards.read(reinterpret_cast<char*>(deck), DECK * sizeof(int));
    //close the file
    cards.close();
    //GET THE FACE VALUES OF THE DECK
    fv.open("cards.dat", ios::in);
    //just the player 1 values will be used
    for(int i = 0; i < DECK; i++){
       getline(fv,pfv[0].show[i]);
    }
    cout << endl;  
    //close the file
    fv.close();
    //shuffle the deck
    shuffle(deck,DECK,pfv); //shuffle the cards
    //pass out the cards
    for(int i = 0; i < 13; i++) {   //deal out the cards & face values
        p[0].hand.cards[i] =  deck[i];      pfv[0].pshow[i] = pfv[0].show[i] + "\t";
        p[1].hand.cards[i] =  deck[(i+13)]; pfv[1].pshow[i] = pfv[0].show[i+13] + "\t";  
        p[2].hand.cards[i] =  deck[(i+26)]; pfv[2].pshow[i] = pfv[0].show[i+26] + "\t";  
        p[3].hand.cards[i] =  deck[(i+39)]; pfv[3].pshow[i] = pfv[0].show[i+39] + "\t";
    }
    //sort all the hands
    mSort(p,pfv);
    //find the player order
    int indx = linSrch(deck,DECK);
    if     (indx < 13)              { p[0].order = FIRST; p[1].order = SECOND; p[2].order = THIRD; p[3].order = FOURTH; }
    else if(indx > 12 && indx < 26) { p[1].order = FIRST; p[2].order = SECOND; p[3].order = THIRD; p[0].order = FOURTH; }
    else if(indx > 25 && indx < 39) { p[2].order = FIRST; p[3].order = SECOND; p[0].order = THIRD; p[1].order = FOURTH; }
    else                            { p[3].order = FIRST; p[0].order = SECOND; p[1].order = THIRD; p[2].order = FOURTH; }
    //reset the match status & tScores
    for(int i = 0; i < 4; i++){
        p[i].match = false;
        p[i].tScore = 0;
    }
    //Delete the deck array since it's not needed until redeal
    delete[] deck;
}

//Shuffle the deck array (nested inside deal)
void shuffle(int *deck, const int DECK, Show *pfv){
    for (int i = 0; i < DECK; i++) {
        int n = i + (rand()%(52 - i));
        swap(deck[i], deck[n]);
        swap(pfv[0].show[i],pfv[0].show[n]);
    }    
}          

//Find 2 of clubs  (nested inside deal) - deck array
int  linSrch(int *deck, const int DECK){
    int indx = 0;
    // start off with false
    bool found = false;
    // run until the val is found or we run through all the numbers
    while (indx < DECK && !found){
        // if the val is found it returns true and stops the loop, if false it adds to the count
        deck[indx] == 1 ?  found = true : indx++;
    }
    // sends back what index 2 of clubs (1) was found at
    return indx;
}

//Sort each player's hand (nested inside deal)
void mSort(Player *p, Show *pfv){
    //sort all four players
    for(int n = 0; n < 4; n++){
        for(int j = 0; j < 13; j++){
            for(int i = j + 1; i < 13; i++){
                if(p[n].hand.cards[j] > p[n].hand.cards[i]){
                    //sort the player int values
                    int temp = p[n].hand.cards[j];
                    p[n].hand.cards[j] = p[n].hand.cards[i];
                    p[n].hand.cards[i] = temp;
                    //now sort the corresponding show values
                    string ts = pfv[n].pshow[j];
                    pfv[n].pshow[j] = pfv[n].pshow[i];
                    pfv[n].pshow[i] = ts;
                }
            }
        }
    }
} 

//Print out face values of player's hand
void print(Player &p, Show &pfv){
    // output Player's remaining cards - if value is 0 an empty string is output
    cout << endl << "Play Card #:\t";
    if (p.hand.cards[0] == 0) { cout << ""; } else { cout << "1" << "\t"; }
    if (p.hand.cards[1] == 0) { cout << ""; } else { cout << "2" << "\t"; }
    if (p.hand.cards[2] == 0) { cout << ""; } else { cout << "3" << "\t"; }
    if (p.hand.cards[3] == 0) { cout << ""; } else { cout << "4" << "\t"; }
    if (p.hand.cards[4] == 0) { cout << ""; } else { cout << "5" << "\t"; }
    if (p.hand.cards[5] == 0) { cout << ""; } else { cout << "6" << "\t"; }
    if (p.hand.cards[6] == 0) { cout << ""; } else { cout << "7" << "\t"; }
    if (p.hand.cards[7] == 0) { cout << ""; } else { cout << "8" << "\t"; }
    if (p.hand.cards[8] == 0) { cout << ""; } else { cout << "9" << "\t"; }
    if (p.hand.cards[9] == 0) { cout << ""; } else { cout << "10"<< "\t"; }
    if (p.hand.cards[10]== 0) { cout << ""; } else { cout << "11"<< "\t"; }
    if (p.hand.cards[11]== 0) { cout << ""; } else { cout << "12"<< "\t"; }
    if (p.hand.cards[12]== 0) { cout << ""; } else { cout << "13"<< "\t"; }
    // now output the remaining face values
    cout << endl << setw(14) << "\t";
    for (int j = 0; j < 13; j++) {
        cout << pfv.pshow[j];
    }
    cout << endl;  
}      

//Play the trick
void play(Player *p, Show *pfv){
    //set min higher than possible - used to find valid range
    int min = 53;
    //loop 4 times so each player goes
    for(int trick = 0; trick < 4; trick++){
        //Player's Turn    
        if (p[0].order == trick) {         
            // Print player's cards
            print(p[0], pfv[0]); 
            //set valid to false
            bool valid = false;
            //run until valid choice is found
            do {
                cout << "Choose a card in your hand you wish to play: ";
                cin >> p[0].choice;
                // Add 2clubs validation if player is first                                  
                while (p[0].order == FIRST && p[0].hand.cards[0] == 1 && p[0].choice != 1) {
                    //player has 2 clubs and didnt play it
                    cout << "Please play 2\u2663: ";
                    cin >> p[0].choice;
                    //player plays 2 clubs
                    if(p[0].choice == 1){
                        //choice is valid
                        valid = true;
                        //first player always matches
                        p[0].match = true;
                    }
                }    
                //no 2 clubs, player is first    
                if(p[0].order == FIRST){
                    //first player card always valid
                    valid = true;
                    //first player always matches
                    p[0].match = true;
                }    
                
                // Add suit validation if not first player
                // Check for Clubs
                if((p[1].order == FIRST && p[1].choice <= 13) ||
                   (p[2].order == FIRST && p[2].choice <= 13) ||
                   (p[3].order == FIRST && p[3].choice <= 13)) {                       
                    //choice is valid match
                    if (p[0].hand.cards[p[0].choice-1] <= 13){
                        valid = true;
                        p[0].match = true;
                    }
                    //loop through all the cards to get the min
                    for (int n = 0; n < 13; n++){
                        if(p[0].hand.cards[n] < min){
                            min = p[0].hand.cards[n];
                        }
                    }
                    // else if there is a valid match that wasn't played
                    if(min <= 13 && min != 0){
                        while(p[0].hand.cards[p[0].choice-1] > 13){
                            //prompt for new choice
                            cout << "Please play \u2663: ";
                                    cin >> p[0].choice; 
                            //recheck if choice is valid match
                            if (p[0].hand.cards[p[0].choice-1] <= 13){
                                valid = true;
                                p[0].match = true;    
                            }
                        }
                    }
                    else if (min > 13){
                        //no matching cards, so any card will do
                        valid = true;
                        //but we didn't match
                        p[0].match = false;    
                    }
                }
                //now check for Diamonds
                else if((p[1].order == FIRST && (p[1].choice >= 14 && p[1].choice <= 26)) ||
                        (p[2].order == FIRST && (p[2].choice >= 14 && p[2].choice <= 26)) ||
                        (p[3].order == FIRST && (p[3].choice >= 14 && p[3].choice <= 26))) {                       
                    //reset min to original value
                    min = 53;
                    //choice is valid match
                    if (p[0].hand.cards[p[0].choice-1] >= 14 && p[0].hand.cards[p[0].choice-1] <= 26){
                        valid = true;
                        p[0].match = true;
                    }
                    //loop through all the cards to get the min & max
                    for (int n = 0; n < 13; n++){
                        if(p[0].hand.cards[n] >= 14 && p[0].hand.cards[n] <= 26){
                            min = p[0].hand.cards[n];
                        }
                    }
                    // else if there is a valid match that wasn't played
                    if(min >= 14 && min <= 26){
                        while(p[0].hand.cards[p[0].choice-1] < 14 || p[0].hand.cards[p[0].choice-1] > 26){
                            //prompt for new choice
                            cout << "Please play \u2662: ";
                                    cin >> p[0].choice; 
                            //recheck if choice is valid match
                            if (p[0].hand.cards[p[0].choice-1] >= 14 && p[0].hand.cards[p[0].choice-1] <= 26){
                                valid = true;
                                p[0].match = true;    
                            }
                        }
                    }
                    else if (min > 26){
                        //no matching cards, so any card will do
                        valid = true;
                        //but we didn't match
                        p[0].match = false;    
                    }
                }
                
                //now check for Spades
                else if((p[1].order == FIRST && (p[1].choice >= 27 && p[1].choice <= 39)) ||
                        (p[2].order == FIRST && (p[2].choice >= 27 && p[2].choice <= 39)) ||
                        (p[3].order == FIRST && (p[3].choice >= 27 && p[3].choice <= 39))) {                       
                    //reset min again
                    min = 53;
                    //choice is valid match
                    if (p[0].hand.cards[p[0].choice-1] >= 27 && p[0].hand.cards[p[0].choice-1] <= 39){
                        valid = true;
                        p[0].match = true;
                    }
                    //loop through all the cards to get the min & max
                    for (int n = 0; n < 13; n++){
                        if(p[0].hand.cards[n] >= 27 && p[0].hand.cards[n] <= 39){
                            min = p[0].hand.cards[n];
                        }
                    }
                    // else if there is a valid match that wasn't played
                    if(min <= 39){
                        while(p[0].hand.cards[p[0].choice-1] < 27 || p[0].hand.cards[p[0].choice-1] > 39){
                            //prompt for new choice
                            cout << "Please play \u2660: ";
                                    cin >> p[0].choice; 
                            //recheck if choice is valid match
                            if (p[0].hand.cards[p[0].choice-1] >= 27 && p[0].hand.cards[p[0].choice-1] <= 39){
                                valid = true;
                                p[0].match = true;    
                            }
                        }
                    }
                    else if (min > 39){
                        //no matching cards, so any card will do
                        valid = true;
                        //but we didn't match
                        p[0].match = false;    
                    }
                }
                //last check for Hearts
                else if((p[1].order == FIRST && p[1].choice >= 40) ||
                        (p[2].order == FIRST && p[2].choice >= 40) ||
                        (p[3].order == FIRST && p[3].choice >= 40)) {                       
                    //reset min (it's actually max now)
                    min = 1;
                    //choice is valid match
                    if (p[0].hand.cards[p[0].choice-1] >= 40){
                        valid = true;
                        p[0].match = true;
                    }
                    //loop through all the cards to get the min & max
                    for (int n = 0; n < 13; n++){
                        if(p[0].hand.cards[n] >= 40){
                            min = p[0].hand.cards[n];
                        }
                    }
                    // else if there is a valid match that wasn't played
                    if(min > 39){
                        while(p[0].hand.cards[p[0].choice-1] < 40){
                            //prompt for new choice
                            cout << "Please play \u2661: ";
                                    cin >> p[0].choice; 
                            //recheck if choice is valid match
                            if (p[0].hand.cards[p[0].choice-1] >= 40){
                                valid = true;
                                p[0].match = true;    
                            }
                        }
                    }
                    else if (min < 40){
                        //no matching cards, so any card will do
                        valid = true;
                        //but we didn't match
                        p[0].match = false;    
                    }
                }
            } while ((p[0].choice < 1 || p[0].choice > 13) && !valid);               
        // Player played
        played(p[0],pfv[0]);
        //Player set
        set(p[0]);       
        } 
        // Larry's Turn
        else if (p[1].order == trick) {
        //    cout << "Larry's cards";
            print(p[1],pfv[1]);
            playCard(p,1);
            // Output the card played
            played(p[1], pfv[1]);
            // Set the played card for scoring
            set(p[1]);    
        } 
        // Curly's Turn
        else if (p[2].order == trick) {
        //    cout << "Curly's cards";
            print(p[2],pfv[2]);
            playCard(p,2);
            // Output the card played
            played(p[2], pfv[2]);
            // Set the played card for scoring
            set(p[2]);    
        }
        // Moe's Turn
        else if (p[3].order == trick) {
        //    cout << "Curly's cards";
            print(p[3],pfv[3]);
            playCard(p,3);
            // Output the card played
            played(p[3], pfv[3]);
            // Set the played card for scoring
            set(p[3]);    
        } 
    }     
}      

//Stooge picks a card
void playCard(Player *p, int n){
    bool chosen = false;
    // If npc is first to play in the trick - check for 2 clubs first
    if(p[n].order == FIRST) { 
        if ( p[n].hand.cards[0] == 1) {p[n].choice = 1; p[n].match = true; chosen = true;}
        // If no 2 clubs, play lowest card
        else {
            for(int i = 0; i < 13 && !chosen; i++){
                if(p[n].hand.cards[i] != 0) { p[n].choice = i+1; chosen = true; p[n].match = true; }
            }
        }
    }    
    else {
        //Check against all 4 players
        for(int s = 0; s < 4; s++){
            if(p[s].order == FIRST) {
                int min = p[s].choice < 14 ? 0 : p[s].choice < 27 ? 14 : p[s].choice < 40 ? 27 : 40;
                int max = min + 13;
            // p[n].match the suit if possible - playing lowest card possible    
                for (int i = 0; i < 13 && !chosen; i++) {
                    if (p[n].hand.cards[i] >= min && p[n].hand.cards[i] <= max && p[n].hand.cards[i] != 0) {
                        p[n].choice = (i+1); chosen = true; p[n].match = true; }
                }
            // Play Q spades, A spades, or K spades first if can't p[n].match suit   
                if(!chosen){
                    for (int j = 12; j > 0 && !chosen; j--) {
                        if (p[n].hand.cards[j] == 37) {p[n].choice = (j+1); chosen = true; p[n].match = false;}
                        if (p[n].hand.cards[j] == 39) {p[n].choice = (j+1); chosen = true; p[n].match = false;}
                        if (p[n].hand.cards[j] == 38) {p[n].choice = (j+1); chosen = true; p[n].match = false;}
                    }
                }
            // Lastly, play the highest card available   
                if(!chosen){
                    for (int j = 12; j > 0 && !chosen; j--) {
                        if (p[n].hand.cards[j] != 0) {p[n].choice = (j+1); chosen = true; p[n].match = false; }
                    }
                } 
            }
        }
    }
}

//Print out the cards played (nested inside playCard)
void played(Player &p, Show &pfv){
    cout << p.name << " played: ";
    switch (p.choice) {
        case 1: cout << pfv.pshow[0]; break;
        case 2: cout << pfv.pshow[1]; break;
        case 3: cout << pfv.pshow[2]; break;
        case 4: cout << pfv.pshow[3]; break;
        case 5: cout << pfv.pshow[4]; break;
        case 6: cout << pfv.pshow[5]; break;
        case 7: cout << pfv.pshow[6]; break;
        case 8: cout << pfv.pshow[7]; break;
        case 9: cout << pfv.pshow[8]; break;
        case 10:cout << pfv.pshow[9]; break;
        case 11:cout << pfv.pshow[10];break;
        case 12:cout << pfv.pshow[11];break; 
        default:cout << pfv.pshow[12];break;
    }
    cout << endl;
}    

//Set the player's choice to card value (nested inside playCard)
void set(Player &p){
// Set p.choice to card value for scoring
    p.choice == 1  ? p.choice = p.hand.cards[0] : p.choice == 2  ? p.choice = p.hand.cards[1] :
    p.choice == 3  ? p.choice = p.hand.cards[2] : p.choice == 4  ? p.choice = p.hand.cards[3] : 
    p.choice == 5  ? p.choice = p.hand.cards[4] : p.choice == 6  ? p.choice = p.hand.cards[5] :  
    p.choice == 7  ? p.choice = p.hand.cards[6] : p.choice == 8  ? p.choice = p.hand.cards[7] : 
    p.choice == 9  ? p.choice = p.hand.cards[8] : p.choice == 10 ? p.choice = p.hand.cards[9] : 
    p.choice == 11 ? p.choice = p.hand.cards[10]: p.choice == 12 ? p.choice = p.hand.cards[11]: 
    p.choice = p.hand.cards[12];    
}       

//Score the trick
void trick( Player *p){
    //local counters
    int score = 0,  //holds the trick points
        max = 0,    //hold the highest card value
        winner;     //holds the winner's location
    //loop through all four players
    for(int i = 0; i < 4; i++){
        //if the player matched the suit and their choice is highest
        if(p[i].match == true && p[i].choice > max){
            //set their choice to the max
            max = p[i].choice;
            //set them as winner
            winner = i;
        }
        //now see if there was a heart played
        if(p[i].choice > 39){
            //add 1 to the trick value
            score += 1;
        }
        //last check if the Q Spades was played
        if(p[i].choice == 37){
            score += 13;
        }
    }
    //output the trick value
    cout << endl << "Trick is worth " << score << " points. ";
    //output the winner
    cout << p[winner].name << " takes the trick." << endl << endl;
    //set the new order - player was winner?
    winner == 0 ? p[0].order = FIRST,p[1].order = SECOND,p[2].order = THIRD,p[3].order = FOURTH :
    //larry was winner?
    winner == 1 ? p[1].order = FIRST,p[2].order = SECOND,p[3].order = THIRD,p[0].order = FOURTH :
    //curly was winner?
    winner == 2 ? p[2].order = FIRST,p[3].order = SECOND,p[0].order = THIRD,p[1].order = FOURTH :
    //else moe was the winner
    winner == 3 ? p[3].order = FIRST,p[0].order = SECOND,p[1].order = THIRD,p[2].order = FOURTH : 0;
    //assign the points to the winner
    p[winner].tScore += score;
    //check all 4 players
    for(int i = 0; i < 4; i++){
        //reset match for all
        p[i].match = false;
        //for testing - output all hand values
        cout << p[i].name <<"'s hand is " << p[i].tScore << "\t"; 
    }
    cout << endl; 
}          

//Set choice back & remove played card from hand (nested inside trick)
void unset(Player &p, Show &pfv){
    // set chosen card to 0 & empty face values so they dont show
    if (p.choice == p.hand.cards[0]) { p.hand.cards[0]  = 0; pfv.pshow[0]  = "";}
    if (p.choice == p.hand.cards[1]) { p.hand.cards[1]  = 0; pfv.pshow[1]  = "";}
    if (p.choice == p.hand.cards[2]) { p.hand.cards[2]  = 0; pfv.pshow[2]  = "";}
    if (p.choice == p.hand.cards[3]) { p.hand.cards[3]  = 0; pfv.pshow[3]  = "";}
    if (p.choice == p.hand.cards[4]) { p.hand.cards[4]  = 0; pfv.pshow[4]  = "";}
    if (p.choice == p.hand.cards[5]) { p.hand.cards[5]  = 0; pfv.pshow[5]  = "";}
    if (p.choice == p.hand.cards[6]) { p.hand.cards[6]  = 0; pfv.pshow[6]  = "";}
    if (p.choice == p.hand.cards[7]) { p.hand.cards[7]  = 0; pfv.pshow[7]  = "";}
    if (p.choice == p.hand.cards[8]) { p.hand.cards[8]  = 0; pfv.pshow[8]  = "";}
    if (p.choice == p.hand.cards[9]) { p.hand.cards[9]  = 0; pfv.pshow[9]  = "";}
    if (p.choice == p.hand.cards[10]){ p.hand.cards[10] = 0; pfv.pshow[10] = "";}
    if (p.choice == p.hand.cards[11]){ p.hand.cards[11] = 0; pfv.pshow[11] = "";}
    if (p.choice == p.hand.cards[12]){ p.hand.cards[12] = 0; pfv.pshow[12] = "";}    
}       