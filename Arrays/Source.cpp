//************************************  PROGRAM IDENTIFICATION  **************************************
//*																									 *
//*   PROGRAM FILE NAME:  Project1.cpp          ASSIGNMENT #:  1            Grade: _________		 *
//*																									 *
//*   PROGRAM AUTHOR:																				 *
//*                   ___________________________________________________							 *
//*                                     Biraj Singh GC												 *
//*																									 *
//*   COURSE #:  CSC 36000 11                              DUE DATE: February 08, 2019				 *
//*																									 *
//****************************************************************************************************

//*************************************** PROGRAM DESCRIPTION ****************************************
//*                                                                                                  *
//*  PROCESS:         This program is designed to read in passenger information and assign           *
//*                   passengers to their seats according to their requests and the seating rules.   *
//*  USER DEFINED                                                                                    *
//*    MODULES     :   Header.........................Prints the output Header preamble              *
//*                    Footer.........................Prints the output footer Preamble              *
//*                    FileReader.....................Reads the Data File and stores the data into   * 
//*                                                   object                                         *
//*                    FlightClass....................Class that contains information about all the  *
//*                                                   Flights and stores them as objects             *
//*                                                                                                  *
//****************************************************************************************************


#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

//********************************************** FlightClass Class Declaration ***************************************************//
class FlightClass
{
private:
	int FlightNumber, SeatArray[10][3], NoofWaitllist = 0;					//declare integer Variale for Flight Number, Arrar of Seat Plan, Number of waitlist
	string FlightFrom, FlightTo;											//declare string variable for destination and departure of the flight.
	int WaitlistArray[40] = { 0 };											//declare and initialize array for the waitlist. 
public:
	FlightClass(int, string, string);										//Constructor Function
	int getFlightNumber() { return FlightNumber; }							//Accessor Function for Flight Number
	string getFlightFrom() { return FlightFrom; }                           //Accessor Function for FlightFrom                         
	string getFlightTo() { return FlightTo; }                               //Accessor Function for FlightTo
	int getSeat(int FRow, int FCol) { return SeatArray[FRow][FCol]; }		//Accessor Function for SeatArray
	void WaitlistAppend(int);												//Manipulator Function to add passenger to waiting list
	void SeatFinder_F(char, int, int);										//Manipulator Function to find seat in first class
	void SeatFinder_C(char, int, int);										//Manipulator Function to find seat in coach.
	void WaitlistPrinter(ofstream&);										//Function to print Waitlist.
};
//********************************************** End of FlightClass Class Declaration ********************************************//

//--------------------------------------------------------------------------------------------------------------------------------//

//********************************************** FlightClass Constructor Function ************************************************//

FlightClass::FlightClass(int NewFlight, string NewFrom, string NewTo){
	//Class:    FlightClass
	//Function:	Constructor Function
	//Receives: Int for Flight Number, String For destination, String For Departure
	//Tasks:	Initializes the Flight number, Departure, Destination and Seat Array for the FlightClass Object. 
	//Returns:  Initalized Object of FlightClass.
	FlightNumber = NewFlight;				//Initialize The FlightNumber 
	FlightFrom = NewFrom;					//Initialize The Flight departure 			
	FlightTo = NewTo;						//Initialize The Flight destiation. 

	//loop through the seats to initialize all seats to -999
	for (int i = 0; i < 10; i++){			
		for (int j = 0; j < 3; j++){
			SeatArray[i][j] = -999;
		}
	}
}
//********************************************** End of FlightClass Constructor Function *******************************************//

//----------------------------------------------------------------------------------------------------------------------------------//

//********************************************** Flightclass: WaitlistAppend Function **********************************************//

void FlightClass::WaitlistAppend(int BoardingNumber) {
	//Class:    FlightClass
	//Function:	WaitlisstAppend
	//Receives: Int for Bording Number of passenger.
	//Tasks:	Stores the passenger into waiting list and keeps track of the size of waitinglist . 
	//Returns:  Updated WaitList array and NoofWaitlist.
	WaitlistArray[NoofWaitllist] = BoardingNumber; //Append the bording number to waitlist array
	NoofWaitllist++;							   //Increase the waitlist count by 1.
}

//********************************************** End of WaitlistAppend Function ***************************************************//

//---------------------------------------------------------------------------------------------------------------------------------//

