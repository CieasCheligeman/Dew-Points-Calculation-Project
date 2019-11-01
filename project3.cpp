/*
 * main.cpp
 *
 * COSC 051 Summer 2019
 * Project #3
 *
 * Due on: JUL 30, 2019
 * Author: cc2133
 *
 *
 * In accordance with the class policies and Georgetown's
 * Honor Code, I certify that I have neither
 * given nor received any assistance on this project.
 *
 * References not otherwise commented within the program source code.
 * Note that you should not mention any help from the TAs, the professor,
 * or any code taken from the class textbooks.
 */

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

//prototype of func.
//as what the name says.
char displayMenu();
//as what the name says.
bool uploadFile(string, vector<int>&, vector<int>&, vector<int>&, vector<double>&,
                vector<double>&, vector<char>&, vector<string>&);
//present all data in details.
void allDetails(const vector<int>&,const vector<int>&,const vector<int>&,
                const vector<double>&,const vector<double>&,
                const vector<char>&,const vector<string>& );
//present the detail data of a specific dates.
void dateDetails(const vector<int>&,const vector<int>&,const vector<int>&,
                 const vector<double>&,const vector<double>&,const vector<char>&,
                 const vector<string>&);
//organized by temp scale.
void summaryByScale(const vector<int>&,const vector<int>&,const vector<int>&,
                    const vector<double>&,const vector<double>&,const vector<char>&,
                    const vector<string>&);
//ALL can infer by name.
double dew_point_calculation (double, double, char);
void headerPrint(string);
void dataClear(vector<int>&, vector<int>&, vector<int>&, vector<double>&,
               vector<double>&, vector<char>&, vector<string>&);
//tools will be used in uploadfile.
bool isValidRH(double);
bool isValidScale(char);
bool isValidTemp(char, double);
bool isValidYear(int, int, int);
//func ends.
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
const int BIG_DAY_MAX = 31;
const int SEC_DAY_MAX = 30;
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

int main()
{
    vector<int> vDay;
    vector<int> vMonth;
    vector<int> vYear;
    vector<double> vRH;
    vector<double> vTemp;
    vector<char> vUnit;
    vector<double> dew_point;
    vector<string> vName;
    char choice = '?';
    while (choice != 'q' && choice != 'Q')
    {
        choice = displayMenu();
        string inputFile = "";
        switch (choice)
        {
            case 'U':
            case 'u':
                cout << "Please enter your input file name: ";
                getline(cin, inputFile);
                uploadFile(inputFile , vDay, vMonth, vYear, vRH, vTemp, vUnit, vName);
                break;
                
                
            case 'A':
            case 'a':
                allDetails( vDay, vMonth, vYear, vRH, vTemp, vUnit, vName);
                break;
                
                
            case 'D':
            case 'd':
                dateDetails(vDay, vMonth, vYear, vRH, vTemp, vUnit, vName );
                break;
                
                
            case 'S':
            case 's':
                summaryByScale(vDay, vMonth, vYear, vRH, vTemp, vUnit, vName );
                break;
                
                
            case 'C':
            case 'c':
                dataClear(vDay, vMonth, vYear, vRH, vTemp, vUnit, vName);
                cout << "Your upload file data has been cleaned! : ) .. " << endl;
                break;
                
                //for examine the maximum attemots to be valid.
            case '.':
                cout << "sorry you spend too much time on deciding a choice, program no"
                << "w quit...." << endl;
                choice = 'q'; //for quitting the while loop.
                break;
                
            case 'Q':
            case 'q':
                cout << "You choose to quit the program, see you then. :)" << endl;
                break;
                
                
        }//END of switch (choice) statement.
    }//END of while(choice).
    
    
    return 0; //normal exit
    
}//END of main.
/********************************************************************************************************************************************************
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                               FIVE ISVALID FUNC                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *********************************************************************************************************************************************************/
//**************************************
bool isValidRH(double relHumidity)
{
    if ( relHumidity > MIN_RH && relHumidity < MAX_RH )
        return true;
    else
        return false;
}

bool isValidScale(char tempScale)
{
    if ( tempScale == 'C' || tempScale == 'c' || tempScale == 'F' ||
        tempScale == 'f' )
        return true;
    else
        return false;
}

