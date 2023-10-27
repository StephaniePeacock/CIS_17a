/* 
 * File:   main.cpp
 * Author: Stephanie Peacock
 *Created on September 9, 2023, 9:39 PM
 * 
 * Purpose: Convert temperature from freedom units to imperial units.
 */

//System Libraries
#include <iostream>
#include <iomanip>
using namespace std;

//User Libraries

//Global Constants - Math/Physics/Chemistry/Conversions Only

//Function Prototypes
void celsius(int);

//Execution Begins Here
int main(int argc, char** argv) {
    //Setting Random Number Seed
    
    //Declare all variables here
    int freedom;

    //Initialize variables/input values

    //Map Input to Output/Process

    //Display Output
    for(int i = 0; i <= 20; i++){
        celsius(i);
    }
    //Exit Program    
    return 0;
}
void celsius(int freedom){
    float temp = (freedom - 32) * 5/9.0;
    cout << fixed << setprecision(2);
    cout << freedom << " degrees fahrenheit is equal to " << temp << " degrees celsius." << endl;
}