//********************************************** Flightclass: SeatFinder_F Function************************************************//
void FlightClass::SeatFinder_F(char CharColF,int RowF, int BoardingNumber){
	//Class:    FlightClass
	//Function:	SeatFinder_F Function
	//Receives: Char For column, Int of rownumber , Int of boarding Number
	//Tasks:	Locates a vacant seat for first class as per the rules of seating and seats the passenger. 
	//Returns:	Updated SeatArray, Waitlist Array.
	bool condition = true;							//initialize temporary condition as true											
	int ColinInt = 0;								//initialize ColinInt as zero.
	char CharCol[3] = {'L','M','R'};				//initialize the array with three possible columns.
	RowF--;
	//loop through CharCol to set ColinInt according to CharColF
	for (int i = 0; i < 3; i++) {
		if (CharColF == CharCol[i]) {
			ColinInt = i;
			break;
		}
	}//Check if the seat is taken or empty.
	if (SeatArray[RowF][ColinInt] != -999) {
		//Check if the row is taken or empty
		if (condition) {                           // if the seat is taken loop through the row to find empty seat.
			for (int i = 0; i < 3; i++){
				if (SeatArray[RowF][i] == -999){
					ColinInt = i;
					condition = false;		
					break;
				}
			}
		}//Check if the column is taken or empty
		if (condition){
			for (int i = 0; i < 3; i++){		  // if the row is taken loop through the column to find empty seat.
				if (SeatArray[i][ColinInt] == -999){
					RowF = i;
					condition = false;
					break;
				}
			}
		}//Check if the section is taken or empty
		if (condition){							  // if the column is taken loop through the section to find empty seat.
			for (int i = 0; i < 3; i++){
				for (int j = 0; j < 3; j++){
					if (SeatArray[i][j] == -999){
						RowF = i;
						ColinInt = j;
						condition = false;
						break;
					}
				}
			}
		}
	}
	else 
		condition = false;

	if (condition == true)						//If no seats are empty, add to wait list.
		WaitlistAppend(BoardingNumber);
	else
			SeatArray[RowF][ColinInt] = BoardingNumber;	
}
//********************************************** End of SeatFinder_F Function *****************************************************//

//---------------------------------------------------------------------------------------------------------------------------------//

//********************************************** Flightclass: SeatFinder_C Function************************************************//

void FlightClass::SeatFinder_C(char CharColF, int RowF, int BoardingNumber)
{
	//Class:    FlightClass
	//Function:	SeatFinder_C Function
	//Receives: Char For column, Int of rownumber , Int of boarding Number
	//Tasks:	Locates a vacant seat for Coach as per the rules of seating and seats the passenger. 
	//Returns:	Updated SeatArray, Waitlist Array.
	bool condition = true;                 //initialize temporary condition as true	
	int ColinInt = 0;                      //initialize ColinInt as zero.
	char CharCol[3] = { 'L','M','R' };     //initialize the array with three possible columns.
	RowF--;
	//loop through CharCol to set ColinInt according to CharColF
	for (int i = 0; i < 3; i++){
		if (CharColF == CharCol[i]){
			ColinInt = i;
			break;
		}
	}
	//Check if the seat is taken or empty.
	if (SeatArray[RowF][ColinInt] != -999){ 
		//Check if the row is taken or empty.
		if (condition == true){                        //if the seat is taken loop through the row to find empty seat.
			for (int i = 0; i < 3; i++){
				if (SeatArray[RowF][i] == -999){
					ColinInt = i;
					condition = false;
					break;
				}
			}
		}//Check if the column is taken or empty.
		if (condition == true){                        //if the row is taken loop through the column to find empty seat.
			for (int i = 3; i < 10; i++){
				if (SeatArray[i][ColinInt] == -999){
					RowF = i;
					condition = false;
					break;
				}
			}
		}//Check if the section is taken or empty.
		if (condition == true){                        //if the column is taken loop through the section to find empty seat.
			for (int i = 3; i < 10; i++){
				for (int j = 0; j < 3; j++){
					if (SeatArray[i][j] == -999){
						RowF = i;
						ColinInt = j;
						condition = false;
						break;
					}
				}
			}
		}
	}
	else
		condition = false;

	if (condition)                                     //If no seats are empty, add to wait list.
		WaitlistAppend(BoardingNumber);
	else
		SeatArray[RowF][ColinInt] = BoardingNumber;
}
//********************************************** End of SeatFinder_C Function *********************************************//

//-------------------------------------------------------------------------------------------------------------------------//

//********************************************** Flightclass:WaitlistPrinter Function *************************************//

void FlightClass::WaitlistPrinter(ofstream& outfile)
{
	//Class:    FlightClass
	//Function:	WaitlistPrinter
	//Receives: Outfile
	//Tasks:	Prints out the waitlist in orderly manner. 
	//Returns:	Updated outfile.
	if(WaitlistArray[0] == 0){                                   //print if no one is in waitlist.
		outfile << "There is no waiting fot this flight.";
	}
	else{                                                        //print the waitlist 
		for (int i = 0; i < 40; i++){
			if (WaitlistArray[i] != 0){
				if (i % 10 == 0)                                 //print 10 passengers per row.
					outfile << endl << "      ";
				outfile << WaitlistArray[i] << "   ";
			}
			else
				break;
		}
	}
	outfile << endl;
}
//********************************************** End of WaitlistPrinter ***************************************************//

//-------------------------------------------------------------------------------------------------------------------------//

//********************************************** FileReader Function ******************************************************//

/* Function prototypes*/

void Header(ofstream&);																	//print the header for the project.
void Footer(ofstream&);																	//print the footer for the project.
void FileReader(ifstream& ,FlightClass[]);												//read the file from the output into an array of objects.


/* End of Function prototypes*/


