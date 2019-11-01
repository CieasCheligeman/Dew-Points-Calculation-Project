/***************************************************************************************
 *                                                                                     *
 *                             Summer 2019 Project #4                                  *
 *                            class Weather declaraion                                 *
 *                                                                                     *
 *                                                                                     *
 ***************************************************************************************/


/*
 *  main.cpp
 *
 *  COSC 051 Summer 2019
 *  Project #4
 *
 *  Due on: AUG 7, 2019
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
#include <vector>

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
// /Users/a1209899754/desktop/P3kepler.txt
class Weather
{
    // overloaded stream insertion operator
    // outputs all values for this object on one line (similar to the format of the input file)
    //because of a friend class, return os to the cout so ostream class can use the private member data to print to the screen.
    friend ostream& operator<<( ostream &os, const Weather &rhsObj );
    
    
    // overloaded stream extraction operator
    // in one statement extracts all values from a stream and updates the data member values
    friend istream& operator>>( istream &is, Weather &rhsObj );
    
private:
    int month, day, year;
    double relativeHumidity, airTemp;
    char tempUnits;
    string name;
    string dataOfDate;
    
public:
    
    // default constructor
    Weather();
    // constructor with parameters
    Weather( int m, int d, int y, double rH, double aT, char tU, string n );
    // copy constructor
    Weather( const Weather & );
    // destructor, the destructor for this class does not have much (really anything) to
    // do, but it can be informative to put some diagnostic output during early
    // stages of development
    ~Weather(){}
    
    // overloaded assignment operator
    Weather& operator=( const Weather &obj );
    
    
    // method to calculate the dew point for this Weather object
    double getDewPoint() const;
    // method to validate the date
    void isValidDate(bool &answer, string &message) const;
    // method to validate the relative humidity
    void isValidRH(bool &answer, string &message) const;
    // method to validate the air temperature
    void isValidTemp(bool &answer, string &message) const;
    // method to validate the units
    void isValidUnits(bool &answer, string &message) const;
    bool isValidUnits() const;
    // method to return true answer if all validation tests are successful
    // also returns a string with consolidated error message from
    // all other validation tests
    void isValidRecord(bool &answer, string &message) const;
    
    // basic accessor functions (may be implemented inside (inline) or outside the declaration
    int getMonth() const {  return month; }
    int getDay() const { return day; }
    int getYear() const {  return year; }
    double getRelativeHumidity() const { return relativeHumidity; }
    double getAirTemp() const {  return airTemp; }
    char getTempUnits() const {  return tempUnits; }
    string getName() const {  return name; }
    string getDataOfDate() const { return dataOfDate; }
    // basic mutator functions (may be implemented inside (inline) or outside the declaration
    void setMonth(int m) { month = m; }
    void setDay(int d) { day = d; }
    void setYear(int y) { year = y; }
    void setRelativeHumidity(double rh) { relativeHumidity = rh;}
    void setAirTemp(double temp) { airTemp = temp; }
    void setTempUnits(char uni) { tempUnits = uni; }
    void setName(string na) { name = na; }
    void setDataOfDate( string date ) { dataOfDate = date; }
    
}; //END declaration for class Weather

/***************************************************************************************
 *                                                                                     *
 *                             NORMAL FUNCTION prototype AREA                          *
 *                                                                                     *
 *                                                                                     *
 *                                                                                     *
 ***************************************************************************************/

char displayMenu();

bool uploadFile(string fName, vector<Weather> &readings);

void allDetails(const vector<Weather> &readings);

void headerPrint(string);

void dateDetails(const vector<Weather> &readings);

void summaryByScale(const vector<Weather> &readings);

void dataClear(vector<Weather> &readings);


/***************************************************************************************
 *                                                                                     *
 *                             MAIN                                                    *
 *                                                                                     *
 *                                                                                     *
 *                                                                                     *
 ***************************************************************************************/

