/* 
 * File:   main.cpp
 * Author: Stephanie Peacock
 *Created on September 9, 2023, 8:05 PM
 * 
 * Purpose: Calculate the future population.
 */

//System Libraries
#include <iostream>
#include <iomanip>
using namespace std;

//User Libraries

//Global Constants - Math/Physics/Chemistry/Conversions Only

//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {
    //Setting Random Number Seed
    
    //Declare all variables here
    int start, days;
    float percent, newpop;
    //Initialize variables/input values
    start = days = 0;
    percent = 0.0;
    
    while (start < 2){
       cout << "Enter a starting population of at least 2 organisms:";
       cin  >> start;
       cout << endl;
    }
    while (percent < 1){
        cout << "What percent does the population increase per day? ";
        cin  >> percent;
        cout << endl;
    }
    while (days < 1){
        cout << "How many days will the organisms multiply? ";
        cin  >> days;
        cout << endl;
    }
    //Map Input to Output/Process
    percent = percent/100.0;
    newpop = start;
    //Display Output
    for(int i = 1; i <= days; i++){
        newpop += newpop * percent;
        //since we can't have part of an organism, decimals should be removed
        cout << fixed << setprecision(0) << noshowpoint;
        cout << "The population on day " << i << " will be: " << newpop << endl;
    }
    //Exit Program    
    return 0;
}

