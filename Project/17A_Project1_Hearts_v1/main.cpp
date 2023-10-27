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
    //GET THE FACE VALUES OF THE DECK
    fv.open("cards.dat", ios::in);
    
    //For Testing
    cout << "Show values: ";
    //just the player 1 values will be used
    for(int i = 0; i < DECK; i++){
       getline(fv,pfv[0].show[i]);
       cout << pfv[0].show[i] << " ";
    }
    cout << endl;

 //   cin.ignore();
    
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
    
    //Deal the cards
    deal(cards,deck,p,DECK,pfv);
    
    for(int n = 0; n < 4; n++){
        cout << "Player" << n << " info: " << p[0].name;
        for(int j = 0; j < 13; j++){
            cout << p[n].hand.cards[j] << " ";
        }
        cout << endl << "Order: " << p[n].order << " Match: " << p[n].match << endl;
    }
    
    cout << endl;
    print(p[0],pfv[0]);
    
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
void deal(fstream &cards, int *deck, Player *p, const int DECK, Show *pfv){
    //read in fresh cards
    cards.open("cards.bin", ios::in | ios::binary);
    deck = new int[DECK];
    cards.read(reinterpret_cast<char*>(deck), DECK * sizeof(int));
    
    cout << endl << "Deck Array: ";
    for(int i = 0; i < DECK; i++){
        cout << deck[i] << " ";
    }
    cout << endl;
    cout << endl << "Show Array: ";
    for(int i = 0; i < DECK; i++){
        cout << pfv[0].show[i] << " ";
    }
    cout << endl;
    
    
    //shuffle the cards
    shuffle(deck,DECK,pfv);
    
    cout << endl << "Shuffled Deck Array: ";
    for(int i = 0; i < DECK; i++){
        cout << deck[i] << " ";
    }
    cout << endl;
    cout << endl << "Shuffled Show Array: ";
    for(int i = 0; i < DECK; i++){
        cout << pfv[0].show[i] << " ";
    }
    cout << endl;
    
    //deal out the cards & face values
    for(int i = 0; i < 13; i++) {
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
    //reset the match status
    for(int i = 0; i < 4; i++){
        p[i].match = false;    
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
        if (count) {
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
}      

//Determine which card to play
void playCard(Player *, string*){
    
}      

//Print out the cards played (nested inside playCard)
void played(Player &,string*){
    
}    

//Set the player's choice to card value (nested inside playCard)
void set(Player &){
    
}       

//Score the trick
void trick( Player *){
    
}          

//Set choice back & remove played card from hand (nested inside trick)
void unset(Player &){
    
}       

//Counts how many tricks have been played
void count(){
    
} 