int main()
{
    vector<Weather> weatherData;
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
                uploadFile(inputFile, weatherData);
                break;
                
                
            case 'A':
            case 'a':
                allDetails(weatherData);
                break;
                
                
            case 'D':
            case 'd':
                dateDetails(weatherData);
                break;
                
                
            case 'S':
            case 's':
                summaryByScale(weatherData);
                break;
                
                
            case 'C':
            case 'c':
                cout << weatherData.size() << " elements are on the class vector." << endl;
                dataClear(weatherData);
                cout << "Called clear method for all vectors, Your upload file data has been cleaned! : ) .. " << endl;
                cout << weatherData.size() << " elements are on the class vector." << endl;
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

/***************************************************************************************
 *                                                                                     *
 *                             MEMBER FUNCTION implementation AREA                     *
 *                                                                                     *
 *                                                                                     *
 *                                                                                     *
 ***************************************************************************************/
//constructor with input.

Weather::Weather() { month = 0; day = 0; year = 0; relativeHumidity = 0; airTemp = 0; tempUnits = '?'; name = "unknown" ;}

ostream& operator<<( ostream &os, const Weather &rhsObj )
{
    int organizer = 0;
    if ( rhsObj.day < 10 && rhsObj.month < 10 ){
        organizer = 16;
        os <<  fixed << setprecision(2) << "0" << rhsObj.month << "/" << "0" << rhsObj.day << "/"
        << rhsObj.year << right << setw(organizer) << rhsObj.relativeHumidity << right
        << setw(16) << rhsObj.airTemp << right << setw(4) << rhsObj.tempUnits
        << setw(16) << right << rhsObj.getDewPoint() << " "
        << rhsObj.getTempUnits() << setw(5) << right
        << rhsObj.name << endl;}
    if ( rhsObj.day >= 10 && rhsObj.month < 10 ){
        organizer = 16;
        os << fixed << setprecision(2) << "0" << rhsObj.month << "/" << rhsObj.day << "/"
        << rhsObj.year << right << setw(organizer) << rhsObj.relativeHumidity << right
        << setw(16) << rhsObj.airTemp << right << setw(4) << rhsObj.tempUnits
        << setw(16) << right << rhsObj.getDewPoint() << " "
        << rhsObj.getTempUnits() << setw(5) << right
        << rhsObj.name << endl;}
    if ( rhsObj.day >= 10 && rhsObj.month >= 10 ){
        organizer = 16;
        os << fixed << setprecision(2) << rhsObj.month << "/" << rhsObj.day << "/"
        << rhsObj.year << right << setw(organizer) << rhsObj.relativeHumidity << right
        << setw(16) << rhsObj.airTemp << right << setw(4) << rhsObj.tempUnits
        << setw(16) << right << rhsObj.getDewPoint() << " "
        << rhsObj.getTempUnits() << setw(5) << right
        << rhsObj.name << endl;}
    if ( rhsObj.day < 10 && rhsObj.month >= 10 ){
        organizer = 16;
        os << fixed << setprecision(2) << rhsObj.month << "/" << "0" << rhsObj.day << "/" << rhsObj.year
        << right << setw(organizer) << rhsObj.relativeHumidity << right
        << setw(16) << rhsObj.airTemp << right << setw(4) << rhsObj.tempUnits
        << setw(16) << right << rhsObj.getDewPoint() << " "
        << rhsObj.getTempUnits() << setw(5) << right
        << rhsObj.name << endl;}
    return os;
}

istream& operator>>( istream &is, Weather &rhsObj )
{
    string date = "unkown";
    double rela = 0, air = 0;
    char unit = 'u';
    string name = "un";
    is >> date >> rela >> air >> unit;;
    getline(is, name);
    rhsObj.setAirTemp(air);
    rhsObj.setName(name);
    rhsObj.setTempUnits(unit);
    rhsObj.setRelativeHumidity(rela);
    rhsObj.setDataOfDate(date);
    return is;
}

Weather& Weather::operator=( const Weather &obj )
{
    //avoid returning the original reference so that compiler can work.
    if ( this != &obj )
    {
        setName(obj.getName());
        setDay(obj.getDay());
        setYear(obj.getYear());
        setMonth(obj.getMonth());
        setRelativeHumidity(obj.getRelativeHumidity());
        setAirTemp(obj.getAirTemp());
        setTempUnits(obj.getTempUnits());
        dataOfDate = "unknown";
        
    }
    
    return *this;
}


Weather::Weather(int m, int d, int y, double rH, double aT, char tU, string n )
{
    setName(n);
    setDay(d);
    setYear(y);
    setMonth(m);
    setRelativeHumidity(rH);
    setAirTemp(aT);
    setTempUnits(tU);
    dataOfDate = "unknown";
}

Weather::Weather( const Weather &obj )
{
    setName(obj.getName());
    setDay(obj.getDay());
    setYear(obj.getYear());
    setMonth(obj.getMonth());
    setRelativeHumidity(obj.getRelativeHumidity());
    setAirTemp(obj.getAirTemp());
    setTempUnits(obj.getTempUnits());
    dataOfDate = "unknown";
}


void Weather::isValidRH(bool &ans, string &mess) const
{
    if ( relativeHumidity > MIN_RH && relativeHumidity < MAX_RH )
        ans = true;
    else
    {
        ans = false;
        mess = "The relative Humidity is not valid." ;
    }
}

void Weather::isValidDate(bool &answer, string &message) const
{
    int falseCounter = 0;
    if ( !(year >= MINYEAR && year <= MAXYEAR) ){
        falseCounter++ ;
        message = "This is not a valid year.\n" ;
    }
    if ( !(month >= MINMONTH && month <= MAXMONTH) ){
        falseCounter++ ;
        message += "This is not a valid month.\n" ;
        message += "This is not a valid day.\n" ;
    }
    else
    {
        switch (month) {
            case JAN:
            case MAR:
            case MAY:
            case JUL:
            case AUG:
            case OCT:
            case DEC:
                if ( !(day > 0 && day <= BIG_DAY_MAX) )
                    falseCounter++;
                message += "This is not a valid day.\n" ;
                break;
                
            case FEB:
                if ( !(day > 0 && day <= FEB_DAY_MAX) )
                    falseCounter++;
                message += "This is not a valid day.\n" ;
                break;
                
            case APR:
            case JUN:
            case SEP:
            case NOV:
                if ( !(day > 0 && day <= SEC_DAY_MAX) )
                    falseCounter++;
                message += "This is not a valid day.\n" ;
                break;
        }
    }
    if ( falseCounter >= 1 )
        answer = false;
    else
        answer = true;
}

void Weather::isValidTemp(bool &answer, string &message) const
{
    if ( isValidUnits() )
    {
        if ( tempUnits == 'c' || tempUnits == 'C' )
        {
            //range check.
            if ( airTemp <= TEMP_MAXIMUM && airTemp >= TEMP_MINIMUM )
            {
                answer = true;
            }
            else{
                answer = false;
                message = "The temperature is not valid.";
            }
        }
        else
        {
            //range check.
            double subTemp = airTemp;
            subTemp = F_TO_C * ( airTemp - TEMP_C_FACTOR );
            if ( subTemp <= TEMP_MAXIMUM && subTemp >= TEMP_MINIMUM )
            {
                answer = true;
            }
            else
            {
                answer = false;
                message = "The temperature is not valid.";
                
            }
        }
    }
    else
    {
        answer = false;
        message = "The temperature is not valid.";
    }
}

void Weather::isValidUnits(bool &answer, string &message) const
{
    if ( tempUnits == 'C' || tempUnits == 'c' || tempUnits == 'F' ||
        tempUnits == 'f' )
    {
        answer = true;
    }
    else
    {
        answer = false;
        message = "The temperature units is not valid.";
        
    }
}

//for the simple code of isValid temp.
bool Weather::isValidUnits() const
{
    bool checker = false;
    if ( tempUnits == 'C' || tempUnits == 'c' || tempUnits == 'F' ||
        tempUnits == 'f' )
        checker = true;
    return checker;
}

void Weather::isValidRecord(bool &answer, string &message) const
{
    bool check = false;
    int falseCounter = 0;
    string useless = "";
    isValidUnits(check, useless);
    if ( check == false )
        falseCounter++;
    isValidDate(check, useless);
    if ( check == false )
        falseCounter++;
    isValidTemp(check, useless);
    if ( check == false )
        falseCounter++;
    isValidRH(check, useless);
    if ( check && falseCounter == 0 )
        answer = true;
    else
        message = "Check input!";
}

double Weather::getDewPoint() const
{
    double transTemp = 0;
    double dew_point = 0;
    if ( tempUnits == 'c' || tempUnits == 'C' )
    {
        //dew point calculation
        dew_point = ( DEW_B * ( (DEW_A * airTemp) / ( DEW_B + airTemp) + log(relativeHumidity) ) ) /
        ( DEW_A - ( (DEW_A * airTemp) / ( DEW_B + airTemp) + log(relativeHumidity) ) );
        
    }
    else
    {
        //dew point calculation
        // transfer temp from f to c in order to use the formula.
        transTemp = F_TO_C * (airTemp - 32);
        //formula processing.
        dew_point = ( DEW_B * ( (DEW_A * transTemp) / ( DEW_B + transTemp ) + log(relativeHumidity) ) ) /
        ( DEW_A - ( (DEW_A * transTemp) / ( DEW_B + transTemp ) + log(relativeHumidity) ) );
        //transfer dew point back to fahrenheit unit.
        
    }
    return dew_point;
}

/***************************************************************************************
 *                                                                                     *
 *                             NORMAL FUNCTION implementation AREA                     *
 *                                                                                     *
 *                                                                                     *
 *                                                                                     *
 ***************************************************************************************/


/***************************************************************************************
 *                                                                                     *
 *                             Display the menu                                        *
 *                                                                                     *
 *                                                                                     *
 *                                                                                     *
 ***************************************************************************************/

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
        cout << "Please enter a correct choice. " << endl;
        cout << endl;
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
        cout << "Enter your choice again: ";
        cin >> initialChoice;
        cin.ignore(100,'\n');
        maximumAttempts++ ;
    }
    if ( maximumAttempts == 3 )
        initialChoice = '.';
    return initialChoice;
}