bool isValidTemp(char tempScale, double airTemp)
{
    if ( isValidScale(tempScale) )
    {
        if ( tempScale == 'c' || tempScale == 'C' )
        {
            //range check.
            if ( airTemp <= TEMP_MAXIMUM && airTemp >= TEMP_MINIMUM )
            {
                return true;
            }
            else
                return false;
        }
        else
        {
            //range check.
            airTemp = F_TO_C * ( airTemp - TEMP_C_FACTOR );
            if ( airTemp <= TEMP_MAXIMUM && airTemp >= TEMP_MINIMUM )
            {
                return true;
            }
            else
                return false;
        }
    }
    return false;
}

bool isValidYearForPrint(int m, int d, int y)
{
    int falseCounter = 0;
    if ( !(y >= MINYEAR && y <= MAXYEAR) ){
        falseCounter++ ;
        cout << "\t" << y << " is not a valid year" << endl;
    }
    if ( !(m >= MINMONTH && m <= MAXMONTH) ){
        falseCounter++ ;
        cout << "\t" << m << " is not a valid month" << endl;
        cout << "\t" << d << " is not a valid day" << endl;
    }
    else
    {
        switch (m) {
            case JAN:
            case MAR:
            case MAY:
            case JUL:
            case AUG:
            case OCT:
            case DEC:
                if ( !(d > 0 && d <= BIG_DAY_MAX) )
                    falseCounter++;
                cout << "\t" << d << " is not a valid day, please check." << endl;
                break;
                
            case FEB:
                if ( !(d > 0 && d <= FEB_DAY_MAX) )
                    falseCounter++;
                cout << "\t" << d << " is not a valid day, please check." << endl;
                break;
                
            case APR:
            case JUN:
            case SEP:
            case NOV:
                if ( !(d > 0 && d <= SEC_DAY_MAX) )
                    falseCounter++;
                cout << "\t" << d << " is not a valid day, please check." << endl;
                break;
        }
    }
    if ( falseCounter >= 1 )
        return false;
    return true;
}
bool isValidYearForReturn(int m, int d, int y)
{
    int falseCounter = 0;
    if ( !(y >= MINYEAR && y <= MAXYEAR) ){
        falseCounter++ ;
    }
    if ( !(m >= MINMONTH && m <= MAXMONTH) ){
        falseCounter++ ;
    }
    else
    {
        switch (m) {
            case JAN:
            case MAR:
            case MAY:
            case JUL:
            case AUG:
            case OCT:
            case DEC:
                if ( !(d > 0 && d <= BIG_DAY_MAX) )
                    falseCounter++;
                break;
                
            case FEB:
                if ( !(d > 0 && d <= FEB_DAY_MAX) )
                    falseCounter++;
                break;
                
            case APR:
            case JUN:
            case SEP:
            case NOV:
                if ( !(d > 0 && d <= SEC_DAY_MAX) )
                    falseCounter++;
                break;
        }
    }
    if ( falseCounter >= 1 )
        return false;
    return true;
}
//**************************************

/********************************************************************************************************************************************************
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                               MENU DISPLAY                                                                            *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *********************************************************************************************************************************************************/
char displayMenu()
{
    cout << "\t\tBlue Ridge Weather Analytics" << endl;
    cout << "\tThis application calculates the dew point for given" << endl;
    cout << "\trelative humidity and air temperature values." << endl;
    cout << endl;
    cout << right << setw(59) << "upload a meteorologist's data file     U" << endl;
    cout << right << setw(59) << "display details (all loaded data)     A" << endl;
    cout << right << setw(59) << "list details for a specific date (all matches)     D" << endl;
    cout << right << setw(59) << "display summary - order by temperature scale     S" << endl;
    cout << right << setw(59) << "clear all data     C" << endl;
    cout << right << setw(59) << "quit     Q" << endl;
    char initialChoice = '?';
    int maximumAttempts = 0;
    cout << "Please enter your choice: ";
    cin >> initialChoice;
    cin.ignore(100,'\n');
    while ( initialChoice != 'U' && initialChoice != 'u' && initialChoice != 'A' &&
           initialChoice != 'a' && initialChoice != 'D' && initialChoice != 'd'
           && initialChoice != 'c'&& initialChoice != 'C' && initialChoice != 's'
           && initialChoice != 'S' && initialChoice != 'Q'
           && initialChoice != 'q' && maximumAttempts < 3 )
    {
        cout << "Please enter a proper choice.." << endl;
        cout << "Your choice: ";
        cin >> initialChoice;
        cin.ignore(100,'\n');
        maximumAttempts++ ;
    }
    if ( maximumAttempts == 3 )
        return '.';
    return initialChoice;
}
//**************************************


