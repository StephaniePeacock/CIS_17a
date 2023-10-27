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
#include <fstream>
using namespace std;

//User Libraries

//Global Constants - Math/Physics/Chemistry/Conversions Only
const int COLS = 30;
//Function Prototypes
void month(char[][COLS], int);
//Execution Begins Here
int main(int argc, char** argv) {
    //Setting Random Number Seed
    
    //Declare all variables here
    int rows = 3, rain = 0, shine = 0, cloud = 0;
    char sky[rows][COLS];
    int most[3]{0};

    //Initialize variables/input values
    ifstream data;
    data.open("RainOrShine.txt");
    //Fill the array from the file
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < COLS; j++){
            data >> sky[i][j];
            // get the totals while we are filling
            sky[i][j] == 'R' ? rain++, most[i]++ : sky[i][j] == 'S' ? shine++ : cloud++;   
        }  
    }
    //Map Input to Output/Process
    
    //Display Output
    // Monthly breakdown
    cout << "June   : ";
    month(sky, 0);
    cout << "July   : ";
    month(sky, 1);
    cout << "August : ";
    month(sky, 2);
    // All rainy days
    cout << "All together there were " << rain << " rainy days, " 
         << cloud << " cloudy days, and " << shine << " sunny days." << endl;
    // Most rainy days
    most[0] > most[1] && most[0] > most[2] ? cout << "June had the most rainy days." << endl:
    most[1] > most[0] && most[1] > most[2] ? cout << "July had the most rainy days." << endl:    
        cout << "August had the most rainy days." << endl;
    //Exit Program  
    data.close();
    return 0;
}
void month(char sky[][COLS], int month){
    int rainy = 0, shiny = 0, cloudy = 0;
    for(int i = 0; i < COLS; i++){
        sky[month][i] == 'R' ? rainy++ : sky[month][i] == 'S' ? shiny++ : cloudy++;
        cout << sky[month][i] << "  ";
    }
    cout << endl << "There was a total of " << rainy << " rainy days, "
         << cloudy << " cloudy days, and " << shiny << " sunny days." << endl << endl; 
    
}