/***************************************************************************************
 *                                                                                     *
 *                             file uploading                                          *
 *                                                                                     *
 *                                                                                     *
 *                                                                                     *
 ***************************************************************************************/


bool uploadFile(string fName, vector<Weather> &readings)
{
    //for doing the deviation eplicitly.
    int sizeOfWeather = readings.size();
    vector<double> cTemp;
    vector<double> fTemp;
    int counterError = 0;
    int counterFree = 0;
    int totalCounter = 0;
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
        cout << "Entered upload file function "<<  readings.size() <<" elements in the vectors." << endl;
        cout << "Now file " << fName << " is opened: " << endl;
        headerPrint("upper_header");
        //one needed new object.
        Weather tester1;
        //rewrite the tester object content for every while loop.
        while ( u_file >> tester1 )
        {
            int yearCounter = 0;
            //for limiting the time of executing month data.
            int monthCounter = 0;
            //for limiting the time of executing day.
            int dayCounter = 1;
            int day1 = 0;
            int month1 = 0;
            int year1 = 0;
            //create parellel array.
            //prevent the validation of the parrelel array.
            int begin_date = 0;
            string dataOfDate = tester1.getDataOfDate();
            //store date data into the vector.
            for ( int i = 0; i < dataOfDate.length(); i ++ )
            {
                if ( (dataOfDate.substr(i , 1) == "/") && (monthCounter < 1) )
                {
                    //for converting string to int.
                    string current_string = dataOfDate.substr(0 , i);
                    stringstream geek(current_string);
                    geek >> month1;
                    tester1.setMonth(month1);
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
                    tester1.setDay(day1);
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
                    tester1.setYear(year1);
                    yearCounter = 0;
                }
            }
            bool checker = false;
            string nothing;
            tester1.isValidRecord(checker, nothing);
            if ( checker )
            {
                totalCounter++ ;
                counterFree++ ;
                readings.push_back(tester1);
                dewPoint = tester1.getDewPoint();
                cout << fixed << setprecision(2) << left << setw(17) << tester1.getDataOfDate() << left
                << setw(18) << tester1.getRelativeHumidity() << left
                << setw(16) << tester1.getAirTemp() << setw(11) << right << dewPoint
                << right << setw(4) << tester1.getTempUnits() << setw(10) << right
                << tester1.getName() << endl;
                if ( tester1.getTempUnits() == 'c' || tester1.getTempUnits() == 'C' ){
                    cWholeTemp += tester1.getAirTemp();
                    cTemp.push_back(tester1.getAirTemp());
                }
                if ( tester1.getTempUnits() == 'f' || tester1.getTempUnits() == 'F' ){
                    fWholeTemp += tester1.getAirTemp();
                    fTemp.push_back(tester1.getAirTemp());
                }
            }
            else
            {
                totalCounter++ ;
                counterError++ ;
                cout << fixed << setprecision(2) << left << setw(17) << tester1.getDataOfDate() << left
                << setw(18) << tester1.getRelativeHumidity() << left
                << setw(16) << tester1.getAirTemp() << setw(11) << right << "Check input!"
                << right << setw(3) << tester1.getTempUnits() << setw(10)
                << right << tester1.getName() << endl;
                nothing = "";
                tester1.isValidUnits(checker, nothing);
                if ( !checker )
                    cout << tester1.getTempUnits() << ": " << nothing << endl;
                nothing = "";
                tester1.isValidRH(checker, nothing);
                if ( !checker )
                    cout << tester1.getRelativeHumidity() << ": " << nothing << endl;
                nothing = "";
                tester1.isValidTemp(checker, nothing);
                if ( !checker )
                    cout << tester1.getAirTemp() << ": " << nothing << endl;
                //in case there will be no duplicate info inside the nothing string.
                nothing = "";
                tester1.isValidDate(checker, nothing);
                if ( !checker )
                    cout << nothing ;
            }
        }//END of while.
        cTempAverage = cWholeTemp / cTemp.size() ;
        fTempAverage = fWholeTemp / fTemp.size() ;
        //calculate deviation for celsius.
        for (int i = 0; i < cTemp.size() ; i ++)
        {
            cDeviation += pow((cTemp.at(i) - cTempAverage),2);
        }
        cDeviation = sqrt(cDeviation / (cTemp.size() - 1));
        //calculate deviation for fahrenheit.
        for (int i = 0; i < fTemp.size() ; i ++)
        {
            fDeviation += pow((fTemp.at(i) - fTempAverage),2);
        }
        fDeviation = sqrt(fDeviation / (fTemp.size() - 1));
    }
    
    //check wehther successfully loaded or not.
    int checker2 = false;
    if ( readings.size() - sizeOfWeather > 0 )
    {
        cout << "Total records in file: " << totalCounter << endl;
        cout << cTemp.size() <<" Celsius readings, with average air temp = "
        << cTempAverage << " and standard deviation = " << cDeviation << endl;
        cout << fTemp.size() <<" Fahrenheit readings, with average air temp = "
        << fTempAverage << " and standard deviation = " << fDeviation << endl;
        cout << counterError << " readings with invalid data." << endl;
        cout << endl;
        cout << "Exiting upload file function "<< readings.size()
        <<" elements in the vectors."<< endl;
        cout << "NOTE: The data file successfully loaded." << endl;
        headerPrint("lower_header");
        checker2 = true;
    }
    else
    {
        cout << "NOTE: The data file has failed to load." << endl;
        headerPrint("lower_header");
        checker2 = false;
    }
    return checker2;
}
/***************************************************************************************
 *                                                                                     *
 *                             cleaning function                                       *
 *                                                                                     *
 *                                                                                     *
 *                                                                                     *
 ***************************************************************************************/