/********************************************************************************************************************************************************
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                               UPLOADFILE                                                                              *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *********************************************************************************************************************************************************/
bool uploadFile(string fName, vector<int> &vDay, vector<int> &vMonth, vector<int> &vYear,
                vector<double> &vRH, vector<double> &vTemp,
                vector<char> &vUnit, vector<string> &vName)
{
    int v_day = 0;
    vector<double> cTemp;
    vector<double> fTemp;
    int counterError = 0;
    int counterFree = 0;
    int v_month = 0;
    int v_year = 0;
    int totalCounter = 0;
    double v_rh = 0;
    double v_temp = 0;
    char v_unit = 0;
    double cWholeTemp = 0;
    double fWholeTemp = 0;
    double cTempAverage = 0;
    double fTempAverage = 0;
    double cDeviation = 0;
    double fDeviation = 0;
    // convert type
    string v_name;
    ifstream u_file;
    u_file.open(fName.c_str());
    //f_ile becomes useless after this line.
    //check whether the file is legible for system.
    if ( !u_file )
    {
        cout << "Please enter a right file name." << endl;
    }
    //file is legible.
    else
    {
        string dataOfDate = "";
        string header = "";
        double dewPoint = 0;
        //clean the header first.
        getline(u_file, header);
        //read the content out.
        //this will automatically close the file after reading if i am remember it right. // Entered upload file function 0 elements in the vectors.
        cout << "Enter the function upLoadFile successfully." << endl;
        cout << "Entered upload file function "<<  vTemp.size() <<" elements in the vectors." << endl;
        cout << "Now file " << fName << " is opened: " << endl;
        headerPrint("upper_header");
        while ( u_file >> dataOfDate >> v_rh >> v_temp >> v_unit )
        {
            int yearCounter = 0;
            //for limiting the time of executing month data.
            int monthCounter = 0;
            //for limiting the time of executing day.
            int dayCounter = 1;
            int day1 = 0;
            int month1 = 0;
            int year1 = 0;
            //for counting the number of data.
            getline(u_file, v_name);
            //create parellel array.
            //prevent the validation of the parrelel array.
            int begin_date = 0;
            //store date data into the vector.
            for ( int i = 0; i < dataOfDate.length(); i ++ )
            {
                if ( (dataOfDate.substr(i , 1) == "/") && (monthCounter < 1) )
                {
                    //for converting string to int.
                    string current_string = dataOfDate.substr(0 , i);
                    stringstream geek(current_string);
                    geek >> month1;
                    monthCounter++ ;
                    begin_date = i + 1;
                    //for validing the first else if statement.
                    dayCounter = 0;
                }
                else if ( (dataOfDate.substr(i , 1) == "/") && (dayCounter < 1) )
                {
                    string current_string = dataOfDate.substr(begin_date , i - 1);
                    stringstream geek(current_string);
                    geek >> day1;
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
                    geek >> year1;
                    yearCounter = 0;
                }
            }
                if ( isValidRH(v_rh) && isValidTemp(v_unit, v_temp)
                    && isValidScale(v_unit) && isValidYearForReturn(month1, day1, year1) )
                {
                    totalCounter++ ;
                    counterFree++ ;
                    vRH.push_back(v_rh);
                    vYear.push_back(year1);
                    vMonth.push_back(month1);
                    vDay.push_back(day1);
                    vTemp.push_back(v_temp);
                    vUnit.push_back(v_unit);
                    vName.push_back(v_name);
                    dewPoint = dew_point_calculation(v_temp, v_rh, v_unit);
                    cout << left << setw(17) << dataOfDate << left
                    << setw(18) << v_rh << left
                    << setw(16) << v_temp << setw(11) << right << dewPoint
                    << right << setw(4) << v_unit << setw(10) << right
                    << v_name << endl;
                    if ( v_unit == 'c' || v_unit == 'C' ){
                        cWholeTemp += v_temp;
                        cTemp.push_back(v_temp);
                    }
                    if ( v_unit == 'f' || v_unit == 'F' ){
                        fWholeTemp += v_temp;
                        fTemp.push_back(v_temp);
                    }
                }
                else
                {
                    totalCounter++ ;
                    counterError++ ;
                    cout << left << setw(17) << dataOfDate << left << setw(18) << v_rh << left
                    << setw(16) << v_temp << setw(11) << right << "Check input!"
                    << right << setw(3) << v_unit << setw(10) << right << v_name << endl;
                    if ( !(isValidScale(v_unit)) )
                        cout << "\t" << v_unit <<" unit is not valid. " << endl;
                    if ( !(isValidRH(v_rh)) )
                        cout << "\t" << "relative humidity " << v_rh << " is not valid. " << endl;
                    if ( !(isValidTemp(v_unit, v_temp)) )
                        cout << "\t" << "temperature: " << v_temp << " is not valid. " << endl;
                    if ( !(isValidYearForReturn(month1, day1, year1)) )
                        isValidYearForPrint(month1, day1, year1);
                }
        }//END of while.
        cTempAverage = cWholeTemp / cTemp.size() ;
        fTempAverage = fWholeTemp / fTemp.size() ;
        //calculate deviation for celsius.
        for (int i = 0; i < cTemp.size() ; i ++)
        {
            cDeviation += pow((cTemp.at(i) - cTempAverage),2);
        }
        cDeviation = sqrt(cDeviation / cTemp.size());
        //calculate deviation for fahrenheit.
        for (int i = 0; i < fTemp.size() ; i ++)
        {
            fDeviation += pow((fTemp.at(i) - fTempAverage),2);
        }
        fDeviation = sqrt(fDeviation / fTemp.size());
    }
    
    //check wehther successfully loaded or not.
    if ( cTemp.size() > 1 )
    {
        cout << "Total records in file: " << totalCounter << endl;
        cout << cTemp.size() <<" Celsius readings, with average air temp = "
        << cTempAverage << " and standard deviation = " << cDeviation << endl;
        cout << fTemp.size() <<" Fahrenheit readings, with average air temp = "
        << fTempAverage << " and standard deviation = " << fDeviation << endl;
        cout << counterError << " readings with invalid data." << endl;
        cout << endl;
        cout << "Exiting upload file function "<< vTemp.size()
        <<" elements in the vectors."<< endl;
        cout << "NOTE: The data file successfully loaded." << endl;
        headerPrint("lower_header");
        return true;
    }
    else
    {
        cout << "NOTE: The data file has failed to load." << endl;
        headerPrint("lower_header");
        return false;
    }
}
//**************************************

