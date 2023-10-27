/* 
 * File:   main.cpp
 * Author: Stephanie Peacock
 *Created on August 28 16, 2023, 8:05 PM
 * 
 * Purpose: Convert USD to Yen & Euros
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
    const float YPD = 146.39,   // Japanese Yen per US Dollar
                EPD = 0.92;     // Euro per US Dollar
    float usd, yen, euro;
    //Initialize variables/input values
    cout << "Enter the number of US Dollars to convert to Yen and Euros." << endl;
    cin  >> usd;
    //Map Input to Output/Process
    yen = (usd * YPD);
    euro = (usd * EPD);
    //Display Output
    cout << showpoint << fixed << setprecision(2);
    cout << "$" << usd << " USD is worth $ " << yen << " Japanese Yen and $ " << euro << " Euros." << endl;
    //Exit Program    
    return 0;
}