void dataClear(vector<Weather> &readings)
{
    readings.clear();
}
/***************************************************************************************
 *                                                                                     *
 *                             FUNCTION summaryByScale                                 *
 *                                                                                     *
 *                                                                                     *
 *                                                                                     *
 ***************************************************************************************/
void summaryByScale(const vector<Weather> &readings)
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
    if ( readings.size() < 1)
        cout << "Please upload a file successfully first..." << endl;
    else
    {
        for (int i = 0; i < readings.size(); i ++)
        {
            if ( readings.at(i).getTempUnits() == 'c' || readings.at(i).getTempUnits() == 'C' ){
                cTempNum++ ;
                cRHNum++ ;
                cTemp += readings.at(i).getAirTemp();
                cRH += readings.at(i).getRelativeHumidity();
                cDew += readings.at(i).getDewPoint();
                
            }
            if ( readings.at(i).getTempUnits() == 'f' || readings.at(i).getTempUnits() == 'F' ){
                fTempNum++ ;
                fRHNum++ ;
                fTemp += readings.at(i).getAirTemp();
                fRH += readings.at(i).getRelativeHumidity();
                fDew += readings.at(i).getDewPoint();
            }
            
        }
        //wait for testing data and teacher's sample execution.
        cTemp /= cTempNum;
        fTemp /= fTempNum;
        fRH /= cRHNum;
        cRH /= fRHNum;
        cDew /= cTempNum;
        fDew /= fTempNum;
        fDew = fDew * C_TO_F + 32;
        cout << "Entered function summaryByScale, there are "
        << readings.size() <<" elements in the vectors." << endl;
        cout << "\n\n";
        cout << "\t\t" << "Average Readings by Temperature Scale" << endl;
        cout << "\t\t  Relative" << "\tAir" << "\t\tDew" << endl;
        cout << "\t\t  Humidity" << "\tTemp" << "\t\tPoint" << endl;
        cout << "\t  ---------------------------------------------------" << endl;
        cout << "\t\t   " <<  cRH << "\t        " << cTemp
        << "  " << "C" << "\t" << cDew << "  C" << endl;
        cout << "\t\t   " <<  fRH << "\t        " << fTemp << "  "
        << "F" << "\t" << fDew << "  F" << endl;
        cout << endl;
        cout << "Exiting function summaryByScale." << endl;
        
    }//END OF ELSE
}