//************************************************* Main Fuction *********************************************************//
int main()
{
	ifstream infile("data1.txt", ios::in);												//import the file 
	ofstream outfile("result.txt", ios::out);											//export the file

	if (infile.fail()){																	//Error catcher 
		cout << " The file was not found." << endl;
		exit(1);																		//Exit the program
	}
	//Declare objects for all the flights.
	FlightClass flight1(1010, "Jackson, Mississippi", "Memphis, Tennessee");
	FlightClass flight2(1015, "Memphis, Tennessee", "Jackson, Mississippi");
	FlightClass flight3(1020, "Jackson, Mississippi", "Little Rock, Arkansas");
	FlightClass flight4(1025, "Little Rock, Arkansas", "Jackson, Mississippi");
	FlightClass flight5(1030, "Jackson, Mississippi", "Shreveport, Louisiana");
	FlightClass flight6(1035, "Shreveport, Louisiana", "Jackson, Mississippi");
	FlightClass flight7(1040, "Jackson, Mississippi", "Huntsville, Alabama");
	FlightClass flight8(1045, "Huntsville, Alabama ", "Jackson, Mississippi");

	//add the objects into the array.
	FlightClass flights[8] = { flight1, flight2, flight3, flight4, flight5, flight6, flight7, flight8 };
	FileReader(infile, flights);                                                        //read the input file into the array of objects.

	Header(outfile);																	//print the header for the project.
	//print the Seat plan by looping through all the flights.
	for (int i = 0; i < 8; i++){
		outfile << "                                         SOUTHERN COMFORT AIRLINES" << endl << endl;
		outfile << "Flight " << flights[i].getFlightNumber();
		outfile << "                                                  FROM: " << flights[i].getFlightFrom() << endl;
		outfile << "                                                             TO: " << flights[i].getFlightTo();
		outfile << endl << endl;
			
		for (int k = 0; k < 10; k++){
			outfile << "            ";
			for (int j = 0; j < 3; j++) {
				outfile << flights[i].getSeat(k, j) << "                ";
			}
			outfile << endl << endl;
		}
		outfile << "WAITING LIST" << endl;
		outfile << "            ";
		flights[i].WaitlistPrinter(outfile);
		outfile << endl;
		outfile << "END OF SEATING CHART" << endl;
		outfile << endl << endl << endl << endl << endl << endl << endl << endl;
	}
	Footer(outfile);																		//print	 the footer for the project.
	return 0;
}
//********************************************** End of Main Fuction *******************************************************//

//---------------------------------------------------------------------------------------------------------------------------//

//********************************************** Header Function ***********************************************************//
void Header(ofstream& Outfile){
	//Function: Header
	//Receives – the output file
	//Task - Prints the output preamble
	//Returns - Nothing
	Outfile << setw(30) << "Biraj Singh GC";
	Outfile << setw(17) << "CSC 36400";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(30) << "Spring 2020";
	Outfile << setw(20) << "Assignment #1" << endl;
	Outfile << setw(35) << "---------------------------------- - ";
	Outfile << setw(35) << "---------------------------------- -  " << endl << endl;
	return;
}
//******************************************* End of Header Function ********************************************************//

//---------------------------------------------------------------------------------------------------------------------------//

//********************************************** Footer Function ************************************************************//
void Footer(ofstream& Outfile){
	//Function:	 Footer
	//Receives – the output file
	//Task -	 Prints the output salutation
	//Returns -	 Nothing
	Outfile << endl;
	Outfile << setw(35) << "-------------------------------- - " << endl;
	Outfile << setw(35) << " | END OF PROGRAM OUTPUT | " << endl;
	Outfile << setw(35) << "-------------------------------- - " << endl;
	return;
}
//********************************************** End of footer Function ***************************************************//

//-------------------------------------------------------------------------------------------------------------------------//

//********************************************** FileReader Function ******************************************************//
void FileReader(ifstream& infile, FlightClass Flight[]){
	//Function:	FileReader
	//Receives: Input file, array of objects of FLightClass
	//Tasks:	Reads the input file and stores in the array of objects 
	//Returns:  Array of objeccts of FightClass.
	int BoardingNumber, FlightNumber, RowNumber;               //declare temp variable for Boarding number, Flight number and Row number,
	char FlightSection, FlightCol;							   //declare temp variable for Flight Section and FLight column.
	//loop through the file to read the file.
	while (infile >> BoardingNumber >> FlightNumber >> FlightSection >> RowNumber >> FlightCol){
		if (BoardingNumber < 0){                               //Stop reading if boarding number is less than 0
			break;
		}
		for (int i = 0; i < 8; i++){
			if (FlightNumber == Flight[i].getFlightNumber()){ // Loop through all flights to match the flight number.
				if(FlightSection == 'F')					  // Check the section requested.
					Flight[i].SeatFinder_F(FlightCol, RowNumber, BoardingNumber); // add the passenger in first class
				else
					Flight[i].SeatFinder_C(FlightCol, RowNumber, BoardingNumber); //add the passenger to the coach
				break;
			}
		}
	}
}
/********************************************** End of FileReader Function ************-********************	************************/