/*
 *  main.cpp                                 
 *                                                
 *  COSC 051 Summer 2019                          
 *  Project #2                                    
 *                                                
 *  Due on: JUL 22, 2019                  
 *  Author: cc2133
 * 
 *
 *  In accordance with the class policies and Georgetown's
 *  Honor Code, I certify that I have neither
 *  given nor received any assistance on this project. 
 *
 *  References not otherwise commented within the program source code.
 *  Note that you should not mention any help from the TAs, the professor, 
 *  or any code taken from the class textbooks.
 */

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <sstream>


using namespace std;

//declare dew point calculation constant.
const double TEMP_MAXIMUM = 60.0;
const double TEMP_MINIMUM = -100.0;
const double MAX_RH = 1.0;
const double MIN_RH = 0.0;
const double DEW_B = 237.7;
const double DEW_A = 17.27;
const double TEMP_C_FACTOR = 32;
const double F_TO_C = 5.0 / 9.0;
const double C_TO_F = 9.0 / 5.0;
const int MINYEAR = 1800;
const int MAXYEAR = 2019;
const int MINMONTH = 1;
const int MAXMONTH = 12;
const int ALLMONTHMIN_DAY = 1;
const int BIG_DAY_MAX = 31;
const int SEC_DAY_MA = 30;
const int FEB_DAY_MAX = 29;
const int JAN = 1;
const int FEB = 2;
const int MAR = 3;
const int APR = 4;
const int MAY = 5;
const int JUN = 6;
const int JUL = 7;
const int AUG = 8;
const int SEP = 9;
const int OCT = 10;
const int NOV = 11;
const int DEC = 12;
const string SEPERATELINE = "--------------------------------------------------------------------------------------------------------" ;