/********************************************************************************************************************************************************
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                               ALLDetails                                                                              *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *********************************************************************************************************************************************************/

void allDetails(const vector<int> &vDay,const vector<int> &vMonth,const vector<int> &vYear,
                const vector<double> &vRH,const vector<double> &vTemp,const vector<char> &vUnit,
                const vector<string> &vName)
{
    double dewPoint = 0;
    int rowCounter = 0;
    int organizer = 0;
    double cWholeTemp = 0;
    double fWholeTemp = 0;
    double cTempAverage = 0;
    double fTempAverage = 0;
    double cDeviation = 0;
    double fDeviation = 0;
    vector<double> fTemp;
    vector<double> cTemp;
    if ( vTemp.size() < 1 )
        cout << "Please upload a file successfully first..." << endl;
    else
    {
        cout << "Entered function allDetails, there are "<< vTemp.size() <<" elements in the vectors." << endl;
        headerPrint("upper_header");
        for (int i = 0; i < vDay.size(); i++)
        {
            
            rowCounter++ ;
            dewPoint = dew_point_calculation(vTemp.at(i), vRH.at(i), vUnit.at(i));
            if ( vDay.at(i) < 10 && vMonth.at(i) < 10 ){
                organizer = 18;
                cout << vMonth.at(i) << "/" << vDay.at(i) << "/" << vYear.at(i) << right
                << setw(organizer) << vRH.at(i) << right
                << setw(16) << vTemp.at(i) << right << setw(4) << vUnit.at(i)
                << setw(16) << right << dewPoint << setw(5)
                << right << vName.at(i) << endl;}
            if ( vDay.at(i) >= 10 && vMonth.at(i) < 10 ){
                organizer = 17;
                cout << vMonth.at(i) << "/" << vDay.at(i) << "/" << vYear.at(i)
                << right << setw(organizer) << vRH.at(i) << right
                << setw(16) << vTemp.at(i) << right << setw(4) << vUnit.at(i)
                << setw(16) << right << dewPoint << setw(5) << right
                << vName.at(i) << endl;}
            if ( vDay.at(i) >= 10 && vMonth.at(i) >= 10 ){
                organizer = 16;
                cout << vMonth.at(i) << "/" << vDay.at(i) << "/"
                << vYear.at(i) << right << setw(organizer) << vRH.at(i) << right
                << setw(16) << vTemp.at(i) << right << setw(4) << vUnit.at(i)
                << setw(16) << right << dewPoint << setw(5) << right
                << vName.at(i) << endl;}
            if ( vDay.at(i) < 10 && vMonth.at(i) >= 10 ){
                organizer = 17;
                cout << vMonth.at(i) << "/" << vDay.at(i) << "/" << vYear.at(i)
                << right << setw(organizer) << vRH.at(i) << right
                << setw(16) << vTemp.at(i) << right << setw(4) << vUnit.at(i)
                << setw(16) << right << dewPoint << setw(5) << right
                << vName.at(i) << endl;}
            //For deviation calculation.
            if ( vUnit.at(i) == 'c' || vUnit.at(i) == 'C' ){
                cWholeTemp += vTemp.at(i);
                cTemp.push_back(vTemp.at(i));
            }
            if ( vUnit.at(i) == 'f' || vUnit.at(i) == 'F' ){
                fWholeTemp += vTemp.at(i);
                fTemp.push_back(vTemp.at(i));
            }
            
        }//END of for loop.
        cTempAverage = cWholeTemp / cTemp.size() ;
        fTempAverage = fWholeTemp / fTemp.size() ;
        //calculate deviation for celsius.
        for (int i = 0; i < cTemp.size() ; i ++)
        {
            cDeviation += pow((cTemp.at(i) - cTempAverage),2);
        }
        cDeviation = sqrt(cDeviation / cTemp.size());
        //calculate deviation for fahrenheit.
        for (int i = 0; i < fTemp.size() ; i ++)
        {
            fDeviation += pow((fTemp.at(i) - fTempAverage),2);
        }
        fDeviation = sqrt(fDeviation / fTemp.size());
        headerPrint("lower_header");
        cout << "There are total " << rowCounter << " rows of valid data in this file." << endl;
        cout << cTemp.size() <<" Celsius readings, with average air temp = "
        << cTempAverage << " and standard deviation = " << cDeviation << endl;
        cout << endl;
        cout << fTemp.size() <<" Fahrenheit readings, with average air temp = "
        << fTempAverage << " and standard deviation = " << fDeviation << endl;
        cout << endl;
        cout << endl;
        cout << "Exiting function allDetails." << endl;
    }//END of else
}
//**************************************

