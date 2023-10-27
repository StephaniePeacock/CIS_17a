/* 
 * File:   main.cpp
 * Author: Stephanie Peacock
 *Created on August 28 16, 2023, 7:42 PM
 * 
 * Purpose: Convert temperature from Celsius to Fahrenheit
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries

//Global Constants - Math/Physics/Chemistry/Conversions Only

//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {
    //Setting Random Number Seed
    
    //Declare all variables here
    int degC,       //Degrees Celsius
        degF;       //Degrees Fahrenheit
    //Initialize variables/input values
    cout << "Enter a temperature in Celsius to be converted." << endl;
    cin  >> degC;
    //Map Input to Output/Process
    degF = (degC * 9/5) + 32;
    //Display Output
    cout << degC << " degrees Celsius is " << degF << " degrees Fahrenheit." << endl;
    //Exit Program    
    return 0;
}