int main(){
    //choice delacration.
    char choice;
    //file var preperation.
    ifstream u_file;
    //hook.
    cout << "welcome to the Blue Ridge Agency (BRWA) Dew Point Calculator.\n";
    cout << endl;
    cout << "s - Single entry from keyboard\n";
    cout << "b - Bulk entry from file\n";
    cout << "q - quit\n";
    cout << "Please enter the letter correspond to one of the options above:\n";
    
    //read the input of choice from user.
    cin >> choice;
    cin.ignore(1000, '\n');
    
    //case when single entry.
    if ( choice == 's' ){
        double re_humi = 0;
        //using char in single section instead of using it in bulk reading section for eliminating code duplicate a bit.
        char temp_unit = 'i';
        double temp = 0;
        double final_ans = 0;
        cout << "Hi there!" << endl;
        cout << "Enter the relative humidity between 0 (exclusive) and 1 (inclusive): " ;
        // input info from user.
        cin >> re_humi;
        //legal number check #1
        if ( re_humi <= MAX_RH && re_humi >= MIN_RH )
        {
            cout << endl;
            cout << "Please Enter the temperature units, either F/f for Fahrenheit or C/c for Celsius: " ;
            cin >> temp_unit;
            // convert unit to uppercase so we will have no need to worry
            //about later.
            cin.ignore(100,'\n');
            cout << endl;
            //legal check.
            if ( temp_unit == 'F' || temp_unit == 'f' || temp_unit == 'C' || temp_unit == 'c' )
            {
                
                if ( temp_unit == 'C' || temp_unit == 'c')
                {
                    cout << "Please Enter the air temperature between -100 degrees Celsius and 60 degrees Celsius (inclusive) sir/madam : " ;
                    cin >> temp;
                    //range check.
                    if ( temp <= TEMP_MAXIMUM && temp >= TEMP_MINIMUM )
                    {
                        //calculate answer using dew formula.
                        final_ans = ( DEW_B * ( (DEW_A * temp) / ( DEW_B + temp ) + log(re_humi) ) ) /
                        ( DEW_A - ( (DEW_A * temp) / ( DEW_B + temp ) + log(re_humi) ) );
                        cout << "your input relative humidity is: " << re_humi << endl;
                        cout << "your input temperature is: " << temp << " degree Celcius." << endl;
                        cout << "The dew point temperature is: " << final_ans << endl;
                    }
                    else
                    {
                        cout << "Please enter the right range of temperature, thanks." << endl;
                        return 123;
                    }
                }
                // situation for F.
                else
                {
                    cout << "Enter the air temperature between -148 degrees Fahrenheit and 140 degrees Fahrenheit (inclusive): " ;
                    cin >> temp;
                    //convert F to C.
                    temp = F_TO_C * ( temp - TEMP_C_FACTOR );
                    //range check for F.
                    if ( temp <= TEMP_MAXIMUM && temp >= TEMP_MINIMUM )
                    {
                        //calculate answer.
                        final_ans = ( DEW_B * ( (DEW_A * temp) / ( DEW_B + temp ) + log(re_humi) ) ) /
                        ( DEW_A - ( (DEW_A * temp) / ( DEW_B + temp ) + log(re_humi) ) );
                        //convert the unit back.
                        temp = C_TO_F * temp + TEMP_C_FACTOR;
                        cout << "your input relative humidity is: " << re_humi << endl;
                        cout << "your input temperature is: " << temp << " degree Fahrenheit." << endl;
                        cout << "The dew point temperature is: " << final_ans << endl;
                    }
                    //warning of temp.
                    else
                    {
                        cout << "Please enter the right range of temperature between -148 degrees Fahrenheit and 140 degrees Fahrenheit (inclusive), thanks." << endl;
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
        }// END for re-humi checking
        //warning of relative humidity.
        else{
            cout << "Please enter the right range of humidity, thanks." << endl;
            return 123;
            
        }
        //finish
        return 0;
    }//END for choice s.
    // situation b.
    else if ( choice == 'b' )
    {
        cout << "Please enter the file's name in order to be proccessed: \n" ;
        int orga_num = 0;
        //declaere var name for reading the file.
        string date;
        string relahumi;
        string airtemp;
        string airtemp2;
        string unit;
        string nameOfG;
        string nameOfG2;
        string dataOfDate;
        double dataOfRh;
        double dataOftemp;
        string dataOfunit;
        string dataOfname;
        string dew_point;
        
        int counterFlaw = 0;
        double counterOfC = 0;
        double counterOfF = 0;
        //for average division.
        double counterOfFNum = 0;
        double counterOfCNum = 0;
        int counterOfRow = 0;
        //for counting the substring of date.
        //for colleting the user input.
        string f_ile;
        cin >> f_ile;
        cin.ignore(100,'\n');
        u_file.open(f_ile.c_str());
        //f_ile becomes useless after this line.
        //check whether the file is legible for system.
        if ( !u_file )
        {
            cout << "Please enter a right file name." << endl;
            return 123;
        }
        //file is legible.
        else
        {
            //organization the header first.
            u_file >> date >> relahumi >> airtemp >> airtemp2 >> unit >> nameOfG >> nameOfG2 ;
            cout << "  " << date << "      " << relahumi << "      " << airtemp << airtemp2
            << "          DewPoint           "  << unit << "          " << nameOfG << nameOfG2 << endl;
            cout << endl;
            cout << SEPERATELINE << endl;
            //read the content out.
            //this will automatically close the file after reading if i am remember it right.
            while ( u_file >> dataOfDate >> dataOfRh >> dataOftemp >> dataOfunit )
            {
                getline(u_file, dataOfname);
                int dayOfDate = 0;
                int monthOfDate = 0;
                int yearOfDate = 0;
                //for limiting the time of executing year data.
                int yearCounter = 0;
                //for limiting the time of executing month data.
                int monthCounter = 0;
                //for limiting the time of executing day.
                int dayCounter = 1;
                //for counting the number of data.
                int d_tracker = 0;
                //for counting the number of data.
                // convert type
                //row calculation for every time of execution .
                counterOfRow++ ;
                double re_humi = dataOfRh;
                //for letting if statement be brief a bit than using char. Char has been used in the single input section.
                string temp_unit = dataOfunit;
                double temp = dataOftemp;
                double final_ans = 0;
                //legal number check #1
                //all of the following code under if statement just for assigning the value for dew point.
                if ( re_humi <= MAX_RH && re_humi >= MIN_RH )
                {
                    for(int k = 0; k < temp_unit.length(); k++)
                    {
                        temp_unit[k] = toupper(temp_unit[k]);
                    }
                    if ( temp_unit.substr(0,1) == "F" || temp_unit.substr(0,1) == "C" )
                    {
                        if ( temp_unit.substr(0,1) == "C" )
                        {
                            //range check.
                            if ( temp <= TEMP_MAXIMUM && temp >= TEMP_MINIMUM )
                            {
                                //calculate answer using dew formula.
                                final_ans = ( DEW_B * ( (DEW_A * temp) / ( DEW_B + temp ) + log(re_humi) ) ) /
                                ( DEW_A - ( (DEW_A * temp) / ( DEW_B + temp ) + log(re_humi) ) );
                                ostringstream dew_pointStrm;
                                dew_pointStrm << final_ans;
                                dew_point = dew_pointStrm.str();
                                counterOfC += temp;
                                counterOfCNum++ ;
                            }
                            else
                            {
                                dew_point = "ErrorInput" ;
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
                                final_ans = ( DEW_B * ( (DEW_A * temp) / ( DEW_B + temp ) + log(re_humi) ) ) /
                                ( DEW_A - ( (DEW_A * temp) / ( DEW_B + temp ) + log(re_humi) ) );
                                //convert the unit back.
                                temp = C_TO_F * temp + TEMP_C_FACTOR;
                                ostringstream dew_pointStrm;
                                dew_pointStrm << final_ans;
                                dew_point = dew_pointStrm.str();
                                counterOfF += temp;
                                counterOfFNum++ ;
                            }
                            //warning of temp.
                            else
                            {
                                dew_point = "ErrorInput" ;
                            }
                        }
                    }//END of checking re-humi and other thing left. 
                    //warning of temp unit.
                    else
                    {
                        dew_point = "ErrorInput" ;
                    }
                }
                else
                {
                    dew_point = "ErrorInput" ;
                }
                //invalid noted.
                if ( dew_point == "ErrorInput" )
                    counterFlaw++ ;
  
                //output the file.
                //check whether the first letter of the date can conver to double, which confirms its a number.
                //we can also use getline.
                cout << left << setw(17) << dataOfDate << left << setw(18) << dataOfRh << left
                << setw(16) << dataOftemp << setw(11) << left << dew_point << right << setw(11) << dataOfunit << setw(10) << right << dataOfname << endl;
                //for putting the error reminder after the revealing of the data line, dew point has finished previously.
                if ( re_humi <= MAX_RH && re_humi >= MIN_RH )
                {
                    for(int k = 0; k < temp_unit.length(); k++)
                    {
                        temp_unit[k] = toupper(temp_unit[k]);
                    }
                    if ( temp_unit.substr(0,1) == "F" || temp_unit.substr(0,1) == "C" )
                    {
                        if ( temp_unit.substr(0,1) == "C" )
                        {
                            //range check.
                            if ( temp <= TEMP_MAXIMUM && temp >= TEMP_MINIMUM )
                            {
                                //aim for outputing nothing.
                                int i = 0;
                            }
                            else
                            {
                                cout << "Please enter the right range of temperature, thanks." << endl;
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
                                //aim for outputing nothing.
                                int i = 0;
                            }
                            //warning of temp.
                            else
                            {
                                cout << "Please enter the right range of temperature between -148 degrees Fahrenheit and 140 degrees Fahrenheit (inclusive), thanks." << endl;
                            }
                        }
                    }//END of checking F.
                    //warning of temp unit.
                    else
                    {
                        cout << temp_unit << " is not the right temperature unit, thanks." << endl;
                        //no need to check the temperature because of the wrong unit.
                        //warning.
                        cout << "Please enter the right temperature, thanks." << endl;
                    }
                }
                //warning of relative humidity.
                else{
                    cout << "Please enter the right range of humidity, thanks." << endl;
                    for(int k = 0; k < temp_unit.length(); k++)
                    {
                        temp_unit[k] = toupper(temp_unit[k]);
                    }
                    if ( !(temp_unit.substr(0,1) == "F" || temp_unit.substr(0,1) == "C") )
                    {
                        cout << temp_unit << " is not the right temperature unit, thanks." << endl;
                        cout << "Please enter the right temperature, thanks." << endl;
                    }
                    else
                    {
                        if ( temp_unit.substr(0,1) == "C" )
                        {
                            //range check.
                            if ( temp <= TEMP_MAXIMUM && temp >= TEMP_MINIMUM )
                            {
                                //aim for outputing nothing.
                                int i = 0;
                            }
                            else
                            {
                                cout << "Please enter the right range of temperature, thanks." << endl;
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
                                //aim for outputing nothing.
                                int i = 0;
                            }
                            //warning of temp.
                            else
                            {
                                cout << "Please enter the right range of temperature between -148 degrees Fahrenheit and 140 degrees Fahrenheit (inclusive), thanks." << endl;
                            }
                        }
                    }
                }
                //for warning the date issue.
                //for the day to begin execute.
                int begin_date = 0;
                for ( int i = 0; i < dataOfDate.length(); i ++ )
                {
                    if ( (dataOfDate.substr(i , 1) == "/") && (monthCounter < 1) )
                    {
                        //for converting string to int.
                        string current_string = dataOfDate.substr(0 , i);
                        stringstream geek(current_string);
                        geek >> monthOfDate;
                        monthCounter++ ;
                        begin_date = i + 1;
                        //for validing the first else if statement.
                        dayCounter = 0;
                    }
                    else if ( (dataOfDate.substr(i , 1) == "/") && (dayCounter < 1) )
                    {
                        string current_string = dataOfDate.substr(begin_date , i - 1);
                        stringstream geek(current_string);
                        geek >> dayOfDate ;
                        dayCounter++ ;
                        //for the year to execute succesfully in range.
                        //i have already been added in the condition of loop.
                        begin_date = i + 1;
                        yearCounter = 1 ;
                    }
                    else if ( yearCounter == 1 )
                    {
                        string current_string = dataOfDate.substr(begin_date , 4);
                        stringstream geek(current_string);
                        geek >> yearOfDate ;
                        yearCounter = 0;
                    }
                }//END for for loop for collecting the date data in int.
                
                if ( !(yearOfDate >= MINYEAR && yearOfDate <= MAXYEAR) )
                {
                    cout << yearOfDate << " is not a valid year, please check." << endl;
                    if ( !(monthOfDate >= MINMONTH && monthOfDate <= MAXMONTH) )
                    {
                        cout << monthOfDate << " is not a valid month, please check." << endl;
                        cout << dayOfDate << " is not a valid day, please check." << endl;
                    }
                    else if ( monthOfDate >= MINMONTH && monthOfDate <= MAXMONTH )
                    {
                        switch (monthOfDate) {
                            case JAN:
                            case MAR:
                            case MAY:
                            case JUL:
                            case AUG:
                            case OCT:
                            case DEC:
                                if ( !(dayOfDate > 0 && dayOfDate <= BIG_DAY_MAX) )
                                    cout << dayOfDate << " is not a valid day, please check." << endl;
                                break;
                                
                            case FEB:
                                if ( !(dayOfDate > 0 && dayOfDate <= FEB_DAY_MAX) )
                                    cout << dayOfDate << " is not a valid day, please check." << endl;
                                break;
                                
                            case APR:
                            case JUN:
                            case SEP:
                            case NOV:
                                if ( !(dayOfDate > 0 && dayOfDate <= FEB_DAY_MAX) )
                                    cout << dayOfDate << " is not a valid day, please check." << endl;
                                break;
                        }
                    }// END for day validation
                }//END for year month day validation.
                    
                
                
            }// END for while loop of reading data.
            
            
            
        } // END for successful open file processing execution.
        //close the file.
        cout << "There are total " << counterOfRow << " rows of data." << endl;
        cout << "There are total " << counterFlaw << " rows is invalid." << endl;
        cout << "The average temperature for " << counterOfCNum << " readings of Celcius is: " << counterOfC / counterOfCNum << endl;
        cout << "The average temperature for " << counterOfFNum << " readings of Fahrenheit is: " << counterOfF / counterOfFNum << endl;
        u_file.close();
    }// END for choie b.
    
    //situation c.
    else
    {
        cout << "You choose to quit." << endl;
        //close the file.
        u_file.close();
        return 123;
    }
    //finish, close the file before return.
    u_file.close();
    return 0;
}