/********************************************************************************************************************************************************
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                               DateDetails                                                                             *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *********************************************************************************************************************************************************/
void dateDetails(const vector<int> &vDay,const vector<int> &vMonth,const vector<int> &vYear,
                 const vector<double> &vRH,const vector<double> &vTemp,const vector<char> &vUnit,
                 const vector<string> &vName)
{
    string dataOfDate = "";
    if ( vTemp.size() < 1)
        cout << "Please upload a file successfully first..." << endl;
    else
    {
        cout << "Enter the date to display, please enter the date you want to search for:(mm/dd/yyyy) ";
        getline(cin , dataOfDate);
        int yearCounter = 0;
        //for limiting the time of executing month data.
        int monthCounter = 0;
        //for limiting the time of executing day.
        int dayCounter = 1;
        //for counting the number of data.
        int begin_date = 0;
        //for calculating the total match file.
        double cWholeTemp = 0;
        double fWholeTemp = 0;
        double cTempAverage = 0;
        double fTempAverage = 0;
        double cDeviation = 0;
        double fDeviation = 0;
        int matchFileNum = 0;
        vector<double> fTemp;
        vector<double> cTemp;
        int day = 0;
        int month = 0;
        int year = 0;
        for ( int i = 0; i < dataOfDate.length(); i ++ )
        {
            if ( (dataOfDate.substr(i , 1) == "/") && (monthCounter < 1) )
            {
                //for converting string to int.
                string current_string = dataOfDate.substr(0 , i);
                stringstream geek(current_string);
                geek >> month;
                monthCounter++ ;
                cout << "The month you input is : " << month << "."<< endl;
                begin_date = i + 1;
                //for validing the first else if statement.
                dayCounter = 0;
            }
            else if ( (dataOfDate.substr(i , 1) == "/") && (dayCounter < 1) )
            {
                string current_string = dataOfDate.substr(begin_date , i - 1);
                stringstream geek(current_string);
                geek >> day;
                cout << "The day you input is : " << day << "."<< endl;
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
                geek >> year;
                cout << "The year you input is : " << year << "."<< endl;
                yearCounter = 0;
            }
        }
        headerPrint("upper_header");
        for ( int i = 0; i < vTemp.size() ; i ++){
            int checker = 0;
            int dewPoint = 0;
            if ( (vDay.at(i) - day) == 0 && (vMonth.at(i) - month) == 0
                && (vYear.at(i) - year) == 0 )
                checker++ ;
            if ( checker > 0 )
            {
                matchFileNum++ ;
                dewPoint = dew_point_calculation(vTemp.at(i), vRH.at(i), vUnit.at(i));
                cout << vMonth.at(i) << "/" << vDay.at(i) << "/" << vYear.at(i)
                << setw(12) << right << vRH.at(i) << setw(17) << right
                << vTemp.at(i) << right << setw(3)
                << vUnit.at(i) << right << setw(20) << dewPoint << right
                << setw(7) << vName.at(i) << endl;
                if ( vUnit.at(i) == 'c' || vUnit.at(i) == 'C' ){
                    cWholeTemp += vTemp.at(i);
                    cTemp.push_back(vTemp.at(i));
                }
                if ( vUnit.at(i) == 'f' || vUnit.at(i) == 'F' ){
                    fWholeTemp += vTemp.at(i);
                    fTemp.push_back(vTemp.at(i));
                }
            }
        }
        if ( fTemp.size() == 0 && cTemp.size() == 0 )
            cout << "There are no matching data, please check your input." << endl;
        else
        {
            if ( cTemp.size() > 0 )
                cTempAverage = cWholeTemp / cTemp.size() ;
            if ( fTemp.size() > 0 )
                fTempAverage = fWholeTemp / fTemp.size() ;
            //calculate deviation for celsius.
                if ( cTemp.size() > 1 ){
                    for (int i = 0; i < cTemp.size() ; i ++)
                    {
                        cDeviation += pow((cTemp.at(i) - cTempAverage),2);
                    }
                    cDeviation = sqrt(cDeviation / cTemp.size());
                }
                //calculate deviation for fahrenheit.
                if ( fTemp.size() > 1 ){
                    for (int i = 0; i < fTemp.size() ; i ++)
                    {
                        fDeviation += pow((fTemp.at(i) - fTempAverage),2);
                    }
                    fDeviation = sqrt(fDeviation / fTemp.size());
                    
                }
            
            }//END of for loop.
            headerPrint("lower_header");
            cout << "Total matching records in file: "<< matchFileNum << endl;
            if ( fDeviation > 0 )
            {
                cout << fTemp.size() <<" Fahrenheit readings, with average air temp = "
                << fTempAverage << " and standard deviation = " << fDeviation << endl;
            }
            else
            {
                cout << fTemp.size() <<" fahrenheit readings, with average air temp = "
                << fTempAverage << endl;
            }
            if ( cDeviation > 0 )
            {
                cout << cTemp.size() <<" Celsius readings, with average air temp = "
                << cTempAverage << " and standard deviation = " << cDeviation << endl;
                cout << endl;
            }
            else
            {
                cout << cTemp.size() <<" Celsius readings, with average air temp = "
                << cTempAverage << endl;
                cout << endl;
            }
        }//END of else.
        cout << "Exiting function dateDetails." << endl;
    }

