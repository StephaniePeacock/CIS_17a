/* 
 * File:   main.cpp
 * Author: Stephanie Peacock
 *Created on September 10, 2023, 9:37 PM
 * 
 * Purpose: Binary String Search.
 */

//System Libraries
#include <iostream>
#include <string>
using namespace std;

//User Libraries

//Global Constants - Math/Physics/Chemistry/Conversions Only
const int NUM = 20;
//Function Prototypes
void msort(string [], int);
bool binSrch(string [],int, string, int&);
//Execution Begins Here
int main(int argc, char** argv) {
    //Setting Random Number Seed
    
    //Declare all variables here
    string names[NUM] = {"Collins, Bill", "Smith, Bart",    "Allen, Jim",
                         "Griffin, Jim",  "Stamey, Marty",  "Rose, Geri",
                         "Taylor, Terri", "Johnson, Jill",  "Allison, Jeff",
                         "Looney, Joe",   "Wolfe, Bill",    "James, Jean",
                         "Weaver, Jim",   "Pore, Bob",      "Rutherford, Greg",
                         "Javens, Renee", "Harrison, Rose", "Setzer, Cathy",
                         "Pike, Gordon",  "Holland, Beth" };
    string name;
    int indx;
    //Initialize variables/input values
    for(int i = 0; i < NUM; i++){
        cout << names[i] << endl;
    }
    cout << endl << "Enter a name to search for: ";
    getline(cin, name);
    //Map Input to Output/Process
    msort(names, NUM);
    
        for(int i = 0; i < NUM; i++){
        cout << names[i] << " is at index " << i << endl;
    }
    
    //Display Output
    binSrch(names, NUM, name, indx) != 0 ? 
        cout << endl << "After sorting, " << name << " was found at index " << indx << endl :
        cout << endl << name << " was not found." << endl;
    //Exit Program  
    return 0;
}
void msort(string names[], const int NUM){
    for(int j = 0; j < NUM - 1; j++){
        for(int i = j + 1; i < NUM; i++){
            if(names[j] > names[i]){
                string temp = names[j];
                names[j] = names[i];
                names[i] = temp;
            }
        }
    }    
}
bool binSrch(string names[],int NUM, string name, int& indx){
    int beg = 0, end = NUM - 1;
    do {
       // divide the total in half to get the starting point
       indx = (end + beg)/2;
       // see if the halfway matches
       if (names[indx] == name){
          return true; 
       }
       //if it doesn't, see if the halfway is bigger
       else if (names[indx] > name) {
           end = indx - 1;
       }
       //or if the halfway is smaller
       else {
           beg = indx + 1;
       }
    // do this until there are no more divisions   
    } while (beg <= end);
    // if it isn't found, then exit
    return false;    
}