/***************************************************************************************
 *                                                                                     *
 *                             function all details                                    *
 *                                                                                     *
 *                                                                                     *
 *                                                                                     *
 ***************************************************************************************/


void allDetails(const vector<Weather> &readings)
{
    double dewPoint = 0;
    int rowCounter = 0;
    double cWholeTemp = 0;
    double fWholeTemp = 0;
    double cTempAverage = 0;
    double fTempAverage = 0;
    double cDeviation = 0;
    double fDeviation = 0;
    vector<double> fTemp;
    vector<double> cTemp;
    if ( readings.size() < 1 )
        cout << "Please upload a file successfully first..." << endl;
    else
    {
        cout << "Entered function allDetails, there are "<<
        readings.size() <<" elements in the vectors." << endl;
        headerPrint("upper_header");
        for (int i = 0; i < readings.size(); i++)
        {
            
            rowCounter++ ;
            dewPoint = readings.at(i).getDewPoint();
            cout << readings.at(i);
            //For deviation calculation.
            if ( readings.at(i).getTempUnits() == 'c' || readings.at(i).getTempUnits() == 'C' ){
                cWholeTemp += readings.at(i).getAirTemp();
                cTemp.push_back(readings.at(i).getAirTemp());
            }
            if ( readings.at(i).getTempUnits() == 'f' || readings.at(i).getTempUnits() == 'F' ){
                fWholeTemp += readings.at(i).getAirTemp();
                fTemp.push_back(readings.at(i).getAirTemp());
            }
            
        }//END of for loop.
        cTempAverage = cWholeTemp / cTemp.size() ;
        fTempAverage = fWholeTemp / fTemp.size() ;
        //calculate deviation for celsius.
        for (int i = 0; i < cTemp.size() ; i ++)
        {
            cDeviation += pow((cTemp.at(i) - cTempAverage),2);
        }
        cDeviation = sqrt(cDeviation / (cTemp.size() - 1));
        //calculate deviation for fahrenheit.
        for (int i = 0; i < fTemp.size() ; i ++)
        {
            fDeviation += pow((fTemp.at(i) - fTempAverage),2);
        }
        fDeviation = sqrt(fDeviation / (fTemp.size() - 1));
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

/***************************************************************************************
 *                                                                                     *
 *                             function datedetails                                    *
 *                                                                                     *
 *                                                                                     *
 *                                                                                     *
 ***************************************************************************************/

void dateDetails(const vector<Weather> &readings)
{
    string dataOfDate = "";
    if ( readings.size() < 1)
        cout << "Please upload a file successfully first..." << endl;
    else
    {
        cout << "Enter the date to display, please enter "<<
        "the date you want to search for:(mm/dd/yyyy) ";
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
        for ( int i = 0; i < readings.size() ; i ++){
            int checker = 0;
            if ( (readings.at(i).getDay() - day) == 0 && (readings.at(i).getMonth() - month) == 0
                && (readings.at(i).getYear() - year) == 0 )
                checker++ ;
            if ( checker > 0 )
            {
                matchFileNum++ ;
                cout << fixed << setprecision(2) << readings.at(i).getMonth() << "/"
                << readings.at(i).getDay() << "/" << readings.at(i).getYear()
                << setw(12) << right << readings.at(i).getRelativeHumidity() << setw(17) << right
                << readings.at(i).getAirTemp() << right << setw(3)
                << readings.at(i).getTempUnits() << right << setw(20) << readings.at(i).getDewPoint()
                << right << setw(3) << readings.at(i).getTempUnits() << right
                << setw(4) << readings.at(i).getName() << endl;
                if ( readings.at(i).getTempUnits() == 'c' || readings.at(i).getTempUnits() == 'C' ){
                    cWholeTemp += readings.at(i).getAirTemp();
                    cTemp.push_back(readings.at(i).getAirTemp());
                }
                if ( readings.at(i).getTempUnits() == 'f' || readings.at(i).getTempUnits() == 'F' ){
                    fWholeTemp += readings.at(i).getAirTemp();
                    fTemp.push_back(readings.at(i).getAirTemp());
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
            if ( cTemp.size() > 1 )
            {
                for (int i = 0; i < cTemp.size() ; i ++)
                {
                    cDeviation += pow((cTemp.at(i) - cTempAverage),2);
                }
                cDeviation = sqrt(cDeviation / (cTemp.size() - 1));
            }
            //calculate deviation for fahrenheit.
            if ( fTemp.size() > 1 )
            {
                for (int i = 0; i < fTemp.size() ; i ++)
                {
                    fDeviation += pow((fTemp.at(i) - fTempAverage),2);
                }
                fDeviation = sqrt(fDeviation / (fTemp.size() - 1));
                
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

/***************************************************************************************
 *                                                                                     *
 *                             print the header                                        *
 *                                                                                     *
 *                                                                                     *
 *                                                                                     *
 ***************************************************************************************/

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