/********************************************************************************************************************************************************
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                               SUMMARY BY SCALE                                                                        *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *********************************************************************************************************************************************************/

void summaryByScale(const vector<int> &vDay,const vector<int> &vMonth,
                    const vector<int> &vYear,const vector<double> &vRH,
                    const vector<double> &vTemp,const vector<char> &vUnit,
                    const vector<string> &vName)
{
    double cTemp = 0;
    double cTempNum = 0;
    double fTemp = 0;
    double fTempNum = 0;
    double cDew = 0;
    double fDew = 0;
    double cRHNum = 0;
    double fRHNum = 0;
    double cRH = 0;
    double fRH = 0;
    if ( vTemp.size() < 1)
        cout << "Please upload a file successfully first..." << endl;
    else
    {
        for (int i = 0; i < vTemp.size(); i ++)
        {
            if ( vUnit.at(i) == 'c' || vUnit.at(i) == 'C' ){
                cTempNum++ ;
                cRHNum++ ;
                cTemp += vTemp.at(i);
                cRH += vRH.at(i);
                cDew += dew_point_calculation( vTemp.at(i), vRH.at(i), vUnit.at(i) );
                
            }
            if ( vUnit.at(i) == 'f' || vUnit.at(i) == 'F' ){
                fTempNum++ ;
                fRHNum++ ;
                fTemp += vTemp.at(i);
                fRH += vRH.at(i);
                fDew += dew_point_calculation( vTemp.at(i), vRH.at(i), vUnit.at(i) );
            }
            
        }
        //wait for testing data and teacher's sample execution.
        cTemp /= cTempNum;
        fTemp /= fTempNum;
        fRH /= cRHNum;
        cRH /= fRHNum;
        cDew /= cTempNum;
        fDew /= fTempNum;
        cout << "Entered function summaryByScale, there are "
        << vTemp.size() <<" elements in the vectors." << endl;
        cout << "\n\n";
        cout << "\t\t" << "Average Readings by Temperature Scale" << endl;
        cout << "\t\t  Relative" << "\tAir" << "\t\tDew" << endl;
        cout << "\t\t  Humidity" << "\tTemp" << "\t\tPoint" << endl;
        cout << "\t  ---------------------------------------------------" << endl;
        cout << "\t\t   " <<  cRH << "\t        " << cTemp
        << "  " << "C" << "\t" << cDew << "  C" << endl;
        cout << "\t\t   " <<  fRH << "   " << fTemp << "  "
        << "F" << "\t" << fDew << "  F" << endl;
        cout << endl;
        cout << "Exiting function summaryByScale." << endl;
        
    }//END OF ELSE
}

