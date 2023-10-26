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


using namespace std;

//User Libraries
#include "hearts.h"  // Hearts specific library
//Global Constants - Math/Physics/Chemistry/Conversions Only
//Function Prototypes - included in hearts.h


//Execution Begins Here
int main(int argc, char** argv) {
    //Setting Random Number Seed
    
    //Declare all variables here
    
    //Initialize variables/input values
    const int SIZE = 4;     //constant number of players
    const int DECK = 52;    //constant number of cards
    string show[DECK];      //face values for the cards
    char saved;              //check if player wants to resume or save game
    fstream save,           //saved.bin - stream for save file
            cards,          //cards.bin - initial card values file
            fv;             //cards.dat - for storing face values
    int *deck;              //pointer to store the card values
    Player p[SIZE];         //4 player structures, for each player
    //set the names
    p[1].name = "Larry"; p[2].name = "Curly"; p[3].name = "Moe"; 
    //INTRO
    cout << "Hey buddy, we need a fourth player!" << endl
         << "Let's play some Hearts!" << endl
         << "Would you like to resume a saved game?" << endl
         << "Enter y to load saved game or n to start a new game." << endl;
    cin >> saved;
    if(saved == 'y' || saved == 'Y'){
    
    }else{
    cout << "My name is Larry, this is my good friend Curly," << endl
         << "and that's his brother, Moe." << endl << endl
         << "So what's your name?" << endl;
    string input;
    getline(cin,input);
    p[0].name = new char[input.length()];
    cout << "Alright " << p[0].name << ", let's play Hearts! I'll deal." << endl;
    }
    //make sure we ignore the newline char
    cin.ignore();
    /* 
     *GET THE FACE VALUES OF THE DECK
     */
    fv.open("cards.dat", ios::in);
    
    cout << "Show values: ";
    for(int i = 0; i < DECK; i++){
        getline(fv,show[i]);
        cout << show[i] << " ";
    }
    fv.close();
    //read in fresh cards
    cards.open("cards.bin", ios::in | ios::binary);
    deck = new int[DECK];
    cards.read(reinterpret_cast<char*>(deck), DECK * sizeof(int));
    
    cout << endl << "Deck values: ";
    for(int i = 0; i < DECK; i++){
        cout << deck[i] << " ";
    }
    cout << endl;
    
    //save.open("saved.bin", ios::out | ios::in | ios::binary);   //read in saved file
    //make sure we start at the beginning
    //save.seekg(0);
    //save.read(reinterpret_cast<char*>(Player), SIZE * sizeof(Player));
    //make sure we start at the beginning
    //save.seekp(0);
    //save.write(reinterpret_cast<char*>(Player), SIZE * sizeof(Player));
    
    
    delete []deck;
    delete []p[0].name;
    //Exit Program    
    return 0;
}