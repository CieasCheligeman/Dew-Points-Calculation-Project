/*
 *  main.cpp
 *
 *  COSC 051 Summer 2019
 *  Project #1b
 *
 *  Due on: JUL 15, 2019
 *  Author: cc2133
 *
 *
 *  In accordance with the class policies and Georgetown's
 *  Honor Code, I certify that, with the exception of the
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project.
 *
 *  References not otherwise commented within the program source code.
 *  Note that you should not mention any help from the TAs, the professor,
 *  or any code taken from the class textbooks.
 */

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

const double TEMP_MAXIMUM = 60.0;
const double TEMP_MINIMUM = -100.0;
const double MAX_RH = 1.0;
const double MIN_RH = 0.0;
const double DEW_B = 237.7;
const double DEW_A = 17.27;
const double TEMP_C_FACTOR = 32;
const double F_TO_C = 5.0 / 9.0;
const double C_TO_F = 9.0 / 5.0;

int main(){

    //send questions to user.
    double re_humi = 0;
    string temp_unit = "initial";
    double temp = 0;
    double final_ans = 0;
    cout << "Hi there!" << endl;
    cout << "Please enter the relative humidity: " ;
    // input info from user.
    cin >> re_humi;
    //legal number check #1
    if ( re_humi <= MAX_RH && re_humi >= MIN_RH )
    {
        cout << endl;
        cout << "Please enter the temperature unit: " ;
        cin >> temp_unit;
        // convert unit to uppercase so we will have no need to worry
        //about later.
        for(int k = 0; k < temp_unit.length(); k++)
        {
            temp_unit[k] = toupper(temp_unit[k]);
        }
        cout << endl;
        //legal check.
        if ( temp_unit.substr(0,1) == "F" || temp_unit.substr(0,1) == "C" )
        {
            cout << "Please enter the temperature: " ;
            cin >> temp;
            if ( temp_unit.substr(0,1) == "C" )
            {
                //range check.
                if ( temp <= TEMP_MAXIMUM && temp >= TEMP_MINIMUM )
                {
                    //calculate answer using dew formula.
                    final_ans = ( DEW_B * ( (DEW_A * temp) / ( DEW_B + temp ) + log(re_humi) ) ) / ( DEW_A - ( (DEW_A * temp) / ( DEW_B + temp ) + log(re_humi) ) );
                    cout << "your input temperature is: " << temp << endl;
                    cout << "The dew point temperature is: " << final_ans << endl;
                }
                else
                {
                    cout << "Please enter the right range of temperature unit, thanks." << endl;
                    return 123;
                }
            }
            // situation for F.
            else
            {
                //convert F to C.
                temp = F_TO_C * ( temp - TEMP_C_FACTOR );
                //range check for F.
                if ( temp <= TEMP_MAXIMUM && temp >= TEMP_MINIMUM )
                {
                    //calculate answer.
                    final_ans = ( DEW_B * ( (DEW_A * temp) / ( DEW_B + temp ) + log(re_humi) ) ) / ( DEW_A - ( (DEW_A * temp) / ( DEW_B + temp ) + log(re_humi) ) );
                    //convert the unit back.
                    temp = C_TO_F * temp + TEMP_C_FACTOR;
                    cout << "your input temperature is: " << temp << endl;
                    cout << "The dew point temperature is: " << final_ans << endl;
                }
                //warning of temp.
                else
                {
                    cout << "Please enter the right range of temperature, thanks." << endl;
                    return 123;
                }
            }
        }
        //warning of temp unit.
        else
        {
            cout << "Please enter the right temperature unit, thanks." << endl;
            return 123;
        }
    }
    //warning of relative humidity.
    else{
        cout << "Please enter the right range of humidity, thanks." << endl;
        return 123;
        
    }
    //finish
    return 0;
}