/********************************************************************************************************************************************************
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                               DEWPOINT CALCULATION                                                                    *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *********************************************************************************************************************************************************/

double dew_point_calculation (double temp, double rh, char unit)
{
    double dew_point = 0;
    int transTemp = 0;
    if ( unit == 'c' || unit == 'C' )
    {
        //dew point calculation
        dew_point = ( DEW_B * ( (DEW_A * temp) / ( DEW_B + temp) + log(rh) ) ) /
        ( DEW_A - ( (DEW_A * temp) / ( DEW_B + temp) + log(rh) ) );
        
    }
    else
    {
        //temp conversion data
        transTemp = F_TO_C * ( temp - TEMP_C_FACTOR );
        //dew point calculation
        dew_point = ( DEW_B * ( (DEW_A * transTemp) / ( DEW_B + transTemp ) + log(rh) ) ) /
        ( DEW_A - ( (DEW_A * transTemp) / ( DEW_B + transTemp ) + log(rh) ) );
        dew_point = C_TO_F * ( transTemp + TEMP_C_FACTOR );
        //TEMPCFACTOR == TEMPFFACTOR
        
    }
    return dew_point;
}

/********************************************************************************************************************************************************
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                               Header Printing                                                                         *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *********************************************************************************************************************************************************/

void headerPrint(string input)
{
    if ( input == "upper_header" ){
        cout << "\t\t" << "relative" << "\t" << "   Air"
        << "\t\t\t\t\t\t" << "Meteorologist" << endl;
        cout << "Date" << "\t\t" << "Humidity" << "\t  " << " Temp"
        << "\t\t\t" << "Dew point" << "\t\t" << "Name" << endl;
        cout << "-----------------------------------------------------" <<
        "---------------------------------------------" << endl;
    }
    if ( input == "lower_header" ){
        cout << "-----------------------------------------------------" <<
        "---------------------------------------------" << endl;
    }
}

/********************************************************************************************************************************************************
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                               Data Clear                                                                              *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *                                                                                                                                                       *
 *********************************************************************************************************************************************************/

void dataClear(vector<int> &vDay, vector<int> &vMonth, vector<int> &vYear,
               vector<double> &vRH, vector<double> &vTemp,
               vector<char> &vUnit, vector<string> &vName)
{
    cout << vDay.size() <<" elements are on the day vector." << endl;
    vDay.clear();
    vName.clear();
    vUnit.clear();
    vTemp.clear();
    vRH.clear();
    vYear.clear();
    vMonth.clear();
    cout << "Called clear method for all vectors, data have been deleted." << endl;
    cout << "now " << vDay.size() << " elements are on the day vector." << endl;
}
