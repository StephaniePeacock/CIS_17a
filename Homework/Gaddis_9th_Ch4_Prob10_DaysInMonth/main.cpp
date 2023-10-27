/* 
 * File:   main.cpp
 * Author: Stephanie Peacock
 *Created on August 28 16, 2023, 8:20 PM
 * 
 * Purpose: Find out how many days a month has, accounting for leap years.
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
    int month, year, days;
    //Initialize variables/input values
    cout << "Enter a month (1 - 12): ";
    cin  >> month;
    cout << endl << "Enter a year: ";
    cin >> year;
   
    //Map Input to Output/Process
    if((year%100 == 0 && year%400 == 0) || (year%4 == 0)) {
        switch (month){
            case 1 : days = 31; break;
            case 2 : days = 29; break;
            case 3 : days = 31; break;
            case 4 : days = 30; break;
            case 5 : days = 31; break;
            case 6 : days = 30; break;
            case 7 : days = 31; break;
            case 8 : days = 31; break;
            case 9 : days = 30; break;
            case 10: days = 31; break;
            case 11: days = 30; break;
            default: days = 31;   
        } 
    } else {
        switch (month){
            case 1 : days = 31; break;
            case 2 : days = 28; break;
            case 3 : days = 31; break;
            case 4 : days = 30; break;
            case 5 : days = 31; break;
            case 6 : days = 30; break;
            case 7 : days = 31; break;
            case 8 : days = 31; break;
            case 9 : days = 30; break;
            case 10: days = 31; break;
            case 11: days = 30; break;
            default: days = 31;  
        }
    }  

    //Display Output
    cout << endl <<  "That month has " << days << " days." << endl;
    //Exit Program    
    return 0;
}

